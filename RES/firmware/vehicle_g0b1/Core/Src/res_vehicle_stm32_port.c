#include "res_vehicle_stm32_port.h"

#include "fdcan.h"
#include "gpio.h"
#include "res_vehicle_app.h"
#include "res_vehicle_board_config.h"
#include "usart.h"
#include "iwdg.h"

static res_vehicle_app_t vehicle_app;
static uint8_t uart1_rx_byte;

static uint32_t port_millis(void *context)
{
    (void)context;
    return HAL_GetTick();
}

static bool port_radio_write(void *context, const uint8_t *data, size_t length)
{
    (void)context;
    /*
     * A complete RES frame takes about 64 ms at 9600 bit/s. Keep enough
     * margin for the UART transfer; RF transmission is handled by the bridge.
     */
    return HAL_UART_Transmit(&huart1, (uint8_t *)data, (uint16_t)length, 120u) == HAL_OK;
}

static bool port_can_write(void *context,
                           uint16_t standard_id,
                           const uint8_t *data,
                           uint8_t length)
{
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

    res_vehicle_app_init(&vehicle_app, &io, auth_key, make_boot_session());
    if (HAL_FDCAN_Start(&hfdcan1) != HAL_OK) {
        res_vehicle_app_set_local_fault(&vehicle_app,
                                        RES_VEHICLE_FAULT_CAN,
                                        true);
    }
    (void)HAL_UART_Receive_IT(&huart1, &uart1_rx_byte, 1u);
}

void RES_Vehicle_Application_Task(void)
{
    res_vehicle_app_tick(&vehicle_app);
}

void RES_Vehicle_UART_RxComplete(UART_HandleTypeDef *huart)
{
    if (huart == &huart1) {
        res_vehicle_app_receive_byte(&vehicle_app, uart1_rx_byte);
        (void)HAL_UART_Receive_IT(&huart1, &uart1_rx_byte, 1u);
    }
}
