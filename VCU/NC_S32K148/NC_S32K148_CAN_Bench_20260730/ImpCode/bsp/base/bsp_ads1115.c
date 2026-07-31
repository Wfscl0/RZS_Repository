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
	uint8_t rx_buf[2] = {0U, 0U};
	uint8_t pointer = 0U;

	if((channel < 1U) || (channel > 4U))
	{
		return 0U;
	}

	/* Continuous conversion, +/-6.144 V range, 860 SPS, comparator off. */
	tx_buf[0] = 1U;
	tx_buf[1] = (uint8_t)(0xC0U + ((channel - 1U) << 4U));
	tx_buf[2] = 0xE3U;
	if(I2C_MasterSendDataBlocking(&i2c0_ads15_instance, tx_buf, 3U, true, 5U)
		!= STATUS_SUCCESS)
	{
		return 0U;
	}

	/* Allow one 860-SPS conversion before selecting and reading register 0. */
	ADS1115_Delay();
	if(I2C_MasterSendDataBlocking(&i2c0_ads15_instance, &pointer, 1U, false, 5U)
		!= STATUS_SUCCESS)
	{
		return 0U;
	}
	if(I2C_MasterReceiveDataBlocking(&i2c0_ads15_instance, rx_buf, 2U, true, 5U)
		!= STATUS_SUCCESS)
	{
		return 0U;
	}

	return (uint16_t)(((uint16_t)rx_buf[0] << 8U) | rx_buf[1]);
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






