#include "res_vehicle_stm32_port.h"

#include "fdcan.h"
#include "gpio.h"
#include "res_vehicle_app.h"
#include "res_vehicle_board_config.h"
#include "usart.h"
#include "iwdg.h"
#include "res_transport.h"

#ifndef RES_BENCH_NO_CAN
#define RES_BENCH_NO_CAN 0
#endif
/* 台架版本明确留标记；正常构建默认仍要求 CAN。 */
volatile uint32_t res_bench_no_can;
volatile uint32_t res_bench_can_suppressed;
volatile struct {
    uint32_t relay_commands, start_pulses, start_rise_ms, start_fall_ms;
} res_vehicle_output_diag;

static res_vehicle_app_t vehicle_app;

static uint32_t port_millis(void *context)
{
    (void)context;
    return HAL_GetTick();
}

static bool port_radio_write(void *context, const uint8_t *data, size_t length)
{
    (void)context;
    /* The S017 transport returns once RF TX has started, never waits on air. */
    const bool sent = res_uart_send(data, length);
    if (!sent) {
        res_vehicle_app_set_local_fault(&vehicle_app, RES_VEHICLE_FAULT_RADIO_TIMEOUT, true);
    }
    return sent;
}

static bool port_can_write(void *context,
                           uint16_t standard_id,
                           const uint8_t *data,
                           uint8_t length)
{
#if RES_BENCH_NO_CAN
    /* 仅隔离台架：记录丢弃的 CAN 帧，不宣称已实际发送。 */
    (void)context; (void)standard_id; (void)data;
    if (length != RES_CAN_FRAME_LENGTH) return false;
    ++res_bench_can_suppressed;
    return true;
#else
    FDCAN_TxHeaderTypeDef header = {0};
    (void)context;
    if (length != RES_CAN_FRAME_LENGTH) {
        return false;
    }
    header.Identifier = standard_id;
    header.IdType = FDCAN_STANDARD_ID;
    header.TxFrameType = FDCAN_DATA_FRAME;
    header.DataLength = FDCAN_DLC_BYTES_8;
    header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    header.BitRateSwitch = FDCAN_BRS_OFF;
    header.FDFormat = FDCAN_CLASSIC_CAN;
    header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    return HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1,
                                         &header,
                                         (uint8_t *)data) == HAL_OK;
#endif
}

static void write_active(GPIO_TypeDef *port,
                         uint16_t pin,
                         bool active,
                         bool active_low)
{
    const GPIO_PinState state = (active != active_low)
        ? GPIO_PIN_SET
        : GPIO_PIN_RESET;
    HAL_GPIO_WritePin(port, pin, state);
}

static void port_set_relay(void *context,
                           res_vehicle_relay_t relay,
                           bool closed)
{
    (void)context;
    const uint32_t mask = relay == RES_VEHICLE_RELAY_1 ? 1u : 2u;
    if (closed) res_vehicle_output_diag.relay_commands |= mask;
    else res_vehicle_output_diag.relay_commands &= ~mask;
    if (relay == RES_VEHICLE_RELAY_1) {
        write_active(RES_RELAY_1_GPIO_Port,
                     RES_RELAY_1_Pin,
                     closed,
                     RES_RELAY_ACTIVE_LOW != 0);
    } else {
        write_active(RES_RELAY_2_GPIO_Port,
                     RES_RELAY_2_Pin,
                     closed,
                     RES_RELAY_ACTIVE_LOW != 0);
    }
}

static void port_set_output(void *context,
                            res_vehicle_output_t output,
                            bool active)
{
    (void)context;
    if (output == RES_VEHICLE_OUTPUT_START) {
        /* 保存 GO 脉冲边沿，避免调试器漏采约 100 ms 的输出。 */
        const bool was_active = HAL_GPIO_ReadPin(RES_START_OUT_GPIO_Port,
                                                 RES_START_OUT_Pin) == GPIO_PIN_SET;
        if (active && !was_active) {
            ++res_vehicle_output_diag.start_pulses;
            res_vehicle_output_diag.start_rise_ms = HAL_GetTick();
        } else if (!active && was_active) {
            res_vehicle_output_diag.start_fall_ms = HAL_GetTick();
        }
        write_active(RES_START_OUT_GPIO_Port,
                     RES_START_OUT_Pin,
                     active,
                     RES_LOGIC_OUTPUT_ACTIVE_HIGH == 0);
    } else {
        write_active(RES_FAULT_OUT_GPIO_Port,
                     RES_FAULT_OUT_Pin,
                     active,
                     RES_LOGIC_OUTPUT_ACTIVE_HIGH == 0);
    }
}

static void port_refresh_watchdog(void *context)
{
    (void)context;
    (void)HAL_IWDG_Refresh(&hiwdg);
}

static uint32_t make_boot_session(void)
{
    uint32_t value = HAL_GetUIDw0() ^ (HAL_GetUIDw1() << 7u) ^
                     (HAL_GetUIDw2() >> 3u) ^ HAL_GetTick();
    /* SysTick phase supplies oscillator/startup jitter; zero is reserved. */
    value ^= SysTick->VAL;
    value ^= value << 13u;
    value ^= value >> 17u;
    value ^= value << 5u;
    return (value == 0u) ? 1u : value;
}

void RES_Vehicle_Application_Init(void)
{
    res_bench_no_can = RES_BENCH_NO_CAN;
    static const uint8_t auth_key[RES_AUTH_KEY_SIZE] = RES_DEMO_AUTH_KEY_BYTES;
    const res_vehicle_io_t io = {
        .context = NULL,
        .millis = port_millis,
        .radio_write = port_radio_write,
        .can_write = port_can_write,
        .set_relay = port_set_relay,
        .set_output = port_set_output,
        .refresh_watchdog = port_refresh_watchdog
    };
#if !RES_BENCH_NO_CAN
    FDCAN_FilterTypeDef filter = {0};

    /* Keep the CAN transceiver in normal mode. */
    write_active(RES_CAN_STB_GPIO_Port,
                 RES_CAN_STB_Pin,
                 false,
                 RES_CAN_STB_ACTIVE_HIGH == 0);

    /* Receiver transmits only, but reject all non-matching traffic explicitly. */
    filter.IdType = FDCAN_STANDARD_ID;
    filter.FilterIndex = 0u;
    filter.FilterType = FDCAN_FILTER_MASK;
    filter.FilterConfig = FDCAN_FILTER_REJECT;
    filter.FilterID1 = 0u;
    filter.FilterID2 = 0x7FFu;
    (void)HAL_FDCAN_ConfigFilter(&hfdcan1, &filter);
    (void)HAL_FDCAN_ConfigGlobalFilter(&hfdcan1,
                                       FDCAN_REJECT,
                                       FDCAN_REJECT,
                                       FDCAN_REJECT_REMOTE,
                                       FDCAN_REJECT_REMOTE);

#else
    /* 航空插头断开时测试；CAN 收发器保持待机。 */
    HAL_GPIO_WritePin(RES_CAN_STB_GPIO_Port, RES_CAN_STB_Pin, GPIO_PIN_SET);
#endif
    res_vehicle_app_init(&vehicle_app, &io, auth_key, make_boot_session());
#if !RES_BENCH_NO_CAN
    if (HAL_FDCAN_Start(&hfdcan1) != HAL_OK) {
        res_vehicle_app_set_local_fault(&vehicle_app,
                                        RES_VEHICLE_FAULT_CAN,
                                        true);
    }
#endif
    res_uart_start(2u);
#if RES_RADIO_SI4463
    if (!res_si4463_diag.ready)
        res_vehicle_app_set_local_fault(&vehicle_app, RES_VEHICLE_FAULT_RADIO_TIMEOUT, true);
#endif
}

void RES_Vehicle_Application_Task(void)
{
    uint8_t byte;
#if !RES_BENCH_NO_CAN
    FDCAN_ProtocolStatusTypeDef can_status;
#endif
    unsigned budget = 128u;
#if RES_RADIO_SI4463
    const uint32_t previous_sequence = vehicle_app.replay.highest_sequence;
#endif
#if !RES_BENCH_NO_CAN
    if (HAL_FDCAN_GetProtocolStatus(&hfdcan1, &can_status) != HAL_OK || can_status.BusOff) {
        res_vehicle_app_set_local_fault(&vehicle_app, RES_VEHICLE_FAULT_CAN, true);
    }
#endif
    /* Expiry/START pulse deadlines are evaluated before servicing RF. */
    res_vehicle_app_tick(&vehicle_app);
    while (budget-- != 0u && res_uart_next(&vehicle_app.parser, &byte)) {
        res_vehicle_app_receive_byte(&vehicle_app, byte);
    }
#if RES_RADIO_SI4463
    if (vehicle_app.replay.highest_sequence != previous_sequence)
        res_radio_follow(vehicle_app.active_channel);
    if (!res_si4463_diag.ready)
        res_vehicle_app_set_local_fault(&vehicle_app, RES_VEHICLE_FAULT_RADIO_TIMEOUT, true);
#endif
    res_vehicle_app_tick(&vehicle_app);
    res_uart_diag.tick_ms = HAL_GetTick();
    res_uart_diag.last_valid_rx_ms = vehicle_app.last_valid_rx_ms;
    res_uart_diag.state = vehicle_app.state;
    res_uart_diag.faults = vehicle_app.fault_flags;
    res_uart_diag.outputs = (vehicle_app.relay_1_closed ? 1u : 0u) |
                           (vehicle_app.relay_2_closed ? 2u : 0u);
}

void RES_Vehicle_UART_RxComplete(UART_HandleTypeDef *huart)
{
    if (huart == &huart1) {
        res_uart_received();
    }
}

void RES_Vehicle_UART_Error(UART_HandleTypeDef *huart)
{
    if (huart == &huart1) {
        res_uart_error();
    }
}
