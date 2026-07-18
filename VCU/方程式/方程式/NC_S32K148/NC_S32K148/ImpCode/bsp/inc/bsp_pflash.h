/*
 * flash.h
 *
 *  Created on: 2024年3月7日
 *      Author: ROG
 */

#ifndef _BSP_PFLASH_H_
#define _BSP_PFLASH_H_

#include "Flash1.h"



/*******************************************************************************
** 内存划分
*/
//#define FLASH_ADDR_BOOTLOADER			0x0000000 //Bootloader程序 48K
//#define FLASH_ADDR_APPDOWNINFO		0x000C000 //APP下载升级信息 16K
//#define FLASH_ADDR_VAL				0x0010000 //APP程序变量 64K
//#define FLASH_ADDR_APP				0x0020000 //APP 256K
//#define FLASH_ADDR_APPBACK			0x0060000 //APP下载区程序 256K
//#define FLASH_ADDR_RESERVE			0x00A0000 //预留内存 384K

//APP 读写内存划分
#define FLASH_ADDR_VAL					0x0010000 //APP程序变量 64K	0x001 0000 ~ 0x001 FFFF
//#define FLASH_ADDR_SAVE1				0x00A0000 //数据内存1 384K  0x00A 0000 ~ 0x00F FFFF
//数据内存1 384K 划分2个部分。
#define FLASH_ADDR_SV1_DIG				0x00A0000 //数据内存1。128K  故障诊断存储
#define FLASH_ADDR_SV1_REV				0x00C0000 //数据内存1。256K  预留
#define FLASH_ADDR_SAVE2				0x0100000 //数据内存2 512k  0x010 0000 ~ 0x017 FFFF



/*******************************************************************************
** FLASH存储信息 结构体变量声明
*/
#define FSIZE_VAL 64 //根据需要，进行扩大。16384
typedef struct
{
	//一般变量进行统一存储。数据统一以32位进行存储
	
	uint32_t value[FSIZE_VAL];   
	
	uint8_t  test1;
	uint16_t test2;
	uint32_t test3;

}FLASH_APPVAL;

extern FLASH_APPVAL FlashVal;




uint16_t BSP_FLASH_WriteData(uint32_t waddr, uint8_t *pbuf, uint32_t length);
uint16_t BSP_FLASH_Erase(uint32_t waddr, uint32_t length);
void BSP_FLASH_ReadData_Byte(uint32_t raddr, uint8_t *pbuf, uint32_t length);
void BSP_FLASH_ReadData(uint32_t raddr, uint32_t *pbuf, uint32_t length);

void BSP_FLASH_Init(void);
void BSP_FLASH_Write_APPVAL(void);
void BSP_FLASH_Read_APPVAL(void);
void BSP_Flash_Task(void);

#endif /* PFLASH_H_ */



