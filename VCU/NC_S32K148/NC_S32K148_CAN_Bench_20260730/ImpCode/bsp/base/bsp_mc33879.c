/*
 * ********************************************************************************
 * VCU 输出控制。LO1-LO8、HO1-H08  SPI2
 * bsp_mc33879.c
 *
 * Created on: 2024年12月x日
 *     Author: ROG
 */
#include "bsp_mc33879.h"
#include "lpspi_shared_function.h"
#include "task.h"



MC33879_PAR     MC33879;

/* ********************************************************************************
 * MC33879 初始化
 */
void BSP_MC33879_Init(void)
{
	//SPI2
	SPI_MasterInit(&spi2_mc338Instance, &spi2_mc338_MasterConfig0);

	MC33879_EN1_OFF;
	MC33879_EN2_OFF;
}

/* ********************************************************************************
 * MC33879 输出关闭
 */
void BSP_MC33879_Disable(void)
{
	//控制命令清零
	MC33879.cmd1 = 0;
	MC33879.cmd2 = 0;

	//芯片使能关闭
	MC33879_EN1_OFF;
	MC33879_EN2_OFF;
}

/* ********************************************************************************
 * MC33879 输出控制
 */
uint16_t mc338_recv[2] = {0, 0};
void MC33879_Control(void)
{
	uint16_t control_cmd = 0U;

	//芯片使能
	MC33879_EN1_ON; MC33879_EN2_ON;

	//cmdL控制芯片1。位控制，高位控制LO4-LO1 低位控制HO4-HO1
	//eg: 0x10 控制LO1 0x01控制HO1
	SPI_SetSS(&spi2_mc338Instance, LPSPI_PCS0);
	control_cmd = (uint16_t)(0xFF00U | MC33879.cmd1);
	if(SPI_MasterTransferBlocking(&spi2_mc338Instance, &control_cmd,
		&mc338_recv[0], 1U, 2U) == STATUS_SUCCESS)
	{
		MC33879.state1 = (uint8_t)mc338_recv[0];
	}

    //cmdH控制芯片2。位控制，高位控制LO8-LO5 低位控制HO8-HO5
	//eg: 0x10 控制LO5 0x01控制HO5
	SPI_SetSS(&spi2_mc338Instance, LPSPI_PCS1);
	control_cmd = (uint16_t)(0xFF00U | MC33879.cmd2);
	if(SPI_MasterTransferBlocking(&spi2_mc338Instance, &control_cmd,
		&mc338_recv[1], 1U, 2U) == STATUS_SUCCESS)
	{
		MC33879.state2 = (uint8_t)mc338_recv[1];
	}
}

/* ********************************************************************************
 * MC33879 输出控制
 *
 */
void BSP_MC33879_Task(uint8_t outl, uint8_t outh)
{
	//芯片1控制变量
	MC33879.cmd1 = ((outl<<4)&0xF0) + (outh&0x0F);
	//芯片2控制变量
	MC33879.cmd2 = (outl&0xF0) + ((outh>>4)&0x0F);
	
	MC33879_Control();
}
