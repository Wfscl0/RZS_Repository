/*
 * os_task_VcuCtrl.c
 *
 * Created on: 2024年3月x日
 *     Author: ROG
 */
#include "os_task_VcuCtrl.h"
#include "userif.h"



static HVCUCTRL_PAR	*pvcuCtrl;
HVCUCTRL_PAR		hvcuCtrl;

TaskHandle_t Task_taskInfo_Handler;



void OS_Task_VcuCtrl(void *pvPara)
{
	(void)pvPara;
	static uint8_t uln_out=0,mc3_outl=0,mc3_outh=0;

	while(1)
	{  
		//请求消息。hvcuCtrl
		if(xQueueReceive(Que_Hcore_VcuCtrl, &(pvcuCtrl), 0) == pdTRUE)
		{
			uln_out = pvcuCtrl->uln_out;
			mc3_outl = pvcuCtrl->mc3_outl;
			mc3_outh = pvcuCtrl->mc3_outh;
		}
		
		if(uln_out != hvcuCtrl.uln_out){
			hvcuCtrl.uln_out = uln_out;
			BSP_Pin_Out(hvcuCtrl.uln_out);
		}
		if(mc3_outl!=hvcuCtrl.mc3_outl || mc3_outh!=hvcuCtrl.mc3_outh){
			hvcuCtrl.mc3_outl = mc3_outl;
			hvcuCtrl.mc3_outh = mc3_outh;
			BSP_MC33879_Task(hvcuCtrl.mc3_outl, hvcuCtrl.mc3_outh); //需要时间：4ms
		}

		BSP_TLF35584_Task();
		BSP_AT24C_Task(); //需要时间。写入：DatLen*8ms  读取：DatLen*6 ms
		BSP_UCC27_Task();
        BSP_Flash_Task(); //测试Flash函数
        BSP_Bootld_Task();
		
		LED_D12; //SYSLED D12
		PrgSts.task_VcuCtrl++;
		vTaskDelay(200);
	}
}
