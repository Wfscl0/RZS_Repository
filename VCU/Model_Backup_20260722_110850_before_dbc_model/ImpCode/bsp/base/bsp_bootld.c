#include "bsp_bootld.h"


#define BOOT_RAM __attribute__((section(".flag")))
//下载请求Flag地址
uint32_t BOOT_RAM g_JumpInit;
uint8_t  bootjumpflag=0;

/***************************************************************************
 * Bootld 初始化
 *
 */
void BSP_Bootld_Init(void)
{
	
}

/***************************************************************************
 * Bootld 主循环任务
 *
 */
void BSP_Bootld_Task(void)
{
	if(bootjumpflag)
	{
		g_JumpInit = DOWNLOAD_FLAG;
		
		//软件重启
		INT_SYS_DisableIRQGlobal(); //关闭总中断
		SystemSoftwareReset();
//		__set_FAULTMASK(1);	 //关闭所有中断
//		NVIC_SystemReset();  //系统复位
	}
}











