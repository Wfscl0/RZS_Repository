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

#define CAN_FRESHNESS_TIMEOUT_TICKS  (30U) /* 30 * 10 ms = 300 ms */
#define CAN_RECOVERY_VALID_FRAMES    (3U)

typedef struct
{
	uint8_t last_count;
	uint8_t age_ticks;
	uint8_t valid_streak;
	bool active;
} CAN_FRESHNESS_PAR;

static HCAN1RX_PAR	hcan1_recv;
static HCAN0RX_PAR 	*pcan0_recv;
static HCAN1RX_PAR 	*pcan1_recv;
static HCAN2RX_PAR 	*pcan2_recv;
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
static void Task_CoreApp_ApplyCanFreshness(void);

static bool CAN_FreshnessUpdate(CAN_FRESHNESS_PAR *state, uint8_t counter,
	uint8_t recoveryFrames)
{
	if(counter != state->last_count)
	{
		state->last_count = counter;
		state->age_ticks = 0U;
		if(state->valid_streak < recoveryFrames)
		{
			state->valid_streak++;
		}
		if(state->valid_streak >= recoveryFrames)
		{
			state->active = true;
		}
	}
	else if(state->age_ticks < CAN_FRESHNESS_TIMEOUT_TICKS)
	{
		state->age_ticks++;
	}

	if(state->age_ticks >= CAN_FRESHNESS_TIMEOUT_TICKS)
	{
		state->active = false;
		state->valid_streak = 0U;
	}

	return state->active;
}

/* ********************************************************************************
 * 模型等复杂功能处理。核心线程
 */
void OS_Task_CoreApp(void *pvPara)
{
	(void)pvPara;
	uint8_t model_step_count;
	TickType_t lastWakeTime = xTaskGetTickCount();

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
		
		//模型代码：CoreApp为10ms周期，模型基础步长为10ms
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
		vTaskDelayUntil(&lastWakeTime, CORE_APP_PERIOD_MS);
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
		/* Take an atomic local snapshot; the ISR-owned queue item is a pointer. */
		taskENTER_CRITICAL();
		memcpy(&hcan1_recv, pcan1_recv, sizeof(hcan1_recv));
		taskEXIT_CRITICAL();
		memcpy(ESP_T_03, hcan1_recv.ESP_T_03, 8);
		memcpy(ESP_T_06, hcan1_recv.ESP_T_06, 8);
		memcpy(ESP_T_07, hcan1_recv.ESP_T_07, 8);
		memcpy(res_msg, hcan1_recv.res_msg, 8);
		memcpy(canb_ipctsmsg1, hcan1_recv.canb_ipctsmsg1, 8);
		memcpy(canb_ipctsmsg2, hcan1_recv.canb_ipctsmsg2, 8);
		memcpy(AMI_Tx, hcan1_recv.AMI_Tx, 8);
		memcpy(canb_epssendmsg1, hcan1_recv.canb_epssendmsg1, 8);
		memcpy(canb_epssendmsg2, hcan1_recv.canb_epssendmsg2, 8);
#if (VCU_ENABLE_BENCH_DEBUG != 0U)
		memcpy(vcu_dbg_control, hcan1_recv.vcu_dbg_control, 8);
		memcpy(vcu_dbg_pedal_adc, hcan1_recv.vcu_dbg_pedal_adc, 8);
		memcpy(vcu_dbg_air_wheel, hcan1_recv.vcu_dbg_air_wheel, 8);
		memcpy(vcu_dbg_digital, hcan1_recv.vcu_dbg_digital, 8);
		vcu_dbg_rx_count[0] = hcan1_recv.vcu_dbg_control_rx_count;
		vcu_dbg_rx_count[1] = hcan1_recv.vcu_dbg_pedal_rx_count;
		vcu_dbg_rx_count[2] = hcan1_recv.vcu_dbg_air_wheel_rx_count;
		vcu_dbg_rx_count[3] = hcan1_recv.vcu_dbg_digital_rx_count;
#endif
	}

	Task_CoreApp_ApplyCanFreshness();
	
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
	model_hin = BSP_Pin_GetHIN();
	PrgSts.hin = model_hin;

	/* APPS/brake are the board 0-5 V ADS1115 channels. The two pressure
	 * sensors use the MCU ADC channels designed for 0-10 V inputs. */
	model_ain[0] = hgetIn1.ads115_value[0];
	model_ain[1] = hgetIn1.ads115_value[1];
	model_ain[2] = hgetIn1.ads115_value[2];
	model_ain[3] = hgetIn1.adc0_value[0];
	model_ain[4] = hgetIn1.adc0_value[1];
	/* No physical wheel-speed assignment exists in the current hand code. */
	wlspd_fsensor = 0.0F;
	wlspd_hsensor = 0.0F;
}

static void Task_CoreApp_ApplyCanFreshness(void)
{
	static CAN_FRESHNESS_PAR esp03Fresh;
	static CAN_FRESHNESS_PAR esp06Fresh;
	static CAN_FRESHNESS_PAR esp07Fresh;
	static CAN_FRESHNESS_PAR resFresh;
	static CAN_FRESHNESS_PAR ipc1Fresh;
	static CAN_FRESHNESS_PAR ipc2Fresh;
	static CAN_FRESHNESS_PAR amiFresh;
	static CAN_FRESHNESS_PAR eps1Fresh;
	static CAN_FRESHNESS_PAR eps2Fresh;

	/* Command/feedback channels recover after three structurally valid frames.
	 * RES uses one valid frame so a checksum-valid Stop is never delayed. */
	if(!CAN_FreshnessUpdate(&esp03Fresh, hcan1_recv.esp_t03_rx_count,
		CAN_RECOVERY_VALID_FRAMES)) memset(ESP_T_03, 0, 8U);
	if(!CAN_FreshnessUpdate(&esp06Fresh, hcan1_recv.esp_t06_rx_count,
		CAN_RECOVERY_VALID_FRAMES)) memset(ESP_T_06, 0, 8U);
	if(!CAN_FreshnessUpdate(&esp07Fresh, hcan1_recv.esp_t07_rx_count,
		CAN_RECOVERY_VALID_FRAMES)) memset(ESP_T_07, 0, 8U);
	if(!CAN_FreshnessUpdate(&resFresh, hcan1_recv.res_rx_count, 1U))
		memset(res_msg, 0, 8U);
	if(!CAN_FreshnessUpdate(&ipc1Fresh, hcan1_recv.ipc_msg1_rx_count,
		CAN_RECOVERY_VALID_FRAMES)) memset(canb_ipctsmsg1, 0, 8U);
	if(!CAN_FreshnessUpdate(&ipc2Fresh, hcan1_recv.ipc_msg2_rx_count,
		CAN_RECOVERY_VALID_FRAMES)) memset(canb_ipctsmsg2, 0, 8U);
	if(!CAN_FreshnessUpdate(&amiFresh, hcan1_recv.ami_rx_count,
		CAN_RECOVERY_VALID_FRAMES)) memset(AMI_Tx, 0, 8U);
	if(!CAN_FreshnessUpdate(&eps1Fresh, hcan1_recv.eps_msg1_rx_count,
		CAN_RECOVERY_VALID_FRAMES)) memset(canb_epssendmsg1, 0, 8U);
	if(!CAN_FreshnessUpdate(&eps2Fresh, hcan1_recv.eps_msg2_rx_count,
		CAN_RECOVERY_VALID_FRAMES)) memset(canb_epssendmsg2, 0, 8U);
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

	/* 台架副本回显模型实际采用的输入；本体工程不发送这些报文。 */
#if (VCU_ENABLE_BENCH_DEBUG != 0U)
	memcpy(hcan_send.vcu_dbg_status, VCU10_Y.vcu_dbg_status, 8);
	memcpy(hcan_send.vcu_dbg_pedal_echo, VCU10_Y.vcu_dbg_pedal_echo, 8);
	memcpy(hcan_send.vcu_dbg_air_wheel_echo, VCU10_Y.vcu_dbg_air_wheel_echo, 8);
#endif

	//-----------------------------CAN2
	//-----------------------------OUT
	hvcuCtrl1.uln_out = VCU10_Y.model_lox;
	hvcuCtrl1.mc3_outh = VCU10_Y.model_hox;
	hvcuCtrl1.ebs_watchdog = (uint8_t)ebs_watchdog;

	//向队列中，发送数据。发送一个指向结构体对象的指针
	pcan_send = &hcan_send;
	xQueueSend(Que_Hcore_CanSend, (void *)&pcan_send, 0);

	//向队列中，发送数据。发送一个指向结构体对象的指针
	pvcuCtrl = &hvcuCtrl1;
	xQueueSend(Que_Hcore_VcuCtrl, (void *)&pvcuCtrl, 0);
}
