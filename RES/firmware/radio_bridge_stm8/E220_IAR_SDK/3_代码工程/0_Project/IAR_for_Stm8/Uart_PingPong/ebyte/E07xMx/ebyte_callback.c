/**
  **********************************************************************************
  * @file      ebyte_callback.h
  * @brief     EBYTE驱动库的收发完成回调函数 由客户实现自己的逻辑代码 
  * @details   详情请参见 https://www.ebyte.com/       
  * @author    JiangHeng     
  * @date      2021-05-26     
  * @version   1.0.0     
  **********************************************************************************
  * @copyright BSD License 
  *            成都亿佰特电子科技有限公司  
  *   ______   ____   __     __  _______   ______ 
  *  |  ____| |  _ \  \ \   / / |__   __| |  ____|
  *  | |__    | |_) |  \ \_/ /     | |    | |__   
  *  |  __|   |  _ <    \   /      | |    |  __|  
  *  | |____  | |_) |    | |       | |    | |____ 
  *  |______| |____/     |_|       |_|    |______| 
  *
  **********************************************************************************
  */
#include "ebyte_callback.h"

/*= !!!配置目标硬件平台头文件 =======================================*/
#include "board.h"  //E15-EVB02 评估板
/*= !!!配置目标硬件变量       =======================================*/
extern uint8_t RxBuffer[64];
extern uint8_t BufferPing[4];
extern uint8_t Callback_isPingCheckReady;
/*==================================================================*/



/* !
 * @brief 发送完成回调接口 由客户实现自己的发送完成逻辑
 * 
 * @param state 上层回调提供的状态码 客户请根据示例注释找到对应区域
 *  
 * @note E22x 模块可提供的状态码
 *         IRQ_TX_DONE                             = 0x0001,
 *         IRQ_RX_DONE                             = 0x0002,
 *         IRQ_PREAMBLE_DETECTED                   = 0x0004,
 *         IRQ_SYNCWORD_VALID                      = 0x0008,
 *         IRQ_HEADER_VALID                        = 0x0010,
 *         IRQ_HEADER_ERROR                        = 0x0020,
 *         IRQ_CRC_ERROR                           = 0x0040,
 *         IRQ_CAD_DONE                            = 0x0080,
 *         IRQ_CAD_ACTIVITY_DETECTED               = 0x0100,
 *         IRQ_RX_TX_TIMEOUT                       = 0x0200, 
 */
void Ebyte_Port_TransmitCallback( uint16e_t state )
{       
    /* 发送: 正常完成 */
    if( state &= 0x0001 )
    {
        //To-do 实现自己的逻辑 
    }
    /* 发送: 异常超时 */
    else if ( state &= 0x0200 )
    {
        //To-do 实现自己的逻辑 
    }
    /* 发送: 未知错误 */
    else
    {
        /* 发送状态标识不正确，请检查软硬件  
           常见问题 1:SPI通信不正确 2:模块供电不足 */
        while(1);
    }
}

/* !
 * @brief 接收完成回调接口 由客户实现自己的发送完成逻辑
 * 
 * @param state 上层回调提供的状态码 客户请根据示例注释找到对应区域
 * 
 * @note E22x 模块可提供的状态码
 *         IRQ_TX_DONE                             = 0x0001,
 *         IRQ_RX_DONE                             = 0x0002,
 *         IRQ_PREAMBLE_DETECTED                   = 0x0004,
 *         IRQ_SYNCWORD_VALID                      = 0x0008,
 *         IRQ_HEADER_VALID                        = 0x0010,
 *         IRQ_HEADER_ERROR                        = 0x0020,
 *         IRQ_CRC_ERROR                           = 0x0040,
 *         IRQ_CAD_DONE                            = 0x0080,
 *         IRQ_CAD_ACTIVITY_DETECTED               = 0x0100,
 *         IRQ_RX_TX_TIMEOUT                       = 0x0200, 
 */
void Ebyte_Port_ReceiveCallback(  uint16e_t state, uint8e_t *buffer, uint8e_t length )
{
    uint8_t  i,j;
  
    /* 接收: 正常 */
    if( state &= 0x0002 )
    {
        
       
         
        //To-do 实现自己的逻辑 
        
        /* 通过长度判断是否是ping pong指令  */
        if( length == 4 )
        {
             uint8_t *p;
             p = buffer;
             for(j=0;j<4;j++)
             {
                 if( BufferPing[j] != *p++)
                 {
                    break;
                 }
                 
             }
             //比较到了末尾表示完全匹配
             if( j == 4 )
             {
                Callback_isPingCheckReady = 1;
             }
        }
          
        Ebyte_BSP_LedControl( BSP_LED_1 , ON );
        
        for( i = 0; i < length; i++ )
        {
            while ( USART_GetFlagStatus( USART1, USART_FLAG_TXE ) == RESET );
            USART_SendData8( USART1, *buffer++ ); //EVB02串口输出
        }       
        Ebyte_BSP_LedControl( BSP_LED_1 , OFF );
    }
    /* 接收: 异常超时 */
    else if ( state &= 0x0200 )
    {
        //To-do 实现自己的逻辑 
    }
    /* 接收: 未知错误 */
    else
    {
        /* 发送状态标识不正确，请检查软硬件  
           常见问题 1:SPI通信不正确 2:模块供电不足 */
        while(1);
    }
}