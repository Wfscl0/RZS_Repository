/*
 * ********************************************************************************
 *  UART2 UART	100000
 *  bsp_uart_sbus.c
 *
 * Created on: 2025年10月x日
 *     Author: ROG
 */
#include "bsp_uart_sbus.h"
#include "os_task.h"
#include <string.h>



static uint8_t 		RxBuffer; //接收中断缓冲
static uint8_t 		sbus_start;
static uint8_t  	sbus_cnt;
static uint8_t  	sbus_buf[25];
static UART2_PAR   	uart2_recv1;
static UART2_PAR   	*puart2_recv1;

/* ********************************************************************************
 * UART2 UART	100000
 */
/* UART rx callback for continuous reception, byte by byte */
void Uart2_Rx_Callback(void *driverState, uart_event_t event, void *userData)
{
	uint32_t bytesRemaining;
	status_t statusTTL;
	uint8_t  i;

	/* Unused parameters */
	(void)driverState;
	(void)userData;

	if(UART_GetReceiveStatus(&uart2_sbus_instance, &bytesRemaining) != STATUS_BUSY)
	{
		statusTTL = UART_GetReceiveStatus(&uart2_sbus_instance, &bytesRemaining); //串口数据接收成功
		if(statusTTL == STATUS_SUCCESS) {
			/*完成操作后清除中断标志位并重新开始接收串口数据*/
			UART_ReceiveData(&uart2_sbus_instance, &RxBuffer, 1U);
		}
		else {
			//error handle
			UART_ReceiveData(&uart2_sbus_instance, &RxBuffer, 1U);
		}
	}

	/* Check the event type */
	if (event == UART_EVENT_RX_FULL)
	{
		/* The reception stops when newline is received or the buffer is full */
		if(sbus_start==0 && RxBuffer==0x0F) {//数据头
			sbus_start = 1;
			sbus_cnt = 0;
			sbus_buf[sbus_cnt] = RxBuffer;
		}
		else if(sbus_start == 1){ //SBUS数据缓存
			sbus_cnt++;
			sbus_buf[sbus_cnt] = RxBuffer;

			if(sbus_cnt >= 24){
				sbus_start = 0;
				if(sbus_buf[24] == 0x00) //数据尾
				{
					//数据缓存
					uart2_recv1.rx_count++;
					taskENTER_CRITICAL();
					for(i=0; i<23; i++)
					{
						uart2_recv1.rx_buf[i] = sbus_buf[i+1];
					}
					taskEXIT_CRITICAL();

					//向队列中，发送数据。发送一个指向结构体对象的指针
					puart2_recv1 = &uart2_recv1;

					//队列操作
					BaseType_t xHigherPriorityTaskWoken = pdFALSE;
					xQueueSendFromISR(Que_Huart2_CoreApp, &puart2_recv1, &xHigherPriorityTaskWoken);
					portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
				}
			}
		}

		UART_SetRxBuffer(&uart2_sbus_instance, &RxBuffer, 1U);
	}

}


/* ********************************************************************************
 * UART1 UART	初始化
 */
void BSP_Uart2_SBUS_Init(void)
{
	UART_Init(&uart2_sbus_instance, &uart2_sbus_Config0);
	
	//外设默认优先级00！会导致操作系统内核函数无法调用，导致系统错误！！！
	//重新设置外设中断优先级。
	INT_SYS_SetPriority(LPUART2_RxTx_IRQn, 0x02);
	
	UART_ReceiveData(&uart2_sbus_instance, &RxBuffer, 1U);
}








