/*
 * ********************************************************************************
 * VCU 输入、输出控制。INPUT HIN1-HIN14、LIN1-LIN6、OUT1-OUT7
 * bsp_pin.c
 *
 * Created on: 2024年3月x日
 *     Author: ROG
 */
#include "bsp_pin.h"
#include "os_task.h"




/* ********************************************************************************
 * VCU PIN初始化
 * 
 */
void BSP_Pin_Init(void)
{
	PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr);
	LED_D12_ON;
	LED_D16_OFF;

	EN5VV_ON;
	EN_OFF; RST_OFF;
}

/* ********************************************************************************
 * VCU 输入信号读取。
 * INPUT HIN1-HIN14	LIN1-LIN6
 */
//读取全部LIN信号。以数据位返回，0x01表示LIN1为1，其他为0
static uint8_t Read_Pin_LIN(void)
{
	uint8_t lin=0;

	if(LIN1_Read)	{ lin |= 1<<0; }
	else			{ lin &= ~(1U<<0); }

	if(LIN2_Read)	{ lin |= 1<<1; }
	else			{ lin &= ~(1U<<1); }

	if(LIN3_Read)	{ lin |= 1<<2; }
	else			{ lin &= ~(1U<<2); }

	if(LIN4_Read)	{ lin |= 1<<3; }
	else			{ lin &= ~(1U<<3); }

	if(LIN5_Read)	{ lin |= 1<<4; }
	else			{ lin &= ~(1U<<4); }

	if(LIN6_Read)	{ lin |= 1<<5; }
	else			{ lin &= ~(1U<<5); }

	return lin;
}

//读取全部HIN信号。以数据位返回，0x01表示HIN1为1，其他为0
static uint16_t Read_Pin_HIN(void)
{
	uint16_t hin=0;

	if(HIN1_Read)	{ hin |= 1<<0; }
	else		 	{ hin &= ~(1U<<0); }

	if(HIN2_Read)	{ hin |= 1<<1; }
	else		 	{ hin &= ~(1U<<1); }

	if(HIN3_Read)	{ hin |= 1<<2; }
	else		 	{ hin &= ~(1U<<2); }

	if(HIN4_Read)	{ hin |= 1<<3; }
	else		 	{ hin &= ~(1U<<3); }

	if(HIN5_Read)	{ hin |= 1<<4; }
	else		 	{ hin &= ~(1U<<4); }

	if(HIN6_Read)	{ hin |= 1<<5; }
	else		 	{ hin &= ~(1U<<5); }

	if(HIN7_Read)	{ hin |= 1<<6; }
	else		 	{ hin &= ~(1U<<6); }

	if(HIN8_Read)	{ hin |= 1<<7; }
	else		 	{ hin &= ~(1U<<7); }

	if(HIN9_Read)	{ hin |= 1<<8; }
	else		 	{ hin &= ~(1U<<8); }

	if(HIN10_Read)	{ hin |= 1<<9; }
	else		 	{ hin &= ~(1U<<9); }

	if(HIN11_Read)	{ hin |= 1<<10; }
	else		 	{ hin &= ~(1U<<10); }

	if(HIN12_Read)	{ hin |= 1<<11; }
	else		 	{ hin &= ~(1U<<11); }

	if(HIN13_Read)	{ hin |= 1<<12; }
	else		 	{ hin &= ~(1U<<12); }

	if(HIN14_Read)	{ hin |= 1<<13; }
	else		 	{ hin &= ~(1U<<13); }

	return hin;
}

/* Critical HIN signals are sampled directly by CoreApp every 10 ms. The
 * slower getIn2 task remains responsible for auxiliary ADC/temperature data. */
uint16_t BSP_Pin_GetHIN(void)
{
	return Read_Pin_HIN();
}

/* ********************************************************************************
 * 输出控制。
 * OUTPUT	OUT1-OUT7
 */
static void Write_Pin_Out(uint8_t out)
{
	if(out & 0x01) 	{ OUT1_ON; }
	else			{ OUT1_OFF; }

	if(out & 0x02) 	{ OUT2_ON; }
	else			{ OUT2_OFF; }

	if(out & 0x04) 	{ OUT3_ON; }
	else			{ OUT3_OFF; }

	if(out & 0x08) 	{ OUT4_ON; }
	else			{ OUT4_OFF; }

	if(out & 0x10) 	{ OUT5_ON; }
	else			{ OUT5_OFF; }

	if(out & 0x20) 	{ OUT6_ON; }
	else			{ OUT6_OFF; }

	if(out & 0x40) 	{ OUT7_ON; }
	else			{ OUT7_OFF; }
}



/* ********************************************************************************
 * BSP_Pin_In
 * 
 */
void BSP_Pin_In(void)
{
	getIn2.lin = Read_Pin_LIN();
	getIn2.hin = Read_Pin_HIN();
}

/* ********************************************************************************
 * BSP_Pin_Out
 * 
 */
void BSP_Pin_Out(uint8_t out)
{
	Write_Pin_Out(out);
}

/* ********************************************************************************
 * BSP_Pin_NetPWR
 * 
 */
void BSP_Pin_NetPWR(uint8_t state)
{
	if(state == 1){
		NET_PWRON; //网关电源开
	}
	else{
		NET_PWROFF; //网关电源关
	}
}




