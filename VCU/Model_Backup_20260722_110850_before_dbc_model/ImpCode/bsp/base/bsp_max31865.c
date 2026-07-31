/*
 * ********************************************************************************
 * PT100A-C		SPI1
 * bsp_max31865.c
 *
 * Created on: 2024Äê12ÔÂxÈÕ
 *     Author: ROG
 */
#include "bsp_max31865.h"
#include "lpspi_shared_function.h"
#include "os_task.h"



/* ********************************************************************************
 * PT100A-C	Çý¶¯
 */
static void MAX31865_Configuration(void)
{
	uint8_t tx_buf[2] = {0, 0};
	uint8_t rx_buf[2] = {0, 0};

	//ÅäÖÃ¼Ä´æÆ÷00 PT100-A
	tx_buf[0] = 0x80; tx_buf[1] = 0xD3; //
	CS_A_LOW; vTaskDelay(2);
	SPI_MasterTransfer(&spi1_max318Instance, &tx_buf[0], &rx_buf[0], 2);
	vTaskDelay(2); CS_A_HIGH;
	vTaskDelay(2);

	//ÅäÖÃ¼Ä´æÆ÷00 PT100-B
	tx_buf[0] = 0x80; tx_buf[1] = 0xD3; //
	CS_B_LOW; vTaskDelay(2);
	SPI_MasterTransfer(&spi1_max318Instance, &tx_buf[0], &rx_buf[0], 2);
	vTaskDelay(2); CS_B_HIGH;
	vTaskDelay(2);

	//ÅäÖÃ¼Ä´æÆ÷00 PT100-C
	tx_buf[0] = 0x80; tx_buf[1] = 0xD3; //
	CS_C_LOW; vTaskDelay(2);
	SPI_MasterTransfer(&spi1_max318Instance, &tx_buf[0], &rx_buf[0], 2);
	vTaskDelay(2); CS_C_HIGH;
	vTaskDelay(2);
}

static void MAX31865_Config_Read(void)
{
	uint8_t tx_buf[2] = {0, 0};
	uint8_t rx_buf[2] = {0, 0};

	//¶ÁÈ¡ÅäÖÃ¼Ä´æÆ÷ PT100-A
	tx_buf[0] = 0x00; tx_buf[1] = 0x00;
	CS_A_LOW; vTaskDelay(2);
	SPI_MasterTransfer(&spi1_max318Instance, &tx_buf[0], &rx_buf[0], 2);
	vTaskDelay(2); CS_A_HIGH;
    getIn2.max318.config[0] = rx_buf[0]*256+rx_buf[1];
	vTaskDelay(2);

	//¶ÁÈ¡ÅäÖÃ¼Ä´æÆ÷ PT100-B
	tx_buf[0] = 0x00; tx_buf[1] = 0x00;
	CS_B_LOW; vTaskDelay(2);
	SPI_MasterTransfer(&spi1_max318Instance, &tx_buf[0], &rx_buf[0], 2);
	vTaskDelay(2); CS_B_HIGH;
	getIn2.max318.config[1] = rx_buf[0]*256+rx_buf[1];
	vTaskDelay(2);

	//¶ÁÈ¡ÅäÖÃ¼Ä´æÆ÷ PT100-C
	tx_buf[0] = 0x00; tx_buf[1] = 0x00;
	CS_C_LOW; vTaskDelay(2);
	SPI_MasterTransfer(&spi1_max318Instance, &tx_buf[0], &rx_buf[0], 2);
	vTaskDelay(2); CS_C_HIGH;
	getIn2.max318.config[2] = rx_buf[0]*256+rx_buf[1];
	vTaskDelay(2);
}

static void MAX31865_Fault_Status(void)
{
	uint8_t tx_buf[2] = {0, 0};
	uint8_t rx_buf[2] = {0, 0};

	//¶ÁÈ¡ÅäÖÃ¼Ä´æÆ÷ PT100-A
	tx_buf[0] = 0x07; tx_buf[1] = 0x00;
	CS_A_LOW; vTaskDelay(2);
	SPI_MasterTransfer(&spi1_max318Instance, &tx_buf[0], &rx_buf[0], 2);
	vTaskDelay(2); CS_A_HIGH;
	getIn2.max318.fault[0] = rx_buf[0]*256+rx_buf[1];
	vTaskDelay(2);

	//¶ÁÈ¡ÅäÖÃ¼Ä´æÆ÷ PT100-B
	tx_buf[0] = 0x07; tx_buf[1] = 0x00;
	CS_B_LOW; vTaskDelay(2);
	SPI_MasterTransfer(&spi1_max318Instance, &tx_buf[0], &rx_buf[0], 2);
	vTaskDelay(2); CS_B_HIGH;
	getIn2.max318.fault[1] = rx_buf[0]*256+rx_buf[1];
	vTaskDelay(2);

	//¶ÁÈ¡ÅäÖÃ¼Ä´æÆ÷ PT100-C
	tx_buf[0] = 0x07; tx_buf[1] = 0x00;
	CS_C_LOW; vTaskDelay(2);
	SPI_MasterTransfer(&spi1_max318Instance, &tx_buf[0], &rx_buf[0], 2);
	vTaskDelay(2); CS_C_HIGH;
	getIn2.max318.fault[2] = rx_buf[0]*256+rx_buf[1];
	vTaskDelay(2);
}

static void MAX31865_Get_RTD(void)
{
	uint8_t tx_buf[2] = {0, 0};
	uint8_t rx_buf[2] = {0, 0};
    uint16_t tempval = 0;

	//¶ÁÈ¡RTDµç×è¼Ä´æÆ÷ PT100-A
	if(DRDY_A_Read)
	{
		tx_buf[0] = 0x01; tx_buf[1] = 0x00;
		CS_A_LOW; vTaskDelay(2);
		SPI_MasterTransfer(&spi1_max318Instance, &tx_buf[0], &rx_buf[0], 2);
		vTaskDelay(2); CS_A_HIGH;
		tempval = rx_buf[1]*256;

		tx_buf[0] = 0x02; tx_buf[1] = 0x00;
		CS_A_LOW; vTaskDelay(2);
		SPI_MasterTransfer(&spi1_max318Instance, &tx_buf[0], &rx_buf[0], 2);
		vTaskDelay(2); CS_A_HIGH;

		getIn2.max318.rtd[0] = tempval+rx_buf[1];
		vTaskDelay(2);
	}

	//¶ÁÈ¡RTDµç×è¼Ä´æÆ÷ PT100-B
	if(DRDY_B_Read)
	{
		tx_buf[0] = 0x01; tx_buf[1] = 0x00;
		CS_B_LOW; vTaskDelay(2);
		SPI_MasterTransfer(&spi1_max318Instance, &tx_buf[0], &rx_buf[0], 2);
		vTaskDelay(2); CS_B_HIGH;
		tempval = rx_buf[1]*256;

		tx_buf[0] = 0x02; tx_buf[1] = 0x00;
		CS_B_LOW; vTaskDelay(2);
		SPI_MasterTransfer(&spi1_max318Instance, &tx_buf[0], &rx_buf[0], 2);
		vTaskDelay(2); CS_B_HIGH;

		getIn2.max318.rtd[1] = tempval+rx_buf[1];
		vTaskDelay(2);
	}

	//¶ÁÈ¡RTDµç×è¼Ä´æÆ÷ PT100-C
	if(DRDY_C_Read)
	{
		tx_buf[0] = 0x01; tx_buf[1] = 0x00;
		CS_C_LOW; vTaskDelay(2);
		SPI_MasterTransfer(&spi1_max318Instance, &tx_buf[0], &rx_buf[0], 2);
		vTaskDelay(2); CS_C_HIGH;
		tempval = rx_buf[1]*256;

		tx_buf[0] = 0x02; tx_buf[1] = 0x00;
		CS_C_LOW; vTaskDelay(2);
		SPI_MasterTransfer(&spi1_max318Instance, &tx_buf[0], &rx_buf[0], 2);
		vTaskDelay(2); CS_C_HIGH;

		getIn2.max318.rtd[2] = tempval+rx_buf[1];
		vTaskDelay(2);
	}
}


/* ********************************************************************************
 * BSP_MAX31865_Init
 */
void BSP_MAX31865_Init(void)
{
	//SPI1
	SPI_MasterInit(&spi1_max318Instance, &spi1_max318_MasterConfig0);

	CS_A_HIGH;
	CS_B_HIGH;
	CS_C_HIGH; //Ð¾Æ¬Ê§ÄÜ
}

/* ********************************************************************************
 * BSP_MAX31865_Task
 */
void BSP_MAX31865_Task(void)
{
	if(getIn2.max318.flag == 0)
	{
		getIn2.max318.flag = 1;
		MAX31865_Configuration(); //ÐèÒªÊ±¼ä£º6*3 = 18ms
	}

	MAX31865_Config_Read(); //ÐèÒªÊ±¼ä£º6*3 = 18ms
	MAX31865_Fault_Status(); //ÐèÒªÊ±¼ä£º6*3 = 18ms
	MAX31865_Get_RTD(); //ÐèÒªÊ±¼ä£º10*3 = 30ms
}


