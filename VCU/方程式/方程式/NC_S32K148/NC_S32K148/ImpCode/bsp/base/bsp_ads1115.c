/*
 * ********************************************************************************
 * VCU ADC输入。AIN0-AIN3 I2C0
 * bsp_ads1115.c
 *
 * Created on: 2024年12月x日
 *     Author: ROG
 */
#include "bsp_ads1115.h"
#include "os_task.h"




/* ********************************************************************************
 * ADS1115 通道数据获取
 */
static void ADS1115_Delay(void)
{
	vTaskDelay(2);
}

/* ********************************************************************************
 * ADS1115 通道数据获取
 */
uint16_t ADS1115_Channel_Value(uint8_t channel)
{
	uint8_t tx_buf[3];
	uint8_t rx_buf[2];

	tx_buf[0] = 1;
	tx_buf[2] = 227;
	switch(channel)
	{
		case 1:
			//配置（写）
			tx_buf[1] = 0xc0;
			I2C_MasterSendData(&i2c0_ads15_instance, &tx_buf[0], 3, true);
			ADS1115_Delay();

			//获取数据（读）
			I2C_MasterSendData(&i2c0_ads15_instance, 0, 1, false);
			ADS1115_Delay();
			I2C_MasterReceiveData(&i2c0_ads15_instance, &rx_buf[0], 2, true);
			ADS1115_Delay();
			break;
		case 2:
			//配置（写）
			tx_buf[1] = 0xd0;
			I2C_MasterSendData(&i2c0_ads15_instance, &tx_buf[0], 3, true);
			ADS1115_Delay();

			//获取数据（读）
			I2C_MasterSendData(&i2c0_ads15_instance, 0, 1, false);
			ADS1115_Delay();
			I2C_MasterReceiveData(&i2c0_ads15_instance, &rx_buf[0], 2, true);
			ADS1115_Delay();
			break;
		case 3:
			//配置（写）
			tx_buf[1] = 0xe0;
			I2C_MasterSendData(&i2c0_ads15_instance, &tx_buf[0], 3, true);
			ADS1115_Delay();

			//获取数据（读）
			I2C_MasterSendData(&i2c0_ads15_instance, 0, 1, false);
			ADS1115_Delay();
			I2C_MasterReceiveData(&i2c0_ads15_instance, &rx_buf[0], 2, true);
			ADS1115_Delay();
			break;
		case 4:
			//配置（写）
			tx_buf[1] = 0xf0;
			I2C_MasterSendData(&i2c0_ads15_instance, &tx_buf[0], 3, true);
			ADS1115_Delay();

			//获取数据（读）
			I2C_MasterSendData(&i2c0_ads15_instance, 0, 1, false);
			ADS1115_Delay();
			I2C_MasterReceiveData(&i2c0_ads15_instance, &rx_buf[0], 2, true);
			ADS1115_Delay();
			break;
		default:
			break;
	}

	return ((uint16_t)(rx_buf[0]<<8)+rx_buf[1]);
}

static void ADS1115_Get_Value(void)
{
	static uint8_t ads1115_step=0;
	
	ads1115_step++;
	getIn1.ads115_value[ads1115_step-1] = ADS1115_Channel_Value(ads1115_step);
    
	if(ads1115_step >= 4)
	{
		ads1115_step = 0;
	}
}



/* ********************************************************************************
 * ADS1115 初始化
 */
void BSP_ADS1115_Init(void)
{
	I2C_MasterInit(&i2c0_ads15_instance, &i2c0_ads15_MasterConfig0);
}

/* ********************************************************************************
 * ADS1115 任务函数
 */
void BSP_ADS1115_Task(void)
{
	ADS1115_Get_Value(); //需要时间：6ms
}






