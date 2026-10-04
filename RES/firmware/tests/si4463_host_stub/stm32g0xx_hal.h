#ifndef RES_SI4463_HAL_STUB
#define RES_SI4463_HAL_STUB
#include <stdint.h>
typedef enum { HAL_OK, HAL_ERROR } HAL_StatusTypeDef;
typedef enum { GPIO_PIN_RESET, GPIO_PIN_SET } GPIO_PinState;
typedef unsigned GPIO_TypeDef;
#define GPIOA ((GPIO_TypeDef *)1)
#define GPIOB ((GPIO_TypeDef *)2)
#define GPIO_PIN_2 4u
#define GPIO_PIN_3 8u
#define GPIO_PIN_4 16u
#define GPIO_PIN_5 32u
#define GPIO_PIN_6 64u
#define GPIO_PIN_7 128u
#define GPIO_MODE_OUTPUT_PP 1u
#define GPIO_MODE_INPUT 2u
#define GPIO_MODE_AF_PP 3u
#define GPIO_PULLUP 1u
#define GPIO_PULLDOWN 2u
#define GPIO_NOPULL 0u
#define GPIO_SPEED_FREQ_LOW 0u
#define GPIO_SPEED_FREQ_HIGH 3u
#define GPIO_AF0_SPI1 0u
#define SPI1 ((void *)3)
#define SPI_MODE_MASTER 1u
#define SPI_DIRECTION_2LINES 0u
#define SPI_DATASIZE_8BIT 8u
#define SPI_POLARITY_LOW 0u
#define SPI_PHASE_1EDGE 0u
#define SPI_NSS_SOFT 1u
#define SPI_BAUDRATEPRESCALER_64 64u
#define SPI_BAUDRATEPRESCALER_256 256u
#define SystemCoreClock 64000000u
void res_test_nop(void);
#define __NOP() res_test_nop()
#define SPI_FIRSTBIT_MSB 0u
#define SPI_TIMODE_DISABLE 0u
#define SPI_CRCCALCULATION_DISABLE 0u
#define SPI_CRC_LENGTH_DATASIZE 0u
#define SPI_NSS_PULSE_DISABLE 0u
#define __HAL_RCC_GPIOA_CLK_ENABLE() ((void)0)
#define __HAL_RCC_GPIOB_CLK_ENABLE() ((void)0)
#define __HAL_RCC_SPI1_CLK_ENABLE() ((void)0)
typedef struct { uint32_t Pin, Mode, Pull, Speed, Alternate; } GPIO_InitTypeDef;
typedef struct { void *Instance; struct {
 uint32_t Mode, Direction, DataSize, CLKPolarity, CLKPhase, NSS;
 uint32_t BaudRatePrescaler, FirstBit, TIMode, CRCCalculation;
 uint32_t CRCPolynomial, CRCLength, NSSPMode;
} Init; } SPI_HandleTypeDef;
uint32_t HAL_GetTick(void);
uint32_t __get_IPSR(void);
void HAL_Delay(uint32_t ms);
void HAL_GPIO_Init(GPIO_TypeDef *p, GPIO_InitTypeDef *g);
void HAL_GPIO_WritePin(GPIO_TypeDef *p,uint32_t pin,GPIO_PinState state);
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *p,uint32_t pin);
HAL_StatusTypeDef HAL_SPI_Init(SPI_HandleTypeDef *h);
HAL_StatusTypeDef HAL_SPI_TransmitReceive(SPI_HandleTypeDef *h,uint8_t *tx,uint8_t *rx,uint16_t n,uint32_t timeout);
#endif
