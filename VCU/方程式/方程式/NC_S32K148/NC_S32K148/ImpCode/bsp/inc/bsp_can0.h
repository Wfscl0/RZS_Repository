/*
 * bsp_can0.h
 *
 * Created on: 2024年3月x日
 *     Author: ROG
 */
#ifndef _BSP_CAN0_H
#define _BSP_CAN0_H

#include "can0.h"


/* ********************************************************************************
 * CAN0
 */
//发送、接收分别定义两个邮箱，一个用于STD，一个用于EXT
#define RX_MAILBOX_CAN0_STD  	(0UL)
#define TX_MAILBOX_CAN0_STD  	(1UL)
#define TX_MAILBOX_CAN0_STD_EX  (8UL)
#define RX_MAILBOX_CAN0_EXT  	(2UL)
#define TX_MAILBOX_CAN0_EXT  	(3UL) 	//注意，can0-2之间，邮箱号不能重复！！！
#define TX_MAILBOX_CAN0_EXT_EX 	(9UL)







void BSP_CAN0_Init(void);
void BSP_CAN0_Send_STD(uint16_t id, uint8_t data[8]);
void BSP_CAN0_Send_EXT(uint32_t id, uint8_t data[8]);
void BSP_CAN0_Send_XCP(uint16_t id, uint8_t* data,uint8_t len);
void BSP_CAN0_Send_BSW(uint32_t id, uint8_t data[8], uint8_t len);

#endif /*  */





