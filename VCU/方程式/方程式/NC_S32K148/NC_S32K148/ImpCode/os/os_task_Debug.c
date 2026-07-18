/*
 * os_task_Debug.c
 *
 * Created on: 2025年4月x日
 *     Author: ROG
 */
#include "os_task_Debug.h"
#include "os_task.h"
#include <stdio.h>


void Debug_Show_Value(void);

/* ********************************************************************************
 * OS_Task_Debug 任务线程
 */
void OS_Task_Debug(void *pvPara)
{
	uint8_t debug=1;
	(void)pvPara;

	while(1)
	{
		if(debug){
			Debug_Show_Value();
		}

		PrgSts.task_Debug++;
		vTaskDelay(1000);
	}
}



void Debug_Show_Value(void)
{
	uint8_t buff[1000];
	uint16_t size=0;

	//打印硬件输入
	sprintf(&buff[0], "Hin:%d Lin:%d \r\n", getIn2.hin, getIn2.lin);
	size = strlen(buff); //缓存大小

	sprintf(&buff[size], "AI1:%d AI2:%d AI3:%d AI4:%d AI5:%d AI6:%d AI7:%d AI8:%d\r\n", getIn2.adsch8[0], getIn2.adsch8[1],
			getIn2.adsch8[2], getIn2.adsch8[3], getIn2.adsch8[4], getIn2.adsch8[5], getIn2.adsch8[6], getIn2.adsch8[7]);
	size = strlen(buff); //缓存大小

	sprintf(&buff[size], "AIN0:%d AIN1:%d AIN2:%d AIN3:%d\r\n", getIn1.ads115_value[0], getIn1.ads115_value[1],
			getIn1.ads115_value[2], getIn1.ads115_value[3]);
	size = strlen(buff); //缓存大小

	sprintf(&buff[size], "AIN4:%d AIN5:%d AIN6:%d AIN7:%d 5vv:%d 12v:%d\r\n", getIn1.adc0_value[0], getIn1.adc0_value[1],
						getIn1.adc0_value[2], getIn1.adc0_value[3], getIn1.adc0_value[4], getIn1.adc0_value[5]);
	size = strlen(buff); //缓存大小

	//打印硬件输出
	sprintf(&buff[size], "uln_out:%d mc3_outl:%d mc3_outh:%d\r\n", hvcuCtrl.uln_out, hvcuCtrl.mc3_outl, hvcuCtrl.mc3_outh);
	size = strlen(buff); //缓存大小

	//打印调试过程变量

	sprintf(&buff[size], "%s:%d\r\n", "size", size); //显示最大缓存数
	BSP_Uart_printf(buff);
}

