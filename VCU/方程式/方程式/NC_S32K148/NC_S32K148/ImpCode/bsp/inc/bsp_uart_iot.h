/*
 * bsp_uart_iot.h
 *
 * Created on: 2024年3月x日
 *     Author: ROG
 */
#ifndef _BSP_UART_IOT_H
#define _BSP_UART_IOT_H

#include "uart0_iot.h"


/* ********************************************************************************
 * UART0
 */
#define UART0_BUF_SIZE 64UL

typedef struct
{
	uint8_t rx_count;
	uint8_t rx_buf[UART0_BUF_SIZE];

	uint8_t tx_len;
	uint8_t txbuf[UART0_BUF_SIZE];

} UART_PAR;




void BSP_Uart0_IoT_Init(void);
void BSP_Uart0_IoT_Send(uint8_t *buf, uint8_t len);

void BSP_Uart0_printf(char* fmt,...); //调试使用

#endif /*  */





