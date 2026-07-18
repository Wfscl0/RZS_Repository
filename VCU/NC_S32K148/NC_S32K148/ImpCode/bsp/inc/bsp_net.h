/*
 * bsp_net.h
 *
 * Created on: 2024年3月x日
 *     Author: ROG
 */
#ifndef _BSP_NET_H
#define _BSP_NET_H

#include "pin_mux.h"

/* ********************************************************************************
 * 网口
 */

#define NET_SIZE 512

typedef struct
{
	uint8_t rx_count;
	uint8_t rx_buf[NET_SIZE];

	uint8_t tx_len;
	uint8_t txbuf[NET_SIZE];

} NET_PAR;

extern NET_PAR Net;





void BSP_NET_Start(void);
void BSP_NET_Init(void);
void BSP_NET_Task(void);

#endif /*  */





