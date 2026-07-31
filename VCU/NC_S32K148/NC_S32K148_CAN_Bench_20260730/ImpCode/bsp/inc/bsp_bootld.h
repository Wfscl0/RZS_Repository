#ifndef _BSP_BOOTLD_H
#define _BSP_BOOTLD_H

#include "bsp_can0.h"
#include "cpu.h"


/* 与CAN通信相关的配置 */
#define TX_ID 					0x7A1 //发送ID	
#define RX_ID					0x7A0 //接收ID

//下载请求Flag
#define DOWNLOAD_FLAG 		0x1735FECD //下载请求

//下载请求Flag地址
extern uint32_t g_JumpInit;
extern uint8_t  bootjumpflag;


void BSP_Bootld_Init(void);
void BSP_Bootld_Task(void);

#endif















