#ifndef HAL_UART_TEST_STUB
#define HAL_UART_TEST_STUB
#include <stdint.h>
typedef enum { HAL_OK, HAL_ERROR, HAL_BUSY } HAL_StatusTypeDef;
#define HAL_UART_STATE_READY 0u
#define HAL_UART_STATE_BUSY_RX 1u
typedef struct { uint32_t RxState, ErrorCode; } UART_HandleTypeDef;
uint32_t HAL_GetTick(void);
uint32_t __get_PRIMASK(void);
uint32_t __get_IPSR(void);
void __disable_irq(void);
void __set_PRIMASK(uint32_t value);
uint32_t HAL_UART_GetError(UART_HandleTypeDef *h);
HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *h,uint8_t *p,uint16_t n);
HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *h,uint8_t *p,uint16_t n,uint32_t timeout);
#endif
