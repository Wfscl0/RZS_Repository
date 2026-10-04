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
static uint8_t current_channel = 0u;
/* ISR owns head, main owns tail; 8-bit indices are atomic on STM8. */
static volatile uint8_t rx_head, rx_tail, rx_lost;
static volatile uint8_t rx_ring[128];
static uint8_t tx_length;
volatile uint16_t res_bridge_overflows;
volatile uint16_t res_bridge_tx_frames;
volatile uint16_t res_bridge_bad_frames;

void RES_Bridge_OnUartByte(uint8e_t byte)
{
    uint8_t next = (uint8_t)((rx_head + 1u) & 127u);
    if (next == rx_tail) {
        rx_lost = 1u;
        ++res_bridge_overflows;
        return;
    }
    rx_ring[rx_head] = byte;
    rx_head = next;
}

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

uint8e_t RES_Bridge_OnReceivedFrame(const uint8e_t *buffer, uint8e_t length)
{
    if (!res_frame_is_valid(buffer, length)) {
        ++res_bridge_bad_frames;
        pending_event = RES_EVENT_SCAN;
        return 0u;
    }
    /* Polling context: be ready for the reply BEFORE notifying the STM32.
     * UART output blocks for tens of ms while the peer is already listening. */
    pending_event = RES_EVENT_NONE;
    tune_and_receive(next_channel(buffer[9],
                                  get_u32_le(buffer + 14u),
                                  get_u32_le(buffer + 10u)));
    return 1u;
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
    tune_and_receive((uint8_t)((current_channel + 1u) %
                               RES_BRIDGE_CHANNEL_COUNT));
}

static void drop_first_byte(void)
{
    uint8_t i;
    --tx_length;
    for (i = 0u; i < tx_length; ++i) {
        tx_buffer[i] = tx_buffer[i + 1u];
    }
}

static void task_transmit(void)
{
    uint8_t budget = 127u;
    while (budget-- != 0u) {
        uint8_t byte;
        uint8_t tail;
        uint8_t head;
        uint16_t expected;
        if (rx_lost) {
            /* A gap invalidates queued partial data. Resync on a new CRC frame. */
            rx_lost = 0u;
            rx_tail = rx_head;
            tx_length = 0u;
            return;
        }
        /* Separate volatile reads: ISR may advance head between statements. */
        tail = rx_tail;
        head = rx_head;
        if (tail == head) {
            return;
        }
        byte = rx_ring[tail];
        rx_tail = (uint8_t)((tail + 1u) & 127u);
        tx_buffer[tx_length++] = byte;
        while (tx_length != 0u) {
            if ((tx_buffer[0] != RES_MAGIC_0) ||
                ((tx_length >= 2u) && (tx_buffer[1] != RES_MAGIC_1)) ||
                ((tx_length >= 3u) &&
                 (tx_buffer[2] != RES_BRIDGE_PROTOCOL_VERSION))) {
                drop_first_byte();
                continue;
            }
            if (tx_length < RES_BRIDGE_HEADER_SIZE) {
                break;
            }
            if ((tx_buffer[18] > RES_BRIDGE_MAX_PAYLOAD) ||
                (tx_buffer[9] >= RES_BRIDGE_CHANNEL_COUNT)) {
                drop_first_byte();
                continue;
            }
            expected = RES_BRIDGE_HEADER_SIZE + tx_buffer[18] +
                       RES_BRIDGE_TRAILER_SIZE;
            if (tx_length < expected) {
                break;
            }
            if (!res_frame_is_valid(tx_buffer, expected)) {
                ++res_bridge_bad_frames;
                drop_first_byte();
                continue;
            }
            /* Do not wait for 500 ms idle or merge adjacent RES frames. */
            current_channel = tx_buffer[9];
            Ebyte_E220x_SetRfFrequency(channel_frequency[current_channel]);
            Ebyte_RF.Send(tx_buffer, (uint8_t)expected, 0u);
            ++res_bridge_tx_frames;
            tune_and_receive(next_channel(tx_buffer[9],
                                          get_u32_le(tx_buffer + 14u),
                                          get_u32_le(tx_buffer + 10u)));
            tx_length = 0u;
            return; /* Poll RF events between complete outgoing frames. */
        }
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
