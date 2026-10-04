#ifndef RES_SI4463_TRANSPORT_H
#define RES_SI4463_TRANSPORT_H
/* One translation unit per endpoint, matching the existing UART port API.
 * Main-loop-only SPI; no unbounded waits or RF transmit waits. nIRQ is
 * polled each task iteration so there is no SPI operation inside an ISR. */
#include "stm32g0xx_hal.h"
#include "res_radio_config.h"
#include "res_protocol.h"
#include "radio_config_Si4463_vendor.h"
#include <string.h>

typedef struct {
    uint32_t magic, role, revision, tick_ms;
    uint32_t rx_bytes, tx_frames, tx_failures, uart_errors;
    uint32_t last_uart_error, rx_overflows, rearm_failures, last_rx_ms;
    uint32_t last_tx_ms, processed_bytes, resyncs, stale_bytes;
    uint32_t last_valid_rx_ms, state, faults, feedback_valid;
    uint32_t battery_mv, battery_valid, input_stop, outputs;
    uint32_t decoded_frames, unmatched_acks, accepted_acks;
    uint8_t rx_trace[128];
} res_uart_diag_t;
/* Preserve debugger addresses by symbol, not by hard-coded numeric offset. */
volatile res_uart_diag_t res_uart_diag;
typedef struct {
    uint32_t ready, error, cts_timeouts, spi_errors, tx_done, rx_packets;
    uint32_t crc_errors, chip_errors, scans, channel, tx_busy;
    uint32_t part, chip_revision, configured_xo_hz;
    uint32_t init_offset, last_command, command_phase, last_cts;
    uint32_t ph_pending, chip_pending, irq_samples;
    uint32_t init_props;
    uint32_t property_checks, property_failure, irq_fallbacks;
    /* 保留失败现场：前四个期望/实读字节，按小端打包，关断后仍可读。 */
    uint32_t property_expected, property_actual;
    /* 芯片错误后、SDN 关断前保存命令原因；valid=0 表示查询本身失败。 */
    uint32_t chip_detail_valid, cmd_error_status, cmd_error_id;
} res_si4463_diag_t;
volatile res_si4463_diag_t res_si4463_diag;
static SPI_HandleTypeDef res_spi;
static uint8_t res_rf_rx[RES_RADIO_PACKET_SIZE];
static uint8_t res_rf_pos, res_rf_length, res_rf_next_channel;
static uint32_t res_rf_tx_started, res_rf_tuned, res_rf_received;
static uint8_t res_rx_byte; /* compatibility for unused UART callbacks */
static uint32_t res_rf_last_irq_check;

/* Bounded guard: at least 2 us worth of NOPs at SystemCoreClock, plus loop
 * overhead. Not a calibrated timer; no interrupt masking or millisecond wait. */
static void res_rf_cs_guard(void)
{
    uint32_t cycles = SystemCoreClock / 500000u + 1u;
    while (cycles-- != 0u) { __NOP(); }
}

static void res_rf_select(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
    res_rf_cs_guard();
}

static void res_rf_deselect(void)
{
    res_rf_cs_guard();
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
    res_rf_cs_guard();
}

static void res_rf_fault(uint32_t error)
{
    res_si4463_diag.error = error;
    res_si4463_diag.ready = 0u;
    res_si4463_diag.tx_busy = 0u;
    res_rf_length = res_rf_pos = 0u;
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
}

static bool res_rf_spi(uint8_t *tx, uint8_t *rx, uint16_t n)
{
    /* 49 bytes at 250 kHz need 1.568 ms, before HAL/tick quantization. */
    if (HAL_SPI_TransmitReceive(&res_spi, tx, rx, n, 3u) != HAL_OK) {
        ++res_si4463_diag.spi_errors;
        res_rf_fault(1u);
        return false;
    }
    return true;
}

static bool res_rf_response(uint8_t *response, uint8_t n, uint32_t timeout)
{
    const uint32_t start = HAL_GetTick();
    unsigned polls = 0u;
    do {
        uint8_t tx[18] = {0x44u, 0xffu}, rx[18] = {0};
        res_rf_select();
        if (!res_rf_spi(tx, rx, 2u)) return false;
        res_si4463_diag.last_cts = rx[1];
        if (rx[1] == 0xffu) {
            if (n != 0u && !res_rf_spi(tx + 2u, rx + 2u, n)) return false;
            res_rf_deselect();
            if (n != 0u) memcpy(response, rx + 2u, n);
            return true;
        }
        res_rf_deselect();
    } while ((uint32_t)(HAL_GetTick() - start) < timeout && ++polls < 100000u);
    ++res_si4463_diag.cts_timeouts;
    res_rf_fault(2u);
    return false;
}

static bool res_rf_command(const uint8_t *cmd, uint8_t n,
                           uint8_t *reply, uint8_t reply_n, uint32_t timeout)
{
    uint8_t tx[16], rx[16];
    if (n == 0u || n > sizeof(tx) || reply_n > 16u) return false;
    res_si4463_diag.last_command = cmd[0];
    res_si4463_diag.command_phase = 1u;
    if (!res_rf_response(NULL, 0u, timeout)) return false;
    memcpy(tx, cmd, n);
    res_rf_select();
    if (!res_rf_spi(tx, rx, n)) return false;
    res_rf_deselect();
    res_si4463_diag.command_phase = 2u;
    return res_rf_response(reply, reply_n, timeout);
}

/* Read-only verification; never retry START_TX/FIFO writes after uncertainty. */
static bool res_rf_verify_properties(const uint8_t *setting)
{
    uint8_t query[] = {0x12, setting[1], setting[2], setting[3]};
    uint8_t values[12];
    for (unsigned pass = 0; pass < 2u; ++pass) {
        if (!res_rf_command(query, sizeof(query), values, setting[2], 5u)) return false;
        ++res_si4463_diag.property_checks;
        if (memcmp(values, setting + 4u, setting[2]) != 0) {
            res_si4463_diag.property_expected = 0u;
            res_si4463_diag.property_actual = 0u;
            for (unsigned i = 0; i < setting[2] && i < 4u; ++i) {
                res_si4463_diag.property_expected |= (uint32_t)setting[4u+i] << (8u*i);
                res_si4463_diag.property_actual |= (uint32_t)values[i] << (8u*i);
            }
            res_si4463_diag.property_failure = ((uint32_t)setting[1] << 8) | setting[3];
            res_rf_fault(8u); return false;
        }
    }
    return true;
}

static bool res_rf_interrupts(uint8_t status[8])
{
    const uint8_t cmd[] = {0x20, 0, 0, 0};
    bool ok = res_rf_command(cmd, sizeof(cmd), status, 8u, 5u);
    if (ok) {
        res_si4463_diag.ph_pending = status[2];
        res_si4463_diag.chip_pending = status[6];
        ++res_si4463_diag.irq_samples;
    }
    return ok;
}

static void res_rf_chip_fault(void)
{
    const uint8_t query[] = {0x23, 0xff}; /* GET_CHIP_STATUS, preserve pending bits. */
    uint8_t detail[4];
    res_si4463_diag.chip_detail_valid = 0u;
    if (res_rf_command(query, sizeof(query), detail, sizeof(detail), 5u)) {
        res_si4463_diag.cmd_error_status = detail[2];
        res_si4463_diag.cmd_error_id = detail[3];
        res_si4463_diag.chip_detail_valid = 1u;
    }
    res_rf_fault(5u); /* 仍然关断，不忽略错误或自动重发 TX。 */
}

static bool res_rf_receive(uint8_t channel)
{
    const uint8_t ready[] = {0x34, 3};
    const uint8_t reset[] = {0x15, 2};
    uint8_t rx[] = {0x32, channel, 0, 0, RES_RADIO_PACKET_SIZE, 0, 3, 3};
    if (!res_rf_command(ready, sizeof(ready), NULL, 0, 5u) ||
        !res_rf_command(reset, sizeof(reset), NULL, 0, 5u) ||
        !res_rf_command(rx, sizeof(rx), NULL, 0, 5u)) return false;
    res_si4463_diag.channel = channel;
    res_rf_tuned = HAL_GetTick();
    return true;
}

static void res_uart_start(uint32_t role)
{
    GPIO_InitTypeDef pin = {0};
    static const uint8_t config[] = RADIO_CONFIGURATION_DATA_ARRAY;
    const uint8_t part_cmd[] = {0x01};
    /* Final overrides: fixed packet size; all PH flags; conservative PA code.
     * Retain the vendor's calibrated modem, sync, CRC, RF switch GPIO2/3. */
    const uint8_t packet[] = {0x11, 0x12, 2, 0x0d, 0, RES_RADIO_PACKET_SIZE};
    const uint8_t interrupts[] = {0x11, 1, 4, 0, 5, 0x38, 0, 0x28};
    const uint8_t power[] = {0x11, 0x22, 1, 1, RES_RADIO_PA_CODE};
    const uint8_t modem[] = {RF_MODEM_MOD_TYPE_12_1};
    const uint8_t frequency[] = {RF_FREQ_CONTROL_INTE_8_1};
    uint8_t part[8], status[8];
    size_t off = 0u;
    res_uart_diag.magic = 0x52455344u;
    res_uart_diag.role = role;
    res_uart_diag.revision = 0x20260924u;
    res_si4463_diag.configured_xo_hz = RADIO_CONFIGURATION_DATA_RADIO_XO_FREQ;
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_SPI1_CLK_ENABLE();
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
    pin.Pin = GPIO_PIN_4; pin.Mode = GPIO_MODE_OUTPUT_PP;
    pin.Pull = GPIO_PULLUP; pin.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &pin);
    pin.Pin = GPIO_PIN_3; pin.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOB, &pin);
    pin.Pin = GPIO_PIN_2; pin.Mode = GPIO_MODE_INPUT; pin.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOB, &pin);
    pin.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    pin.Mode = GPIO_MODE_AF_PP; pin.Pull = GPIO_NOPULL;
    pin.Speed = GPIO_SPEED_FREQ_LOW; pin.Alternate = GPIO_AF0_SPI1;
    HAL_GPIO_Init(GPIOA, &pin);
    res_spi.Instance = SPI1;
    res_spi.Init.Mode = SPI_MODE_MASTER;
    res_spi.Init.Direction = SPI_DIRECTION_2LINES;
    res_spi.Init.DataSize = SPI_DATASIZE_8BIT;
    res_spi.Init.CLKPolarity = SPI_POLARITY_LOW;
    res_spi.Init.CLKPhase = SPI_PHASE_1EDGE;
    res_spi.Init.NSS = SPI_NSS_SOFT;
    res_spi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
    res_spi.Init.FirstBit = SPI_FIRSTBIT_MSB;
    res_spi.Init.TIMode = SPI_TIMODE_DISABLE;
    res_spi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    res_spi.Init.CRCPolynomial = 7;
    res_spi.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
    res_spi.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
    if (HAL_SPI_Init(&res_spi) != HAL_OK) { res_rf_fault(1u); return; }
    HAL_Delay(5u);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
    HAL_Delay(20u); /* Startup-only POR margin; not a per-packet reset. */
    while (off < sizeof(config) && config[off] != 0u) {
        res_si4463_diag.init_offset = (uint32_t)off;
        uint8_t n = config[off++];
        if (n > 16u || n > sizeof(config) - off) { res_rf_fault(3u); return; }
        /* IRCAL is a startup-only calibration (typical initial total 250 ms).
         * Keep the 5 ms runtime limit; do not apply it to this slow command. */
        if (!res_rf_command(config + off, n, NULL, 0,
                            config[off] == 0x17u ? 350u : 20u)) return;
        off += n;
    }
    if (off >= sizeof(config)) { res_rf_fault(3u); return; }
    if (!res_rf_command(part_cmd, sizeof(part_cmd), part, 8u, 5u)) return;
    res_si4463_diag.part = ((uint32_t)part[1] << 8u) | part[2];
    res_si4463_diag.chip_revision = part[0];
    if (res_si4463_diag.part != 0x4463u) { res_rf_fault(4u); return; }
    if (!res_rf_command(packet, sizeof(packet), NULL, 0, 5u) ||
        !res_rf_command(interrupts, sizeof(interrupts), NULL, 0, 5u) ||
        !res_rf_command(power, sizeof(power), NULL, 0, 5u) ||
        !res_rf_interrupts(status)) return;
    if ((status[6] & 0x28u) != 0u) { res_rf_chip_fault(); return; }
    if (!res_rf_verify_properties(interrupts) || !res_rf_verify_properties(packet) ||
        !res_rf_verify_properties(power) || !res_rf_verify_properties(modem) ||
        !res_rf_verify_properties(frequency)) return;
    res_rf_last_irq_check = HAL_GetTick();
    if (res_rf_receive(0u)) {
        const uint8_t properties[] = {0x12, 1, 4, 0};
        uint8_t values[4];
        if (!res_rf_command(properties, 4, values, 4, 5u)) return;
        memcpy((void *)&res_si4463_diag.init_props, values, 4);
        if (values[0] != 5u || values[1] != 0x38u ||
            values[2] != 0u || values[3] != 0x28u) {
            res_rf_fault(8u); return;
        }
        res_si4463_diag.ready = 1u;
    }
}

static void res_rf_poll(void)
{
    uint8_t status[8];
    if (!res_si4463_diag.ready) return;
    const bool irq_low = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == GPIO_PIN_RESET;
    if (irq_low || (uint32_t)(HAL_GetTick() - res_rf_last_irq_check) >= 10u) {
        res_rf_last_irq_check = HAL_GetTick();
        if (!irq_low) ++res_si4463_diag.irq_fallbacks;
        if (!res_rf_interrupts(status)) return;
        if ((status[6] & 0x28u) != 0u) {
            ++res_si4463_diag.chip_errors; res_rf_chip_fault(); return;
        }
        if (res_si4463_diag.tx_busy && (status[2] & 0x20u)) {
            res_si4463_diag.tx_busy = 0u;
            ++res_si4463_diag.tx_done;
            (void)res_rf_receive(res_rf_next_channel);
            return;
        }
        if (!res_si4463_diag.tx_busy && (status[2] & 0x18u)) {
            if (status[2] & 0x08u) {
                ++res_si4463_diag.crc_errors;
            } else {
                uint8_t tx[RES_RADIO_PACKET_SIZE + 1u] = {0x77};
                uint8_t rx[RES_RADIO_PACKET_SIZE + 1u];
                uint8_t count[2];
                const uint8_t fifo[] = {0x15, 0};
                if (!res_rf_command(fifo, sizeof(fifo), count, 2u, 5u)) return;
                if (count[0] != RES_RADIO_PACKET_SIZE) { res_rf_fault(6u); return; }
                res_rf_select();
                if (!res_rf_spi(tx, rx, sizeof(tx))) return;
                res_rf_deselect();
                if (res_rf_pos < res_rf_length) {
                    ++res_uart_diag.rx_overflows;
                    res_rf_fault(6u); return;
                }
                if (rx[1] >= RES_FRAME_HEADER_SIZE + RES_FRAME_TRAILER_SIZE &&
                    rx[1] < RES_RADIO_PACKET_SIZE) {
                    res_rf_length = rx[1]; res_rf_pos = 0u;
                    memcpy(res_rf_rx, rx + 2u, res_rf_length);
                    res_rf_received = HAL_GetTick();
                    res_uart_diag.last_rx_ms = res_rf_received;
                    res_uart_diag.rx_bytes += res_rf_length;
                    ++res_si4463_diag.rx_packets;
                }
            }
            (void)res_rf_receive((uint8_t)res_si4463_diag.channel);
            return;
        }
    }
    if (res_si4463_diag.tx_busy) {
        if ((uint32_t)(HAL_GetTick() - res_rf_tx_started) >= RES_RADIO_TX_TIMEOUT_MS) {
            ++res_uart_diag.tx_failures; res_rf_fault(7u);
        }
    } else if (res_rf_pos == res_rf_length &&
               (uint32_t)(HAL_GetTick() - res_rf_tuned) >= RES_RADIO_SCAN_MS) {
        ++res_si4463_diag.scans;
        (void)res_rf_receive((uint8_t)((res_si4463_diag.channel + 1u) % RES_HOP_CHANNEL_COUNT));
    }
}

static bool res_uart_send(const uint8_t *data, size_t length)
{
    const uint8_t ready[] = {0x34, 3}, reset[] = {0x15, 3};
    uint8_t status[8], tx[RES_RADIO_PACKET_SIZE + 1u] = {0x66}, rx[sizeof(tx)];
    uint8_t start[] = {0x31, 0, 0x30, 0, RES_RADIO_PACKET_SIZE, 0, 0};
    res_rf_poll();
    if (!res_si4463_diag.ready || length >= RES_RADIO_PACKET_SIZE ||
        length < RES_FRAME_HEADER_SIZE + RES_FRAME_TRAILER_SIZE || __get_IPSR() != 0u) return false;
    /* STOP can preempt a normal TX. A normal packet is never queued behind
     * another normal packet; the caller sees a real transmit failure. */
    if (res_si4463_diag.tx_busy &&
        !(data[3] == RES_MSG_COMMAND && data[RES_FRAME_HEADER_SIZE] == RES_COMMAND_STOP)) return false;
    if (data[9] >= RES_HOP_CHANNEL_COUNT) return false;
    if (!res_rf_command(ready, sizeof(ready), NULL, 0, 5u) ||
        !res_rf_command(reset, sizeof(reset), NULL, 0, 5u) ||
        !res_rf_interrupts(status)) return false;
    tx[1] = (uint8_t)length;
    memcpy(tx + 2u, data, length);
    res_rf_select();
    if (!res_rf_spi(tx, rx, sizeof(tx))) return false;
    res_rf_deselect();
    start[1] = data[9];
    if (!res_rf_command(start, sizeof(start), NULL, 0, 5u)) return false;
    res_rf_next_channel = res_hop_next_channel(data[9], res_get_u32_le(data + 14u),
                                              res_get_u32_le(data + 10u));
    res_rf_tx_started = HAL_GetTick();
    res_si4463_diag.tx_busy = 1u;
    res_si4463_diag.channel = data[9];
    res_uart_diag.last_tx_ms = res_rf_tx_started;
    ++res_uart_diag.tx_frames;
    return true;
}

static bool res_uart_next(res_stream_parser_t *parser, uint8_t *byte)
{
    res_rf_poll();
    if (!res_si4463_diag.ready || res_rf_pos >= res_rf_length) return false;
    if ((uint32_t)(HAL_GetTick() - res_rf_received) > 100u) {
        res_rf_pos = res_rf_length;
        res_stream_parser_init(parser);
        ++res_uart_diag.stale_bytes;
        return false;
    }
    if (res_rf_pos == 0u) res_stream_parser_init(parser);
    *byte = res_rf_rx[res_rf_pos++];
    ++res_uart_diag.processed_bytes;
    return true;
}

/* Called only after the application accepts/authenticates a frame. */
static void res_radio_follow(uint8_t channel)
{
    if (res_si4463_diag.ready && !res_si4463_diag.tx_busy &&
        channel != res_si4463_diag.channel) (void)res_rf_receive(channel);
}
static void res_uart_received(void) { (void)res_rx_byte; /* USART1 is not the radio. */ }
static void res_uart_error(void) { /* USART1 is not the radio. */ }
#endif
