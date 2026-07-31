/*
 * ********************************************************************************
 * VCU CAN2
 * bsp_can2.c
 *
 * Created on: 2024年3月x日
 *     Author: ROG
 */
#include "bsp_can2.h"
#include "os_task.h"
#include "CAN_Node.h"


/* ********************************************************************************
 * CAN2
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

static can_buff_config_t Tx_buffCfg_STD_EX =  {
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


static can_message_t 	recvMsg_CAN2_STD;
static can_message_t 	recvMsg_CAN2_EXT;
static HCAN2RX_PAR		can2_recv1; //接收缓存
static HCAN2RX_PAR 		*pcan2_recv1;

/* ********************************************************************************
 * CAN2_Callback
 */
void CAN2_Callback(uint32_t instance,can_event_t event,uint32_t buffIdx,void *flexcanState)
{
	(void)flexcanState;//此处防止警报
	(void)instance;
	(void)buffIdx;
	uint16_t  slaveid=0,tempid=0;

	//接收报文并重新注册回调函数
	CAN_Receive(&can2_instance, RX_MAILBOX_CAN2_STD, &recvMsg_CAN2_STD); //标准帧
	CAN_Receive(&can2_instance, RX_MAILBOX_CAN2_EXT, &recvMsg_CAN2_EXT); //扩展帧

	switch(event)//回调事件
	{
		case CAN_EVENT_RX_COMPLETE: //接收完成事件
			
			if(recvMsg_CAN2_STD.id != 0)
			{
				switch (recvMsg_CAN2_STD.id)
				{
					default:
						break;
				}
			}

			if(recvMsg_CAN2_EXT.id != 0)
			{
				tempid = (recvMsg_CAN2_EXT.id & 0xfff00)>>8;
				slaveid = (uint8_t)(recvMsg_CAN2_EXT.id & 0xff);
				switch (tempid)
				{
					default:
						break;
				}
			}
			
			//向队列中，发送数据。发送一个指向结构体对象的指针
			pcan2_recv1 = &can2_recv1;
			xQueueSendFromISR(Que_Hcan2_CanIn, (void *)&pcan2_recv1, 0);
			
			PrgSts.can2_isr++;
			recvMsg_CAN2_STD.id = 0;
			recvMsg_CAN2_EXT.id = 0;
			break;

		case CAN_EVENT_TX_COMPLETE: //发送完成事件
			break;
		default:
			break;
	}
}

static void CAN2_Operating_Modes(uint8_t mode)
{
	switch(mode)
	{
		case 0: //Normal mode
			//条件：STBN=H and EN=H
			CAN2_STBN_ON;
			CAN2_EN_ON;
			break;
		case 1: //Listen-only mode
			//条件：STBN=H and EN=L
			CAN2_STBN_ON;
			CAN2_EN_OFF;
			break;
		case 2: //Standby mode
			//条件：STBN=L and EN=L or wake flag set
			CAN2_STBN_OFF;
			CAN2_EN_OFF;
			break;
		case 3: //Go-to-Sleep mode
			//条件：STBN=L and EN=H or wake flag clear
			CAN2_STBN_OFF;
			CAN2_EN_ON;
			break;
		default:
			break;
	}
}

static uint8_t CAN2_Pin_Read(void)
{
	uint8_t key=0;

	if(CAN2_INH_Read)	{ key |= 1<<0; } //Else mode: HIGH
	else				{ key &= ~(0<<0); } //Sleep mode: floating

	if(CAN2_ERRN_Read)	{ key |= 1<<1; }
	else				{ key &= ~(0<<1); }

	return key;
}

/* ********************************************************************************
 * BSP_CAN2_Send
 */
void BSP_CAN2_Send_STD(uint16_t id, uint8_t data[8])
{
	uint16_t i;
	can_message_t Tx_msg; 
	
	Tx_msg.id = id;
	Tx_msg.length = 8;
	//Tx_msg.cs = 0;
	
	for(i=0; i<8; i++)
	{
		Tx_msg.data[i] = data[i];
	}
	
	_Bool  EX_Flag = false;
    while(CAN_GetTransferStatus(&can2_instance, TX_MAILBOX_CAN2_STD) != STATUS_SUCCESS){
		if((++i) > 500)
		{
			EX_Flag = true;
			CAN_AbortTransfer(&can2_instance,TX_MAILBOX_CAN2_STD);
			CAN_Send(&can2_instance, TX_MAILBOX_CAN2_STD, &Tx_msg);
			break;
		}
	}
	if (!EX_Flag) CAN_Send(&can2_instance, TX_MAILBOX_CAN2_STD, &Tx_msg);
}

void BSP_CAN2_Send_EXT(uint32_t id, uint8_t data[8])
{
	uint16_t i;
	can_message_t Tx_msg; 
	
	Tx_msg.id = id;
	Tx_msg.length = 8;
	//Tx_msg.cs = 0;
	
	for(i=0; i<8; i++)
	{
		Tx_msg.data[i] = data[i];
	}

//    CAN_AbortTransfer(&can2_instance,TX_MAILBOX_CAN2_EXT);
	while(CAN_GetTransferStatus(&can2_instance, TX_MAILBOX_CAN2_EXT) != STATUS_SUCCESS){
		if((++i) > 1000) break;
	}
	CAN_Send(&can2_instance, TX_MAILBOX_CAN2_EXT, &Tx_msg);
}



/* ********************************************************************************
 * CAN2_Init
 */
void BSP_CAN2_Init(void)
{
	uint32_t Rx_Filter = 0x00;

	CAN_Init(&can2_instance, &can2_Config0);
	//注册接收配置和MSGID过滤器
	CAN_ConfigRxBuff(&can2_instance, RX_MAILBOX_CAN2_STD, &Rx_buffCfg_STD, Rx_Filter);
	CAN_ConfigTxBuff(&can2_instance, TX_MAILBOX_CAN2_STD, &Tx_buffCfg_STD); //配置发送
	CAN_ConfigTxBuff(&can2_instance, TX_MAILBOX_CAN2_STD_EX, &Tx_buffCfg_STD_EX); //配置发送

	CAN_ConfigRxBuff(&can2_instance, RX_MAILBOX_CAN2_EXT, &Rx_buffCfg_EXT, Rx_Filter);
	CAN_ConfigTxBuff(&can2_instance, TX_MAILBOX_CAN2_EXT, &Tx_buffCfg_EXT); //配置发送

	/*设置MSGID的掩码，掩码粗略可以理解为对11bit MSGID地址的过滤，
	如果某bit位需要过滤设置为1,不过滤设置为0,例如掩码设置为0x7ff则过滤全部标准id,
	如果设置为0x7fe,这只能接受0x01的报文(不存在0x0的地址)*/
	CAN_SetRxFilter(&can2_instance, CAN_MSG_ID_STD, RX_MAILBOX_CAN2_STD, 0x0000); //设置MSGID掩码
	CAN_SetRxFilter(&can2_instance, CAN_MSG_ID_EXT, RX_MAILBOX_CAN2_EXT, 0x00000000); //设置MSGID掩码
	CAN_InstallEventCallback(&can2_instance, &CAN2_Callback, (void*)0); //注册回调函数
	
	//外设默认优先级00！会导致操作系统内核函数无法调用，导致系统错误！！！
	//重新设置外设中断优先级。
	INT_SYS_SetPriority(CAN2_ORed_0_15_MB_IRQn, 0x02);

	//此函数不只有接收作用 还有续订回调函数的作用
	CAN_Receive(&can2_instance, RX_MAILBOX_CAN2_STD, &recvMsg_CAN2_STD); //标准帧
	CAN_Receive(&can2_instance, RX_MAILBOX_CAN2_EXT, &recvMsg_CAN2_EXT); //扩展帧

	CAN2_Operating_Modes(0); //Normal mode
}

uint8_t BSP_CAN2_Modes(uint8_t mode)
{
	uint8_t key1;
	static uint8_t modelast=0;
	
	if(modelast != mode)
	{
		modelast = mode;
		CAN2_Operating_Modes(mode); //设置CAN工作模式
	}
	
	key1 = CAN2_Pin_Read(); //查询CAN硬件引脚信息
	
	return key1;

}


