/*
 * bsp_adsch8.h
 *
 * Created on: 2024年3月x日
 *     Author: ROG
 */
#ifndef _BSP_ADSCH8_H
#define _BSP_ADSCH8_H

#include "pin_mux.h"


/* ********************************************************************************
 * IO 模拟 IIC2
 */
#define IIC2_SCL_ON			PINS_DRV_WritePin(PTB, 9, 1)
#define IIC2_SCL_OFF		PINS_DRV_WritePin(PTB, 9, 0) //PB9
#define IIC2_SDAOUT			PINS_DRV_SetPinDirection(PTB, 10, 1);
#define IIC2_SDA_ON			PINS_DRV_WritePin(PTB, 10, 1)
#define IIC2_SDA_OFF		PINS_DRV_WritePin(PTB, 10, 0)
#define IIC2_SDAIN			PINS_DRV_SetPinDirection(PTB, 10, 0);
#define IIC2_SDARead		((PINS_DRV_ReadPins(PTB) >> 10) & 0x01) //PB10




void BSP_ADSCH8_Init(void);
void BSP_ADSCH8_Task(void);

#endif /*  */





