/*
 * Replacement main.c for Ebyte's official E15-EVB02 / Uart_PingPong IAR project.
 * Authentication remains on the two STM32 safety endpoints.  The bridge does
 * execute physical frequency changes; merely carrying a channel byte would not
 * satisfy the automatic-hopping requirement.
 */
#include "ebyte_core.h"
#include "ebyte_kfifo.h"
#include "ebyte_e220x.h"
#include "res_bridge_config.h"
#include "res_bridge_control.h"

#define RES_MAGIC_0              0x52u
#define RES_MAGIC_1              0x53u
#define RES_EVENT_NONE           0u
#define RES_EVENT_HOP            1u
#define RES_EVENT_SCAN           2u

Ebyte_FIFO_t hfifo;
uint8_t Uart_isRecvReady = 0u;
uint8_t FIFO_isTimeCheckReady = 0u;

static uint8_t tx_buffer[RES_BRIDGE_MAX_FRAME];
static volatile uint8_t pending_event = RES_EVENT_NONE;
static volatile uint8_t pending_channel = 0u;
static uint8_t current_channel = 0u;

static const uint32e_t channel_frequency[RES_BRIDGE_CHANNEL_COUNT] = {
    RES_BRIDGE_FREQUENCY_0_HZ,
    RES_BRIDGE_FREQUENCY_1_HZ,
    RES_BRIDGE_FREQUENCY_2_HZ
};

static uint32e_t get_u32_le(const uint8e_t *source)
{
    return (uint32e_t)source[0] |
           ((uint32e_t)source[1] << 8u) |
           ((uint32e_t)source[2] << 16u) |
           ((uint32e_t)source[3] << 24u);
}

static uint16e_t crc16_ccitt(const uint8e_t *data, uint16e_t length)
{
    uint16e_t crc = 0xFFFFu;
    uint16e_t index;
    uint8e_t bit;
    for (index = 0u; index < length; ++index) {
        crc ^= (uint16e_t)data[index] << 8u;
        for (bit = 0u; bit < 8u; ++bit) {
            crc = (crc & 0x8000u) ?
                (uint16e_t)((crc << 1u) ^ 0x1021u) :
                (uint16e_t)(crc << 1u);
        }
    }
    return crc;
}

static uint8_t next_channel(uint8_t channel,
                            uint32e_t session,
                            uint32e_t sequence)
{
    uint32e_t mixed;
    uint8_t step;
    if (channel >= RES_BRIDGE_CHANNEL_COUNT) {
        channel = 0u;
    }
    mixed = session ^ (sequence * 0x9E3779B9UL);
    mixed ^= mixed >> 16u;
    mixed *= 0x7FEB352DUL;
    mixed ^= mixed >> 15u;
    step = (uint8_t)(1u + (mixed % (RES_BRIDGE_CHANNEL_COUNT - 1u)));
    return (uint8_t)((channel + step) % RES_BRIDGE_CHANNEL_COUNT);
}

static void tune_and_receive(uint8_t channel)
{
    current_channel = (uint8_t)(channel % RES_BRIDGE_CHANNEL_COUNT);
    Ebyte_E220x_SetRfFrequency(channel_frequency[current_channel]);
    Ebyte_RF.EnterReceiveMode(RES_BRIDGE_RX_DWELL_TICKS);
}

static uint8_t res_frame_is_valid(const uint8_t *buffer, uint16_t length)
{
    uint16_t expected;
    uint16_t message_length;
    uint16_t received_crc;
    if ((length < (RES_BRIDGE_HEADER_SIZE + RES_BRIDGE_TRAILER_SIZE)) ||
        (length > RES_BRIDGE_MAX_FRAME) ||
        (buffer[0] != RES_MAGIC_0) ||
        (buffer[1] != RES_MAGIC_1) ||
        (buffer[2] != RES_BRIDGE_PROTOCOL_VERSION) ||
        (buffer[9] >= RES_BRIDGE_CHANNEL_COUNT) ||
        (buffer[18] > RES_BRIDGE_MAX_PAYLOAD)) {
        return 0u;
    }
    message_length = (uint16_t)(RES_BRIDGE_HEADER_SIZE + buffer[18]);
    expected = (uint16_t)(message_length + RES_BRIDGE_TRAILER_SIZE);
    if (expected != length) {
        return 0u;
    }
    received_crc = (uint16e_t)buffer[message_length] |
                   ((uint16e_t)buffer[message_length + 1u] << 8u);
    return received_crc == crc16_ccitt(buffer, message_length);
}

void RES_Bridge_OnReceivedFrame(const uint8e_t *buffer, uint8e_t length)
{
    if (res_frame_is_valid(buffer, length)) {
        pending_channel = next_channel(buffer[9],
                                       get_u32_le(buffer + 14u),
                                       get_u32_le(buffer + 10u));
        pending_event = RES_EVENT_HOP;
    }
}

void RES_Bridge_OnReceiveTimeout(void)
{
    pending_event = RES_EVENT_SCAN;
}

static void apply_pending_radio_event(void)
{
    uint8_t event = pending_event;
    if (event == RES_EVENT_NONE) {
        return;
    }
    pending_event = RES_EVENT_NONE;
    if (event == RES_EVENT_HOP) {
        tune_and_receive(pending_channel);
    } else {
        tune_and_receive((uint8_t)((current_channel + 1u) %
                                   RES_BRIDGE_CHANNEL_COUNT));
    }
}

static void task_transmit(void)
{
    uint16_t length = 0u;
    Ebyte_FIFO_GetDataLength(&hfifo, &length);
    if (((length != 0u) && (Uart_isRecvReady != 0u)) ||
        ((length != 0u) && (FIFO_isTimeCheckReady != 0u))) {
        if (length > RES_BRIDGE_MAX_FRAME) {
            /* Drain malformed/overflowed UART data; never send partial safety frames. */
            while (length != 0u) {
                uint16_t chunk = (length > RES_BRIDGE_MAX_FRAME) ?
                    RES_BRIDGE_MAX_FRAME : length;
                Ebyte_FIFO_Read(&hfifo, tx_buffer, chunk);
                length = (uint16_t)(length - chunk);
            }
        } else {
            Ebyte_FIFO_Read(&hfifo, tx_buffer, length);
            if (res_frame_is_valid(tx_buffer, length)) {
                uint8_t next;
                /* Header channel is authoritative for a locally-originated TX. */
                Ebyte_E220x_SetRfFrequency(channel_frequency[tx_buffer[9]]);
                current_channel = tx_buffer[9];
                Ebyte_RF.Send(tx_buffer, (uint8_t)length, 0u);
                next = next_channel(tx_buffer[9],
                                    get_u32_le(tx_buffer + 14u),
                                    get_u32_le(tx_buffer + 10u));
                tune_and_receive(next);
            }
        }
        if (Uart_isRecvReady != 0u) {
            --Uart_isRecvReady;
        }
        FIFO_isTimeCheckReady = 0u;
    }
}

int main(void)
{
    Ebyte_BSP_Init();
    Ebyte_FIFO_Init(&hfifo, EBYTE_FIFO_SIZE);
    Ebyte_RF.Init();
    tune_and_receive(0u);
    Ebyte_BSP_GlobalIntEnable();

    while (1) {
        task_transmit();
        Ebyte_RF.StartPollTask();
        apply_pending_radio_event();
    }
}
