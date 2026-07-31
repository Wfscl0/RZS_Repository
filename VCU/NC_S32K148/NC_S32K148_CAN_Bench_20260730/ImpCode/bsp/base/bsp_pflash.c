/*
 * ********************************************************************************
 * VCU Flash存储
 * pflash.c
 *
 *  Created on: 2024年12月7日
 *      Author: ROG
 */

#include "bsp_pflash.h"



static flash_ssd_config_t 	pSSDConfig;
FLASH_APPVAL 				FlashVal;

/* ********************************************************************************
 * FLASH初始化
 *
 */
void BSP_FLASH_Init(void)
{
	/* Disable cache to ensure that all flash operations will take effect instantly, this is device dependent */
    MSCM->OCMDR[0u] |= MSCM_OCMDR_OCM1(0x3u);
    MSCM->OCMDR[1u] |= MSCM_OCMDR_OCM1(0x3u);
	
	FLASH_DRV_Init(&Flash1_InitConfig0, &pSSDConfig);
}


/* ********************************************************************************
 * 读取指定地址的全字(32位数据)
 *
 */
uint32_t FLASH_Read_Word(uint32_t address)
{
    return *(volatile uint32_t *)address;
}

uint8_t FLASH_Read_Byte(uint32_t address)
{
	return *(volatile uint8_t *)address;
}

/***************************************************************************
 * 从指定地址开始擦除指定长度存储。长度为字节单位（注意，调用时加关中断！）
 *
 */
uint16_t FLASH_Erase(uint32_t waddr, uint32_t length)
{
	uint16_t  ret;
	uint16_t tempsize;
	
	//数据擦除最小扇区大小是4k。大小不足时，增加剩余部分
	tempsize = length % 4096;
	if(tempsize){
		if(length < 4096){
			length = 4096;
		}
		else{
			length = length-tempsize+4096;
		}
	}
	
	ret = FLASH_DRV_EraseSector(&pSSDConfig, waddr, length);
	if (ret != STATUS_SUCCESS){
        return ret;
    }
	
	/* Disable Callback */
    pSSDConfig.CallBack = NULL_CALLBACK;
	
	/* Verify the erase operation at margin level value of 1, user read */
    ret = FLASH_DRV_VerifySection(&pSSDConfig, waddr, length/FTFx_DPHRASE_SIZE, 1u);
    if (ret != STATUS_SUCCESS){
        return ret;
    }
	
	return ret;
}

uint16_t BSP_FLASH_Erase(uint32_t waddr1, uint32_t length1)
{
	uint16_t  ret1;

	INT_SYS_DisableIRQGlobal();
	ret1 = FLASH_Erase(waddr1, length1);
	INT_SYS_EnableIRQGlobal();
	return ret1;
}

/* ********************************************************************************
 * 从指定地址开始写入多个数据。字节为单位，写入大小需要时8的倍数！！
 *
 */
uint16_t BSP_FLASH_WriteData(uint32_t waddr, uint8_t *pbuf, uint32_t length)
{
	uint16_t ret;
	uint32_t addrx=0,endaddr=0;
	uint32_t p_failAddr,tempval;
	
	INT_SYS_DisableIRQGlobal();
	
	addrx = waddr;              /* 写入的起始地址 */
    endaddr = waddr+length;   	/* 写入的结束地址 */
	
	while (addrx < endaddr) {	/* 扫清一切障碍.(对非FFFFFFFF的地方,先擦除) */
		//有非0XFFFFFFFF的地方,要擦除这个扇区
		if(FLASH_Read_Word(addrx) != 0XFFFFFFFF) { 
			tempval = endaddr-addrx;
			ret = FLASH_Erase(addrx, tempval); //擦除
			if(ret != STATUS_SUCCESS){
				INT_SYS_EnableIRQGlobal();
				return ret;
			}
		}
		else{
			addrx += 4;
		}
	}
	
	/* 向FLASH中写入数据 */
    ret = FLASH_DRV_Program(&pSSDConfig, waddr, length, pbuf);
	 if (ret != STATUS_SUCCESS){
		INT_SYS_EnableIRQGlobal();
        return ret;
    }
	
	/* 校验写入的数据 */
    ret = FLASH_DRV_ProgramCheck(&pSSDConfig, waddr, length, pbuf, &p_failAddr, 1u);
    if (ret != STATUS_SUCCESS){
		INT_SYS_EnableIRQGlobal();
        return ret;
    }
	
	INT_SYS_EnableIRQGlobal();
	return ret;
}

/* ********************************************************************************
 * 从指定地址开始读取多个数据。字节为单位！
 *
 */
void BSP_FLASH_ReadData_Byte(uint32_t raddr, uint8_t *pbuf, uint32_t length)
{
    uint32_t i;

	INT_SYS_DisableIRQGlobal();
	
    for(i=0; i<length; i++)
    {
        pbuf[i] = FLASH_Read_Byte(raddr); /* 读取1个字节. */
		raddr++;
    }
	INT_SYS_EnableIRQGlobal();
}

/* ********************************************************************************
 * 从指定地址开始读取多个数据。字为单位！
 *
 */
void BSP_FLASH_ReadData(uint32_t raddr, uint32_t *pbuf, uint32_t length)
{
    uint32_t i;

	INT_SYS_DisableIRQGlobal();
	
    for(i=0; i<length; i++)
    {
        pbuf[i] = FLASH_Read_Word(raddr); /* 读取4个字节. */
        raddr += 4; /* 偏移4个字节. */
    }
	INT_SYS_EnableIRQGlobal();
}

/***************************************************************************
 * APP下载升级信息。存储
 *
 */
uint8_t Flash_Write_Data(uint8_t *pdata, uint32_t value)
{
	pdata[0] = (uint8_t)(value & 0xFF);
	pdata[1] = (uint8_t)((value >> 8) & 0xFF);
	pdata[2] = (uint8_t)((value >> 16) & 0xFF);
	pdata[3] = (uint8_t)((value >> 24) & 0xFF);
	
	return 4;
}

void BSP_FLASH_Write_APPVAL(void)
{
	//uint16_t i = 0;
	uint16_t lenval1=0;
	uint16_t  temp12=0,k;
	uint8_t  tempdata[FSIZE_VAL*4];
	
	for(k=0; k<FSIZE_VAL; k++){
		lenval1 += Flash_Write_Data(&tempdata[lenval1], FlashVal.value[k]);
	}
	
	temp12 = lenval1%8; //数据存储需要是8的倍数。不够时，增加剩余大小
	if(temp12){
		temp12 = 8-temp12;
		temp12 += lenval1;
	}
	else{
		temp12 = lenval1;
	}
	
	BSP_FLASH_WriteData(FLASH_ADDR_VAL, tempdata, temp12);
}

/***************************************************************************
 * APP下载升级信息。读取
 *
 */
void BSP_FLASH_Read_APPVAL(void)
{
	//uint16_t i = 0;
	
	BSP_FLASH_ReadData(FLASH_ADDR_VAL, FlashVal.value, FSIZE_VAL);
}


/***************************************************************************
 * 任务函数。测试
 *
 */
uint8_t tflag[2];
void BSP_Flash_Task(void)
{
	uint16_t i = 0;
	
	if(tflag[1] != tflag[0]){
		tflag[1] = tflag[0];
		
		FlashVal.test1 = 0x21;
		FlashVal.test2 = 0x1234;
		FlashVal.test3 = 0x12345678;
		
		//TEST
		FlashVal.value[i++] = FlashVal.test1;
		FlashVal.value[i++] = FlashVal.test2;
		FlashVal.value[i++] = FlashVal.test3;
		
		BSP_FLASH_Write_APPVAL();
	}
	
	BSP_FLASH_Read_APPVAL();
	
	//TEST
	FlashVal.test1 = FlashVal.value[i++];
	FlashVal.test2 = FlashVal.value[i++];
	FlashVal.test3 = FlashVal.value[i++];
}



