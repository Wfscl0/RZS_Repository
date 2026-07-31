/*
 * ********************************************************************************
 * VCU CAN1
 * bsp_can1.c
 *
 * Created on: 2024年12月x日
 *     Author: ROG
 */
#include "bsp_can1.h"
#include "os_task.h"
#include "CAN_Node.h"
#include "userif.h"


/* ********************************************************************************
 * CAN1
 */
/*此结构体必须设置为全局变量 否则发送报文为遥控帧*/
static can_buff_config_t Rx_buffCfg_STD =  {
	.enableFD = false,  //CANFD帧 true false
	.enableBRS = false, //可变波特率
	.fdPadding = 8U,    //data length code (DLC)
	.idType = CAN_MSG_ID_STD, //standard or extended CAN_MSG_ID_STD
	.isRemote = false   //standard or remote
};

static can_buff_config_t Rx_buffCfg_EXT =  {
	.enableFD = false,  //CANFD帧 true false
	.enableBRS = false, //可变波特率
	.fdPadding = 8U,    //data length code (DLC)
	.idType = CAN_MSG_ID_EXT, //standard or extended CAN_MSG_ID_EXT
	.isRemote = false   //standard or remote
};

static can_buff_config_t Tx_buffCfg_STD =  {
	.enableFD = false,  //CANFD帧
	.enableBRS = false, //可变波特率
	.fdPadding = 8U,    //data length code (DLC)
	.idType = CAN_MSG_ID_STD, //standard or extended
	.isRemote = false   //standard or remote
};

static can_buff_config_t Tx_buffCfg_EXT =  {
	.enableFD = false,  //CANFD帧
	.enableBRS = false, //可变波特率
	.fdPadding = 8U,    //data length code (DLC)
	.idType = CAN_MSG_ID_EXT, //standard or extended
	.isRemote = false   //standard or remote
};


static can_message_t 	recvMsg_CAN1_STD;
static can_message_t 	recvMsg_CAN1_EXT;
static HCAN1RX_PAR		can1_recv1; //接收缓存
static HCAN1RX_PAR 		*pcan1_recv1;

static bool CAN1_ProcessStdFrame(const can_message_t *message)
{
	if(message->length != 8U)
	{
		return false;
	}

	switch(message->id)
	{
		case 0x13U:
			memcpy(can1_recv1.ESP_T_03, message->data, 8U);
			can1_recv1.esp_t03_rx_count++;
			break;
		case 0x16U:
			memcpy(can1_recv1.ESP_T_06, message->data, 8U);
			can1_recv1.esp_t06_rx_count++;
			break;
		case 0x17U:
			memcpy(can1_recv1.ESP_T_07, message->data, 8U);
			can1_recv1.esp_t07_rx_count++;
			break;
		case 0x1E4U:
			/* RES byte 2 is the XOR of bytes 0 and 1. Invalid Stop frames
			 * must never enter the model, even though ordinary bus faults are
			 * tolerated by the model-side confirmed timeout. */
			if(message->data[2] != (uint8_t)(message->data[0] ^ message->data[1]))
			{
				return false;
			}
			memcpy(can1_recv1.res_msg, message->data, 8U);
			can1_recv1.res_rx_count++;
			break;
		case 0x11U:
			memcpy(can1_recv1.canb_ipctsmsg1, message->data, 8U);
			can1_recv1.ipc_msg1_rx_count++;
			break;
		case 0x12U:
			memcpy(can1_recv1.canb_ipctsmsg2, message->data, 8U);
			can1_recv1.ipc_msg2_rx_count++;
			break;
		case 0x42U:
			memcpy(can1_recv1.AMI_Tx, message->data, 8U);
			can1_recv1.ami_rx_count++;
			break;
		case 0x401U:
			memcpy(can1_recv1.canb_epssendmsg1, message->data, 8U);
			can1_recv1.eps_msg1_rx_count++;
			break;
		case 0x402U:
			memcpy(can1_recv1.canb_epssendmsg2, message->data, 8U);
			can1_recv1.eps_msg2_rx_count++;
			break;
#if (VCU_ENABLE_BENCH_DEBUG != 0U)
		case VCU_DBG_CONTROL_ID:
			memcpy(can1_recv1.vcu_dbg_control, message->data, 8U);
			can1_recv1.vcu_dbg_control_rx_count++;
			break;
		case VCU_DBG_PEDAL_ADC_ID:
			memcpy(can1_recv1.vcu_dbg_pedal_adc, message->data, 8U);
			can1_recv1.vcu_dbg_pedal_rx_count++;
			break;
		case VCU_DBG_AIR_WHEEL_ID:
			memcpy(can1_recv1.vcu_dbg_air_wheel, message->data, 8U);
			can1_recv1.vcu_dbg_air_wheel_rx_count++;
			break;
		case VCU_DBG_DIGITAL_ID:
			memcpy(can1_recv1.vcu_dbg_digital, message->data, 8U);
			can1_recv1.vcu_dbg_digital_rx_count++;
			break;
#endif
		default:
			return false;
	}

	return true;
}

/* ********************************************************************************
 * CAN1_Callback
 */
void CAN1_Callback(uint32_t instance,can_event_t event,uint32_t buffIdx,void *flexcanState)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	bool notifyTask = false;

	(void)flexcanState;//此处防止警报
	(void)instance;

	switch(event)//回调事件
	{
		case CAN_EVENT_RX_COMPLETE: //接收完成事件
			if(buffIdx == RX_MAILBOX_CAN1_STD)
			{
				notifyTask = CAN1_ProcessStdFrame(&recvMsg_CAN1_STD);
				CAN_Receive(&can1_instance, RX_MAILBOX_CAN1_STD, &recvMsg_CAN1_STD);
			}
			else if(buffIdx == RX_MAILBOX_CAN1_EXT)
			{
				CAN_Receive(&can1_instance, RX_MAILBOX_CAN1_EXT, &recvMsg_CAN1_EXT);
			}

			if(notifyTask)
			{
				pcan1_recv1 = &can1_recv1;
				xQueueSendFromISR(Que_Hcan1_CanIn, (void *)&pcan1_recv1,
					&xHigherPriorityTaskWoken);
			}
			PrgSts.can1_isr++;
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
			break;

		case CAN_EVENT_TX_COMPLETE: //发送完成事件
			break;
		default:
			break;
	}
}

/* ********************************************************************************
 * BSP_CAN1_Send
 */
void BSP_CAN1_Send_STD(uint16_t id, uint8_t data[8])
{
	can_message_t Tx_msg = {0};

	Tx_msg.id = id;
	Tx_msg.length = 8U;
	memcpy(Tx_msg.data, data, 8U);
	(void)CAN_SendBlocking(&can1_instance, TX_MAILBOX_CAN1_STD, &Tx_msg, 2U);
}

//void BSP_CAN1_Send_STD_MB(uint16_t id, uint8_t data[8],uint32_t MB)
//{
//	uint16_t i;
//	can_message_t Tx_msg;
//
//	Tx_msg.id = id;
//	Tx_msg.length = 8;
//	//Tx_msg.cs = 0;
//
//	for(i=0; i<8; i++)
//	{
//		Tx_msg.data[i] = data[i];
//	}
//
////	CAN_AbortTransfer(&can1_instance,MB);
//	 while(CAN_GetTransferStatus(&can1_instance, TX_MAILBOX_CAN1_STD) != STATUS_SUCCESS){
//	 	if((++i) > 1000) break;
//	 }
//	CAN_Send(&can1_instance, TX_MAILBOX_CAN1_STD, &Tx_msg);
//}

void BSP_CAN1_Send_EXT(uint32_t id, uint8_t data[8])
{
	can_message_t Tx_msg = {0};

	Tx_msg.id = id;
	Tx_msg.length = 8U;
	memcpy(Tx_msg.data, data, 8U);
	(void)CAN_SendBlocking(&can1_instance, TX_MAILBOX_CAN1_EXT, &Tx_msg, 2U);
}


/* ********************************************************************************
 * CAN1_Init
 */
void BSP_CAN1_Init(void)
{
	uint32_t Rx_Filter = 0x00;

	CAN_Init(&can1_instance, &can1_Config0);
	//注册接收配置和MSGID过滤器
	CAN_ConfigRxBuff(&can1_instance, RX_MAILBOX_CAN1_STD, &Rx_buffCfg_STD, Rx_Filter);
	CAN_ConfigTxBuff(&can1_instance, TX_MAILBOX_CAN1_STD, &Tx_buffCfg_STD); //配置发送

	CAN_ConfigRxBuff(&can1_instance, RX_MAILBOX_CAN1_EXT, &Rx_buffCfg_EXT, Rx_Filter);
	CAN_ConfigTxBuff(&can1_instance, TX_MAILBOX_CAN1_EXT, &Tx_buffCfg_EXT); //配置发送

	/*设置MSGID的掩码，掩码粗略可以理解为对11bit MSGID地址的过滤，
	如果某bit位需要过滤设置为1,不过滤设置为0,例如掩码设置为0x7ff则过滤全部标准id,
	如果设置为0x7fe,这只能接受0x01的报文(不存在0x0的地址)*/
	CAN_SetRxFilter(&can1_instance, CAN_MSG_ID_STD, RX_MAILBOX_CAN1_STD, 0x0000); //设置MSGID掩码
	CAN_SetRxFilter(&can1_instance, CAN_MSG_ID_EXT, RX_MAILBOX_CAN1_EXT, 0x00000000); //设置MSGID掩码
	CAN_InstallEventCallback(&can1_instance, &CAN1_Callback, (void*)0); //注册回调函数
	
	//外设默认优先级00！会导致操作系统内核函数无法调用，导致系统错误！！！
	//重新设置外设中断优先级。
	INT_SYS_SetPriority(CAN1_ORed_0_15_MB_IRQn, 0x02);

	//此函数不只有接收作用 还有续订回调函数的作用
	CAN_Receive(&can1_instance, RX_MAILBOX_CAN1_STD, &recvMsg_CAN1_STD); //标准帧
	CAN_Receive(&can1_instance, RX_MAILBOX_CAN1_EXT, &recvMsg_CAN1_EXT); //扩展帧
}



