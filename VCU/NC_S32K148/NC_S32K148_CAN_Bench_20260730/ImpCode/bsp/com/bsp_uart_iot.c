/*
 * ********************************************************************************
 *  UART0 232 115200
 *
 * Created on: 2024年12月x日
 *     Author: ROG
 */
#include "bsp_uart_iot.h"
#include "os_task.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>



static UART_PAR    Uart0;
static HUART_PAR	uart0_recv;
static HUART_PAR	*puart0_recv;

/* ********************************************************************************
 * UART0 232 115200
 */
/* UART rx callback for continuous reception, byte by byte */
void Uart0_Rx_Callback(void *driverState, uart_event_t event, void *userData)
{
	uint8_t  i;
	uint32_t bytesRemaining;
	status_t statusTTL;

	/* Unused parameters */
	(void)driverState;
	(void)userData;

	if(UART_GetReceiveStatus(&uart0_iot_instance, &bytesRemaining) != STATUS_BUSY)
	{
		statusTTL = UART_GetReceiveStatus(&uart0_iot_instance, &bytesRemaining); //串口数据接收成功
		if(statusTTL == STATUS_SUCCESS)
		{
			//数据缓存
			uart0_recv.rx_count = Uart0.rx_count;
			for(i=0; i<UART0_BUF_SIZE; i++)
			{
				uart0_recv.rx_buf[i] = Uart0.rx_buf[i];
			}
			
			//向队列中，发送数据。发送一个指向结构体对象的指针
			puart0_recv = &uart0_recv;
			xQueueSendFromISR(Que_Huart0_ComIn, (void *)&puart0_recv, 0);
			
			/* Reset the buffer index to start a new reception */
			memset(Uart0.rx_buf, 0, UART0_BUF_SIZE);
			Uart0.rx_count = 0U;
			/*完成操作后清除中断标志位并重新开始接收串口数据*/
			UART_ReceiveData(&uart0_iot_instance, Uart0.rx_buf, 1U);
		}
		else
		{
			//error handle
			UART_ReceiveData(&uart0_iot_instance, Uart0.rx_buf, 1U);
		}
	}

	/* Check the event type */
	if (event == UART_EVENT_RX_FULL)
	{
		/* The reception stops when newline is received or the buffer is full */
		if ((Uart0.rx_buf[Uart0.rx_count] != '\n') && (Uart0.rx_count != (UART0_BUF_SIZE - 2U)))
		{
			/* Update the buffer index and the rx buffer */
			Uart0.rx_count++;
			UART_SetRxBuffer(&uart0_iot_instance, &Uart0.rx_buf[Uart0.rx_count], 1U);
		}
	}
}



/* ********************************************************************************
 * UART0 232 初始化
 */
void BSP_Uart0_IoT_Init(void)
{
	UART_Init(&uart0_iot_instance, &uart0_iot_Config0);
	
	//外设默认优先级00！会导致操作系统内核函数无法调用，导致系统错误！！！
	//重新设置外设中断优先级。
	INT_SYS_SetPriority(LPUART0_RxTx_IRQn, 0x02);
	
	UART_ReceiveData(&uart0_iot_instance, &Uart0.rx_buf[0], 1U);
}

/* ********************************************************************************
 * UART0 232 数据发送
 */
void BSP_Uart0_IoT_Send(uint8_t *buf, uint8_t len)
{
	UART_SendData(&uart0_iot_instance, buf, len);
}

/* ********************************************************************************
 * BSP_Uart0_printf
 */
void BSP_Uart0_printf(char* fmt,...) //调试使用。谨慎使用！！！
{
	uint32_t bytesRemaining;
	char USART0_TX_BUF[100];

	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)USART0_TX_BUF,fmt,ap);
	va_end(ap);
	UART_SendData(&uart0_iot_instance, (uint8_t *)USART0_TX_BUF, strlen(USART0_TX_BUF)); //发送
	while (UART_GetTransmitStatus(&uart0_iot_instance, &bytesRemaining) != STATUS_SUCCESS) {}
}



