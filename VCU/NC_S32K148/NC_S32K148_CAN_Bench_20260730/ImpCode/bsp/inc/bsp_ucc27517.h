/*
 * bsp_ucc27517.h
 *
 * Created on: 2024年3月x日
 *     Author: ROG
 */
#ifndef _BSP_UCC27517_H
#define _BSP_UCC27517_H

#include "pwm5.h"
#include "pwm1_ucc27.h"






void BSP_UCC27_Init(void);
void BSP_UCC27_SetEBSWatchdog(uint8_t enable);
void BSP_UCC27_Task(void);

#endif /*  */





