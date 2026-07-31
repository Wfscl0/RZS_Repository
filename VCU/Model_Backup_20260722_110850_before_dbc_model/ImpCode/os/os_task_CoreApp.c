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

/* Debug input must be refreshed at least once every 500 ms. */
#define VCU_DBG_TIMEOUT_CYCLES  (500U / CORE_APP_PERIOD_MS)

static uint8_t  vcu_dbg_requested_flags;
static uint8_t  vcu_dbg_active_flags;
static uint8_t  vcu_dbg_last_control_count;
static uint8_t  vcu_dbg_last_pedal_count;
static uint8_t  vcu_dbg_last_air_wheel_count;
static uint8_t  vcu_dbg_last_digital_count;
static uint16_t vcu_dbg_control_age = VCU_DBG_TIMEOUT_CYCLES;
static uint16_t vcu_dbg_pedal_age = VCU_DBG_TIMEOUT_CYCLES;
static uint16_t vcu_dbg_air_wheel_age = VCU_DBG_TIMEOUT_CYCLES;
static uint16_t vcu_dbg_digital_age = VCU_DBG_TIMEOUT_CYCLES;

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
static void Task_CoreApp_DebugUpdate(void);
static void Task_CoreApp_SignalConvert(void);
static void Task_CoreApp_SignalSend(void);
static uint16_t Task_CoreApp_ReadU16LE(const uint8_t data[8], uint8_t index);
static void Task_CoreApp_WriteU16LE(uint8_t data[8], uint8_t index, uint16_t value);

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
		Task_CoreApp_DebugUpdate();
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
		/* Take a local snapshot; the ISR-owned queue item is a pointer. */
		memcpy(&hcan1_recv, pcan1_recv, sizeof(hcan1_recv));
		memcpy(ESP_T_03, hcan1_recv.ESP_T_03, 8);
		memcpy(ESP_T_06, hcan1_recv.ESP_T_06, 8);
		memcpy(ESP_T_07, hcan1_recv.ESP_T_07, 8);
		memcpy(res_msg, hcan1_recv.res_msg, 8);
		memcpy(canb_ipctsmsg1, hcan1_recv.canb_ipctsmsg1, 8);
		memcpy(canb_ipctsmsg2, hcan1_recv.canb_ipctsmsg2, 8);
		memcpy(AMI_Tx, hcan1_recv.AMI_Tx, 8);
		memcpy(canb_epssendmsg1, hcan1_recv.canb_epssendmsg1, 8);
		memcpy(canb_epssendmsg2, hcan1_recv.canb_epssendmsg2, 8);
	}
	
	// 请求消息。CAN2_In
	if(xQueueReceive(Que_Hcan2_CanIn, &(pcan2_recv), 0) == pdTRUE)
	{

	}
}

/*
 * Update debug-frame watchdogs and derive the active override mask.
 * A valid control frame requires unlock bytes A5 5A. Stopping the cyclic
 * control or data frame automatically restores the corresponding hardware input.
 */
static void Task_CoreApp_DebugUpdate(void)
{
	if(hcan1_recv.vcu_dbg_control_rx_count != vcu_dbg_last_control_count)
	{
		vcu_dbg_last_control_count = hcan1_recv.vcu_dbg_control_rx_count;
		if((hcan1_recv.vcu_dbg_control[0] == VCU_DBG_UNLOCK_BYTE0) &&
		   (hcan1_recv.vcu_dbg_control[1] == VCU_DBG_UNLOCK_BYTE1))
		{
			vcu_dbg_requested_flags =
				(uint8_t)(hcan1_recv.vcu_dbg_control[2] & 0x0FU);
			vcu_dbg_control_age = 0U;
		}
		else
		{
			vcu_dbg_requested_flags = 0U;
			vcu_dbg_control_age = VCU_DBG_TIMEOUT_CYCLES;
		}
	}
	else if(vcu_dbg_control_age < VCU_DBG_TIMEOUT_CYCLES)
	{
		vcu_dbg_control_age++;
	}

	if(hcan1_recv.vcu_dbg_pedal_rx_count != vcu_dbg_last_pedal_count)
	{
		vcu_dbg_last_pedal_count = hcan1_recv.vcu_dbg_pedal_rx_count;
		vcu_dbg_pedal_age = 0U;
	}
	else if(vcu_dbg_pedal_age < VCU_DBG_TIMEOUT_CYCLES)
	{
		vcu_dbg_pedal_age++;
	}

	if(hcan1_recv.vcu_dbg_air_wheel_rx_count != vcu_dbg_last_air_wheel_count)
	{
		vcu_dbg_last_air_wheel_count = hcan1_recv.vcu_dbg_air_wheel_rx_count;
		vcu_dbg_air_wheel_age = 0U;
	}
	else if(vcu_dbg_air_wheel_age < VCU_DBG_TIMEOUT_CYCLES)
	{
		vcu_dbg_air_wheel_age++;
	}

	if(hcan1_recv.vcu_dbg_digital_rx_count != vcu_dbg_last_digital_count)
	{
		vcu_dbg_last_digital_count = hcan1_recv.vcu_dbg_digital_rx_count;
		vcu_dbg_digital_age = 0U;
	}
	else if(vcu_dbg_digital_age < VCU_DBG_TIMEOUT_CYCLES)
	{
		vcu_dbg_digital_age++;
	}

	vcu_dbg_active_flags = 0U;
	if(((vcu_dbg_requested_flags & VCU_DBG_FLAG_MASTER) != 0U) &&
	   (vcu_dbg_control_age < VCU_DBG_TIMEOUT_CYCLES))
	{
		vcu_dbg_active_flags |= VCU_DBG_FLAG_MASTER;
		if(((vcu_dbg_requested_flags & VCU_DBG_FLAG_PEDAL_ADC) != 0U) &&
		   (vcu_dbg_pedal_age < VCU_DBG_TIMEOUT_CYCLES))
		{
			vcu_dbg_active_flags |= VCU_DBG_FLAG_PEDAL_ADC;
		}
		if(((vcu_dbg_requested_flags & VCU_DBG_FLAG_AIR_WHEEL) != 0U) &&
		   (vcu_dbg_air_wheel_age < VCU_DBG_TIMEOUT_CYCLES))
		{
			vcu_dbg_active_flags |= VCU_DBG_FLAG_AIR_WHEEL;
		}
		if(((vcu_dbg_requested_flags & VCU_DBG_FLAG_DIGITAL) != 0U) &&
		   (vcu_dbg_digital_age < VCU_DBG_TIMEOUT_CYCLES))
		{
			vcu_dbg_active_flags |= VCU_DBG_FLAG_DIGITAL;
		}
	}
}

/// @brief 信号传入模型的函数
/// @param hcan0_recv:CAN0通道接收到报文的缓存数据
/// @param hcan1_recv:CAN1通道接收到报文的缓存数据
/// @param hcan2_recv:CAN2通道接收到报文的缓存数据
static void Task_CoreApp_SignalConvert(void)
{
	//模型接口IO：model_ain顺序为APP1、APP2、制动、气压1、气压2
	if((vcu_dbg_active_flags & VCU_DBG_FLAG_DIGITAL) != 0U)
	{
		model_hin = Task_CoreApp_ReadU16LE(hcan1_recv.vcu_dbg_digital, 0U);
	}
	else
	{
		model_hin = hgetIn2.hin;
	}
	PrgSts.hin = model_hin;

	if((vcu_dbg_active_flags & VCU_DBG_FLAG_PEDAL_ADC) != 0U)
	{
		model_ain[0] = Task_CoreApp_ReadU16LE(hcan1_recv.vcu_dbg_pedal_adc, 0U);
		model_ain[1] = Task_CoreApp_ReadU16LE(hcan1_recv.vcu_dbg_pedal_adc, 2U);
		model_ain[2] = Task_CoreApp_ReadU16LE(hcan1_recv.vcu_dbg_pedal_adc, 4U);
	}
	else
	{
		model_ain[0] = hgetIn1.adc0_value[0];
		model_ain[1] = hgetIn1.adc0_value[1];
		model_ain[2] = hgetIn1.adc0_value[2];
	}

	if((vcu_dbg_active_flags & VCU_DBG_FLAG_AIR_WHEEL) != 0U)
	{
		model_ain[3] = Task_CoreApp_ReadU16LE(hcan1_recv.vcu_dbg_air_wheel, 0U);
		model_ain[4] = Task_CoreApp_ReadU16LE(hcan1_recv.vcu_dbg_air_wheel, 2U);
		wlspd_fsensor = (real32_T)Task_CoreApp_ReadU16LE(
			hcan1_recv.vcu_dbg_air_wheel, 4U) * 0.1F;
		wlspd_hsensor = (real32_T)Task_CoreApp_ReadU16LE(
			hcan1_recv.vcu_dbg_air_wheel, 6U) * 0.1F;
	}
	else
	{
		model_ain[3] = hgetIn1.ads115_value[0];
		model_ain[4] = hgetIn1.ads115_value[1];
		/* No physical wheel-speed assignment exists in the current hand code. */
		wlspd_fsensor = 0.0F;
		wlspd_hsensor = 0.0F;
	}
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

	/* Bench-debug status and echo frames for TSMaster. */
	hcan_send.vcu_dbg_status[0] = vcu_dbg_active_flags;
	hcan_send.vcu_dbg_status[1] = vcu_dbg_requested_flags;
	Task_CoreApp_WriteU16LE(hcan_send.vcu_dbg_status, 2U, model_hin);
	hcan_send.vcu_dbg_status[4] = VCU10_Y.model_lox;
	hcan_send.vcu_dbg_status[5] = VCU10_Y.model_hox;
	hcan_send.vcu_dbg_status[6] = (uint8_t)vcu_dbg_control_age;
	hcan_send.vcu_dbg_status[7] = hcan1_recv.vcu_dbg_control_rx_count;

	Task_CoreApp_WriteU16LE(hcan_send.vcu_dbg_pedal_echo, 0U, model_ain[0]);
	Task_CoreApp_WriteU16LE(hcan_send.vcu_dbg_pedal_echo, 2U, model_ain[1]);
	Task_CoreApp_WriteU16LE(hcan_send.vcu_dbg_pedal_echo, 4U, model_ain[2]);
	hcan_send.vcu_dbg_pedal_echo[6] =
		(uint8_t)(((vcu_dbg_active_flags & VCU_DBG_FLAG_PEDAL_ADC) != 0U) ? 1U : 0U);
	hcan_send.vcu_dbg_pedal_echo[7] = hcan1_recv.vcu_dbg_pedal_rx_count;

	Task_CoreApp_WriteU16LE(hcan_send.vcu_dbg_air_wheel_echo, 0U, model_ain[3]);
	Task_CoreApp_WriteU16LE(hcan_send.vcu_dbg_air_wheel_echo, 2U, model_ain[4]);
	Task_CoreApp_WriteU16LE(hcan_send.vcu_dbg_air_wheel_echo, 4U,
		(uint16_t)(wlspd_fsensor * 10.0F + 0.5F));
	Task_CoreApp_WriteU16LE(hcan_send.vcu_dbg_air_wheel_echo, 6U,
		(uint16_t)(wlspd_hsensor * 10.0F + 0.5F));

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

static uint16_t Task_CoreApp_ReadU16LE(const uint8_t data[8], uint8_t index)
{
	return (uint16_t)((uint16_t)data[index] |
		((uint16_t)data[(uint8_t)(index + 1U)] << 8));
}

static void Task_CoreApp_WriteU16LE(uint8_t data[8], uint8_t index, uint16_t value)
{
	data[index] = (uint8_t)(value & 0x00FFU);
	data[(uint8_t)(index + 1U)] = (uint8_t)(value >> 8);
}



