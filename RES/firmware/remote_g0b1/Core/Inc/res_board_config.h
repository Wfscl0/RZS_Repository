#ifndef RES_BOARD_CONFIG_H
#define RES_BOARD_CONFIG_H

/*
 * CubeMX pin assignment for the external WeAct STM32G0B1CBT6 board.
 * Rename the GPIO labels in CubeMX exactly as below, or adjust this file.
 */

#define RES_GO_GPIO_Port              GPIOB
#define RES_GO_Pin                    GPIO_PIN_0
#define RES_STOP_GPIO_Port            GPIOB
#define RES_STOP_Pin                  GPIO_PIN_1

#define RES_LED_STATE_BLUE_GPIO_Port  GPIOB
#define RES_LED_STATE_BLUE_Pin        GPIO_PIN_10
#define RES_LED_STATE_YELLOW_GPIO_Port GPIOB
#define RES_LED_STATE_YELLOW_Pin      GPIO_PIN_11
#define RES_LED_SOC_GREEN_GPIO_Port   GPIOB
#define RES_LED_SOC_GREEN_Pin         GPIO_PIN_12
#define RES_LED_SOC_RED_GPIO_Port     GPIOB
#define RES_LED_SOC_RED_Pin           GPIO_PIN_13

#define RES_INA_ALERT_GPIO_Port       GPIOA
#define RES_INA_ALERT_Pin             GPIO_PIN_8

/* Relay boards sold under this appearance are commonly low-level triggered. */
#define RES_OUTPUT_ACTIVE_LOW         1
/* NC fail-safe loop: low=healthy, high=pressed/broken wire/lost optocoupler power. */
#define RES_STOP_FAULT_ACTIVE_HIGH    1
#define RES_GO_ACTIVE_LOW             1

#define RES_INA226_I2C_ADDRESS_7BIT   0x40u

/* Replace with a random per-team key before any field test. Never commit the key. */
#define RES_DEMO_AUTH_KEY_BYTES \
    {0x63u,0x68u,0x61u,0x6Eu,0x67u,0x65u,0x2Du,0x74u, \
     0x68u,0x69u,0x73u,0x2Du,0x6Bu,0x65u,0x79u,0x21u}

#endif
