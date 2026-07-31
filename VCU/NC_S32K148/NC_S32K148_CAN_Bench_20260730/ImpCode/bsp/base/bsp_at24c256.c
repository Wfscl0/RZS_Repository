/*
 * ********************************************************************************
 * 存储。at24c256 I2C1 注意：读写中有vTaskDelay，请勿在OS初始化完成之前使用！！！
 * bsp_adsch8.c
 *
 * Created on: 2024年12月x日
 *     Author: ROG
 */
#include "bsp_at24c256.h"
#include "task.h"




static uint8_t at24c_flag = 2;
static uint8_t at24c_rx[5] = {0};
static uint8_t at24c_tx[5] = "6789"; //调试

/* ********************************************************************************
 * AT24C02 驱动
 */
static void AT24C_WriteOneByte(uint16_t addr, uint8_t Buffer)
{
	uint8_t tx_buf[3];

	if(addr <= AT24C256) //小于最大读写地址
	{
		tx_buf[0] = addr>>8;
		tx_buf[1] = addr;
		tx_buf[2] = Buffer;
		I2C_MasterSendData(&i2c1_at24c_instance, &tx_buf[0], 3, true);
		vTaskDelay(3);
	}
}

static uint8_t AT24C_ReadOneByte(uint16_t addr)
{
	uint8_t tx_buf[2];
	uint8_t rx_buf=0;

	if(addr <= AT24C256) //小于最大读写地址
	{
		tx_buf[0] = addr>>8;
		tx_buf[1] = addr;
		I2C_MasterSendData(&i2c1_at24c_instance, &tx_buf[0], 2, false);
		vTaskDelay(3);
		I2C_MasterReceiveData(&i2c1_at24c_instance, &rx_buf, 1, true);
		vTaskDelay(3);
	}

	return rx_buf;
}

/* ********************************************************************************
 * AT24C02 读
 */
void BSP_AT24C02_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint8_t ReadNum)
{
	while(ReadNum--)
	{
		*pBuffer++=AT24C_ReadOneByte(ReadAddr++);
	}
}

/* ********************************************************************************
 * AT24C02 写
 */
void BSP_AT24C02_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint8_t WriteNum)
{
	while(WriteNum--)
	{
		AT24C_WriteOneByte(WriteAddr, *pBuffer);
		WriteAddr++;
		pBuffer++;
		vTaskDelay(5);
	}
}

/* ********************************************************************************
 * AT24C02 初始化
 */
void BSP_AT24C_Init(void)
{
	I2C_MasterInit(&i2c1_at24c_instance, &i2c1_at24c_MasterConfig0);
}

/* ********************************************************************************
 * AT24C02 任务函数
 */
void BSP_AT24C_Task(void)
{
	if(at24c_flag == 1)
	{
		at24c_flag = 2;
		BSP_AT24C02_Write(0, at24c_tx, 4); //写入需要时间：DatLen*8ms
	}
	else if(at24c_flag == 2)
	{
		at24c_flag = 3;
		BSP_AT24C02_Read(0, at24c_rx, 4); //读取需要时间：DatLen*6 ms
	}
}

