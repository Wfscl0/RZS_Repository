/*
 * os_task_CanOut.h
 *
 * Created on: 2024年3月x日
 *     Author: ROG
 */
#ifndef _OS_TASK_CANOUT_H
#define _OS_TASK_CANOUT_H

#include "os_task.h"



//队列数据交互。数据格式定义
typedef struct
{
	uint8_t  type;		//0:std   1:ext
	uint32_t id;       	/*!< ID of the message */
    uint8_t  data[8];	/*!< Data bytes of the CAN message*/

}HCAN_PAR;

typedef struct
{
	uint8_t  type;		//0:std   1:ext
	uint32_t id;       	/*!< ID of the message */
    uint8_t  data[8];	/*!< Data bytes of the CAN message*/
	
}HCAN_PAR1;

////队列数据交互。数据格式定义
//typedef struct
//{
//	//发送报文
//	HCAN_PAR1 TxC01F001;
//	HCAN_PAR1 TxC01F002;
//	HCAN_PAR1 TxC11E2B1;
//	HCAN_PAR1 Tx18003AD0;
//	//新增VCU与SVCU通信报文
//	HCAN_PAR1 Tx1A0;
//	HCAN_PAR1 Tx1B0;
//	HCAN_PAR1 Tx1B1;
//    HCAN_PAR1 Tx1B2;
//	HCAN_PAR1 Tx1B3;
//    HCAN_PAR1 Tx1B4;
//	HCAN_PAR1 Tx1B5;
//    HCAN_PAR1 Tx1B6;
//	HCAN_PAR1 Tx1B7;
//    HCAN_PAR1 Tx1B8;
//    //新增发送至遥控器报文
//    HCAN_PAR1 Tx1D1;
//    HCAN_PAR1 Tx1D2;
//    HCAN_PAR1 Tx1D3;
//    HCAN_PAR1 Tx1D4;
//    HCAN_PAR1 Tx1D5;
//    HCAN_PAR1 Tx1D6;
//    HCAN_PAR1 Tx1D7;
//    HCAN_PAR1 Tx1D8;
//    HCAN_PAR1 Tx1D9;
//    HCAN_PAR1 Tx1DA;
//    HCAN_PAR1 Tx1DD;
//    HCAN_PAR1 Tx1DE;
//    HCAN_PAR1 Tx1DF;
//    HCAN_PAR1 Tx1E0;
//    HCAN_PAR1 Tx1E1;
//    HCAN_PAR1 Tx1E2;
//    HCAN_PAR1 Tx1E3;
//    HCAN_PAR1 Tx1E4;
//    HCAN_PAR1 Tx1E5;
//    HCAN_PAR1 Tx1E6;
//    HCAN_PAR1 Tx1E7;
//    HCAN_PAR1 Tx1E8;
//    HCAN_PAR1 Tx1E9;
//    HCAN_PAR1 Tx1EA;
//    HCAN_PAR1 Tx1EB;
//    HCAN_PAR1 Tx1ED;
//    HCAN_PAR1 Tx1EE;
//    HCAN_PAR1 Tx1EF;
//    HCAN_PAR1 Tx1F0;
//    HCAN_PAR1 Tx1F1;
//    HCAN_PAR1 Tx1F3;
//    HCAN_PAR1 Tx1F4;
//    HCAN_PAR1 Tx1F6;
//}HCANSEND_PAR;




#endif /*  */





