#ifndef BOARD_PINS_H
#define BOARD_PINS_H

#include "stm32f1xx_hal.h"

/* SX127x SPI1 */
#define LORA_NSS_GPIO_Port       GPIOA
#define LORA_NSS_Pin             GPIO_PIN_4
#define LORA_RST_GPIO_Port       GPIOB
#define LORA_RST_Pin             GPIO_PIN_0

/* ADS1115 ALERT/RDY, active low */
#define ADC_ALERT_GPIO_Port      GPIOA
#define ADC_ALERT_Pin            GPIO_PIN_0

/* Dry-contact inputs. GO is NO-to-GND, SHUT is NC-to-GND. */
#define GO_GPIO_Port             GPIOB
#define GO_Pin                   GPIO_PIN_10
#define SHUT_GPIO_Port           GPIOB
#define SHUT_Pin                 GPIO_PIN_11

/* Relay-group logic inputs, active high. */
#define LED_STATE_B_GPIO_Port    GPIOB
#define LED_STATE_B_Pin          GPIO_PIN_12
#define LED_STATE_Y_GPIO_Port    GPIOB
#define LED_STATE_Y_Pin          GPIO_PIN_13
#define LED_SOC_G_GPIO_Port      GPIOB
#define LED_SOC_G_Pin            GPIO_PIN_14
#define LED_SOC_R_GPIO_Port      GPIOB
#define LED_SOC_R_Pin            GPIO_PIN_15

#endif

