#ifndef RES_VEHICLE_STM32_PORT_H
#define RES_VEHICLE_STM32_PORT_H

#include "main.h"

void RES_Vehicle_Application_Init(void);
void RES_Vehicle_Application_Task(void);
void RES_Vehicle_UART_RxComplete(UART_HandleTypeDef *huart);

#endif
