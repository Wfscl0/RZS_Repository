#include "res_stm32_port.h"

#include "i2c.h"
#include "ina226.h"
#include "res_board_config.h"
#include "res_remote_app.h"
#include "usart.h"
#include "iwdg.h"
#include "res_transport.h"

#define RES_POWER_SAMPLE_MS 100u
#define RES_POWER_RETRY_MS 1000u

static res_remote_app_t remote_app;
static ina226_t ina226;
static uint32_t last_power_sample_ms;
static uint32_t last_power_init_ms;

volatile uint32_t res_uart1_rx_byte_count;
volatile uint32_t res_uart1_error_count;
volatile uint32_t res_uart1_last_error;
volatile uint8_t res_uart1_last_rx_byte;
volatile uint32_t res_power_error_count;
volatile uint32_t res_power_last_error;
volatile uint32_t res_power_last_good_ms;
volatile uint16_t res_power_voltage_mv;
/* Debugger-visible diagnostics, never used to override safety decisions. */
volatile uint32_t res_firmware_revision = 0x20260922u;
volatile uint8_t res_led_command_bits;

static uint32_t port_millis(void *context)
{
    (void)context;
    return HAL_GetTick();
}

static bool port_radio_write(void *context, const uint8_t *data, size_t length)
{
    (void)context;
    /* Transport selected centrally; S017 submits an asynchronous RF packet. */
    return res_uart_send(data, length);
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
    if ((unsigned)led < RES_LED_COUNT) {
        if (on) {
            res_led_command_bits |= (uint8_t)(1u << (unsigned)led);
        } else {
            res_led_command_bits &= (uint8_t)~(1u << (unsigned)led);
        }
    }
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

    /* Keep the diagnostic tag reachable when the linker removes unused data. */
    res_firmware_revision = 0x20260922u;

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
    if (!ina226_init(&ina226)) {
        ++res_power_error_count;
    }
    res_power_last_error = (uint32_t)ina226.last_error;
    last_power_init_ms = HAL_GetTick();
    res_uart_start(1u);
#if RES_RADIO_SI4463
    if (!res_si4463_diag.ready)
        res_remote_app_set_fault(&remote_app, RES_REMOTE_FAULT_RADIO_TX, true);
#endif
}

void RES_Application_Task(void)
{
    uint8_t byte;
    unsigned budget = 128u;
#if RES_RADIO_SI4463
    const uint32_t previous_acks = remote_app.accepted_acks;
#endif
    while (budget-- != 0u && res_uart_next(&remote_app.parser, &byte)) {
        res_remote_app_receive_byte(&remote_app, byte);
    }
#if RES_RADIO_SI4463
    if (remote_app.accepted_acks != previous_acks)
        res_radio_follow(remote_app.active_channel);
    if (!res_si4463_diag.ready)
        res_remote_app_set_fault(&remote_app, RES_REMOTE_FAULT_RADIO_TX, true);
#endif
    const uint32_t now = HAL_GetTick();
    const bool go_pressed = read_pin(RES_GO_GPIO_Port,
                                     RES_GO_Pin,
                                     RES_GO_ACTIVE_LOW != 0);
    const bool stop_fault = read_pin(RES_STOP_GPIO_Port,
                                     RES_STOP_Pin,
                                     RES_STOP_FAULT_ACTIVE_HIGH == 0);

    res_remote_app_set_raw_inputs(&remote_app, go_pressed, stop_fault);
    if ((uint32_t)(now - last_power_sample_ms) >= RES_POWER_SAMPLE_MS) {
        uint16_t voltage_mv = 0u;
        int16_t current_ma = 0;
        uint32_t power_mw = 0u;
        bool valid;
        if (!ina226.initialized &&
            ((uint32_t)(now - last_power_init_ms) >= RES_POWER_RETRY_MS)) {
            (void)ina226_init(&ina226);
            last_power_init_ms = now;
        }
        valid = ina226_read(&ina226, &voltage_mv, &current_ma, &power_mw);
        res_power_last_error = (uint32_t)ina226.last_error;
        res_power_voltage_mv = voltage_mv;
        if (valid) {
            res_power_last_good_ms = HAL_GetTick();
        } else {
            ++res_power_error_count;
        }
        (void)power_mw;
        res_remote_app_set_power(&remote_app, voltage_mv, current_ma, valid);
        last_power_sample_ms = now;
    }
    res_remote_app_tick(&remote_app);
    res_uart_diag.tick_ms = HAL_GetTick();
    res_uart_diag.last_valid_rx_ms = remote_app.last_valid_rx_ms;
    res_uart_diag.state = remote_app.safety_state;
    res_uart_diag.faults = remote_app.fault_flags;
    res_uart_diag.feedback_valid = remote_app.vehicle_feedback_valid;
    res_uart_diag.battery_mv = remote_app.battery_mv;
    res_uart_diag.battery_valid = remote_app.battery_measurement_valid;
    res_uart_diag.input_stop = remote_app.raw_stop_fault;
    res_uart_diag.outputs = res_led_command_bits;
    res_uart_diag.decoded_frames = remote_app.decoded_frames;
    res_uart_diag.unmatched_acks = remote_app.unmatched_acks;
    res_uart_diag.accepted_acks = remote_app.accepted_acks;
}

void RES_Application_UART_RxComplete(UART_HandleTypeDef *huart)
{
    if (huart == &huart1) {
        ++res_uart1_rx_byte_count;
        res_uart1_last_rx_byte = res_rx_byte;
        res_uart_received();
    }
}

void RES_Application_UART_Error(UART_HandleTypeDef *huart)
{
    if (huart == &huart1) {
        ++res_uart1_error_count;
        res_uart1_last_error = HAL_UART_GetError(huart);
        res_uart_error();
    }
}
