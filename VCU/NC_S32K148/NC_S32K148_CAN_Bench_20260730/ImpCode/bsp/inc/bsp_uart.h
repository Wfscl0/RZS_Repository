/*
 * bsp_uart.h
 *
 * Created on: 2024年3月x日
 *     Author: ROG
 */
#ifndef _BSP_UART_H
#define _BSP_UART_H

#include "flexio_uart_tx.h"
#include "flexio_uart_rx.h"


/* ********************************************************************************
 * Flexio UART 232 OR 485
 */
#define BUFFER_SIZE 32

typedef struct
{
	uint8_t rx_count;
	uint8_t rx_buf[BUFFER_SIZE];

	uint8_t tx_count;
	uint8_t tx_len;
	uint8_t txbuf[BUFFER_SIZE];

} FLEXIO_UART_PAR;

extern uint8_t rx1_len;
extern uint8_t rx1_buf[BUFFER_SIZE];




void BSP_Uart_Init(void);
void BSP_Uart_RxBack(void);
void BSP_Uart_printf(char* fmt,...);

#endif /*  */





