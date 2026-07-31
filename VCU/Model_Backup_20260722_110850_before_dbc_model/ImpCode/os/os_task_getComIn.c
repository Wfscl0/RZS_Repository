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

static void JY60_DataParsing(uint8_t *IMU_Data);

/* ********************************************************************************
 * 串口接收,任务线程
 */
void OS_Task_getComIn(void *pvPara)
{

	(void)pvPara;

	while(1)
	{
        //请求消息。UART0 IOT
		if(xQueueReceive(Que_Huart0_ComIn, &(puart0_recv), 0) == pdTRUE)
		{
			huart0_recv.rx_count = puart0_recv->rx_count;
			memcpy(huart0_recv.rx_buf, puart0_recv->rx_buf, 64);
			
			//调试回传
			//BSP_Uart0_IoT_Send(puart0_recv->rx_buf, (puart0_recv->rx_count+1));
		}
		
		//请求消息。UART1 JY60
		if(xQueueReceive(Que_Huart1_ComIn, &(puart1_recv), 0) == pdTRUE)
		{
			huart1_recv.rx_count = puart1_recv->rx_count;
			memcpy(huart1_recv.rx_buf, puart1_recv->rx_buf, 64);
			/*重新开始接收串口数据*/
			BSP_Uart1_JY60_Receive();
		}

		//JY60数据解析
		JY60_DataParsing(huart1_recv.rx_buf);
		
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
		vTaskDelay(500);
	}
}



/* ********************************************************************************
 * UART1 JY60数据解析
 */
float Process_Data(float ByteL,float ByteH,float Gain)
{
	float Temp = ByteL+ByteH*256;
	if (Temp>32767) {Temp = Temp - 65535;}
	return Gain*Temp/32768;
}

void JY60_DataParsing(uint8_t *IMU_Data)
{
	uint8_t  i,j,sum=0;

	for (i = 0; i<UART1_BUF_SIZE; i++)
	{
		if(IMU_Data[i] != 0x55)
		{
			continue;
		}
		// 0x53-三轴角度,0x52-三轴角速度，0x51-三轴加速度
		if ((IMU_Data[i] == 0x55) && (IMU_Data[i + 1] == 0x53))
		{
			for (j = 0; j < 10; j++)
			{
				sum = sum + IMU_Data[i + j];
			}
			if (IMU_Data[i + 10] == sum)
			{
				jy60.Roll = Process_Data((float)IMU_Data[i + 2],(float)IMU_Data[i + 3],180);
				jy60.Pitch = Process_Data((float)IMU_Data[i + 4],(float)IMU_Data[i + 5],180);
				jy60.Yaw = Process_Data((float)IMU_Data[i + 6],(float)IMU_Data[i + 7],180);
			}

            i += 10;
			continue;
		}
		else if ((IMU_Data[i] == 0x55) && (IMU_Data[i + 1] == 0x52))
		{
			for (j = 0; j < 10; j++)
			{
				sum = sum + IMU_Data[i + j];
			}
			if (IMU_Data[i + 10] == sum)
			{
				jy60.WXL = Process_Data((float)IMU_Data[i + 2],(float)IMU_Data[i + 3],2000);
				jy60.WYL = Process_Data((float)IMU_Data[i + 4],(float)IMU_Data[i + 5],2000);
				jy60.WZL = Process_Data((float)IMU_Data[i + 6],(float)IMU_Data[i + 7],2000);
			}

            i += 10;
			continue;
		}
		else if ((IMU_Data[i] == 0x55) && (IMU_Data[i + 1] == 0x51))
		{
			for (j = 0; j < 10; j++)
			{
				sum = sum + IMU_Data[i + j];
			}
			if (IMU_Data[i + 10] == sum)
			{
				jy60.AXL = Process_Data((float)IMU_Data[i + 2],(float)IMU_Data[i + 3],16*9.8);
				jy60.AYL = Process_Data((float)IMU_Data[i + 4],(float)IMU_Data[i + 5],16*9.8);
				jy60.AZL = Process_Data((float)IMU_Data[i + 6],(float)IMU_Data[i + 7],16*9.8);
				jy60.Temperature = Process_Data((float)IMU_Data[i + 8],(float)IMU_Data[i + 9],96.38) + 36.53;
			}

            i += 10;
			continue;
		}
	}
}

