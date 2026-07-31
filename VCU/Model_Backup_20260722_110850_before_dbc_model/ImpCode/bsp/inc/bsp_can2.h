/*
 * bsp_can2.h
 *
 * Created on: 2024年3月x日
 *     Author: ROG
 */
#ifndef _BSP_CAN2_H
#define _BSP_CAN2_H

#include "can2.h"
#include "pin_mux.h"


/* ********************************************************************************
 * CAN2
 */
//发送、接收分别定义两个邮箱，一个用于STD，一个用于EXT
#define RX_MAILBOX_CAN2_STD  	(10UL)
#define TX_MAILBOX_CAN2_STD  	(11UL)
#define TX_MAILBOX_CAN2_STD_EX 	(14UL)
#define RX_MAILBOX_CAN2_EXT  	(12UL)
#define TX_MAILBOX_CAN2_EXT  	(13UL)


/* ********************************************************************************
 * 硬件引脚定义(mcu)
 */
#define CAN2_EN_ON				PINS_DRV_WritePin(PTD, 13, 1)
#define CAN2_EN_OFF				PINS_DRV_WritePin(PTD, 13, 0) //PD13
#define CAN2_STBN_ON			PINS_DRV_WritePin(PTB, 8, 1)
#define CAN2_STBN_OFF			PINS_DRV_WritePin(PTB, 8, 0) //PB8

#define CAN2_INH_Read			((PINS_DRV_ReadPins(PTD) >> 14) & 0x01) //PD14
#define CAN2_ERRN_Read			((PINS_DRV_ReadPins(PTB) >> 11) & 0x01) //PB11


/* ********************************************************************************
 * 								Operating modes
 * ********************************************************************************
 * nternal flags 					Control pins 		Operating mode 		Pin INH
 * UVNOM[1] 	UVBAT 	Wake[2] 	STB_N[3] 	EN
 * (从正常，只听，待机和进入睡眠模式)
 * set 		X 		X 			X 			X 		Sleep mode 				floating
 * cleared 	set 	X 			HIGH 		X 		Standby mode 			HIGH
 * cleared 	X 		set 		LOW 		X 		Standby mode 			HIGH
 * cleared 	X 		cleared 	LOW 		LOW 	Standby mode 			HIGH
 * cleared 	X 		cleared 	LOW 		HIGH 	Go-to-Sleep mode[4] 	HIGH[4]
 * cleared 	cleared X 			HIGH 		LOW 	Listen-only mode 		HIGH
 * cleared 	cleared X 			HIGH 		HIGH 	Normal mode 			HIGH
 * (睡眠模式)
 * set 		X 		X 			X 			X 		Sleep mode 				floating
 * cleared 	set 	X 			HIGH 		X 		Standby mode 			HIGH
 * cleared 	X 		set 		LOW 		X 		Standby mode 			HIGH
 * cleared 	X 		cleared 	LOW 		X 		Sleep mode 				floating
 * cleared 	cleared X 			HIGH 		LOW 	Listen-only mode 		HIGH
 * cleared 	cleared X 			HIGH 		HIGH 	Normal mode 			HIGH
*/


void BSP_CAN2_Init(void);
void BSP_CAN2_Send_STD(uint16_t id, uint8_t data[8]);
void BSP_CAN2_Send_EXT(uint32_t id, uint8_t data[8]);
uint8_t BSP_CAN2_Modes(uint8_t mode);

#endif




