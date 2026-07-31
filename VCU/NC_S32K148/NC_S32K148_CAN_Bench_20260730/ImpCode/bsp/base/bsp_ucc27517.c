/*
 * bsp_ucc27517.c
 *
 * Created on: 2024年3月x日
 *     Author: ROG
 */
#include "bsp_ucc27517.h"



/* ********************************************************************************
 * 比例电磁阀	PWMOUT1-PWMOUT3
 */

void BSP_UCC27_Init(void)
{

	//PWMOUT1	PA31	FTM5 CH6	10kHz（外部EBS看门狗，初始关闭）
	//PWMOUT2	PA15	FTM1 CH2	10kHz	4800
	//PWMOUT3	PA16	FTM1 CH3	10kHz	4800
	PWM_Init(&pwm1_ucc27Instance, &pwm1_ucc27Configs);
	PWM_Init(&pwm5Instance, &pwm5Configs);
	
	//PWM_UpdateDuty(&pwm1_ucc27Instance, 2, 4800); //PWMOUT2 50%
	//PWM_UpdateDuty(&pwm1_ucc27Instance, 3, 2400); //PWMOUT3 50%
	//PWMOUT1由模型ebs_watchdog信号控制，启用时输出50%占空比。
}

void BSP_UCC27_SetEBSWatchdog(uint8_t enable)
{
	/* 10 kHz载波由FTM硬件产生，任务只切换0%/50%，不会引入周期抖动。 */
	(void)PWM_UpdateDuty(&pwm5Instance, 6U, (enable != 0U) ? 2400U : 0U);
}

void BSP_UCC27_Task(void)
{
    
}





