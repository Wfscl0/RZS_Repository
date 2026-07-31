#ifndef _CAN_NODE_H_
#define _CAN_NODE_H_

#include <string.h>
#include <stdio.h>

/*
 * CAN1台架调试协议开关。
 * 本体工程保持为0，忽略0x7A0~0x7A3并停止0x7B0~0x7B2回显；
 * 仅在独立TSMaster/PCAN测试副本中改为1，防止实车误触发输入覆盖。
 */
#ifndef VCU_ENABLE_BENCH_DEBUG
#define VCU_ENABLE_BENCH_DEBUG       (0U)
#endif

/* CAN1台架调试协议ID（11位标准帧）。 */
#define VCU_DBG_CONTROL_ID          (0x7A0U)
#define VCU_DBG_PEDAL_ADC_ID        (0x7A1U)
#define VCU_DBG_AIR_WHEEL_ID        (0x7A2U)
#define VCU_DBG_DIGITAL_ID          (0x7A3U)
#define VCU_DBG_STATUS_ID           (0x7B0U)
#define VCU_DBG_PEDAL_ECHO_ID       (0x7B1U)
#define VCU_DBG_AIR_WHEEL_ECHO_ID   (0x7B2U)

#define VCU_DBG_FLAG_MASTER         (0x01U)
#define VCU_DBG_FLAG_PEDAL_ADC      (0x02U)
#define VCU_DBG_FLAG_AIR_WHEEL      (0x04U)
#define VCU_DBG_FLAG_DIGITAL        (0x08U)
#define VCU_DBG_UNLOCK_BYTE0        (0xA5U)
#define VCU_DBG_UNLOCK_BYTE1        (0x5AU)


/*******************************************************************************
** CAN接收缓存 结构体变量声明
*/

//CAN0 队列数据交互。数据格式定义
typedef struct
{
	//uint8_t  Rx201[8]; //SES反馈
	//uint8_t  Rx202[8]; //SES反馈
	uint8_t reserved;    //CAN0当前不通过队列接收业务报文，避免空结构体扩展

}HCAN0RX_PAR;

//CAN1 队列数据交互。数据格式定义
typedef struct
{
	//uint8_t  Rx1A0[8]; //电机反馈
	//uint8_t  Rx2A0[8]; //电机反馈
	//uint8_t  Rx142[8]; //DBS反馈
	//uint8_t  Rx143[8]; //DBS反馈
	uint8_t  ESP_T_03[8];
	uint8_t  ESP_T_06[8];
	uint8_t  ESP_T_07[8];
	uint8_t  res_msg[8];
	uint8_t  canb_ipctsmsg1[8];
	uint8_t  canb_ipctsmsg2[8];
	uint8_t  AMI_Tx[8];
	uint8_t  canb_epssendmsg1[8];
	uint8_t  canb_epssendmsg2[8];

	/* Production-frame counters are incremented only after ID/DLC validation. */
	uint8_t  esp_t03_rx_count;
	uint8_t  esp_t06_rx_count;
	uint8_t  esp_t07_rx_count;
	uint8_t  res_rx_count;
	uint8_t  ipc_msg1_rx_count;
	uint8_t  ipc_msg2_rx_count;
	uint8_t  ami_rx_count;
	uint8_t  eps_msg1_rx_count;
	uint8_t  eps_msg2_rx_count;

	/* TSMaster bench-debug inputs. Receive counters support timeout handling. */
	uint8_t  vcu_dbg_control[8];
	uint8_t  vcu_dbg_pedal_adc[8];
	uint8_t  vcu_dbg_air_wheel[8];
	uint8_t  vcu_dbg_digital[8];
	uint8_t  vcu_dbg_control_rx_count;
	uint8_t  vcu_dbg_pedal_rx_count;
	uint8_t  vcu_dbg_air_wheel_rx_count;
	uint8_t  vcu_dbg_digital_rx_count;
}HCAN1RX_PAR;

//CAN2 队列数据交互。数据格式定义
typedef struct
{
	//uint8_t  Rx1B0[3][9]; //VCU
	uint8_t reserved;    //CAN2当前预留，避免非标准空结构体

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
	uint8_t vcu_dbg_status[8];
	uint8_t vcu_dbg_pedal_echo[8];
	uint8_t vcu_dbg_air_wheel_echo[8];

	//CAN2

}HCANSEND_PAR;



#endif
