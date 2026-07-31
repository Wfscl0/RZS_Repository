/*
 * ********************************************************************************
 * VCU ADC输入。ADC0 AIN4-AIN7	配置时需要注意，选择PDB0时钟
 * bsp_adc.c
 *
 * Created on: 2024年12月x日
 *     Author: ROG
 */

#include "bsp_adc.h"
#include "os_task.h"
#include <string.h>



//定义本地控制全局变量
static uint16_t adc0_Results[6]; //数据大小参考adc0_Results00
static uint16_t *padc0_Recv;

//队列句柄
QueueHandle_t	Que_Hadc0_get;

/* ********************************************************************************
 * adc采样中断，采样完成后触发
 */
void Adc0_Convert_Callback(const adc_callback_info_t * const callbackInfo, void * userData)
{
	uint8_t i;
	
	(void) userData;
	(void) callbackInfo;
	
	//数据缓存
	for(i=0; i<6; i++)
	{
		adc0_Results[i] = adc0_Results00[i];
	}
	
	//向队列中，发送数据
	padc0_Recv = &adc0_Results[0];
	xQueueSendFromISR(Que_Hadc0_get, (void *)&padc0_Recv, 0);
}

/* ********************************************************************************
 * ADC0 中值算法
 */
static uint16_t MedianFilte(uint16_t *buf , uint8_t len)
{
    uint8_t i,j;
    uint16_t temp;

	for(i=0; i<len; i++)
	{
		for(j=0; j<len-i-1; j++)
		{
			if(buf[j] > buf[j+1] )
			{
				temp = buf[j];
				buf[j] = buf[j+1];
				buf[j+1] = temp;
			}
		}
	}
	return buf[len/2] ;
}

/* ********************************************************************************
 * ADC0 数据转换
 */
//static float pwr5vv=0,pwr12v=0;
static void ADC0_Value_Convert(uint16_t *adc0_Recv)
{
	static uint8_t  adccnt = 0;
	static uint16_t adctemp[6][7] = {0};
	
	/*采样完成后处理数据*/
	adctemp[0][adccnt] = adc0_Recv[0];
	adctemp[1][adccnt] = adc0_Recv[1];
	adctemp[2][adccnt] = adc0_Recv[2];
	adctemp[3][adccnt] = adc0_Recv[3];
	adctemp[4][adccnt] = adc0_Recv[4];
	adctemp[5][adccnt] = adc0_Recv[5];

	adccnt++;
	if(adccnt >= 7) //中值滤波处理
	{
		getIn1.adc0_value[0] = MedianFilte(&adctemp[0][0], 7);
		getIn1.adc0_value[1] = MedianFilte(&adctemp[1][0], 7);
		getIn1.adc0_value[2] = MedianFilte(&adctemp[2][0], 7);
		getIn1.adc0_value[3] = MedianFilte(&adctemp[3][0], 7);
		getIn1.adc0_value[4] = MedianFilte(&adctemp[4][0], 7);
		getIn1.adc0_value[5] = MedianFilte(&adctemp[5][0], 7);
		
//		pwr5vv = (float)getIn1.adc0_value[4]*3.3/4096*2*100; //整数形式，扩大100倍
//		pwr12v = (float)getIn1.adc0_value[5]*3.3/4096*11*100+30; //整数形式，扩大100倍
		adccnt = 0;
	}
}



/* ********************************************************************************
 * ADC0 初始化
 */
void BSP_ADC0_Init(void)
{
	ADC_Init(&adc0_instance, &adc0_InitConfig0);
	
	//外设默认优先级00！会导致操作系统内核函数无法调用，导致系统错误！！！
	//重新设置外设中断优先级。
	INT_SYS_SetPriority(ADC0_IRQn, 0x02);
	
	//ADC接收。队列
	Que_Hadc0_get = xQueueCreate(3, sizeof(uint16_t *));
}

/* ********************************************************************************
 * ADC0 任务主循环
 */
void BSP_ADC0_Task(void)
{
	static uint16_t *pRecv;
	
	//请求消息。ADC0
	if(xQueueReceive(Que_Hadc0_get, &(pRecv), 0) == pdTRUE)
	{
		ADC0_Value_Convert(pRecv);
	}
	
	//查看队列剩余大小
	if(queGlb.fsize == 1)
	{
		queGlb.size.que_hadc0 = uxQueueSpacesAvailable(Que_Hadc0_get);
	}
	
	ADC_StartGroupConversion(&adc0_instance, 0);
}







