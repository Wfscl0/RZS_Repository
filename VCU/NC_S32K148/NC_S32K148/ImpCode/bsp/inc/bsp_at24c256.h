/*
 * bsp_at24c256.h
 *
 * Created on: 2024Äê3ÔÂxÈÕ
 *     Author: ROG
 */
#ifndef _BSP_AT24C256_H
#define _BSP_AT24C256_H

#include "i2c1_at24c.h"


#define AT24C256	32767 	//32768¡Á8=256K



void BSP_AT24C_Init(void);
void BSP_AT24C_Task(void);
void BSP_AT24C02_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint8_t ReadNum);
void BSP_AT24C02_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint8_t WriteNum);

#endif /*  */





