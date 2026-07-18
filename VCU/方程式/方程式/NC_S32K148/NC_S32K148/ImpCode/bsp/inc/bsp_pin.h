/*
 * bsp_pin.h
 *
 * Created on: 2024年3月x日
 *     Author: ROG
 */
#ifndef _BSP_PIN_H
#define _BSP_PIN_H

#include "pin_mux.h"



/* ********************************************************************************
 * LED
 */
#define LED_D12  		PINS_DRV_TogglePins(PTD, 1<<0)	//PD0 	D12
#define LED_D12_ON		PINS_DRV_ClearPins(PTD, 1<<0)
#define LED_D12_OFF		PINS_DRV_SetPins(PTD, 1<<0)
#define LED_D16  		PINS_DRV_TogglePins(PTD, 1<<1)	//PD1 	D16
#define LED_D16_ON		PINS_DRV_ClearPins(PTD, 1<<1)
#define LED_D16_OFF		PINS_DRV_SetPins(PTD, 1<<1)


/* ********************************************************************************
 * +5VV EN引脚
 */
#define EN5VV_ON	PINS_DRV_WritePin(PTD, 24, 0)
#define EN5VV_OFF	PINS_DRV_WritePin(PTD, 24, 1) //PD24

/* ********************************************************************************
 * 网关电源使能引脚
 */
#define NET_PWRON	PINS_DRV_WritePin(PTD, 27, 0)
#define NET_PWROFF	PINS_DRV_WritePin(PTD, 27, 1) //PD27

/* ********************************************************************************
 * 电平转换引脚  EN RST
 */
#define EN_ON		PINS_DRV_WritePin(PTD, 19, 1)
#define EN_OFF		PINS_DRV_WritePin(PTD, 19, 0) //PD19
#define RST_ON		PINS_DRV_WritePin(PTD, 18, 1)
#define RST_OFF		PINS_DRV_WritePin(PTD, 18, 0) //PD18


/* ********************************************************************************
 * INPUT: HIN1-HIN14
 */
#define HIN1_Read 	(!((PINS_DRV_ReadPins(PTE) >> 12) & 0x01)) //PE12
#define HIN2_Read 	(!((PINS_DRV_ReadPins(PTE) >> 14) & 0x01)) //PE14
#define HIN3_Read 	(!((PINS_DRV_ReadPins(PTE) >> 13) & 0x01)) //PE13
#define HIN4_Read 	(!((PINS_DRV_ReadPins(PTE) >> 10) & 0x01)) //PE10
#define HIN5_Read 	(!((PINS_DRV_ReadPins(PTE) >> 11) & 0x01)) //PE11
#define HIN6_Read 	(!((PINS_DRV_ReadPins(PTE) >> 15) & 0x01)) //PE15
#define HIN7_Read 	(!((PINS_DRV_ReadPins(PTE) >> 21) & 0x01)) //PE21
#define HIN8_Read 	(!((PINS_DRV_ReadPins(PTE) >> 20) & 0x01)) //PE20
#define HIN9_Read 	(!((PINS_DRV_ReadPins(PTE) >> 19) & 0x01)) //PE19
#define HIN10_Read 	(!((PINS_DRV_ReadPins(PTE) >> 16) & 0x01)) //PE16
#define HIN11_Read 	(!((PINS_DRV_ReadPins(PTE) >> 22) & 0x01)) //PE22
#define HIN12_Read 	(!((PINS_DRV_ReadPins(PTE) >> 23) & 0x01)) //PE23
#define HIN13_Read 	(!((PINS_DRV_ReadPins(PTE) >> 24) & 0x01)) //PE24
#define HIN14_Read 	(!((PINS_DRV_ReadPins(PTE) >> 25) & 0x01)) //PE25


/* ********************************************************************************
 * INPUT: LIN1-LIN6
 */
#define LIN1_Read 	(!((PINS_DRV_ReadPins(PTC) >> 3) & 0x01)) //PC3
#define LIN2_Read 	(!((PINS_DRV_ReadPins(PTE) >> 8) & 0x01)) //PE8
#define LIN3_Read 	(!((PINS_DRV_ReadPins(PTB) >> 21) & 0x01)) //PB21
#define LIN4_Read 	(!((PINS_DRV_ReadPins(PTB) >> 20) & 0x01)) //PB20
#define LIN5_Read 	(!((PINS_DRV_ReadPins(PTE) >> 9) & 0x01)) //PE9
#define LIN6_Read 	(!((PINS_DRV_ReadPins(PTD) >> 17) & 0x01)) //PD17


/* ********************************************************************************
 * OUTPUT: OUT1-OUT7
 */
#define OUT1_ON		PINS_DRV_WritePin(PTD, 23, 1) //PD23
#define OUT1_OFF	PINS_DRV_WritePin(PTD, 23, 0)
#define OUT2_ON		PINS_DRV_WritePin(PTD, 2, 1) //PD2
#define OUT2_OFF	PINS_DRV_WritePin(PTD, 2, 0)
#define OUT3_ON		PINS_DRV_WritePin(PTD, 3, 1) //PD3
#define OUT3_OFF	PINS_DRV_WritePin(PTD, 3, 0)
#define OUT4_ON		PINS_DRV_WritePin(PTD, 4, 1) //PD4
#define OUT4_OFF	PINS_DRV_WritePin(PTD, 4, 0)
#define OUT5_ON		PINS_DRV_WritePin(PTD, 22, 1) //PD22
#define OUT5_OFF	PINS_DRV_WritePin(PTD, 22, 0)
#define OUT6_ON		PINS_DRV_WritePin(PTC, 15, 1) //PC15
#define OUT6_OFF	PINS_DRV_WritePin(PTC, 15, 0)
#define OUT7_ON		PINS_DRV_WritePin(PTC, 16, 1) //PC16
#define OUT7_OFF	PINS_DRV_WritePin(PTC, 16, 0)




void BSP_Pin_Init(void);
void BSP_Pin_In(void);
void BSP_Pin_Out(uint8_t out);
void BSP_Pin_NetPWR(uint8_t state);

#endif /*  */









