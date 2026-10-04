; STM32G0B1xx startup for Keil MDK-ARM.
; Vector layout follows the STM32G0B1 CMSIS device definition.
; Stack and heap sizes match the CubeMX project settings.

Stack_Size      EQU     0x00000400
Heap_Size       EQU     0x00000200

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp
                DCD     Reset_Handler
                DCD     NMI_Handler
                DCD     HardFault_Handler
                DCD     0, 0, 0, 0, 0, 0, 0
                DCD     SVC_Handler
                DCD     0, 0
                DCD     PendSV_Handler
                DCD     SysTick_Handler

                DCD     WWDG_IRQHandler
                DCD     PVD_VDDIO2_IRQHandler
                DCD     RTC_TAMP_IRQHandler
                DCD     FLASH_IRQHandler
                DCD     RCC_CRS_IRQHandler
                DCD     EXTI0_1_IRQHandler
                DCD     EXTI2_3_IRQHandler
                DCD     EXTI4_15_IRQHandler
                DCD     USB_UCPD1_2_IRQHandler
                DCD     DMA1_Channel1_IRQHandler
                DCD     DMA1_Channel2_3_IRQHandler
                DCD     DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX1_OVR_IRQHandler
                DCD     ADC1_COMP_IRQHandler
                DCD     TIM1_BRK_UP_TRG_COM_IRQHandler
                DCD     TIM1_CC_IRQHandler
                DCD     TIM2_IRQHandler
                DCD     TIM3_TIM4_IRQHandler
                DCD     TIM6_DAC_LPTIM1_IRQHandler
                DCD     TIM7_LPTIM2_IRQHandler
                DCD     TIM14_IRQHandler
                DCD     TIM15_IRQHandler
                DCD     TIM16_FDCAN_IT0_IRQHandler
                DCD     TIM17_FDCAN_IT1_IRQHandler
                DCD     I2C1_IRQHandler
                DCD     I2C2_3_IRQHandler
                DCD     SPI1_IRQHandler
                DCD     SPI2_3_IRQHandler
                DCD     USART1_IRQHandler
                DCD     USART2_LPUART2_IRQHandler
                DCD     USART3_4_5_6_LPUART1_IRQHandler
                DCD     CEC_IRQHandler
__Vectors_End
__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

Reset_Handler   PROC
                EXPORT  Reset_Handler [WEAK]
                IMPORT  __main
                IMPORT  SystemInit
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP

NMI_Handler     PROC
                EXPORT  NMI_Handler [WEAK]
                B       .
                ENDP
HardFault_Handler PROC
                EXPORT  HardFault_Handler [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler [WEAK]
                B       .
                ENDP

Default_Handler PROC
                EXPORT  WWDG_IRQHandler [WEAK]
                EXPORT  PVD_VDDIO2_IRQHandler [WEAK]
                EXPORT  RTC_TAMP_IRQHandler [WEAK]
                EXPORT  FLASH_IRQHandler [WEAK]
                EXPORT  RCC_CRS_IRQHandler [WEAK]
                EXPORT  EXTI0_1_IRQHandler [WEAK]
                EXPORT  EXTI2_3_IRQHandler [WEAK]
                EXPORT  EXTI4_15_IRQHandler [WEAK]
                EXPORT  USB_UCPD1_2_IRQHandler [WEAK]
                EXPORT  DMA1_Channel1_IRQHandler [WEAK]
                EXPORT  DMA1_Channel2_3_IRQHandler [WEAK]
                EXPORT  DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX1_OVR_IRQHandler [WEAK]
                EXPORT  ADC1_COMP_IRQHandler [WEAK]
                EXPORT  TIM1_BRK_UP_TRG_COM_IRQHandler [WEAK]
                EXPORT  TIM1_CC_IRQHandler [WEAK]
                EXPORT  TIM2_IRQHandler [WEAK]
                EXPORT  TIM3_TIM4_IRQHandler [WEAK]
                EXPORT  TIM6_DAC_LPTIM1_IRQHandler [WEAK]
                EXPORT  TIM7_LPTIM2_IRQHandler [WEAK]
                EXPORT  TIM14_IRQHandler [WEAK]
                EXPORT  TIM15_IRQHandler [WEAK]
                EXPORT  TIM16_FDCAN_IT0_IRQHandler [WEAK]
                EXPORT  TIM17_FDCAN_IT1_IRQHandler [WEAK]
                EXPORT  I2C1_IRQHandler [WEAK]
                EXPORT  I2C2_3_IRQHandler [WEAK]
                EXPORT  SPI1_IRQHandler [WEAK]
                EXPORT  SPI2_3_IRQHandler [WEAK]
                EXPORT  USART1_IRQHandler [WEAK]
                EXPORT  USART2_LPUART2_IRQHandler [WEAK]
                EXPORT  USART3_4_5_6_LPUART1_IRQHandler [WEAK]
                EXPORT  CEC_IRQHandler [WEAK]

WWDG_IRQHandler
PVD_VDDIO2_IRQHandler
RTC_TAMP_IRQHandler
FLASH_IRQHandler
RCC_CRS_IRQHandler
EXTI0_1_IRQHandler
EXTI2_3_IRQHandler
EXTI4_15_IRQHandler
USB_UCPD1_2_IRQHandler
DMA1_Channel1_IRQHandler
DMA1_Channel2_3_IRQHandler
DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX1_OVR_IRQHandler
ADC1_COMP_IRQHandler
TIM1_BRK_UP_TRG_COM_IRQHandler
TIM1_CC_IRQHandler
TIM2_IRQHandler
TIM3_TIM4_IRQHandler
TIM6_DAC_LPTIM1_IRQHandler
TIM7_LPTIM2_IRQHandler
TIM14_IRQHandler
TIM15_IRQHandler
TIM16_FDCAN_IT0_IRQHandler
TIM17_FDCAN_IT1_IRQHandler
I2C1_IRQHandler
I2C2_3_IRQHandler
SPI1_IRQHandler
SPI2_3_IRQHandler
USART1_IRQHandler
USART2_LPUART2_IRQHandler
USART3_4_5_6_LPUART1_IRQHandler
CEC_IRQHandler
                B       .
                ENDP

                ALIGN
                IF      :DEF:__MICROLIB
                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit
                ELSE
                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap
                LDR     R0, =Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, =(Heap_Mem + Heap_Size)
                LDR     R3, =Stack_Mem
                BX      LR
                ALIGN
                ENDIF
                END

