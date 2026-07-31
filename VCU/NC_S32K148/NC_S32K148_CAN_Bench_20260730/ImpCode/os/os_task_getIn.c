   /*
 * os_task_getIn.c
 *
 * Created on: 2024年3月x日
 *     Author: ROG
 */
#include "os_task_getIn.h"


//定义线程全局变量。缓存信号输入信息。
GETIN1_PAR 	getIn1;
GETIN2_PAR 	getIn2;
static GETIN1_PAR 	*pgetIn1;
static GETIN2_PAR 	*pgetIn2;

/* ********************************************************************************
 * OS_Task_getIn1 任务线程
 */
void OS_Task_getIn1(void *pvPara)
{
	(void)pvPara;

	while(1)
	{
        BSP_ADC0_Task(); //一次数据获取需要7个周期。
        BSP_ADS1115_Task(); //一次数据需要4个周期。一周期需要6ms
		
		//向队列中，发送数据。发送一个指向结构体对象的指针
		pgetIn1 = &getIn1;
		xQueueSend(Que_getIn1_CoreApp, (void *)&pgetIn1, 0);
		
		PrgSts.task_getIn1++;
		vTaskDelay(5);
	}
}


/* ********************************************************************************
 * OS_Task_getIn2 任务线程
 */
void OS_Task_getIn2(void *pvPara)
{
	(void)pvPara;

	while(1)
	{     
        BSP_Pin_In();
        BSP_ADSCH8_Task(); //需要时间：2*4*6 = 48ms
        BSP_MAX31865_Task(); //需要时间：18+18+30 = 66ms
		
		//向队列中，发送数据。发送一个指向结构体对象的指针
		pgetIn2 = &getIn2;
		xQueueSend(Que_getIn2_CoreApp, (void *)&pgetIn2, 0);
		
		PrgSts.task_getIn2++;
		vTaskDelay(100);
	}
}




