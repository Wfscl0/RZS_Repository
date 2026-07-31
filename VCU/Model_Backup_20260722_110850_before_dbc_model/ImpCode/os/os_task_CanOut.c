/*
 * ********************************************************************************
 * os_task_CanOut.c
 *
 * Created on: 2024年12月x日
 *     Author: ROG
 */
#include "os_task_CanOut.h"
#include "CAN_Node.h"
#include "userif.h"



static HCANSEND_PAR 	*pcan_send1;
static HCANSEND_PAR 	hcansend1;
static COMIN_PAR 		hcomIn1;
static COMIN_PAR 		*pcomIn1;

static void Task_CanOut_SignalReceive(HCANSEND_PAR *pcan_send);
static void Task_CanOut_50ms(void);
static void Task_CanOut_10ms(void);
static void Task_CanOut_20ms(void);
static void Task_CanOut_100ms(void);
static void Task_CanOut_500ms(void);
static void Task_CanOut_1000ms(void);

/* ********************************************************************************
 * CAN发送任务线程
 */
void OS_Task_CanOut(void *pvPara)
{
	uint16_t k1=1;
	uint32_t timer=0;

    //新增LastTick，用于使用vTaskDelayUntil函数
	TickType_t LastTick = 0;
	LastTick = xTaskGetTickCount();
	
	(void)pvPara;

	while(1)
	{   
		//请求消息。hcan_send
        if(xQueueReceive(Que_Hcore_CanSend, &(pcan_send1), 0) == pdTRUE)
        {
			Task_CanOut_SignalReceive(pcan_send1);
        }

        //请求消息。comIn
		if(xQueueReceive(Que_ComIn_CoreApp, &(pcomIn1), 0) == pdTRUE)
		{
			hcomIn1.jy60.AXL = pcomIn1->jy60.AXL;
			hcomIn1.jy60.AYL = pcomIn1->jy60.AYL;
			hcomIn1.jy60.AZL = pcomIn1->jy60.AZL;
			hcomIn1.jy60.WXL = pcomIn1->jy60.WXL;
			hcomIn1.jy60.WYL = pcomIn1->jy60.WYL;
			hcomIn1.jy60.WZL = pcomIn1->jy60.WZL;
			hcomIn1.jy60.Roll = pcomIn1->jy60.Roll;
			hcomIn1.jy60.Pitch = pcomIn1->jy60.Pitch;
			hcomIn1.jy60.Yaw = pcomIn1->jy60.Yaw;
			hcomIn1.jy60.Temperature = pcomIn1->jy60.Temperature;
		}

        timer = k1*10;
        Task_CanOut_10ms();
        if((k1%2) == 0) { //20ms
            Task_CanOut_20ms();
        }

        if((k1%5) == 0) { //50ms
        	Task_CanOut_50ms();
        }

        if((k1%10) == 0) { //100ms
			Task_CanOut_100ms();
		}

        if((k1%50) == 0) { //500ms
        	Task_CanOut_500ms();
        }

        if((k1%100) == 0) { //1000ms
        	Task_CanOut_1000ms();
        }

        k1++;
        if(k1 > 10000){
            k1 = 1;
        }

        vTaskDelayUntil(&LastTick,10); //优化，未使用vTaskDelay函数，使用该函数以相对时间delay
        PrgSts.task_CanOut++;
	}
}


/* ********************************************************************************
* 消息队列，数据转换
*/
static void Task_CanOut_SignalReceive(HCANSEND_PAR *pcan_send)
{
	//-----------------------------CAN0
	memcpy(hcansend1.cana_motor_cmd, pcan_send->cana_motor_cmd, 8);
	memcpy(hcansend1.cana_motor_cmd3, pcan_send->cana_motor_cmd3, 8);
	//memcpy(hcansend1.Tx20B, pcan_send->Tx20B, 8);

	//-----------------------------CAN1
	memcpy(hcansend1.ESP_R_00, pcan_send->ESP_R_00, 8);
	memcpy(hcansend1.canb_ipcrxmsg, pcan_send->canb_ipcrxmsg, 8);
	memcpy(hcansend1.AMI_Rx, pcan_send->AMI_Rx, 8);
	memcpy(hcansend1.canb_epsmsg, pcan_send->canb_epsmsg, 8);
	memcpy(hcansend1.vcu_dbg_status, pcan_send->vcu_dbg_status, 8);
	memcpy(hcansend1.vcu_dbg_pedal_echo, pcan_send->vcu_dbg_pedal_echo, 8);
	memcpy(hcansend1.vcu_dbg_air_wheel_echo, pcan_send->vcu_dbg_air_wheel_echo, 8);
}

static void Task_CanOut_20ms(void)
{
	//BSP_CAN1_Send_STD((uint32_t)0x220, hcansend1.Tx220);
	//BSP_CAN1_Send_STD((uint32_t)0x154, hcansend1.Tx154);
	//BSP_CAN0_Send_STD((uint32_t)0x169, hcansend1.Tx169);
	BSP_CAN1_Send_STD((uint32_t)0x20, hcansend1.ESP_R_00);
	BSP_CAN1_Send_STD((uint32_t)0x41, hcansend1.AMI_Rx);
	BSP_CAN1_Send_STD((uint32_t)0x469, hcansend1.canb_epsmsg);
}

static void Task_CanOut_1000ms(void)
{

}

static void Task_CanOut_50ms(void)
{
	//BSP_CAN0_Send_STD((uint32_t)0x20A, hcansend1.Tx20A);
	//BSP_CAN0_Send_STD((uint32_t)0x20B, hcansend1.Tx20B);
	BSP_CAN1_Send_STD((uint32_t)0x10, hcansend1.canb_ipcrxmsg);

}

static void Task_CanOut_100ms(void)
{
	/* Motor protocol parameter frame, CAN0 extended ID, 100 ms. */
	BSP_CAN0_Send_EXT((uint32_t)0x0CFF09EF, hcansend1.cana_motor_cmd3);

	BSP_CAN1_Send_STD((uint32_t)VCU_DBG_STATUS_ID, hcansend1.vcu_dbg_status);
	BSP_CAN1_Send_STD((uint32_t)VCU_DBG_PEDAL_ECHO_ID, hcansend1.vcu_dbg_pedal_echo);
	BSP_CAN1_Send_STD((uint32_t)VCU_DBG_AIR_WHEEL_ECHO_ID,
		hcansend1.vcu_dbg_air_wheel_echo);
}

static void Task_CanOut_10ms(void)
{
	/* 电机协议要求：MCU1_Rx_Command，29位扩展帧，DLC=8，周期10ms。 */
	BSP_CAN0_Send_EXT((uint32_t)0x0CFF08EF, hcansend1.cana_motor_cmd);
}


static void Task_CanOut_JY60_1(uint8_t temp[8])
{
	temp[0] = (uint8_t)((int16_t)(hcomIn1.jy60.AXL * 100) >> 8);
	temp[1] = (uint8_t)((int16_t)(hcomIn1.jy60.AXL * 100) & 0xFF);
	temp[2] = (uint8_t)((int16_t)(hcomIn1.jy60.AYL * 100) >> 8);
	temp[3] = (uint8_t)((int16_t)(hcomIn1.jy60.AYL * 100) & 0xFF);
	temp[4] = (uint8_t)((int16_t)(hcomIn1.jy60.AZL * 100) >> 8);
	temp[5] = (uint8_t)((int16_t)(hcomIn1.jy60.AZL * 100) & 0xFF);
	temp[6] = (uint8_t)((int16_t)(hcomIn1.jy60.Temperature * 100) >> 8);
	temp[7] = (uint8_t)((int16_t)(hcomIn1.jy60.Temperature * 100) & 0xFF);
}

static void Task_CanOut_JY60_2(uint8_t temp[8])
{
	temp[0] = (uint8_t)((int16_t)(hcomIn1.jy60.WXL * 100) >> 8);
	temp[1] = (uint8_t)((int16_t)(hcomIn1.jy60.WXL * 100) & 0xFF);
	temp[2] = (uint8_t)((int16_t)(hcomIn1.jy60.WYL * 100) >> 8);
	temp[3] = (uint8_t)((int16_t)(hcomIn1.jy60.WYL * 100) & 0xFF);
	temp[4] = (uint8_t)((int16_t)(hcomIn1.jy60.WZL * 100) >> 8);
	temp[5] = (uint8_t)((int16_t)(hcomIn1.jy60.WZL * 100) & 0xFF);
	temp[6] = 0;
	temp[7] = 0;
}

static void Task_CanOut_JY60_3(uint8_t temp[8])
{
	temp[0] = (uint8_t)((int16_t)(hcomIn1.jy60.Pitch * 100) >> 8);
	temp[1] = (uint8_t)((int16_t)(hcomIn1.jy60.Pitch * 100) & 0xFF);
	temp[2] = (uint8_t)((int16_t)(hcomIn1.jy60.Roll * 100) >> 8);
	temp[3] = (uint8_t)((int16_t)(hcomIn1.jy60.Roll * 100) & 0xFF);
	temp[4] = (uint8_t)((int16_t)(hcomIn1.jy60.Yaw * 100) >> 8);
	temp[5] = (uint8_t)((int16_t)(hcomIn1.jy60.Yaw * 100) & 0xFF);
	temp[6] = 0;
	temp[7] = 0;
}

static void Task_CanOut_500ms(void)
{
	uint8_t tempdata[8];

	Task_CanOut_JY60_1(tempdata);
	BSP_CAN1_Send_STD(0xBA, tempdata);
	Task_CanOut_JY60_2(tempdata);
	BSP_CAN1_Send_STD(0xBB, tempdata);
	Task_CanOut_JY60_3(tempdata);
	BSP_CAN1_Send_STD(0xBC, tempdata);
}










