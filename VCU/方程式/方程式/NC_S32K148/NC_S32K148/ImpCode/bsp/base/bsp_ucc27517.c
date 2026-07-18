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

	//PWMOUT1	PA31	FTM5 CH6	10kHz	4800
	//PWMOUT2	PA15	FTM1 CH2	10kHz	4800
	//PWMOUT3	PA16	FTM1 CH3	10kHz	4800
	PWM_Init(&pwm1_ucc27Instance, &pwm1_ucc27Configs);
	PWM_Init(&pwm5Instance, &pwm5Configs);
	
	//PWM_UpdateDuty(&pwm1_ucc27Instance, 2, 4800); //PWMOUT2 50%
	//PWM_UpdateDuty(&pwm1_ucc27Instance, 3, 2400); //PWMOUT3 50%
	//PWM_UpdateDuty(&pwm5Instance, 6, 2400); //PWMOUT1 50%
}

void BSP_UCC27_Task(void)
{
    
}





