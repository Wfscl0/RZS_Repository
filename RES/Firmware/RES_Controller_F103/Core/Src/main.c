#include "main.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "ads1115.h"
#include "board_pins.h"
#include "res_config.h"
#include "res_fsm.h"
#include "res_protocol.h"
#include "sx127x.h"

I2C_HandleTypeDef hi2c1;
IWDG_HandleTypeDef hiwdg;
SPI_HandleTypeDef hspi1;
UART_HandleTypeDef huart1;

typedef enum {
    RADIO_OFFLINE = 0,
    RADIO_RECEIVING,
    RADIO_TRANSMITTING
} RadioPhase;

typedef enum {
    ADC_IDLE = 0,
    ADC_CONVERTING
} AdcPhase;

typedef struct {
    Sx127x device;
    RadioPhase phase;
    uint32_t next_tx_ms;
    uint32_t retry_ms;
    uint16_t sequence;
    uint8_t channel;
    bool available;
} RadioTask;

typedef struct {
    Ads1115 device;
    AdcPhase phase;
    uint32_t next_sample_ms;
    uint32_t conversion_started_ms;
    uint16_t battery_mv;
    uint8_t consecutive_failures;
    bool available;
    bool valid;
} AdcTask;

/* 所有任务均由 1 ms HAL tick 驱动，不在主循环中等待无线发送完成。 */
static ResFsm app;
static RadioTask radio_task;
static AdcTask adc_task;
static uint32_t session_id;
static uint8_t receiver_faults;

static void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_IWDG_Init(void);
static void radio_service(uint32_t now_ms, bool go_pressed, bool shut_open);
static void adc_service(uint32_t now_ms);
static void indicators_service(
    uint32_t now_ms,
    bool go_pressed,
    bool shut_open);

static bool time_reached(uint32_t now_ms, uint32_t deadline_ms)
{
    return (int32_t)(now_ms - deadline_ms) >= 0;
}

static uint32_t radio_frequency(uint8_t channel)
{
    static const uint32_t frequencies[RES_RF_CHANNEL_COUNT] = {
        RES_RF_CHANNEL_0_HZ,
        RES_RF_CHANNEL_1_HZ,
        RES_RF_CHANNEL_2_HZ
    };
    return frequencies[channel % RES_RF_CHANNEL_COUNT];
}

static uint32_t make_session_id(void)
{
    volatile const uint32_t *uid =
        (volatile const uint32_t *)UINT32_C(0x1FFFF7E8);
    uint16_t boot_counter;
    uint32_t value;

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_RCC_BKP_CLK_ENABLE();
    SET_BIT(PWR->CR, PWR_CR_DBP);
    /*
     * 会话号随 MCU 重启变化。赛车端在已经接收 GO 后若看到会话变化，
     * 必须按故障处理，不能把新会话当成“继续运行”。
     */
    boot_counter = (uint16_t)(BKP->DR1 + 1U);
    BKP->DR1 = boot_counter;

    value = uid[0] ^ uid[1] ^ uid[2]
        ^ ((uint32_t)boot_counter << 16)
        ^ UINT32_C(0xA5C39E17);
    value ^= value >> 16;
    value *= UINT32_C(0x7FEB352D);
    value ^= value >> 15;
    return value;
}

static void set_output(
    GPIO_TypeDef *port,
    uint16_t pin,
    bool active)
{
    HAL_GPIO_WritePin(port, pin, active ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

static uint8_t make_status_flags(bool go_pressed, bool shut_open)
{
    uint8_t flags = 0U;

    if (radio_task.available) {
        flags |= RES_FLAG_RADIO_OK;
    }
    if (adc_task.valid) {
        flags |= RES_FLAG_ADC_OK;
        if (adc_task.battery_mv < RES_BATTERY_LOW_MV) {
            flags |= RES_FLAG_LOW_BATTERY;
        }
    }
    if (app.run_authorized) {
        flags |= RES_FLAG_RUN_AUTHORIZED;
    }
    if (app.state == RES_STATE_ESTOP_LATCHED) {
        flags |= RES_FLAG_ESTOP_LATCHED;
    }
    if (go_pressed) {
        flags |= RES_FLAG_GO_PRESSED;
    }
    if (shut_open) {
        flags |= RES_FLAG_SHUT_OPEN;
    }
    return flags;
}

static bool radio_initialize(uint32_t now_ms)
{
    radio_task.available = sx127x_init(
        &radio_task.device,
        &hspi1,
        LORA_NSS_GPIO_Port,
        LORA_NSS_Pin,
        LORA_RST_GPIO_Port,
        LORA_RST_Pin,
        radio_frequency(0U),
        RES_RF_TX_POWER_DBM);
    if (radio_task.available) {
        radio_task.phase = RADIO_RECEIVING;
        radio_task.channel = 0U;
        radio_task.next_tx_ms = now_ms;
        radio_task.available = sx127x_start_rx(&radio_task.device);
    }
    if (!radio_task.available) {
        radio_task.phase = RADIO_OFFLINE;
        radio_task.retry_ms = now_ms + RES_RADIO_RETRY_MS;
    }
    return radio_task.available;
}

static void accept_received_ack(const uint8_t *bytes, uint8_t length, uint32_t now_ms)
{
    ResAckFrame ack;

    /* CRC、配对号和本次启动会话三项全部匹配后，ACK 才能刷新超时。 */
    if (!res_protocol_decode_ack(bytes, length, &ack)
        || (ack.pair_id != RES_PAIR_ID)
        || (ack.session_id != session_id)) {
        return;
    }

    res_fsm_on_ack(&app, now_ms);
    receiver_faults = ack.receiver_faults;
    if (ack.receiver_faults != 0U) {
        res_fsm_force_estop(
            &app, now_ms, RES_ESTOP_RECEIVER_FAULT);
    }
}

static void start_next_transmission(
    uint32_t now_ms,
    bool go_pressed,
    bool shut_open)
{
    ResCommandFrame frame;
    uint8_t encoded[RES_COMMAND_FRAME_SIZE];
    uint32_t period_ms =
        (app.state == RES_STATE_ESTOP_LATCHED)
            ? RES_RADIO_ESTOP_TX_PERIOD_MS
            : RES_RADIO_TX_PERIOD_MS;

    /*
     * 每帧轮换频点。同一个 GO/ESTOP 会在多个频点重复出现，接收端
     * 失链时必须扫描相同频点表，不能只停留在最后一个频道。
     */
    radio_task.channel =
        (uint8_t)((radio_task.channel + 1U) % RES_RF_CHANNEL_COUNT);
    if (!sx127x_set_frequency(
            &radio_task.device,
            radio_frequency(radio_task.channel))) {
        radio_task.available = false;
        radio_task.phase = RADIO_OFFLINE;
        radio_task.retry_ms = now_ms + RES_RADIO_RETRY_MS;
        return;
    }

    ++radio_task.sequence;
    frame.pair_id = RES_PAIR_ID;
    frame.session_id = session_id;
    frame.sequence = radio_task.sequence;
    frame.command = res_fsm_command(&app);
    frame.flags = make_status_flags(go_pressed, shut_open);
    frame.battery_mv = adc_task.valid ? adc_task.battery_mv : 0U;
    frame.uptime_ms = now_ms;
    res_protocol_encode_command(&frame, encoded);

    if (!sx127x_begin_tx(
            &radio_task.device,
            encoded,
            RES_COMMAND_FRAME_SIZE,
            now_ms)) {
        radio_task.available = false;
        radio_task.phase = RADIO_OFFLINE;
        radio_task.retry_ms = now_ms + RES_RADIO_RETRY_MS;
        return;
    }

    radio_task.phase = RADIO_TRANSMITTING;
    radio_task.next_tx_ms = now_ms + period_ms;
}

static void radio_service(uint32_t now_ms, bool go_pressed, bool shut_open)
{
    uint8_t received[64];
    uint8_t received_length = 0U;

    if (!radio_task.available) {
        if (time_reached(now_ms, radio_task.retry_ms)) {
            (void)radio_initialize(now_ms);
        }
        return;
    }

    if (radio_task.phase == RADIO_TRANSMITTING) {
        Sx127xTxStatus status = sx127x_poll_tx(
            &radio_task.device,
            now_ms,
            RES_RADIO_TX_TIMEOUT_MS);
        if (status == SX127X_TX_BUSY) {
            return;
        }
        if (status != SX127X_TX_DONE) {
            radio_task.available = false;
            radio_task.phase = RADIO_OFFLINE;
            radio_task.retry_ms = now_ms + RES_RADIO_RETRY_MS;
            return;
        }
        if (!sx127x_start_rx(&radio_task.device)) {
            radio_task.available = false;
            radio_task.phase = RADIO_OFFLINE;
            radio_task.retry_ms = now_ms + RES_RADIO_RETRY_MS;
            return;
        }
        radio_task.phase = RADIO_RECEIVING;
    }

    if (!sx127x_poll_rx(
            &radio_task.device,
            received,
            sizeof(received),
            &received_length)) {
        radio_task.available = false;
        radio_task.phase = RADIO_OFFLINE;
        radio_task.retry_ms = now_ms + RES_RADIO_RETRY_MS;
        return;
    }
    if (received_length > 0U) {
        accept_received_ack(received, received_length, now_ms);
    }

    if (time_reached(now_ms, radio_task.next_tx_ms)) {
        start_next_transmission(now_ms, go_pressed, shut_open);
    }
}

static uint16_t raw_adc_to_battery_mv(int16_t raw)
{
    uint64_t adc_uv;
    uint64_t battery_mv;

    if (raw <= 0) {
        return 0U;
    }
    /*
     * ADS1115 +/-4.096 V 档每码 125 uV。先用 64 位计算，再还原
     * 分压前的电池电压，避免 32 位乘法溢出。
     */
    adc_uv = (uint64_t)(uint16_t)raw * UINT64_C(125);
    battery_mv =
        adc_uv
        * (RES_BAT_DIVIDER_TOP_OHM + RES_BAT_DIVIDER_BOTTOM_OHM)
        / RES_BAT_DIVIDER_BOTTOM_OHM
        / UINT64_C(1000);
    if (battery_mv > UINT16_MAX) {
        return UINT16_MAX;
    }
    return (uint16_t)battery_mv;
}

static void adc_mark_failure(uint32_t now_ms)
{
    if (adc_task.consecutive_failures < UINT8_MAX) {
        ++adc_task.consecutive_failures;
    }
    if (adc_task.consecutive_failures >= RES_ADC_FAILURE_LIMIT) {
        adc_task.valid = false;
    }
    adc_task.phase = ADC_IDLE;
    adc_task.next_sample_ms = now_ms + RES_ADC_SAMPLE_PERIOD_MS;
}

static void adc_service(uint32_t now_ms)
{
    int16_t raw;
    uint16_t millivolts;

    if (!adc_task.available) {
        if (time_reached(now_ms, adc_task.next_sample_ms)) {
            adc_task.available = ads1115_init(
                &adc_task.device,
                &hi2c1,
                RES_ADS1115_I2C_ADDRESS);
            adc_task.next_sample_ms = now_ms + RES_ADC_SAMPLE_PERIOD_MS;
        }
        return;
    }

    if (adc_task.phase == ADC_IDLE) {
        if (!time_reached(now_ms, adc_task.next_sample_ms)) {
            return;
        }
        if (!ads1115_start_ain0_single(&adc_task.device)) {
            adc_task.available = false;
            adc_mark_failure(now_ms);
            return;
        }
        adc_task.phase = ADC_CONVERTING;
        adc_task.conversion_started_ms = now_ms;
        return;
    }

    if ((HAL_GPIO_ReadPin(ADC_ALERT_GPIO_Port, ADC_ALERT_Pin)
         != GPIO_PIN_RESET)
        && ((now_ms - adc_task.conversion_started_ms)
            < RES_ADC_CONVERSION_MS)) {
        return;
    }

    if (!ads1115_read_conversion(&adc_task.device, &raw)) {
        adc_task.available = false;
        adc_mark_failure(now_ms);
        return;
    }
    millivolts = raw_adc_to_battery_mv(raw);
    if ((millivolts == 0U)
        || (millivolts > RES_BATTERY_MAX_VALID_MV)) {
        adc_mark_failure(now_ms);
        return;
    }

    adc_task.battery_mv = millivolts;
    adc_task.consecutive_failures = 0U;
    adc_task.valid = true;
    adc_task.phase = ADC_IDLE;
    adc_task.next_sample_ms = now_ms + RES_ADC_SAMPLE_PERIOD_MS;
}

static void indicators_service(
    uint32_t now_ms,
    bool go_pressed,
    bool shut_open)
{
    bool blue = false;
    bool yellow = false;
    bool soc_green = false;
    bool soc_red = false;
    bool fast_blink = ((now_ms / 100U) & 1U) == 0U;
    bool slow_blink = (now_ms % 1000U) < 250U;
    bool link_ok = res_fsm_link_ok(&app, now_ms);

    (void)go_pressed;
    (void)shut_open;

    /* 指示灯同时承担灯检、链路、急停、电量和 ADC 自诊断提示。 */
    if (app.state == RES_STATE_LAMP_TEST) {
        blue = true;
        yellow = true;
        soc_green = true;
        soc_red = true;
    } else {
        if (app.state == RES_STATE_ESTOP_LATCHED) {
            yellow = true;
        } else if (!link_ok || app.go_rejected_no_link
                   || (receiver_faults != 0U)) {
            yellow = fast_blink;
        } else if (app.state == RES_STATE_GO_REPEAT) {
            blue = fast_blink;
        } else {
            blue = slow_blink;
        }

        if (!adc_task.valid) {
            soc_red = fast_blink;
        } else if (adc_task.battery_mv >= RES_BATTERY_MID_MV) {
            soc_green = true;
        } else if (adc_task.battery_mv >= RES_BATTERY_LOW_MV) {
            soc_green = true;
            soc_red = true;
        } else {
            soc_red = fast_blink;
        }
    }

    set_output(LED_STATE_B_GPIO_Port, LED_STATE_B_Pin, blue);
    set_output(LED_STATE_Y_GPIO_Port, LED_STATE_Y_Pin, yellow);
    set_output(LED_SOC_G_GPIO_Port, LED_SOC_G_Pin, soc_green);
    set_output(LED_SOC_R_GPIO_Port, LED_SOC_R_Pin, soc_red);
}

int main(void)
{
    uint32_t now_ms;
    bool go_pressed;
    bool shut_open;

    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_SPI1_Init();
    MX_I2C1_Init();
    MX_USART1_UART_Init();

    memset(&radio_task, 0, sizeof(radio_task));
    memset(&adc_task, 0, sizeof(adc_task));
    session_id = make_session_id();

    now_ms = HAL_GetTick();
    go_pressed =
        HAL_GPIO_ReadPin(GO_GPIO_Port, GO_Pin) == GPIO_PIN_RESET;
    shut_open =
        HAL_GPIO_ReadPin(SHUT_GPIO_Port, SHUT_Pin) != GPIO_PIN_RESET;
    res_fsm_init(&app, now_ms, shut_open);

    adc_task.available = ads1115_init(
        &adc_task.device,
        &hi2c1,
        RES_ADS1115_I2C_ADDRESS);
    adc_task.next_sample_ms = now_ms;
    (void)radio_initialize(now_ms);

    /*
     * 一次性初始化完成后再启动看门狗。若之后 MCU 卡死，遥控端停止
     * 心跳，赛车端须在自己的 500 ms 超时路径上断开 SDC。
     */
    MX_IWDG_Init();

    for (;;) {
        now_ms = HAL_GetTick();
        go_pressed =
            HAL_GPIO_ReadPin(GO_GPIO_Port, GO_Pin) == GPIO_PIN_RESET;
        shut_open =
            HAL_GPIO_ReadPin(SHUT_GPIO_Port, SHUT_Pin) != GPIO_PIN_RESET;

        res_fsm_update(&app, now_ms, go_pressed, shut_open);
        adc_service(now_ms);
        radio_service(now_ms, go_pressed, shut_open);
        indicators_service(now_ms, go_pressed, shut_open);
        (void)HAL_IWDG_Refresh(&hiwdg);
    }
}

static void SystemClock_Config(void)
{
    RCC_OscInitTypeDef oscillator = {0};
    RCC_ClkInitTypeDef clocks = {0};

    oscillator.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    oscillator.HSEState = RCC_HSE_ON;
    oscillator.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    oscillator.HSIState = RCC_HSI_ON;
    oscillator.PLL.PLLState = RCC_PLL_ON;
    oscillator.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    oscillator.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&oscillator) != HAL_OK) {
        Error_Handler();
    }

    clocks.ClockType =
        RCC_CLOCKTYPE_HCLK
        | RCC_CLOCKTYPE_SYSCLK
        | RCC_CLOCKTYPE_PCLK1
        | RCC_CLOCKTYPE_PCLK2;
    clocks.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    clocks.AHBCLKDivider = RCC_SYSCLK_DIV1;
    clocks.APB1CLKDivider = RCC_HCLK_DIV2;
    clocks.APB2CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&clocks, FLASH_LATENCY_2) != HAL_OK) {
        Error_Handler();
    }
}

static void MX_SPI1_Init(void)
{
    hspi1.Instance = SPI1;
    hspi1.Init.Mode = SPI_MODE_MASTER;
    hspi1.Init.Direction = SPI_DIRECTION_2LINES;
    hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi1.Init.NSS = SPI_NSS_SOFT;
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi1.Init.CRCPolynomial = 7U;
    if (HAL_SPI_Init(&hspi1) != HAL_OK) {
        Error_Handler();
    }
}

static void MX_I2C1_Init(void)
{
    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 400000U;
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0U;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0U;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
        Error_Handler();
    }
}

static void MX_USART1_UART_Init(void)
{
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200U;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart1) != HAL_OK) {
        Error_Handler();
    }
}

static void MX_IWDG_Init(void)
{
    hiwdg.Instance = IWDG;
    hiwdg.Init.Prescaler = IWDG_PRESCALER_64;
    hiwdg.Init.Reload = 1249U;
    if (HAL_IWDG_Init(&hiwdg) != HAL_OK) {
        Error_Handler();
    }
}

static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef gpio = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    HAL_GPIO_WritePin(LORA_NSS_GPIO_Port, LORA_NSS_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LORA_RST_GPIO_Port, LORA_RST_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(
        GPIOB,
        LED_STATE_B_Pin | LED_STATE_Y_Pin | LED_SOC_G_Pin | LED_SOC_R_Pin,
        GPIO_PIN_RESET);

    gpio.Pin = LORA_NSS_Pin;
    gpio.Mode = GPIO_MODE_OUTPUT_PP;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LORA_NSS_GPIO_Port, &gpio);

    gpio.Pin = LORA_RST_Pin;
    gpio.Mode = GPIO_MODE_OUTPUT_PP;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LORA_RST_GPIO_Port, &gpio);

    gpio.Pin = GO_Pin | SHUT_Pin;
    gpio.Mode = GPIO_MODE_INPUT;
    gpio.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOB, &gpio);

    gpio.Pin = ADC_ALERT_Pin;
    gpio.Mode = GPIO_MODE_INPUT;
    gpio.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(ADC_ALERT_GPIO_Port, &gpio);

    gpio.Pin =
        LED_STATE_B_Pin | LED_STATE_Y_Pin | LED_SOC_G_Pin | LED_SOC_R_Pin;
    gpio.Mode = GPIO_MODE_OUTPUT_PP;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &gpio);
}

void Error_Handler(void)
{
    __disable_irq();
    set_output(LED_STATE_B_GPIO_Port, LED_STATE_B_Pin, false);
    set_output(LED_STATE_Y_GPIO_Port, LED_STATE_Y_Pin, true);
    set_output(LED_SOC_G_GPIO_Port, LED_SOC_G_Pin, false);
    set_output(LED_SOC_R_GPIO_Port, LED_SOC_R_Pin, true);
    for (;;) {
    }
}
