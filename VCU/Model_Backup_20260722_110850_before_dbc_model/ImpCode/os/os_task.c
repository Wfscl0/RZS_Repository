/*
 * ********************************************************************************
 * os_task.c
 *
 * Created on: 2024年12月x日
 *     Author: ROG
 */
#include "os_task.h"
#include "bsp.h"
#include "CAN_Node.h"




//定义线程全局变量，用于调试观察
ProgramStatus 	PrgSts; //程序运行情况
QueGlobal		queGlb;

//常用任务句柄
TaskHandle_t    Task_Init_Handler;
TaskHandle_t    Task_getIn1_Handler;
TaskHandle_t    Task_getIn2_Handler; 
TaskHandle_t    Task_getComIn_Handler;
TaskHandle_t    Task_CoreApp_Handler;
TaskHandle_t    Task_VcuCtrl_Handler;
TaskHandle_t    Task_CanOut_Handler;
TaskHandle_t    Task_Debug_Handler;

//队列句柄
QueueHandle_t 	Que_Hcan0_CanIn;
QueueHandle_t 	Que_Hcan1_CanIn;
QueueHandle_t 	Que_Hcan2_CanIn;
QueueHandle_t	Que_Huart0_ComIn; 
QueueHandle_t	Que_Huart1_ComIn; 
QueueHandle_t  	Que_Huart2_CoreApp;
QueueHandle_t	Que_getIn1_CoreApp;
QueueHandle_t	Que_getIn2_CoreApp;
QueueHandle_t  	Que_Hcore_CanSend;
QueueHandle_t  	Que_Hcore_VcuCtrl;
QueueHandle_t	Que_ComIn_CoreApp;

//事件标志组句柄
EventGroupHandle_t EventGrp_CoreTimer;

/* ********************************************************************************
 * 初始化
 */
void OS_All_Init(void)
{
	//硬件初始化
	CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT,g_clockManCallbacksArr, CLOCK_MANAGER_CALLBACK_CNT);
	CLOCK_SYS_UpdateConfiguration(0U, CLOCK_MANAGER_POLICY_AGREEMENT);

	#if 0
		POWER_SYS_Init(&powerConfigsArr, POWER_MANAGER_CONFIG_CNT, &powerStaticCallbacksConfigsArr, POWER_MANAGER_CALLBACK_CNT);
		POWER_SYS_SetMode(STAT_HSRUN,POWER_MANAGER_POLICY_AGREEMENT);
	#else
	#endif
    //OS运行前，部分程序初始化。
    BSP_Pin_Init();
    
    //创建初始化任务线程
	xTaskCreate((TaskFunction_t	) 					OS_Task_Init,
	 			(        char * ) 					"T_Init",
	 			(const configSTACK_DEPTH_TYPE)	    configMINIMAL_STACK_SIZE,
	 			(void *	        ) 			    NULL,
	 			(UBaseType_t	) 				    4,
	 			(TaskHandle_t *) 					&Task_Init_Handler);
    
	//BSP_NET_Start(); //网口接口。自创建一个线程，用于网口使用！

    vTaskStartScheduler();
}

/* ********************************************************************************
 * 常用任务创建
 */
void Task_Create(void)
{
	//创建In1任务线程，用于处理信号频输入
	xTaskCreate((TaskFunction_t	) 					OS_Task_getIn1,
	 			(        char * ) 					"T_getIn1",
	 			(const configSTACK_DEPTH_TYPE)	    configMINIMAL_STACK_SIZE,
	 			(void *	        ) 			    	NULL,
	 			(UBaseType_t	) 				    4,
	 			(TaskHandle_t *) 					&Task_getIn1_Handler );

 	//创建In2任务线程，用于处理信号高频输入
	xTaskCreate((TaskFunction_t	) 					OS_Task_getIn2,
	 			(        char * ) 					"T_getIn2",
	 			(const configSTACK_DEPTH_TYPE)	    configMINIMAL_STACK_SIZE,
	 			(void *	        ) 			    	NULL,
	 			(UBaseType_t	) 				    4,
	 			(TaskHandle_t *) 					&Task_getIn2_Handler );
    
    //创建ComIn任务线程，用于处理串口数据输入（陀螺仪、遥控等）
	xTaskCreate((TaskFunction_t	) 					OS_Task_getComIn,
				(        char * ) 					"T_getComIn",
				(const configSTACK_DEPTH_TYPE)	    configMINIMAL_STACK_SIZE,
				(void *	        ) 			    	NULL,
				(UBaseType_t	) 				    4,
				(TaskHandle_t *) 					&Task_getComIn_Handler );
	
    //创建CoreApp任务线程，用于整体逻辑处理
	xTaskCreate((TaskFunction_t	) 					OS_Task_CoreApp,
				(        char * ) 					"T_CoreApp",
				(const configSTACK_DEPTH_TYPE)	    configMINIMAL_STACK_SIZE,
				(void *	        ) 			    	NULL,
				(UBaseType_t	) 				    4,
				(TaskHandle_t *) 					&Task_CoreApp_Handler );

	//创建VcuCtrl任务线程，用于处理VCU内部控制，以及外部输出控制
	xTaskCreate((TaskFunction_t	) 					OS_Task_VcuCtrl,
				(        char * ) 					"T_VcuCtrl",
				(const configSTACK_DEPTH_TYPE)	    configMINIMAL_STACK_SIZE,
				(void *	        ) 			    	NULL,
				(UBaseType_t	) 				    4,
				(TaskHandle_t *) 					&Task_VcuCtrl_Handler );

	//创建CanOut任务线程，用于处理CAN通信发送
	xTaskCreate((TaskFunction_t	) 					OS_Task_CanOut,
				(        char * ) 					"T_CanOut",
				(const configSTACK_DEPTH_TYPE)	    configMINIMAL_STACK_SIZE,
				(void *	        ) 			    	NULL,
				(UBaseType_t	) 				    4,
				(TaskHandle_t *) 					&Task_CanOut_Handler );

//	//创建Debug任务线程，用于调试，输出变量信息
//	xTaskCreate((TaskFunction_t	) 					OS_Task_Debug,
//				(        char * ) 					"T_Debug",
//				(const configSTACK_DEPTH_TYPE)	    configMINIMAL_STACK_SIZE,
//				(void *	        ) 			    	NULL,
//				(UBaseType_t	) 				    6,
//				(TaskHandle_t *) 					&Task_Debug_Handler );
}

/* ********************************************************************************
 * 常用队列创建
 */
void Queue_Create(void)
{
	/* ********************************************************************************
	 * 队列数据传递：指针（注意点）
	 * 1，指针指向的内存空间的所有权必须明确。
     * 2，指针指向的内存空间必须有效。
	 */
	
	//CAN接收。队列。。结构体指针类型，可以传输大量数据
	Que_Hcan0_CanIn = xQueueCreate(3, sizeof(HCAN0RX_PAR *));
	Que_Hcan1_CanIn = xQueueCreate(3, sizeof(HCAN1RX_PAR *));
	Que_Hcan2_CanIn = xQueueCreate(3, sizeof(HCAN2RX_PAR *));
	Que_Hcore_CanSend = xQueueCreate(3, sizeof(HCANSEND_PAR *));
	Que_Hcore_VcuCtrl = xQueueCreate(3, sizeof(HVCUCTRL_PAR *));
	
	//串口接收。队列
	Que_Huart0_ComIn = xQueueCreate(3, sizeof(HUART_PAR *)); //IOT
	Que_Huart1_ComIn = xQueueCreate(3, sizeof(HUART_PAR *)); //JY60
	Que_Huart2_CoreApp = xQueueCreate(3, sizeof(HUART_PAR *)); //SBUS
	
	Que_getIn1_CoreApp = xQueueCreate(3, sizeof(GETIN1_PAR *)); //硬件输入
	Que_getIn2_CoreApp = xQueueCreate(3, sizeof(GETIN2_PAR *)); //硬件输入
	Que_ComIn_CoreApp = xQueueCreate(3, sizeof(COMIN_PAR *)); //硬件输入
}

/* ********************************************************************************
 * 常用事件标志组创建
 */
void EventGroup_Create(void)
{
	//创建事件标志组
	EventGrp_CoreTimer = xEventGroupCreate();
}

/* ********************************************************************************
 * 功能初始化
 */
void OS_Task_Init(void *pvPara)
{
	(void)pvPara;
    taskENTER_CRITICAL(); //进入临界区0
    
    //OS运行后，部分程序初始化
    BSP_ADC0_Init();
    BSP_ADS1115_Init();
    BSP_ADSCH8_Init();
    BSP_AT24C_Init();
    //BSP_Uart0_IoT_Init();
    BSP_Uart1_JY60_Init();
    //BSP_Uart_Init();
    BSP_Uart2_SBUS_Init();
    BSP_CAN0_Init();
    BSP_CAN1_Init();
    BSP_CAN2_Init();
    BSP_TLF35584_Init();
    BSP_MC33879_Init();
    BSP_MAX31865_Init();
    BSP_UCC27_Init();
    BSP_FLASH_Init();
    //BSP_NET_Init();

	//控制任务线程创建
    Task_Create();
	//消息队列创建
	Queue_Create();
	//事件标志组创建
	EventGroup_Create();
    
    vTaskDelete(Task_Init_Handler);
    taskEXIT_CRITICAL(); //退出临界区
}

/* ********************************************************************************
 * main.c结尾函数
 */
void OS_ALL_End(void)
{
	LED_D16_ON; //正常不会到这个步骤！！！
}
