/*
 * os_task.h
 *
 * Created on: 2024年3月x日
 *     Author: ROG
 */
#ifndef _OS_TASK_H
#define _OS_TASK_H


#include "FreeRTOS.h"
#include "queue.h"
#include "event_groups.h"
#include "task.h"


#include "os_task_CanOut.h"
#include "os_task_CoreApp.h"
#include "os_task_Debug.h"
#include "os_task_getComIn.h"
#include "os_task_getIn.h"
#include "os_task_VcuCtrl.h"
//#include "userif.h"


#define PEX_RTOS_INIT       OS_All_Init
#define PEX_RTOS_START      OS_ALL_End



/* ********************************************************************************
 * 任务线程
 */
//常用任务句柄
extern TaskHandle_t    Task_Init_Handler;
extern TaskHandle_t    Task_getIn1_Handler;
extern TaskHandle_t    Task_getIn2_Handler; 
extern TaskHandle_t    Task_getComIn_Handler;
extern TaskHandle_t    Task_getCanIn_Handler;
extern TaskHandle_t    Task_CoreApp_Handler;
extern TaskHandle_t    Task_VcuCtrl_Handler;
extern TaskHandle_t    Task_CanOut_Handler;

//定义线程全局变量，用于观察线程运行情况
typedef struct 
{
    uint16_t task_getIn1;
    uint16_t task_getIn2;
	uint16_t task_ComIn;
	uint16_t task_CoreApp;
	uint16_t task_VcuCtrl;
	uint16_t task_CanOut;
	uint16_t task_Debug;
    
} TaskLive; //线程运行情况

/*******************************************************************************
** 程序运行情况 结构体变量声明
*/
//定义线程全局变量，用于观察程序运行情况
typedef struct 
{
	uint16_t hin;				//0-1
	uint8_t  uln_out;			//2
	uint8_t  mc3_outl;			//3
	uint8_t  mc3_outh;			//4
	
	uint8_t  rct_live;			//5
	uint8_t  rct_online;
	uint8_t  rct_emerg;
	
	uint8_t  can0_isr;			//6
	uint8_t  can1_isr;
	uint8_t  can2_isr;
	uint8_t  jy60_isr;
	
	uint8_t  task_getIn1;		//7
	uint8_t  task_getIn2;
	uint8_t  task_ComIn;
	uint8_t  task_CoreApp;
	uint8_t  task_VcuCtrl;
	uint8_t  task_CanOut;
	uint8_t  task_Debug;

} ProgramStatus;

extern ProgramStatus PrgSts; //程序运行情况



/* ********************************************************************************
 * 队列
 */
//队列句柄
extern QueueHandle_t 	Que_Hcan0_CanIn;
extern QueueHandle_t 	Que_Hcan1_CanIn;
extern QueueHandle_t 	Que_Hcan2_CanIn;
extern QueueHandle_t	Que_Huart0_ComIn;
extern QueueHandle_t	Que_Huart1_ComIn; //JY60
extern QueueHandle_t  	Que_Huart2_CoreApp; //SBUS
extern QueueHandle_t	Que_Hadc0_getIn1;
extern	QueueHandle_t	Que_getIn1_CoreApp;
extern	QueueHandle_t	Que_getIn2_CoreApp;
extern QueueHandle_t  	Que_Hcore_CanSend;
extern QueueHandle_t  	Que_Hcore_VcuCtrl;
extern QueueHandle_t	Que_ComIn_CoreApp;

//定义队列全局变量，用于观察队列运行情况   
typedef struct 
{
	uint8_t que_hcan0;
	uint8_t que_hcan1;
	uint8_t que_hcan2;
	uint8_t que_huart0;
	uint8_t que_huart1; //JY60
	
	uint8_t que_hadc0;
	
} QueSize; //队列剩余大小信息

typedef struct
{
	uint8_t fsize; 	//剩余大小查询标志
	QueSize size;	//剩余大小
	
	
} QueGlobal;

extern QueGlobal	queGlb;



/* ********************************************************************************
 * 事件标志组
 */
//事件标志组句柄
extern EventGroupHandle_t EventGrp_CoreTimer;

//8位或24位。configUSE_16_BIT_TICKS为0，事件标志组存储24位
#define EVENT_10MS_BIT			(1<<0) 
#define EVENT_20MS_BIT			(1<<1)
#define EVENT_50MS_BIT			(1<<2)
#define EVENT_100MS_BIT			(1<<3)
#define EVENT_1S_BIT			(1<<5)

#define EVENTBIT_ALL			(EVENT_10MS_BIT|EVENT_20MS_BIT|EVENT_50MS_BIT|EVENT_100MS_BIT|EVENT_1S_BIT)


void OS_All_Init(void);
void OS_ALL_End(void);
void OS_Task_Init(void *pvPara);

void OS_Task_getIn1(void *pvPara);
void OS_Task_getIn2(void *pvPara);
void OS_Task_getComIn(void *pvPara);

void OS_Task_CoreApp(void *pvPara);
void OS_Task_CoreTim(void *pvPara);
void OS_Task_VcuCtrl(void *pvPara);
void OS_Task_CanOut(void *pvPara);
void OS_Task_Debug(void *pvPara);

#endif /*  */





