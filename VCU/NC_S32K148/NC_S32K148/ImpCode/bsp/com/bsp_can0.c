/*
 * ********************************************************************************
 * VCU CAN0
 * bsp_can0.c
 *
 * Created on: 2024年12月x日
 *     Author: ROG
 */
#include "bsp_can0.h"
#include "os_task.h"
#include "CAN_Node.h"



/* ********************************************************************************
 * CAN0
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


static can_message_t 	recvMsg_CAN0_STD;
static can_message_t 	recvMsg_CAN0_EXT;
static HCAN0RX_PAR		can0_recv1; //接收缓存
static HCAN0RX_PAR		*pcan0_recv1; //接收缓存

/* ********************************************************************************
 * CAN0_Callback
 */
void CAN0_Callback(uint32_t instance,can_event_t event,uint32_t buffIdx,void *flexcanState)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	(void)flexcanState;//此处防止警报
	(void)instance;

	switch(event)//回调事件
	{
		case CAN_EVENT_RX_COMPLETE: //接收完成事件
			if(buffIdx == RX_MAILBOX_CAN0_STD)
			{
				if((recvMsg_CAN0_STD.id == RX_ID) &&
					(recvMsg_CAN0_STD.length > 0U) &&
					(recvMsg_CAN0_STD.data[0] == 0x42U))
				{
					bootjumpflag = 1U;
				}
				CAN_Receive(&can0_instance, RX_MAILBOX_CAN0_STD, &recvMsg_CAN0_STD);
			}
			else if(buffIdx == RX_MAILBOX_CAN0_EXT)
			{
				CAN_Receive(&can0_instance, RX_MAILBOX_CAN0_EXT, &recvMsg_CAN0_EXT);
			}
			
			//向队列中，发送数据。发送一个指向结构体对象的指针
			pcan0_recv1 = &can0_recv1;
			xQueueSendFromISR(Que_Hcan0_CanIn, (void *)&pcan0_recv1,
				&xHigherPriorityTaskWoken);
			
			PrgSts.can0_isr++;
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
			break;

		case CAN_EVENT_TX_COMPLETE: //发送完成事件
			break;
		default:
			break;
	}
}

static void CAN0_Send(uint32_t mailbox, uint32_t id, const uint8_t *data,
	uint8_t length)
{
	can_message_t message = {0};

	if(length > 8U)
	{
		length = 8U;
	}
	message.id = id;
	message.length = length;
	memcpy(message.data, data, length);
	(void)CAN_SendBlocking(&can0_instance, mailbox, &message, 2U);
}

/* ********************************************************************************
 * BSP_CAN0_Send
 */
void BSP_CAN0_Send_STD(uint16_t id, uint8_t data[8])
{
	CAN0_Send(TX_MAILBOX_CAN0_STD, id, data, 8U);
}

void BSP_CAN0_Send_EXT(uint32_t id, uint8_t data[8])
{
	CAN0_Send(TX_MAILBOX_CAN0_EXT, id, data, 8U);
}

void BSP_CAN0_Send_XCP(uint16_t id, uint8_t* data,uint8_t len)
{
	CAN0_Send(TX_MAILBOX_CAN0_STD, id, data, len);
}

void BSP_CAN0_Send_BSW(uint32_t id, uint8_t data[8], uint8_t len)
{
	CAN0_Send(TX_MAILBOX_CAN0_STD, id, data, len);
}


/* ********************************************************************************
 * CAN0_Init
 */
void BSP_CAN0_Init(void)
{
	uint32_t Rx_Filter = 0x00;

	CAN_Init(&can0_instance, &can0_Config0);
	//注册接收配置和MSGID过滤器
	CAN_ConfigRxBuff(&can0_instance, RX_MAILBOX_CAN0_STD, &Rx_buffCfg_STD, Rx_Filter);
	CAN_ConfigTxBuff(&can0_instance, TX_MAILBOX_CAN0_STD, &Tx_buffCfg_STD); //配置发送

	CAN_ConfigRxBuff(&can0_instance, RX_MAILBOX_CAN0_EXT, &Rx_buffCfg_EXT, Rx_Filter);
	CAN_ConfigTxBuff(&can0_instance, TX_MAILBOX_CAN0_EXT, &Tx_buffCfg_EXT); //配置发送

	/*设置MSGID的掩码，掩码粗略可以理解为对11bit MSGID地址的过滤，
	如果某bit位需要过滤设置为1,不过滤设置为0,例如掩码设置为0x7ff则过滤全部标准id,
	如果设置为0x7fe,这只能接受0x01的报文(不存在0x0的地址)*/
	CAN_SetRxFilter(&can0_instance, CAN_MSG_ID_STD, RX_MAILBOX_CAN0_STD, 0x0000); //设置MSGID掩码
	CAN_SetRxFilter(&can0_instance, CAN_MSG_ID_EXT, RX_MAILBOX_CAN0_EXT, 0x00000000); //设置MSGID掩码
	CAN_InstallEventCallback(&can0_instance, &CAN0_Callback, (void*)0); //注册回调函数
	
	//外设默认优先级00！会导致操作系统内核函数无法调用，导致系统错误！！！
	//重新设置外设中断优先级。
	INT_SYS_SetPriority(CAN0_ORed_0_15_MB_IRQn, 0x02);

	//此函数不只有接收作用 还有续订回调函数的作用
	CAN_Receive(&can0_instance, RX_MAILBOX_CAN0_STD, &recvMsg_CAN0_STD); //标准帧
	CAN_Receive(&can0_instance, RX_MAILBOX_CAN0_EXT, &recvMsg_CAN0_EXT); //扩展帧
}




