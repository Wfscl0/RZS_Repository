/*
 * os_task.h
 *
 * Created on: 2024年3月x日
 *     Author: ROG
 */
#ifndef _OS_TASK_GETCOMIN_H
#define _OS_TASK_GETCOMIN_H

#include "os_task.h"
#include  "bsp_uart.h"
#include  "bsp_uart_iot.h"
#include  "bsp_uart_jy60.h"

#define JY60_STRUCT

//队列数据交互。数据格式定义
typedef struct
{
	uint8_t rx_count;
	uint8_t rx_buf[64];
	
}HUART_PAR;

typedef struct 
{
    float AXL;
    float AYL;
    float AZL; //加速度

    float WXL;
    float WYL;
    float WZL; //角速度

    float Roll;
    float Pitch;
    float Yaw; //角度
	
	float Temperature; //温度
    
}JY60_PAR;

extern JY60_PAR jy60;

//队列数据交互。数据格式定义
typedef struct
{
	JY60_PAR jy60;

}COMIN_PAR;

extern COMIN_PAR comIn;		//硬件输入缓存



#endif /*  */





