/*
 * os_task.h
 *
 * Created on: 2024年3月x日
 *     Author: ROG
 */
#ifndef _OS_TASK_GETIN_H
#define _OS_TASK_GETIN_H

#include "os_task.h"
#include "bsp_pin.h"
#include "bsp_adc.h"
#include "bsp_ads1115.h"
#include "bsp_adsch8.h"
#include "bsp_max31865.h"



//队列数据交互。数据格式定义
typedef struct
{
	uint16_t adc0_value[6];		//AIN4-AIN7。PWR5vv
	uint16_t ads115_value[4];	//AIN0-AIN3
	
}GETIN1_PAR;

extern GETIN1_PAR getIn1;		//硬件输入缓存



typedef struct 
{
    uint8_t  flag;
    uint16_t config[3];
    uint16_t rtd[3];
    uint16_t fault[3];
    
} MAX318;

typedef struct
{
	uint16_t hin;				//HIN1-HIN14
	uint16_t lin;				//LIN1-LIN6
	uint16_t adsch8[8];			//AI1-AI8
	MAX318	 max318;			//PT100
	
}GETIN2_PAR;

extern GETIN2_PAR getIn2;		//硬件输入缓存




#endif /*  */





