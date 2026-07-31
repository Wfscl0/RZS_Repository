/*
 * ********************************************************************************
 * Flexio UART 232 OR 485  波特率115200（注意：需要高于15000）
 * bsp_uart.c
 *
 * Created on: 2024年12月x日
 *     Author: ROG
 */
#include "bsp_uart.h"
#include <stdio.h>
#include <string.h>
#include "stdarg.h"
#include <stdint.h>
#include <stdbool.h>
#include "task.h"



static FLEXIO_UART_PAR 	  	Uart;
static flexio_uart_state_t   	uartStateTX;
static flexio_uart_state_t   	uartStateRX;
static flexio_device_state_t 	flexIODeviceState; //需设置为全局变量

uint8_t   rx1_len;
uint8_t   rx1_buf[BUFFER_SIZE];

/* ********************************************************************************
 * Flexio UART 232 OR 485  波特率115200
 */
void Flexio_Uart_Rx_Callback(void *driverState, uart_event_t event, void *userData)
{
    (void)userData;
    (void)driverState;

    if(event == UART_EVENT_RX_FULL)
    {
    	//调试，串口协议以0xaa 0xbb开始，换行结束
    	//aa bb 3F 32 33 3F 0D 0A
    	//3F 32 33 3F 0D 0A
    	if(Uart.rx_count >= 1)
    	{
			if(Uart.rx_buf[Uart.rx_count-1]==0xaa && Uart.rx_buf[Uart.rx_count]==0xbb)
			{
				Uart.rx_count = BUFFER_SIZE-1;
			}

			if(Uart.rx_buf[Uart.rx_count-1]==0x0d && Uart.rx_buf[Uart.rx_count]==0x0a)
			{
				memset(rx1_buf, 0, BUFFER_SIZE);
				rx1_len = Uart.rx_count;
				memcpy(rx1_buf, &Uart.rx_buf[0], rx1_len);
				//FLEXIO_UART_DRV_SendData(&uartStateTX, rx1_buf, rx1_len);
			}
    	}

    	/* Advance write pointer to the next location in Rx buffer */
		if (Uart.rx_count == (BUFFER_SIZE-1))
		{
			Uart.rx_count = 0;
		}
        else
        {
            Uart.rx_count++;
        }

        /* Set new RX buffer */
        FLEXIO_UART_DRV_SetRxBuffer(&uartStateRX, &(Uart.rx_buf[Uart.rx_count]), 1UL);
    }
}

void Flexio_Uart_Tx_Callback(void *driverState, uart_event_t event, void *userData)
{
    (void)userData;
    (void)driverState;

    if(event == UART_EVENT_TX_EMPTY){}
}



/* ********************************************************************************
 * Flexio UART 初始化
 */
void BSP_Uart_Init(void)
{
	/* Init the FLEXIO device */
	FLEXIO_DRV_InitDevice(INST_FLEXIO_UART_TX, &flexIODeviceState);
	FLEXIO_UART_DRV_Init(INST_FLEXIO_UART_TX, &flexio_uart_tx_Config0, &uartStateTX);
	FLEXIO_UART_DRV_Init(INST_FLEXIO_UART_RX, &flexio_uart_rx_Config0, &uartStateRX);

	FLEXIO_UART_DRV_ReceiveData(&uartStateRX, Uart.rx_buf, 1U);
}

/* ********************************************************************************
 * 接收缓存，并回传
 */
void BSP_Uart_RxBack(void)
{
	uint8_t txBuffer; /* 1-byte buffer for Tx */

	//接收缓存，并回传。  /* Wait for tx to be idle */
	if(FLEXIO_UART_DRV_GetStatus(&uartStateTX, NULL) == STATUS_SUCCESS)
	{
		if(Uart.rx_count != Uart.tx_count)
		{
			/* Copy received byte to tx buffer */
			txBuffer = Uart.rx_buf[Uart.tx_count];
			/* Advance read pointer to the next location in Rx buffer */
			Uart.tx_count++;
			if(Uart.tx_count == BUFFER_SIZE)
			{
				Uart.tx_count = 0;
			}
			/* Send received byte */
			FLEXIO_UART_DRV_SendData(&uartStateTX, &txBuffer, 1U);
		}
	}
}

/* ********************************************************************************
 * BSP_Uart_printf
 */
void BSP_Uart_printf(char* fmt,...)
{
	char USART_TX_BUF[512];

	va_list ap;
	va_start(ap, fmt);
	vsprintf((char*)USART_TX_BUF, fmt, ap);
	va_end(ap);
	FLEXIO_UART_DRV_SendData(&uartStateTX, (uint8_t *)USART_TX_BUF, strlen(USART_TX_BUF));

	//需要延迟，否则可能造成异常！
	vTaskDelay(5); //所以，不能放在中断中！
}



