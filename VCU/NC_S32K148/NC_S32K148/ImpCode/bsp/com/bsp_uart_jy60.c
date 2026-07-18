/*
 * ********************************************************************************
 *  UART1 UART	9600
 *  bsp_uart_jy60.c
 *
 * Created on: 2024年12月x日
 *     Author: ROG
 */
#include "bsp_uart_jy60.h"
#include "os_task.h"
#include <string.h>




static UART1_PAR   Uart1;
static HUART_PAR	uart1_recv;
static HUART_PAR	*puart1_recv;

/* ********************************************************************************
 * UART1 UART	9600
 */
/* UART rx callback for continuous reception, byte by byte */
void Uart1_Rx_Callback(void *driverState, uart_event_t event, void *userData)
{
	uint32_t bytesRemaining;
	status_t statusTTL;
	uint8_t  i;

	/* Unused parameters */
	(void)driverState;
	(void)userData;

	if(UART_GetReceiveStatus(&uart1_jy60_instance, &bytesRemaining) != STATUS_BUSY)
	{
		statusTTL = UART_GetReceiveStatus(&uart1_jy60_instance, &bytesRemaining); //串口数据接收成功
		if(statusTTL == STATUS_SUCCESS)
		{
			//数据缓存
			uart1_recv.rx_count = Uart1.rx_count;
			taskENTER_CRITICAL();
			for(i=0; i<UART1_BUF_SIZE; i++)
			{
				uart1_recv.rx_buf[i] = Uart1.rx_buf[i];
			}
			taskEXIT_CRITICAL();
			
			//向队列中，发送数据。发送一个指向结构体对象的指针
			puart1_recv = &uart1_recv;

			//队列操作
			BaseType_t xHigherPriorityTaskWoken = pdFALSE;
			xQueueSendFromISR(Que_Huart1_ComIn, &puart1_recv, &xHigherPriorityTaskWoken);
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
			
			PrgSts.jy60_isr++;
			/* Reset the buffer index to start a new reception */
			memset(Uart1.rx_buf, 0, UART1_BUF_SIZE);
			Uart1.rx_count = 0U;
			/*完成操作后清除中断标志位并重新开始接收串口数据*/
			//UART_ReceiveData(&uart1_jy60_instance, Uart1.rx_buf, 1U);
		}
		else
		{
			//error handle
			UART_ReceiveData(&uart1_jy60_instance, Uart1.rx_buf, 1U);
		}
	}

	/* Check the event type */
	if (event == UART_EVENT_RX_FULL)
	{
		/* The reception stops when newline is received or the buffer is full */
		if ((Uart1.rx_buf[Uart1.rx_count] != '\n') && (Uart1.rx_count != (UART1_BUF_SIZE - 2U)))
		{
			/* Update the buffer index and the rx buffer */
			Uart1.rx_count++;
			UART_SetRxBuffer(&uart1_jy60_instance, &Uart1.rx_buf[Uart1.rx_count], 1U);
		}
	}

}


/* ********************************************************************************
 * UART1 UART	初始化
 */
void BSP_Uart1_JY60_Init(void)
{
	UART_Init(&uart1_jy60_instance, &uart1_jy60_Config0);
	
	//外设默认优先级00！会导致操作系统内核函数无法调用，导致系统错误！！！
	//重新设置外设中断优先级。
	INT_SYS_SetPriority(LPUART1_RxTx_IRQn, 0x08);
	
	UART_ReceiveData(&uart1_jy60_instance, &Uart1.rx_buf[0], 1U);
}

void BSP_Uart1_JY60_Receive(void)
{
	/*重新开始接收串口数据*/
	UART_ReceiveData(&uart1_jy60_instance, Uart1.rx_buf, 1U);
}


