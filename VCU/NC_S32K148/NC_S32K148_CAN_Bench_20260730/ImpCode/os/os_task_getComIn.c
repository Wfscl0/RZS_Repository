/*
 * ********************************************************************************
 * os_task_getComIn.c
 *
 * Created on: 2024年12月x日
 *     Author: ROG
 */
#include "os_task_getComIn.h"
#include "bsp_uart_jy60.h"
#include <string.h>



JY60_PAR	jy60;
//定义本地控制全局变量
static HUART_PAR	*puart0_recv;
static HUART_PAR	*puart1_recv;
static HUART_PAR	huart0_recv;
static HUART_PAR	huart1_recv;

COMIN_PAR 	comIn;
static COMIN_PAR 	*pcomIn;

static void JY60_DataParsing(const uint8_t *IMU_Data, uint8_t length);

/* ********************************************************************************
 * 串口接收,任务线程
 */
void OS_Task_getComIn(void *pvPara)
{
	uint8_t copyLength;

	(void)pvPara;

	while(1)
	{
        //请求消息。UART0 IOT
		if(xQueueReceive(Que_Huart0_ComIn, &(puart0_recv), 0) == pdTRUE)
		{
			copyLength = puart0_recv->rx_count;
			if (copyLength > sizeof(huart0_recv.rx_buf))
			{
				copyLength = sizeof(huart0_recv.rx_buf);
			}
			huart0_recv.rx_count = copyLength;
			memcpy(huart0_recv.rx_buf, puart0_recv->rx_buf, copyLength);
			
			//调试回传
			//BSP_Uart0_IoT_Send(puart0_recv->rx_buf, (puart0_recv->rx_count+1));
		}
		
		//请求消息。UART1 JY60
		if(xQueueReceive(Que_Huart1_ComIn, &(puart1_recv), 0) == pdTRUE)
		{
			copyLength = puart1_recv->rx_count;
			if (copyLength > sizeof(huart1_recv.rx_buf))
			{
				copyLength = sizeof(huart1_recv.rx_buf);
			}
			huart1_recv.rx_count = copyLength;
			memcpy(huart1_recv.rx_buf, puart1_recv->rx_buf, copyLength);
			JY60_DataParsing(huart1_recv.rx_buf, huart1_recv.rx_count);
		}
		
		comIn.jy60.AXL = jy60.AXL;
		comIn.jy60.AYL = jy60.AYL;
		comIn.jy60.AZL = jy60.AZL;
		comIn.jy60.WXL = jy60.WXL;
		comIn.jy60.WYL = jy60.WYL;
		comIn.jy60.WZL = jy60.WZL;
		comIn.jy60.Roll = jy60.Roll;
		comIn.jy60.Pitch = jy60.Pitch;
		comIn.jy60.Yaw = jy60.Yaw;
		comIn.jy60.Temperature = jy60.Temperature;
		//向队列中，发送数据。发送一个指向结构体对象的指针
		pcomIn = &comIn;
		xQueueSend(Que_ComIn_CoreApp, (void *)&pcomIn, 0);

		//查看队列剩余大小
		if(queGlb.fsize == 1)
		{
			queGlb.size.que_huart0 = uxQueueSpacesAvailable(Que_Huart0_ComIn);
			queGlb.size.que_huart1 = uxQueueSpacesAvailable(Que_Huart1_ComIn);
			
		}
		
		PrgSts.task_ComIn++;
		vTaskDelay(pdMS_TO_TICKS(50U));
	}
}



/* ********************************************************************************
 * UART1 JY60数据解析
 */
static float Process_Data(uint8_t ByteL, uint8_t ByteH, float Gain)
{
	uint16_t raw = (uint16_t)ByteL | ((uint16_t)ByteH << 8);
	int16_t signedRaw = (int16_t)raw;
	return Gain * (float)signedRaw / 32768.0F;
}

static void JY60_DataParsing(const uint8_t *IMU_Data, uint8_t length)
{
	uint8_t i;
	uint8_t j;
	uint8_t sum;

	for (i = 0U; (uint16_t)i + 10U < length; i++)
	{
		if(IMU_Data[i] != 0x55)
		{
			continue;
		}
		// 0x53-三轴角度,0x52-三轴角速度，0x51-三轴加速度
		if ((IMU_Data[i] == 0x55) && (IMU_Data[i + 1] == 0x53))
		{
			sum = 0U;
			for (j = 0; j < 10; j++)
			{
				sum = sum + IMU_Data[i + j];
			}
			if (IMU_Data[i + 10] == sum)
			{
				jy60.Roll = Process_Data(IMU_Data[i + 2], IMU_Data[i + 3], 180.0F);
				jy60.Pitch = Process_Data(IMU_Data[i + 4], IMU_Data[i + 5], 180.0F);
				jy60.Yaw = Process_Data(IMU_Data[i + 6], IMU_Data[i + 7], 180.0F);
			}

            i += 10;
			continue;
		}
		else if ((IMU_Data[i] == 0x55) && (IMU_Data[i + 1] == 0x52))
		{
			sum = 0U;
			for (j = 0; j < 10; j++)
			{
				sum = sum + IMU_Data[i + j];
			}
			if (IMU_Data[i + 10] == sum)
			{
				jy60.WXL = Process_Data(IMU_Data[i + 2], IMU_Data[i + 3], 2000.0F);
				jy60.WYL = Process_Data(IMU_Data[i + 4], IMU_Data[i + 5], 2000.0F);
				jy60.WZL = Process_Data(IMU_Data[i + 6], IMU_Data[i + 7], 2000.0F);
			}

            i += 10;
			continue;
		}
		else if ((IMU_Data[i] == 0x55) && (IMU_Data[i + 1] == 0x51))
		{
			sum = 0U;
			for (j = 0; j < 10; j++)
			{
				sum = sum + IMU_Data[i + j];
			}
			if (IMU_Data[i + 10] == sum)
			{
				jy60.AXL = Process_Data(IMU_Data[i + 2], IMU_Data[i + 3], 16.0F * 9.8F);
				jy60.AYL = Process_Data(IMU_Data[i + 4], IMU_Data[i + 5], 16.0F * 9.8F);
				jy60.AZL = Process_Data(IMU_Data[i + 6], IMU_Data[i + 7], 16.0F * 9.8F);
				jy60.Temperature = Process_Data(IMU_Data[i + 8], IMU_Data[i + 9], 96.38F) + 36.53F;
			}

            i += 10;
			continue;
		}
	}
}

