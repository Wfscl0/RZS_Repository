/*
 * bsp_tlf35584.h
 *
 * Created on: 2024年3月x日
 *     Author: ROG
 */
#ifndef _BSP_TLF35584_H
#define _BSP_TLF35584_H

#include "pin_mux.h"


/* ********************************************************************************
 * 硬件引脚定义：Input(mcu)
 */
#define TLF3_RST_Read		((PINS_DRV_ReadPins(PTA) >> 6) & 0x01) //PA6
#define TLF3_INT_Read		((PINS_DRV_ReadPins(PTA) >> 7) & 0x01) //PA7
#define TLF3_SS1_Read		((PINS_DRV_ReadPins(PTB) >> 23) & 0x01) //PB23

/* ********************************************************************************
 * 硬件引脚定义：Output(mcu)
 */
#define TLF3_WDI_ON			PINS_DRV_WritePin(PTB, 2, 1) //PB2
#define TLF3_WDI_OFF		PINS_DRV_WritePin(PTB, 2, 0) //PB2

/* ********************************************************************************
 * TLF35584 定义
 */
/* TLF35584 register addresses: */
#define TLF_REG_DEVCFG0                  ( (uint8_t)0x00U ) //设备配置
#define TLF_REG_DEVCFG1                  ( (uint8_t)0x01U ) //
#define TLF_REG_DEVCFG2                  ( (uint8_t)0x02U ) //
#define TLF_REG_PROTCFG                  ( (uint8_t)0x03U ) //保护寄存器
#define TLF_REG_SYSPCFG0                 ( (uint8_t)0x04U ) //系统配置请求（受保护的）
#define TLF_REG_SYSPCFG1                 ( (uint8_t)0x05U ) //
#define TLF_REG_WDCFG0                   ( (uint8_t)0x06U ) //看门狗配置请求（受保护的）
#define TLF_REG_WDCFG1                   ( (uint8_t)0x07U ) //
#define TLF_REG_FWDCFG                   ( (uint8_t)0x08U ) //功能看门狗配置（受保护的）
#define TLF_REG_WWDCFG0                  ( (uint8_t)0x09U ) //窗口看门狗配置请求（受保护的）
#define TLF_REG_WWDCFG1                  ( (uint8_t)0x0AU ) //
#define TLF_REG_RSYSPCFG0                ( (uint8_t)0x0BU ) //系统配置状态
#define TLF_REG_RSYSPCFG1                ( (uint8_t)0x0CU ) //
#define TLF_REG_RWDCFG0                  ( (uint8_t)0x0DU ) //看门狗配置状态
#define TLF_REG_RWDCFG1                  ( (uint8_t)0x0EU ) //
#define TLF_REG_RFWDCFG                  ( (uint8_t)0x0FU ) //功能看门狗配置状态
#define TLF_REG_RWWDCFG0                 ( (uint8_t)0x10U ) //窗口看门狗配置状态
#define TLF_REG_RWWDCFG1                 ( (uint8_t)0x11U ) //
#define TLF_REG_WKTIMCFG0                ( (uint8_t)0x12U ) //唤醒定时器配置
#define TLF_REG_WKTIMCFG1                ( (uint8_t)0x13U ) //
#define TLF_REG_WKTIMCFG2                ( (uint8_t)0x14U ) //
#define TLF_REG_DEVCTRL                  ( (uint8_t)0x15U ) //设备控制请求
#define TLF_REG_DEVCTRLN                 ( (uint8_t)0x16U ) //设备控制反向请求
#define TLF_REG_WWDSCMD                  ( (uint8_t)0x17U ) //窗口看门狗服务命令
#define TLF_REG_FWDRSP                   ( (uint8_t)0x18U ) //功能看门狗响应命令
#define TLF_REG_FWDRSPSYNC               ( (uint8_t)0x19U ) //具有同步功能的看门狗响应命令
#define TLF_REG_SYSFAIL                  ( (uint8_t)0x1AU ) //故障状态标志
#define TLF_REG_INITERR                  ( (uint8_t)0x1BU ) //初始化错误状态标志
#define TLF_REG_IF                       ( (uint8_t)0x1CU ) //中断标志
#define TLF_REG_SYSSF                    ( (uint8_t)0x1DU ) //系统状态标志
#define TLF_REG_WKSF                     ( (uint8_t)0x1EU ) //唤醒状态标志
#define TLF_REG_SPISF                    ( (uint8_t)0x1FU ) //SPI状态标志
#define TLF_REG_MONSF0                   ( (uint8_t)0x20U ) //监视器状态标志
#define TLF_REG_MONSF1                   ( (uint8_t)0x21U ) //
#define TLF_REG_MONSF2                   ( (uint8_t)0x22U ) //
#define TLF_REG_MONSF3                   ( (uint8_t)0x23U ) //
#define TLF_REG_OTFAIL                   ( (uint8_t)0x24U ) //温度过高状态标志
#define TLF_REG_OTWRNSF                  ( (uint8_t)0x25U ) //温度过高警告标志
#define TLF_REG_VMONSTAT                 ( (uint8_t)0x26U ) //电压监视器状态
#define TLF_REG_DEVSTAT                  ( (uint8_t)0x27U ) //设备状态
#define TLF_REG_PROTSTAT                 ( (uint8_t)0x28U ) //保护状态
#define TLF_REG_WWDSTAT                  ( (uint8_t)0x29U ) //窗口看门狗状态
#define TLF_REG_FWDSTAT0                 ( (uint8_t)0x2AU ) //功能看门狗状态
#define TLF_REG_FWDSTAT1                 ( (uint8_t)0x2BU ) //
#define TLF_REG_ABIST_CTRL0              ( (uint8_t)0x2CU ) //ABIST控件
#define TLF_REG_ABIST_CTRL1              ( (uint8_t)0x2DU ) //
#define TLF_REG_ABIST_SELECT0            ( (uint8_t)0x2EU ) //ABIST选择
#define TLF_REG_ABIST_SELECT1            ( (uint8_t)0x2FU ) //
#define TLF_REG_ABIST_SELECT2            ( (uint8_t)0x30U ) //
#define TLF_REG_BCK_FREQ_CHANGE          ( (uint8_t)0x31U ) //降压开关频率变化
#define TLF_REG_BCK_FRE_SPREAD           ( (uint8_t)0x32U ) //降压频率扩展
#define TLF_REG_BCK_MAIN_CTRL            ( (uint8_t)0x33U ) //降压主控制器
#define TLF_REG_GTM                      ( (uint8_t)0x3FU ) //全局测试模式

/*加密解密*/
#define TLF35584_UNLOCK_SEQU0 ((uint8_t) 0xABU)
#define	TLF35584_UNLOCK_SEQU1 ((uint8_t) 0xEFU)
#define TLF35584_UNLOCK_SEQU2 ((uint8_t) 0x56U)
#define TLF35584_UNLOCK_SEQU3 ((uint8_t) 0x12U)

#define TLF35584_LOCK_SEQU0	  ((uint8_t) 0xDFU)
#define TLF35584_LOCK_SEQU1	  ((uint8_t) 0x34U)
#define TLF35584_LOCK_SEQU2	  ((uint8_t) 0xBEU)
#define TLF35584_LOCK_SEQU3   ((uint8_t) 0xCAU)



typedef enum
{
	TLF35584_UNKOWN_STATE = 0,
	TLF35584_INIT_STATE,
	TLF35584_NORMAL_STATE,
	TLF35584_SLEEP_STATE,
	TLF35584_STANDBY_STATE,
	TLF35584_WAKE_STATE,

} Tlf35584DeviceState;

typedef struct
{
	Tlf35584DeviceState		DeviceState;
	uint8_t 				LockStatus;	//解锁后的状态为0，加锁后的状态为1
	uint8_t 				DeviceErr;
    uint8_t                 workmode;
	uint8_t					TxLen;
	uint16_t      			TxBuf[53];
	uint16_t        		RxBuf[53];

} Tlf35584_DataType;





void BSP_TLF35584_Init(void);
void BSP_TLF35584_Task(void);

#endif /*  */





