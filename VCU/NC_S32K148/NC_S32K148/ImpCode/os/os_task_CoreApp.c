/*
 * ********************************************************************************
 * os_task_CoreApp.c
 *
 * Created on: 2026_7_16
 *
 */
#include "os_task_CoreApp.h"
#include "os_task_CanOut.h"
#include "userif.h"
#include "CAN_Node.h"


static uint8_t 		simulink_init_flag=0;

static HCAN0RX_PAR	hcan0_recv;
static HCAN1RX_PAR	hcan1_recv;
static HCAN2RX_PAR	hcan2_recv;
static HCAN0RX_PAR 	*pcan0_recv;
static HCAN1RX_PAR 	*pcan1_recv;
static HCAN2RX_PAR 	*pcan2_recv;
static UART2_PAR   	huart2_recv;
static UART2_PAR   	*puart2_recv;

static GETIN1_PAR 	hgetIn1;
static GETIN2_PAR 	hgetIn2;
static HCANSEND_PAR	hcan_send;
static HVCUCTRL_PAR	hvcuCtrl1;
static GETIN1_PAR 	*pgetIn1;
static GETIN2_PAR 	*pgetIn2;
static HCANSEND_PAR *pcan_send;
static HVCUCTRL_PAR	*pvcuCtrl;

static void Task_CoreApp_SignalReceive(void);
static void Task_CoreApp_SignalConvert(void);
static void Task_CoreApp_SignalSend(void);

/* ********************************************************************************
 * 模型等复杂功能处理。核心线程
 */
void OS_Task_CoreApp(void *pvPara)
{
	(void)pvPara;
	uint8_t model_step_count;

	while(1)
	{
	/* ********************************************************************************
	 * VCU硬件信号，接受
	 */
	#if 1
		Task_CoreApp_SignalReceive();
	#endif
	
	/* ********************************************************************************
	 * 逻辑处理，功能代码1
	 */
	#if 1

	#endif
		
	/* ********************************************************************************
	 * Simulink模型，功能代码
	 */
	#if 1
		//模型初始化，执行一次
		if(simulink_init_flag == 0) {
			simulink_init_flag = 1;
			MODEL_INIT();
		}
		
		//将接收的信号，代入到模型变量中
		Task_CoreApp_SignalConvert();
		
		//模型代码：CoreApp为10ms周期，模型基础步长为1ms
		for(model_step_count = 0U;
			model_step_count < MODEL_STEPS_PER_CORE_PERIOD;
			model_step_count++) {
			MODEL_STEP();
		}

	#endif
	
	/* ********************************************************************************
	 * 逻辑处理，功能代码2
	 */
	#if 1
//        hvcuCtrl1.mc3_outh = 0x2;
	#endif
		
	/* ********************************************************************************
	 * VCU硬件信号，发送
	 */
	#if 1
		//模型代码处理后，发送到相应硬件接口
		Task_CoreApp_SignalSend();

	#endif

		PrgSts.task_CoreApp++;
		vTaskDelay(CORE_APP_PERIOD_MS);
	}
}

/// @brief 信号接收函数，在CoreApp的主任务中应首先调用本函数，本函数用于读取队列中的值。
/// @param hgetIn1:用于接收ADC和ADS1115的数据
///	@param hgetIn2:用于接收GPIO输入、电阻输入和电流输入
static void Task_CoreApp_SignalReceive(void)
{
	//请求消息。getIn1
	if(xQueueReceive(Que_getIn1_CoreApp, &(pgetIn1), 0) == pdTRUE)
	{
		memcpy(hgetIn1.adc0_value, pgetIn1->adc0_value, 6*sizeof(uint16_t));
		memcpy(hgetIn1.ads115_value, pgetIn1->ads115_value, 4*sizeof(uint16_t));
	}
	
	//请求消息。getIn2
	if(xQueueReceive(Que_getIn2_CoreApp, &(pgetIn2), 0) == pdTRUE)
	{
		hgetIn2.hin = pgetIn2->hin;
		hgetIn2.lin = pgetIn2->lin;
		memcpy(hgetIn2.adsch8, pgetIn2->adsch8, 8*sizeof(uint16_t));
		
		hgetIn2.max318.flag = pgetIn2->max318.flag;
		memcpy(hgetIn2.max318.config, pgetIn2->max318.config, 3*sizeof(uint16_t));
		memcpy(hgetIn2.max318.rtd, pgetIn2->max318.rtd, 3*sizeof(uint16_t));
		memcpy(hgetIn2.max318.fault, pgetIn2->max318.fault, 3*sizeof(uint16_t));
	}
	
	// 请求消息。UART2_SBUS_In
	if(xQueueReceive(Que_Huart2_CoreApp, &(puart2_recv), 0) == pdTRUE)
	{
		//huart2_recv.rx_count = puart2_recv->rx_count;
		//memcpy(huart2_recv.rx_buf, puart2_recv->rx_buf, 23*sizeof(uint8_t));
		//memcpy(SbusBuffer, puart2_recv->rx_buf, 23);
		//SbusCount = puart2_recv->rx_count;
	}

	//请求消息。CAN0_In
	if(xQueueReceive(Que_Hcan0_CanIn, &(pcan0_recv), 0) == pdTRUE)
	{
		//memcpy(Rx201_1, pcan0_recv->Rx201, 8);
		//memcpy(Rx202_1, pcan0_recv->Rx202, 8);
	}
	
	//请求消息。CAN1_In
	if(xQueueReceive(Que_Hcan1_CanIn, &(pcan1_recv), 0) == pdTRUE)
	{
		memcpy(ESP_T_03, pcan1_recv->ESP_T_03, 8);
		memcpy(res_msg, pcan1_recv->res_msg, 8);
		memcpy(canb_ipctsmsg1, pcan1_recv->canb_ipctsmsg1, 8);
		memcpy(canb_ipctsmsg2, pcan1_recv->canb_ipctsmsg2, 8);
		memcpy(AMI_Tx, pcan1_recv->AMI_Tx, 8);
		memcpy(canb_epssendmsg1, pcan1_recv->canb_epssendmsg1, 8);
		memcpy(canb_epssendmsg2, pcan1_recv->canb_epssendmsg2, 8);
	}
	
	// 请求消息。CAN2_In
	if(xQueueReceive(Que_Hcan2_CanIn, &(pcan2_recv), 0) == pdTRUE)
	{

	}
}

/// @brief 信号传入模型的函数
/// @param hcan0_recv:CAN0通道接收到报文的缓存数据
/// @param hcan1_recv:CAN1通道接收到报文的缓存数据
/// @param hcan2_recv:CAN2通道接收到报文的缓存数据
static void Task_CoreApp_SignalConvert(void)
{
	//模型接口IO：model_ain顺序为APP1、APP2、制动、气压1、气压2
	PrgSts.hin = hgetIn2.hin;
	model_hin = hgetIn2.hin;
	model_ain[0] = hgetIn1.adc0_value[0];
	model_ain[1] = hgetIn1.adc0_value[1];
	model_ain[2] = hgetIn1.adc0_value[2];
	model_ain[3] = hgetIn1.ads115_value[0];
	model_ain[4] = hgetIn1.ads115_value[1];
}

static void Task_CoreApp_SignalSend(void)
{
	//-----------------------------CAN0
	memcpy(hcan_send.cana_motor_cmd, cana_motor_cmd, 8);
	memcpy(hcan_send.cana_motor_cmd3, cana_motor_cmd3, 8);

	//-----------------------------CAN1
	memcpy(hcan_send.ESP_R_00, VCU10_Y.ESP_R_00, 8);
	memcpy(hcan_send.canb_ipcrxmsg, canb_ipcrxmsg, 8);
	memcpy(hcan_send.AMI_Rx, AMI_Rx, 8);
	memcpy(hcan_send.canb_epsmsg, canb_epsmsg, 8);

	//-----------------------------CAN2
	//-----------------------------OUT
	hvcuCtrl1.uln_out = VCU10_Y.model_lox;
	hvcuCtrl1.mc3_outh = VCU10_Y.model_hox;

	//向队列中，发送数据。发送一个指向结构体对象的指针
	pcan_send = &hcan_send;
	xQueueSend(Que_Hcore_CanSend, (void *)&pcan_send, 0);

	//向队列中，发送数据。发送一个指向结构体对象的指针
	pvcuCtrl = &hvcuCtrl1;
	xQueueSend(Que_Hcore_VcuCtrl, (void *)&pvcuCtrl, 0);
}



