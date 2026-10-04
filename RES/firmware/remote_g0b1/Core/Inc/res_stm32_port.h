#ifndef RES_STM32_PORT_H
#define RES_STM32_PORT_H

#include "main.h"

void RES_Application_Init(void);
void RES_Application_Task(void);

/* Call this from HAL_UART_RxCpltCallback when huart == &huart1. */
void RES_Application_UART_RxComplete(UART_HandleTypeDef *huart);

/* Call this from HAL_UART_ErrorCallback so reception recovers after noise. */
void RES_Application_UART_Error(UART_HandleTypeDef *huart);

/* Live link diagnostics, readable through the debugger without stopping I/O. */
extern volatile uint32_t res_uart1_rx_byte_count;
extern volatile uint32_t res_uart1_error_count;
extern volatile uint32_t res_uart1_last_error;
extern volatile uint8_t res_uart1_last_rx_byte;

#endif
