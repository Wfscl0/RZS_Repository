/*
 * ********************************************************************************
 * Tlf35584。电源管理 SPI0
 * bsp_tlf35584.c
 *
 * Created on: 2024年12月x日
 *     Author: ROG
 */
#include "bsp_tlf35584.h"
#include "lpspi_shared_function.h"
#include "os_task.h"




static Tlf35584_DataType Tlf35584_Data;
static uint8_t Tlf35584_ErrStatus[53] = {0};

/* ********************************************************************************
 * TLF35584 SPI0
 */
static uint8_t ParityBitCal(uint16_t pdata)
{
	uint8_t tmp;
	uint8_t Parity=0;
	uint8_t Index;

	for(Index=1; Index<16; Index++)
	{
		tmp = (pdata>>Index)&0x01;
		Parity^=tmp;
	}

	return Parity;
}

/* ********************************************************************************
 * SPI Write Data Frame
 * | CMD | A5 | A4 | A3 | A2 | A1 | A0 | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 | P |
 * CAM BIT: 0 is Read, 1 is Write
 * A5-A0:   6 bits of register bit
 * D7-D0:   8 bits of data bit
 * P:       check bit, XOR
 */
static uint16_t TLF_Write_Cmd(uint16_t REG, uint16_t VAL)
{
	uint8_t  reg_type = 1;//type 0 : Read ,1 :Write
	uint8_t  reg_clc = 0;
	uint16_t SpiWrite_Data_Buffer = 0;

	SpiWrite_Data_Buffer = ((reg_type & 0x01) << 15);
	SpiWrite_Data_Buffer |= ((REG & 0x3F) << 9);
	SpiWrite_Data_Buffer |= ((VAL & 0xFF) << 1);

	reg_clc = ParityBitCal(SpiWrite_Data_Buffer);
	SpiWrite_Data_Buffer |= ((reg_clc & 0x01) << 0);

	return SpiWrite_Data_Buffer;
}

/* ********************************************************************************
 * SPI Read Data Frame
 * | CMD | S5 | S4 | S3 | S2 | S1 | S0 | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 | P |
 * CAM BIT: 0 is Read, 1 is Write
 * A5-A0:   6 bits of register bit
 * D7-D0:   8 bits of data bit
 * P:       check bit, XOR
 */
static uint16_t TLF_Read_Cmd(uint16_t REG)
{
	uint8_t  reg_type = 0; //type 0 : Read ,1 :Write
	uint8_t  reg_clc = 0;
	uint16_t SpiRead_Data_Buffer = 0;

	SpiRead_Data_Buffer = ((reg_type & 0x01) << 15);
	SpiRead_Data_Buffer |= ((REG & 0x3F) << 9);
	SpiRead_Data_Buffer |= ((0 & 0xFF) << 1);

	reg_clc = ParityBitCal(SpiRead_Data_Buffer);
	SpiRead_Data_Buffer |= ((reg_clc & 0x01) << 0);

	return SpiRead_Data_Buffer;
}

static void Gp_Tlf35584_TransmitData(uint8_t len)
{
	uint8_t i;
	
	for(i=0; i<len; i++)
	{
		if(SPI_MasterTransferBlocking(&spi0_tlf35Instance,
			&Tlf35584_Data.TxBuf[i], &Tlf35584_Data.RxBuf[i], 1U, 2U)
			!= STATUS_SUCCESS)
		{
			Tlf35584_Data.DeviceErr |= 0x01U;
			break;
		}
	}
}

static void Gp_Tlf35584_WriteChcek(uint8_t len)
{
	uint8_t i;

	for(i=0U; i<len; i++)
	{
		if ((Tlf35584_Data.TxBuf[i] & 0x8000U) > 0U)
		{
			if (Tlf35584_Data.TxBuf[i] != Tlf35584_Data.RxBuf[i])
			{
				/*write err*/
				Tlf35584_Data.DeviceErr |= 0x02U;
			}
		}
	}
}

static void Gp_TLF35584_Protect_Reg_Unlock(void)
{
	//0x03-(1: 0xAB 2:0xEF 3:0x56 4:0x12) to unlock access to protected registers.
	Tlf35584_Data.TxBuf[0U] = TLF_Write_Cmd(TLF_REG_PROTCFG, TLF35584_UNLOCK_SEQU0);
	Tlf35584_Data.TxBuf[1U] = TLF_Write_Cmd(TLF_REG_PROTCFG, TLF35584_UNLOCK_SEQU1);
	Tlf35584_Data.TxBuf[2U] = TLF_Write_Cmd(TLF_REG_PROTCFG, TLF35584_UNLOCK_SEQU2);
	Tlf35584_Data.TxBuf[3U] = TLF_Write_Cmd(TLF_REG_PROTCFG, TLF35584_UNLOCK_SEQU3);

	Tlf35584_Data.TxLen = 4U;
	Gp_Tlf35584_TransmitData(Tlf35584_Data.TxLen);
	Gp_Tlf35584_WriteChcek(Tlf35584_Data.TxLen);
}


static void Gp_TLF35584_Protect_Reg_Lock(void)
{
	//0x03-(1: 0xDF 2:0x34 3:0xBE 4:0xCA) to lock access to protected registers.
	Tlf35584_Data.TxBuf[0U] = TLF_Write_Cmd(TLF_REG_PROTCFG, TLF35584_LOCK_SEQU0);
	Tlf35584_Data.TxBuf[1U] = TLF_Write_Cmd(TLF_REG_PROTCFG, TLF35584_LOCK_SEQU1);
	Tlf35584_Data.TxBuf[2U] = TLF_Write_Cmd(TLF_REG_PROTCFG, TLF35584_LOCK_SEQU2);
	Tlf35584_Data.TxBuf[3U] = TLF_Write_Cmd(TLF_REG_PROTCFG, TLF35584_LOCK_SEQU3);

	Tlf35584_Data.TxLen = 4U;
	Gp_Tlf35584_TransmitData(Tlf35584_Data.TxLen);
	Gp_Tlf35584_WriteChcek(Tlf35584_Data.TxLen);
}

static void Gp_Tlf35584_Get_LockStatus(void)
{
	/**
	 * 0x28 - key4  key3 key2 key1 OK  lock
	 * lock : unlock is 0 ,locked is 1
	 */
	uint8_t KEY4OK, KEY3OK, KEY2OK, KEY1OK, LockStatus;

	Tlf35584_Data.TxBuf[0U] = TLF_Read_Cmd(TLF_REG_PROTSTAT);
	Tlf35584_Data.TxLen = 1U;
	Gp_Tlf35584_TransmitData(Tlf35584_Data.TxLen);

	KEY4OK = (uint8_t)((Tlf35584_Data.RxBuf[0] >> 8) & (uint8_t)(0x01));		//Key4 ok status
	KEY3OK = (uint8_t)((Tlf35584_Data.RxBuf[0] >> 7) & (uint8_t)(0x01));		//Key3 ok status
	KEY2OK = (uint8_t)((Tlf35584_Data.RxBuf[0] >> 6) & (uint8_t)(0x01));		//Key2 ok status
	KEY1OK = (uint8_t)((Tlf35584_Data.RxBuf[0] >> 5) & (uint8_t)(0x01));		//Key1 ok status
	LockStatus = (uint8_t)((Tlf35584_Data.RxBuf[0] >> 1) & (uint8_t)(0x01));	//Protected register lock status
	Tlf35584_Data.LockStatus = LockStatus;

	if((KEY4OK == 1)&&(KEY3OK == 1)&&(KEY2OK == 1)&&(KEY1OK == 1))
	{
		/*Key valid*/
	}
	else
	{
		/*Key err*/
		Tlf35584_Data.DeviceErr |= 0x04U;
	}
}

//static void Gp_Tlf35584_EnableFwdWwd(void)
//{
//	//0x06 - WWDETHR | WWDEN | FWDEN | WWDTSEL | WDCYC ,All write 1
//	Tlf35584_Data.TxBuf[0U] = TLF_Write_Cmd(TLF_REG_WDCFG0, 0x9BU);
//
//	Tlf35584_Data.TxLen = 1U;
//	Gp_Tlf35584_TransmitData(Tlf35584_Data.TxLen);
//	Gp_Tlf35584_WriteChcek(Tlf35584_Data.TxLen);
//}

static void Gp_Tlf35584_DisableFwdWwd(void)
{
	//0x06 - WWDETHR | WWDEN | FWDEN | WWDTSEL | WDCYC,all write 0
	Tlf35584_Data.TxBuf[0U] = TLF_Write_Cmd(TLF_REG_WDCFG0, 0x00);
	Tlf35584_Data.TxBuf[1U] = TLF_Write_Cmd(TLF_REG_WDCFG1, 0x00);

	Tlf35584_Data.TxLen = 2U;
	Gp_Tlf35584_TransmitData(Tlf35584_Data.TxLen);
	Gp_Tlf35584_WriteChcek(Tlf35584_Data.TxLen);
}

//static void Gp_Tlf35584_Feed_Dog(void)
//{
//	uint8_t WDG_Trig_CMD;
//	//Read TRIG_STATUS bit first and write inverted value to TRIG bit.
//	//0x17 - | TRIG_STATUS | nu | nu | nu | nu | nu | nu | TRIG |
//	Tlf35584_Data.TxBuf[0U] = TLF_Read_Cmd(TLF_REG_WWDSCMD);
//	Tlf35584_Data.TxLen = 1U;
//	Gp_Tlf35584_TransmitData(Tlf35584_Data.TxLen);
//	WDG_Trig_CMD = !((Tlf35584_Data.RxBuf[0] & 0x80) >> 7);
//
//	Tlf35584_Data.TxBuf[0U] = TLF_Write_Cmd(TLF_REG_WWDSCMD, WDG_Trig_CMD);
//	Tlf35584_Data.TxLen = 1U;
//	Gp_Tlf35584_TransmitData(Tlf35584_Data.TxLen);
//	Gp_Tlf35584_WriteChcek(Tlf35584_Data.TxLen);
//}

//static uint8_t RWDCFG0,RWDCFG1;
static void Gp_Tlf35584_GetFwdWwdStatus(void)
{
	Tlf35584_Data.TxBuf[0U] = TLF_Read_Cmd(TLF_REG_RWDCFG0);
	Tlf35584_Data.TxBuf[1U] = TLF_Read_Cmd(TLF_REG_RWDCFG1);
	Tlf35584_Data.TxLen = 2U;
	Gp_Tlf35584_TransmitData(Tlf35584_Data.TxLen);
	
//	RWDCFG0 = (uint8_t)((Tlf35584_Data.RxBuf[0] >> 1) & (uint8_t)(0xFF));
//	RWDCFG1 = (uint8_t)((Tlf35584_Data.RxBuf[1] >> 1) & (uint8_t)(0xFF));
}

static void Gp_Tlf35584_DisableErrPin(void)
{
	Tlf35584_Data.TxBuf[0U] = TLF_Write_Cmd(TLF_REG_SYSPCFG1,0x0u);

	Tlf35584_Data.TxLen = 1U;
	Gp_Tlf35584_TransmitData(Tlf35584_Data.TxLen);
	Gp_Tlf35584_WriteChcek(Tlf35584_Data.TxLen);
}

static void Gp_Tlf35584_DeviceModeNormal(void)
{
	//NORMAL：正常模式
	//(7 NONE,6 INIT,5 NORMAL,4 SLEEP,3 STANDBY,2 WAKE,1 RESERVED,0 RESERVED)
	Tlf35584_Data.TxBuf[0U] = TLF_Write_Cmd(TLF_REG_DEVCTRL, 0xEA);
	Tlf35584_Data.TxBuf[1U] = TLF_Write_Cmd(TLF_REG_DEVCTRLN, 0x15);

	Tlf35584_Data.TxLen = 2U;
	Gp_Tlf35584_TransmitData(Tlf35584_Data.TxLen);
	Gp_Tlf35584_WriteChcek(Tlf35584_Data.TxLen);
}

static void Gp_Tlf35584_DeviceModeWake(void)
{
	//SLEEP -> WAKE：进入SLEEP模式，但之后会进入WAKE模式
	//(0 NONE,1 INIT,2 NORMAL,3 SLEEP,4 STANDBY,5 WAKE,6 RESERVED,7 RESERVED)
	Tlf35584_Data.TxBuf[0U] = TLF_Write_Cmd(TLF_REG_DEVCTRL, 0x03);
	Tlf35584_Data.TxBuf[1U] = TLF_Write_Cmd(TLF_REG_DEVCTRLN, 0xFC);

	Tlf35584_Data.TxLen = 2U;
	Gp_Tlf35584_TransmitData(Tlf35584_Data.TxLen);
	Gp_Tlf35584_WriteChcek(Tlf35584_Data.TxLen);
}

static void Gp_Tlf35584_DeviceModeWake1(void)
{
	//Wake：关闭QT2、QT1、QCO、QVR电源。
	//(0 NONE,1 INIT,2 NORMAL,3 SLEEP,4 STANDBY,5 WAKE,6 RESERVED,7 RESERVED)
	Tlf35584_Data.TxBuf[0U] = TLF_Write_Cmd(TLF_REG_DEVCTRL, 0x05);
	Tlf35584_Data.TxBuf[1U] = TLF_Write_Cmd(TLF_REG_DEVCTRLN, 0xFA);

	Tlf35584_Data.TxLen = 2U;
	Gp_Tlf35584_TransmitData(Tlf35584_Data.TxLen);
	Gp_Tlf35584_WriteChcek(Tlf35584_Data.TxLen);
}

static Tlf35584DeviceState Gp_Tlf35584_GetDevModeState(void)
{
	uint8_t DeviceState_t;

	//0x27 - DEVSTAT & (0x07)
	//(Device state,7 RESERVED,6 RESERVED,5 WAKE,4 STANDBY,3 SLEEP,2 NORMAL,1 INIT,0 NONE)
	Tlf35584_Data.TxBuf[0] = TLF_Read_Cmd(TLF_REG_DEVSTAT);
	Tlf35584_Data.TxLen = 1U;
	Gp_Tlf35584_TransmitData(Tlf35584_Data.TxLen);

	DeviceState_t = (uint8_t)((Tlf35584_Data.RxBuf[0] >> 1) & (uint8_t)(0x07));
	Tlf35584_Data.DeviceState = (Tlf35584DeviceState)DeviceState_t;

	return (Tlf35584DeviceState)DeviceState_t;
}

static void Gp_Tlf35584_Init(void)
{
	Gp_TLF35584_Protect_Reg_Unlock(); //unlock
	Gp_Tlf35584_Get_LockStatus();

	Gp_Tlf35584_DisableFwdWwd(); //disable wdg
	Gp_Tlf35584_DisableErrPin();
	Gp_Tlf35584_DeviceModeNormal(); //go to noraml

	Gp_TLF35584_Protect_Reg_Lock(); //lock
	Gp_Tlf35584_Get_LockStatus();

	Gp_Tlf35584_GetFwdWwdStatus();   	//get gwd ,wwd status
	Gp_Tlf35584_GetDevModeState();		//get device mode
}

static void Gp_Tlf35584_GetErr(void)
{
	uint8_t index;

	Tlf35584_Data.TxBuf[0U] = TLF_Read_Cmd(TLF_REG_DEVCFG0); //00
	Tlf35584_Data.TxBuf[1U] = TLF_Read_Cmd(TLF_REG_DEVCFG1); //01
	Tlf35584_Data.TxBuf[2U] = TLF_Read_Cmd(TLF_REG_DEVCFG2); //02
	Tlf35584_Data.TxBuf[3U] = TLF_Read_Cmd(TLF_REG_PROTCFG); //03
	Tlf35584_Data.TxBuf[4U] = TLF_Read_Cmd(TLF_REG_SYSPCFG0); //04
	Tlf35584_Data.TxBuf[5U] = TLF_Read_Cmd(TLF_REG_SYSPCFG1); //05
	Tlf35584_Data.TxBuf[6U] = TLF_Read_Cmd(TLF_REG_WDCFG0);	//06
	Tlf35584_Data.TxBuf[7U] = TLF_Read_Cmd(TLF_REG_WDCFG1);	//07

	Tlf35584_Data.TxBuf[8U] = TLF_Read_Cmd(TLF_REG_FWDCFG);	//08
	Tlf35584_Data.TxBuf[9U] = TLF_Read_Cmd(TLF_REG_WWDCFG0); //09
	Tlf35584_Data.TxBuf[10U] = TLF_Read_Cmd(TLF_REG_WWDCFG1); //0A
	Tlf35584_Data.TxBuf[11U] = TLF_Read_Cmd(TLF_REG_RSYSPCFG0);	//0B

	Tlf35584_Data.TxBuf[12U] = TLF_Read_Cmd(TLF_REG_RSYSPCFG1);	//0C
	Tlf35584_Data.TxBuf[13U] = TLF_Read_Cmd(TLF_REG_RWDCFG0); //0D
	Tlf35584_Data.TxBuf[14U] = TLF_Read_Cmd(TLF_REG_RWDCFG1); //0E
	Tlf35584_Data.TxBuf[15U] = TLF_Read_Cmd(TLF_REG_RFWDCFG); //0F
	Tlf35584_Data.TxBuf[16U] = TLF_Read_Cmd(TLF_REG_RWWDCFG0); //10
	Tlf35584_Data.TxBuf[17U] = TLF_Read_Cmd(TLF_REG_RWWDCFG1); //11
	Tlf35584_Data.TxBuf[18U] = TLF_Read_Cmd(TLF_REG_WKTIMCFG0);	//12
	Tlf35584_Data.TxBuf[19U] = TLF_Read_Cmd(TLF_REG_WKTIMCFG1);	//13

	Tlf35584_Data.TxBuf[20U] = TLF_Read_Cmd(TLF_REG_WKTIMCFG2);	//14
	Tlf35584_Data.TxBuf[21U] = TLF_Read_Cmd(TLF_REG_DEVCTRL); //15
	Tlf35584_Data.TxBuf[22U] = TLF_Read_Cmd(TLF_REG_DEVCTRLN); //16
	Tlf35584_Data.TxBuf[23U] = TLF_Read_Cmd(TLF_REG_WWDSCMD); //17
	Tlf35584_Data.TxBuf[24U] = TLF_Read_Cmd(TLF_REG_FWDRSP); //18
	Tlf35584_Data.TxBuf[25U] = TLF_Read_Cmd(TLF_REG_FWDRSPSYNC); //19

	Tlf35584_Data.TxBuf[26U] = TLF_Read_Cmd(TLF_REG_SYSFAIL); //1A
	Tlf35584_Data.TxBuf[27U] = TLF_Read_Cmd(TLF_REG_INITERR); //1B
	Tlf35584_Data.TxBuf[28U] = TLF_Read_Cmd(TLF_REG_IF); //1C
	Tlf35584_Data.TxBuf[29U] = TLF_Read_Cmd(TLF_REG_SYSSF);	//1D
	Tlf35584_Data.TxBuf[30U] = TLF_Read_Cmd(TLF_REG_WKSF); //1E
	Tlf35584_Data.TxBuf[31U] = TLF_Read_Cmd(TLF_REG_SPISF);	//1F

	Tlf35584_Data.TxBuf[32U] = TLF_Read_Cmd(TLF_REG_MONSF0); //20
	Tlf35584_Data.TxBuf[33U] = TLF_Read_Cmd(TLF_REG_MONSF1); //21
	Tlf35584_Data.TxBuf[34U] = TLF_Read_Cmd(TLF_REG_MONSF2); //22
	Tlf35584_Data.TxBuf[35U] = TLF_Read_Cmd(TLF_REG_MONSF3); //23

	Tlf35584_Data.TxBuf[36U] = TLF_Read_Cmd(TLF_REG_OTFAIL); //34
	Tlf35584_Data.TxBuf[37U] = TLF_Read_Cmd(TLF_REG_OTWRNSF); //25
	Tlf35584_Data.TxBuf[38U] = TLF_Read_Cmd(TLF_REG_VMONSTAT); //26
	Tlf35584_Data.TxBuf[39U] = TLF_Read_Cmd(TLF_REG_DEVSTAT); //27
	Tlf35584_Data.TxBuf[40U] = TLF_Read_Cmd(TLF_REG_PROTSTAT); //28
	Tlf35584_Data.TxBuf[41U] = TLF_Read_Cmd(TLF_REG_WWDSTAT); //29
	Tlf35584_Data.TxBuf[42U] = TLF_Read_Cmd(TLF_REG_FWDSTAT0); //2A
	Tlf35584_Data.TxBuf[43U] = TLF_Read_Cmd(TLF_REG_FWDSTAT1); //2B

	Tlf35584_Data.TxBuf[44U] = TLF_Read_Cmd(TLF_REG_ABIST_CTRL0); //2C
	Tlf35584_Data.TxBuf[45U] = TLF_Read_Cmd(TLF_REG_ABIST_CTRL1); //2D
	Tlf35584_Data.TxBuf[46U] = TLF_Read_Cmd(TLF_REG_ABIST_SELECT0);	//2E
	Tlf35584_Data.TxBuf[47U] = TLF_Read_Cmd(TLF_REG_ABIST_SELECT1);	//2F
	Tlf35584_Data.TxBuf[48U] = TLF_Read_Cmd(TLF_REG_ABIST_SELECT2);	//30

	Tlf35584_Data.TxBuf[49U] = TLF_Read_Cmd(TLF_REG_BCK_FREQ_CHANGE); //31
	Tlf35584_Data.TxBuf[50U] = TLF_Read_Cmd(TLF_REG_BCK_FRE_SPREAD); //32
	Tlf35584_Data.TxBuf[51U] = TLF_Read_Cmd(TLF_REG_BCK_MAIN_CTRL);	//33
	Tlf35584_Data.TxBuf[52U] = TLF_Read_Cmd(TLF_REG_GTM); //3F

	Tlf35584_Data.TxLen = 53U;
	Gp_Tlf35584_TransmitData(Tlf35584_Data.TxLen);
	for(index=0; index<Tlf35584_Data.TxLen; index++)
	{
		Tlf35584_ErrStatus[index] = (Tlf35584_Data.RxBuf[index]>>1)&(0xFF);
	}
}


/* ********************************************************************************
 * TLF35584 使用三种模式。INIT,NORMAL,WAKE
 * 
 */
void BSP_TLF35584_WorkMode(uint8_t mode)
{
	static uint8_t modelast = 0;

	switch(mode)
	{
		case 0:
			break;
		case 1: //NORMAL -> WAKE
			if(modelast != mode)
			{
				modelast = mode;
				Gp_Tlf35584_DeviceModeWake();
				vTaskDelay(10);
				Gp_Tlf35584_DeviceModeWake1();
				vTaskDelay(10);
			}
			break;
		case 2: //WAKE -> NORMAL
			if(modelast != mode)
			{
				modelast = mode;
				Gp_Tlf35584_DeviceModeNormal();
				vTaskDelay(10);
			}
			break;

		default: //NORMAL
			if(modelast != mode)
			{
				modelast = mode;
				Gp_Tlf35584_DeviceModeNormal();
				vTaskDelay(100);
			}
			break;
	}
}

/* ********************************************************************************
 * TLF35584 初始化
 * 
 */
void BSP_TLF35584_Init(void)
{
	/* 内部硬件看门狗当前不启用，不输出TLF WDI脉冲。 */

	//SPI 初始化
	SPI_MasterInit(&spi0_tlf35Instance, &spi0_tlf35_MasterConfig0);
	SPI_SetSS(&spi0_tlf35Instance, LPSPI_PCS2);

	Gp_Tlf35584_Init();
}

/* ********************************************************************************
 * TLF35584 任务函数
 * 
 */
void BSP_TLF35584_Task(void)
{
	//static uint8_t mode = 0;

	if(Tlf35584_Data.DeviceState == 1)
	{
		vTaskDelay(100); //初次上电，电源不稳，会导致初始化失败！
		Gp_Tlf35584_Init();
	}
	else
	{
		Gp_Tlf35584_GetErr();
		Gp_Tlf35584_GetDevModeState();
	}

	BSP_TLF35584_WorkMode(Tlf35584_Data.workmode);
}





