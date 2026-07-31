/*
 * bsp_mc33879.h
 *
 * Created on: 2024年3月x日
 *     Author: ROG
 */
#ifndef _BSP_MC33879_H
#define _BSP_MC33879_H

#include "pin_mux.h"
#include "spi2_mc338.h"


/* ********************************************************************************
 * 硬件引脚定义：Output(mcu)
 */
#define MC33879_EN1_ON		PINS_DRV_WritePin(PTC, 12, 1) //PC12
#define MC33879_EN1_OFF		PINS_DRV_WritePin(PTC, 12, 0) //PC12

#define MC33879_EN2_ON		PINS_DRV_WritePin(PTC, 13, 1) //PC13
#define MC33879_EN2_OFF		PINS_DRV_WritePin(PTC, 13, 0) //PC13





typedef struct
{
    uint8_t cmd1; //芯片1。输出控制命令。高位控制LO4-LO1 低位控制HO4-HO1
	uint8_t cmd2; //芯片2。输出控制命令。高位控制LO8-LO5 低位控制HO8-HO5
    uint8_t state1; //芯片1。输出状态。0无故障，1故障（负载开路、短路或TLIM）
	uint8_t state2; //芯片2。输出状态。0无故障，1故障（负载开路、短路或TLIM）

} MC33879_PAR;



void BSP_MC33879_Init(void);
void BSP_MC33879_Disable(void);
void BSP_MC33879_Task(uint8_t outl, uint8_t outh);
extern MC33879_PAR     MC33879;

#endif /*  */





