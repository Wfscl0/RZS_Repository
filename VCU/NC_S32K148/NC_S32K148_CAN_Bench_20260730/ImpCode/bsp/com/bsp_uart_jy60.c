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




#define JY60_BATCH_SIZE       33U
#define JY60_RX_SNAPSHOT_NUM   4U

static UART1_PAR Uart1;
static HUART_PAR uart1_recv[JY60_RX_SNAPSHOT_NUM];
static uint8_t uart1_write_index;

/* ********************************************************************************
 * UART1 UART	9600
 */
/* UART rx callback for continuous reception, byte by byte */
void Uart1_Rx_Callback(void *driverState, uart_event_t event, void *userData)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	HUART_PAR *puart1_recv;

	/* Unused parameters */
	(void)driverState;
	(void)userData;

	if (event != UART_EVENT_RX_FULL)
	{
		return;
	}

	PrgSts.jy60_isr++;

	/* JY60每帧11字节；首字节必须为0x55，失步时在此重新同步。 */
	if ((Uart1.rx_count == 0U) && (Uart1.rx_buf[0] != 0x55U))
	{
		(void)UART_SetRxBuffer(&uart1_jy60_instance, &Uart1.rx_buf[0], 1U);
		return;
	}

	Uart1.rx_count++;
	if (Uart1.rx_count >= JY60_BATCH_SIZE)
	{
		/* 队列深度为3，使用4个快照，避免任务取出指针时ISR覆盖同一块数据。 */
		if (uxQueueMessagesWaitingFromISR(Que_Huart1_ComIn) < 3U)
		{
			uart1_recv[uart1_write_index].rx_count = JY60_BATCH_SIZE;
			memcpy(uart1_recv[uart1_write_index].rx_buf,
				Uart1.rx_buf, JY60_BATCH_SIZE);
			puart1_recv = &uart1_recv[uart1_write_index];
			if (xQueueSendFromISR(Que_Huart1_ComIn, &puart1_recv,
				&xHigherPriorityTaskWoken) == pdTRUE)
			{
				uart1_write_index++;
				if (uart1_write_index >= JY60_RX_SNAPSHOT_NUM)
				{
					uart1_write_index = 0U;
				}
			}
		}
		Uart1.rx_count = 0U;
	}

	(void)UART_SetRxBuffer(&uart1_jy60_instance,
		&Uart1.rx_buf[Uart1.rx_count], 1U);
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
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
	uint32_t bytesRemaining;

	/* 仅用于异常恢复；正常接收由回调逐字节续接。 */
	if (UART_GetReceiveStatus(&uart1_jy60_instance, &bytesRemaining) != STATUS_BUSY)
	{
		(void)UART_ReceiveData(&uart1_jy60_instance,
			&Uart1.rx_buf[Uart1.rx_count], 1U);
	}
}


