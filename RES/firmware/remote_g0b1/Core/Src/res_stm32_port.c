#include "res_stm32_port.h"

#include "i2c.h"
#include "ina226.h"
#include "res_board_config.h"
#include "res_remote_app.h"
#include "usart.h"
#include "iwdg.h"

#define RES_POWER_SAMPLE_MS 100u

static res_remote_app_t remote_app;
static ina226_t ina226;
static uint8_t uart1_rx_byte;
static uint32_t last_power_sample_ms;

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

static void write_output(GPIO_TypeDef *port, uint16_t pin, bool on)
{
#if RES_OUTPUT_ACTIVE_LOW
    HAL_GPIO_WritePin(port, pin, on ? GPIO_PIN_RESET : GPIO_PIN_SET);
#else
    HAL_GPIO_WritePin(port, pin, on ? GPIO_PIN_SET : GPIO_PIN_RESET);
#endif
}

static void port_set_led(void *context, res_led_t led, bool on)
{
    (void)context;
    switch (led) {
    case RES_LED_STATE_BLUE:
        write_output(RES_LED_STATE_BLUE_GPIO_Port, RES_LED_STATE_BLUE_Pin, on);
        break;
    case RES_LED_STATE_YELLOW:
        write_output(RES_LED_STATE_YELLOW_GPIO_Port, RES_LED_STATE_YELLOW_Pin, on);
        break;
    case RES_LED_SOC_GREEN:
        write_output(RES_LED_SOC_GREEN_GPIO_Port, RES_LED_SOC_GREEN_Pin, on);
        break;
    case RES_LED_SOC_RED:
        write_output(RES_LED_SOC_RED_GPIO_Port, RES_LED_SOC_RED_Pin, on);
        break;
    default:
        break;
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
                     (HAL_GetUIDw2() >> 3u) ^ HAL_GetTick() ^ SysTick->VAL;
    value ^= value << 13u;
    value ^= value >> 17u;
    value ^= value << 5u;
    return (value == 0u) ? 1u : value;
}

static bool ina_write_register(void *context, uint8_t reg, uint16_t value)
{
    uint8_t bytes[2] = {(uint8_t)(value >> 8u), (uint8_t)value};
    (void)context;
    return HAL_I2C_Mem_Write(&hi2c1,
                             (uint16_t)(RES_INA226_I2C_ADDRESS_7BIT << 1u),
                             reg,
                             I2C_MEMADD_SIZE_8BIT,
                             bytes,
                             sizeof(bytes),
                             20u) == HAL_OK;
}

static bool ina_read_register(void *context, uint8_t reg, uint16_t *value)
{
    uint8_t bytes[2];
    (void)context;
    if (HAL_I2C_Mem_Read(&hi2c1,
                        (uint16_t)(RES_INA226_I2C_ADDRESS_7BIT << 1u),
                        reg,
                        I2C_MEMADD_SIZE_8BIT,
                        bytes,
                        sizeof(bytes),
                        20u) != HAL_OK) {
        return false;
    }
    *value = (uint16_t)(((uint16_t)bytes[0] << 8u) | bytes[1]);
    return true;
}

static bool read_pin(GPIO_TypeDef *port, uint16_t pin, bool active_low)
{
    const bool high = HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_SET;
    return active_low ? !high : high;
}

void RES_Application_Init(void)
{
    static const uint8_t auth_key[RES_AUTH_KEY_SIZE] = RES_DEMO_AUTH_KEY_BYTES;
    const res_remote_io_t io = {
        .context = NULL,
        .millis = port_millis,
        .radio_write = port_radio_write,
        .set_led = port_set_led,
        .refresh_watchdog = port_refresh_watchdog
    };
    const uint32_t session = make_boot_session();

    write_output(RES_LED_STATE_BLUE_GPIO_Port, RES_LED_STATE_BLUE_Pin, false);
    write_output(RES_LED_STATE_YELLOW_GPIO_Port, RES_LED_STATE_YELLOW_Pin, false);
    write_output(RES_LED_SOC_GREEN_GPIO_Port, RES_LED_SOC_GREEN_Pin, false);
    write_output(RES_LED_SOC_RED_GPIO_Port, RES_LED_SOC_RED_Pin, false);

    res_remote_app_init(&remote_app, &io, auth_key, session);
    /* Fail low until the first successful INA226 conversion is available. */
    res_remote_app_set_power(&remote_app, 0u, 0, false);
    ina226.context = NULL;
    ina226.write_register = ina_write_register;
    ina226.read_register = ina_read_register;
    (void)ina226_init(&ina226);
    (void)HAL_UART_Receive_IT(&huart1, &uart1_rx_byte, 1u);
}

void RES_Application_Task(void)
{
    const uint32_t now = HAL_GetTick();
    const bool go_pressed = read_pin(RES_GO_GPIO_Port,
                                     RES_GO_Pin,
                                     RES_GO_ACTIVE_LOW != 0);
    const bool stop_fault = read_pin(RES_STOP_GPIO_Port,
                                     RES_STOP_Pin,
                                     RES_STOP_FAULT_ACTIVE_HIGH == 0);

    res_remote_app_set_raw_inputs(&remote_app, go_pressed, stop_fault);
    if ((uint32_t)(now - last_power_sample_ms) >= RES_POWER_SAMPLE_MS) {
        uint16_t voltage_mv;
        int16_t current_ma;
        uint32_t power_mw;
        const bool valid = ina226_read(&ina226, &voltage_mv, &current_ma, &power_mw);
        (void)power_mw;
        res_remote_app_set_power(&remote_app, voltage_mv, current_ma, valid);
        last_power_sample_ms = now;
    }
    res_remote_app_tick(&remote_app);
}

void RES_Application_UART_RxComplete(UART_HandleTypeDef *huart)
{
    if (huart == &huart1) {
        res_remote_app_receive_byte(&remote_app, uart1_rx_byte);
        (void)HAL_UART_Receive_IT(&huart1, &uart1_rx_byte, 1u);
    }
}
