/*
 * ********************************************************************************
 * VCU 输入。传感器：4-20ma  	AI1-AI8	 IO 模拟I2C0
 * bsp_adsch8.c
 *
 * Created on: 2024年12月x日
 *     Author: ROG
 */
#include "bsp_adsch8.h"
#include "lpspi_shared_function.h"
#include "os_task.h"



/* ********************************************************************************
 * IO 模拟 IIC2驱动
 */
static void IIC_Delay4(void) //简单延迟
{
	uint16_t n = 40; //delay_us(4)
	while(n--);
}
static void IIC_Delay2(void)
{
	uint16_t n = 20; //delay_us(2)
	while(n--);
}
static void IIC_Delay1(void)
{
	uint16_t n = 10; //delay_us(1)
	while(n--);
}

static void IIC_Init(void)
{
	IIC2_SCL_ON;
	IIC2_SDA_ON;
}

static void IIC_Start(void)
{
	IIC2_SDAOUT;
	IIC2_SDA_ON;
	IIC2_SCL_ON;
	IIC_Delay4(); ;
	IIC2_SDA_OFF; //START: when CLK is high,DATA change form high to low
	IIC_Delay4();
	IIC2_SCL_OFF; //准备发送或接收数据
}

static void IIC_Stop(void)
{
	IIC2_SDAOUT;
	IIC2_SCL_OFF;
	IIC2_SDA_OFF;
	IIC2_SCL_ON; //STOP: when CLK is high DATA change form low to high
	IIC_Delay4();
	IIC2_SDA_ON; //发送I2C总线结束信号
	IIC_Delay4();
}

static uint8_t MCU_Wait_Ack(void)
{
	//MCU等待从设备应答信号到来
	uint8_t ucErrTime=0;

	IIC2_SDAIN;
	IIC2_SDA_ON; IIC_Delay1();
	IIC2_SCL_ON; IIC_Delay1();

	while(IIC2_SDARead)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC2_SCL_OFF;
	return 0;
}

static void MCU_Send_Ack(void)
{
	//MCU产生ACK应答
	IIC2_SCL_OFF;
	IIC2_SDAOUT;
	IIC2_SDA_OFF;
	IIC_Delay2();
	IIC2_SCL_ON;
	IIC_Delay2();
	IIC2_SCL_OFF;
}

static void MCU_NoAck(void)
{
	//MCU不产生ACK应答
	IIC2_SCL_OFF;
	IIC2_SDAOUT;
	IIC2_SDA_ON;
	IIC_Delay2();
	IIC2_SCL_ON;
	IIC_Delay2();
	IIC2_SCL_OFF;
}

static void IIC_write_Byte(uint8_t Senddata)
{
	uint8_t i;

	IIC2_SDAOUT;
	IIC2_SCL_OFF;    //拉低时钟开始数据传输
    for(i=0; i<8; i++)
    {
        if((Senddata&0x80)>>7) 	{ IIC2_SDA_ON; }
        else 					{ IIC2_SDA_OFF; }
        Senddata<<=1;
        IIC_Delay2();
        IIC2_SCL_ON;
        IIC_Delay2();
		IIC2_SCL_OFF;
		IIC_Delay2();
    }
}

static uint8_t IIC_Read_Byte(uint8_t ack)
{
	uint8_t i,receivedata=0;

	IIC2_SDAIN;
	for(i=0; i<8; i++)
	{
		IIC2_SCL_OFF;
		IIC_Delay2();
		IIC2_SCL_ON;
		receivedata<<=1;
		if(IIC2_SDARead) receivedata++;
		IIC_Delay1();
	}

	if (!ack) 	MCU_NoAck(); //发送nACK
	else		MCU_Send_Ack(); //发送ACK
	return receivedata;
}



/* ********************************************************************************
 * ADS1115 驱动
 */
static void ADS1115_Config(uint8_t ch, uint8_t addr)
{
	static uint8_t i=0,channel=0;
	uint8_t tx_buf[4];

	switch(ch)
	{
		case 0: //0通道
			channel = 0xC0;
			break;
		case 1: //1通道
			channel = 0xD0;
			break;
		case 2: //2通道
			channel = 0xE0;
			break;
		case 3: //3通道
			channel = 0xF0;
			break;
		default:
			break;
	}

	tx_buf[0] = addr; //0x90
	tx_buf[1] = 0x01;
	tx_buf[2] = channel;
	tx_buf[3] = 0xe3;

	IIC_Start();
	for(i=0; i<4; i++)
	{
		IIC_write_Byte(tx_buf[i]);
		MCU_Wait_Ack();
	}
	IIC_Stop();   //停止
}

static void Point_Register(uint8_t addr)
{
	uint8_t i;
	uint8_t tx_buf[2];

	tx_buf[0] = addr; //0x90
	tx_buf[1] = 0x00;

	IIC_Start();
	for(i=0; i<2; i++)
	{
		IIC_write_Byte(tx_buf[i]);
		MCU_Wait_Ack();
	}
	IIC_Stop();  //停止
}

static uint16_t ADS1115_ReadData(uint8_t addr)
{
	uint16_t revdata, data[2]={0};

	IIC_Start();
	IIC_write_Byte((addr+1)); //0x90+1
	MCU_Wait_Ack();
	data[0] = IIC_Read_Byte(1);
	data[1] = IIC_Read_Byte(1);
	IIC_Stop();   //停止

	revdata = data[0]*256+data[1];
	return revdata;
}

static uint16_t ADS1115_Get1_Value(uint8_t channel)
{
	uint16_t value;

	ADS1115_Config(channel, 0x90);
	vTaskDelay(2);
	Point_Register(0x90);
	vTaskDelay(2);
	value = ADS1115_ReadData(0x90);
	vTaskDelay(2);
	return value;
}

static uint16_t ADS1115_Get2_Value(uint8_t channel)
{
	uint16_t value;

	ADS1115_Config(channel, 0x92);
	vTaskDelay(2);
	Point_Register(0x92);
	vTaskDelay(2);
	value = ADS1115_ReadData(0x92);
	vTaskDelay(2);

	return value;
}

static void ADSCH8_Get_Value(void)
{
    uint8_t k;
	
    for(k=0; k<4; k++)
	{
		getIn2.adsch8[k] = ADS1115_Get2_Value(k);
	}

	for(k=0; k<4; k++)
	{
		getIn2.adsch8[4+k] = ADS1115_Get1_Value(k);
	}
}


/* ********************************************************************************
 * 初始化。 传感器：4-20ma  	AI1-AI8	
 */
void BSP_ADSCH8_Init(void)
{
	IIC_Init();
}

/* ********************************************************************************
 * 任务函数。 传感器：4-20ma  	AI1-AI8	
 */
void BSP_ADSCH8_Task(void)
{
	ADSCH8_Get_Value(); //需要时间：2*4*6ms
    
    
}



