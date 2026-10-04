/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define GO_BUTTON_Pin GPIO_PIN_0
#define GO_BUTTON_GPIO_Port GPIOB
#define STOP_FAULT_Pin GPIO_PIN_1
#define STOP_FAULT_GPIO_Port GPIOB
#define LED_STATE_BLUE_Pin GPIO_PIN_10
#define LED_STATE_BLUE_GPIO_Port GPIOB
#define LED_STATE_YELLOW_Pin GPIO_PIN_11
#define LED_STATE_YELLOW_GPIO_Port GPIOB
#define LED_SOC_GREEN_Pin GPIO_PIN_12
#define LED_SOC_GREEN_GPIO_Port GPIOB
#define LED_SOC_RED_Pin GPIO_PIN_13
#define LED_SOC_RED_GPIO_Port GPIOB
#define INA_ALERT_Pin GPIO_PIN_8
#define INA_ALERT_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
