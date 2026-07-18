/*
 * bsp_can1.h
 *
 * Created on: 2024年3月x日
 *     Author: ROG
 */
#ifndef _BSP_CAN1_H
#define _BSP_CAN1_H

#include "can1.h"


/* ********************************************************************************
 * CAN1
 */
//发送、接收分别定义两个邮箱，一个用于STD，一个用于EXT
#define RX_MAILBOX_CAN1_STD  	(4UL)
#define TX_MAILBOX_CAN1_STD  	(5UL)
#define RX_MAILBOX_CAN1_EXT  	(6UL)
#define TX_MAILBOX_CAN1_EXT  	(7UL)





void BSP_CAN1_Init(void);
void BSP_CAN1_Send_STD(uint16_t id, uint8_t data[8]);
void BSP_CAN1_Send_EXT(uint32_t id, uint8_t data[8]);

#endif /*  */





