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
	static uint8_t uln_out=0,mc3_outl=0,mc3_outh=0,ebs_watchdog_out=0;
	uint8_t maintenanceDivider = 0U;
	TickType_t lastWakeTime = xTaskGetTickCount();

	while(1)
	{  
		//请求消息。hvcuCtrl
		if(xQueueReceive(Que_Hcore_VcuCtrl, &(pvcuCtrl), 0) == pdTRUE)
		{
			uln_out = pvcuCtrl->uln_out;
			mc3_outl = pvcuCtrl->mc3_outl;
			mc3_outh = pvcuCtrl->mc3_outh;
			ebs_watchdog_out = pvcuCtrl->ebs_watchdog;
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
		if(ebs_watchdog_out != hvcuCtrl.ebs_watchdog){
			hvcuCtrl.ebs_watchdog = ebs_watchdog_out;
			BSP_UCC27_SetEBSWatchdog(hvcuCtrl.ebs_watchdog);
		}

		/* Output changes are handled every 10 ms. Slow housekeeping remains at
		 * 200 ms and therefore does not change the existing task architecture. */
		maintenanceDivider++;
		if(maintenanceDivider >= 20U)
		{
			maintenanceDivider = 0U;
			BSP_TLF35584_Task();
			BSP_AT24C_Task();
			BSP_UCC27_Task();
            BSP_Flash_Task();
            BSP_Bootld_Task();
			LED_D12; //SYSLED D12
		}
		
		PrgSts.task_VcuCtrl++;
		vTaskDelayUntil(&lastWakeTime, 10U);
	}
}
