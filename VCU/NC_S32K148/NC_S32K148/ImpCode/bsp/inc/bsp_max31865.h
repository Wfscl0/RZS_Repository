/*
 * bsp_max31865.h
 *
 * Created on: 2024年3月x日
 *     Author: ROG
 */
#ifndef _BSP_MAX31865_H
#define _BSP_MAX31865_H

#include "pin_mux.h"
#include "spi1_max318.h"


/* ********************************************************************************
 * 硬件引脚定义：(mcu)
 */
//DRDY low when a new conversion result isavailab.
#define DRDY_A_Read 	(!((PINS_DRV_ReadPins(PTD) >> 28) & 0x01)) //PD28
#define DRDY_B_Read 	(!((PINS_DRV_ReadPins(PTA) >> 1) & 0x01)) //PA1
#define DRDY_C_Read 	(!((PINS_DRV_ReadPins(PTA) >> 0) & 0x01)) //PA0

//CS
#define CS_A_LOW		PINS_DRV_WritePin(PTB, 17, 0)
#define CS_A_HIGH		PINS_DRV_WritePin(PTB, 17, 1) //PB17
#define CS_B_LOW		PINS_DRV_WritePin(PTD, 29, 0)
#define CS_B_HIGH		PINS_DRV_WritePin(PTD, 29, 1) //PD29
#define CS_C_LOW		PINS_DRV_WritePin(PTD, 30, 0)
#define CS_C_HIGH		PINS_DRV_WritePin(PTD, 30, 1) //PD30





void BSP_MAX31865_Init(void);
void BSP_MAX31865_Task(void);

#endif /*  */





