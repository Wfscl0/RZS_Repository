#ifndef RES_STM32_PORT_H
#define RES_STM32_PORT_H

#include "main.h"

void RES_Application_Init(void);
void RES_Application_Task(void);

/* Call this from HAL_UART_RxCpltCallback when huart == &huart1. */
void RES_Application_UART_RxComplete(UART_HandleTypeDef *huart);

#endif
