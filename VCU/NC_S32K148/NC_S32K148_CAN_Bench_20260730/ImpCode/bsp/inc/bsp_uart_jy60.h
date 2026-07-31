/*
 * bsp_uart_jy60.h
 *
 * Created on: 2024年3月x日
 *     Author: ROG
 */
#ifndef _BSP_UART_JY60_H
#define _BSP_UART_JY60_H

#include "uart1_jy60.h"


/* ********************************************************************************
 * UART1
 */
#define UART1_BUF_SIZE 36UL

typedef struct
{
	uint8_t rx_count;
	uint8_t rx_buf[UART1_BUF_SIZE];

	uint8_t tx_len;
	uint8_t txbuf[UART1_BUF_SIZE];

} UART1_PAR;





void BSP_Uart1_JY60_Init(void);
void BSP_Uart1_JY60_Task(void);
void BSP_Uart1_JY60_Receive(void);

#endif /*  */





