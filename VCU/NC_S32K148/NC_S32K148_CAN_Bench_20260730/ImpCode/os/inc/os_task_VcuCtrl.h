/*
 * os_task.h
 *
 * Created on: 2024年3月x日
 *     Author: ROG
 */
#ifndef _OS_TASK_VCUCTRL_H
#define _OS_TASK_VCUCTRL_H

#include "os_task.h"

#include "bsp_at24c256.h"
#include "bsp_tlf35584.h"
#include "bsp_mc33879.h"
#include "bsp_ucc27517.h"
#include "bsp_pflash.h"



//队列数据交互。数据格式定义
typedef struct
{
	uint8_t uln_out;
	uint8_t mc3_outh;
	uint8_t mc3_outl;
	uint8_t ebs_watchdog;
	
}HVCUCTRL_PAR;

extern HVCUCTRL_PAR	hvcuCtrl;





#endif /*  */





