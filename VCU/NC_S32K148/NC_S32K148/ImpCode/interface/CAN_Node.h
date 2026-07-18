#ifndef _CAN_NODE_H_
#define _CAN_NODE_H_

#include <string.h>
#include <stdio.h>


/*******************************************************************************
** CAN接收缓存 结构体变量声明
*/

//CAN0 队列数据交互。数据格式定义
typedef struct
{
	//uint8_t  Rx201[8]; //SES反馈
	//uint8_t  Rx202[8]; //SES反馈

}HCAN0RX_PAR;

//CAN1 队列数据交互。数据格式定义
typedef struct
{
	//uint8_t  Rx1A0[8]; //电机反馈
	//uint8_t  Rx2A0[8]; //电机反馈
	//uint8_t  Rx142[8]; //DBS反馈
	//uint8_t  Rx143[8]; //DBS反馈
	uint8_t  ESP_T_03[8];
	uint8_t  res_msg[8];
	uint8_t  canb_ipctsmsg1[8];
	uint8_t  canb_ipctsmsg2[8];
	uint8_t  AMI_Tx[8];
	uint8_t  canb_epssendmsg1[8];
	uint8_t  canb_epssendmsg2[8];
}HCAN1RX_PAR;

//CAN2 队列数据交互。数据格式定义
typedef struct
{
	//uint8_t  Rx1B0[3][9]; //VCU

}HCAN2RX_PAR;


/*******************************************************************************
** CAN发送缓存 结构体变量声明
*/
//CAN发送 队列数据交互。数据格式定义
typedef struct
{
	//CAN0
	//uint8_t Tx169[8]; //转向
	//uint8_t Tx20A[8]; //显示屏
	//uint8_t Tx20B[8]; //显示屏
	uint8_t cana_motor_cmd[8];
	uint8_t cana_motor_cmd3[8];

	//CAN1
	//uint8_t Tx220[8]; //电机
	//uint8_t Tx154[8]; //制动
	uint8_t ESP_R_00[8];
	uint8_t canb_ipcrxmsg[8];
	uint8_t AMI_Rx[8];
	uint8_t canb_epsmsg[8];

	//CAN2

}HCANSEND_PAR;



#endif
