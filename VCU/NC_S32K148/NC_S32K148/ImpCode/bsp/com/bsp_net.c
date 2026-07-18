/*
 * bsp_net.c
 *
 * Created on: 2024年3月x日
 *     Author: ROG
 */
#include "bsp_net.h"


/* ********************************************************************************
 * 网口：
 */

NET_PAR	Net;
extern void start_example(void);

/* ********************************************************************************
 * 硬件关系：计算机PCI总线--以太网MAC芯片--PHY芯片（网口芯片）--MCU（RMII等接口）
 *
 */

void BSP_NET_Start(void)
{
	start_example(); //使用测试程序，修改test.c、udpecho.c文件
}



void BSP_NET_Init(void)
{
	BSP_Pin_NetPWR(1);
}

void BSP_NET_Task(void)
{

}




