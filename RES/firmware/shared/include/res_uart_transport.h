#ifndef RES_UART_TRANSPORT_H
#define RES_UART_TRANSPORT_H

/* Included by exactly one STM32 port translation unit per image. */
#include "stm32g0xx_hal.h"
#include "res_protocol.h"
#include <stdbool.h>
#include <stdint.h>

/* The stock Ebyte bridge decides that a UART frame ended after an idle
 * interval.  Keep production timing unchanged; this explicit compatibility
 * profile inserts a bounded idle gap for boards that still run the vendor
 * bridge firmware. */
#ifndef RES_STOCK_BRIDGE_GAP_MS
#define RES_STOCK_BRIDGE_GAP_MS 0u
#endif

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

volatile res_uart_diag_t res_uart_diag;
static volatile uint16_t res_rx_head, res_rx_tail;
static volatile uint8_t res_rx_data[256];
static volatile uint32_t res_rx_time[256];
static volatile bool res_rx_lost;
static uint8_t res_rx_byte;
extern UART_HandleTypeDef huart1;

static void res_uart_arm(void)
{
    if (huart1.RxState == HAL_UART_STATE_READY) {
        if (HAL_UART_Receive_IT(&huart1, &res_rx_byte, 1u) != HAL_OK) {
            ++res_uart_diag.rearm_failures;
        }
    }
}

static void res_uart_start(uint32_t role)
{
    res_uart_diag.magic = 0x52455344u;
    res_uart_diag.role = role;
    res_uart_diag.revision = 0x20260912u;
    res_uart_arm();
}

/* ISR only copies a byte and rearms RX: never parse or transmit here. */
static void res_uart_received(void)
{
    const uint16_t head = res_rx_head;
    const uint16_t next = (uint16_t)((head + 1u) & 255u);
    const uint8_t byte = res_rx_byte;
    res_uart_diag.rx_trace[res_uart_diag.rx_bytes & 127u] = byte;
    ++res_uart_diag.rx_bytes;
    res_uart_diag.last_rx_ms = HAL_GetTick();
    if (next == res_rx_tail) {
        ++res_uart_diag.rx_overflows;
        res_rx_lost = true;
    } else {
        res_rx_data[head] = byte;
        res_rx_time[head] = res_uart_diag.last_rx_ms;
        res_rx_head = next;
    }
    res_uart_arm();
}

static void res_uart_error(void)
{
    ++res_uart_diag.uart_errors;
    res_uart_diag.last_uart_error = HAL_UART_GetError(&huart1);
    res_rx_lost = true;
    /* HAL has ended RX after ORE; for nonblocking errors it may remain busy. */
    res_uart_arm();
}

static bool res_uart_next(res_stream_parser_t *parser, uint8_t *byte)
{
    uint16_t tail;
    uint32_t stamp;
    uint32_t mask = __get_PRIMASK();
    __disable_irq();
    res_uart_arm(); /* Retry a failed rearm, without racing the IRQ callback. */
    if (res_rx_lost) {
        res_rx_tail = res_rx_head;
        res_rx_lost = false;
        res_stream_parser_init(parser);
        ++res_uart_diag.resyncs;
    }
    tail = res_rx_tail;
    if (tail == res_rx_head) {
        __set_PRIMASK(mask);
        return false;
    }
    *byte = res_rx_data[tail];
    stamp = res_rx_time[tail];
    res_rx_tail = (uint16_t)((tail + 1u) & 255u);
    __set_PRIMASK(mask);
    /* A stalled main loop must not turn old queued traffic into fresh liveness. */
    if ((uint32_t)(HAL_GetTick() - stamp) > 100u) {
        res_stream_parser_init(parser);
        ++res_uart_diag.stale_bytes;
        return false;
    }
    ++res_uart_diag.processed_bytes;
    return true;
}

static bool res_uart_send(const uint8_t *data, size_t length)
{
    HAL_StatusTypeDef result;
    if (__get_IPSR() != 0u || length == 0u || length > RES_MAX_FRAME_SIZE) {
        ++res_uart_diag.tx_failures;
        return false;
    }
    result = HAL_UART_Transmit(&huart1, (uint8_t *)data, (uint16_t)length, 120u);
    if (result != HAL_OK) {
        ++res_uart_diag.tx_failures;
        return false;
    }
    ++res_uart_diag.tx_frames;
    res_uart_diag.last_tx_ms = HAL_GetTick();
#if RES_STOCK_BRIDGE_GAP_MS != 0u
    HAL_Delay(RES_STOCK_BRIDGE_GAP_MS);
#endif
    return true;
}
#endif
