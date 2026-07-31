/*
 * bsp_uart_sbus.h
 *
 * Created on: 2025Äê10ÔÂxÈÕ
 *     Author: ROG
 */
#ifndef _BSP_UART_SBUS_H
#define _BSP_UART_SBUS_H

#include "uart2_sbus.h"


/* ********************************************************************************
 * UART2
 */
typedef struct
{
	uint8_t rx_count;
	uint8_t rx_buf[23];

} UART2_PAR;





void BSP_Uart2_SBUS_Init(void);
void BSP_Uart2_SBUS_Task(void);

#endif /*  */





