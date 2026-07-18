################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ImpCode/bsp/com/bsp_can0.c \
../ImpCode/bsp/com/bsp_can1.c \
../ImpCode/bsp/com/bsp_can2.c \
../ImpCode/bsp/com/bsp_net.c \
../ImpCode/bsp/com/bsp_uart.c \
../ImpCode/bsp/com/bsp_uart_iot.c \
../ImpCode/bsp/com/bsp_uart_jy60.c \
../ImpCode/bsp/com/bsp_uart_sbus.c 

OBJS += \
./ImpCode/bsp/com/bsp_can0.o \
./ImpCode/bsp/com/bsp_can1.o \
./ImpCode/bsp/com/bsp_can2.o \
./ImpCode/bsp/com/bsp_net.o \
./ImpCode/bsp/com/bsp_uart.o \
./ImpCode/bsp/com/bsp_uart_iot.o \
./ImpCode/bsp/com/bsp_uart_jy60.o \
./ImpCode/bsp/com/bsp_uart_sbus.o 

C_DEPS += \
./ImpCode/bsp/com/bsp_can0.d \
./ImpCode/bsp/com/bsp_can1.d \
./ImpCode/bsp/com/bsp_can2.d \
./ImpCode/bsp/com/bsp_net.d \
./ImpCode/bsp/com/bsp_uart.d \
./ImpCode/bsp/com/bsp_uart_iot.d \
./ImpCode/bsp/com/bsp_uart_jy60.d \
./ImpCode/bsp/com/bsp_uart_sbus.d 


# Each subdirectory must supply rules for building sources it contributes
ImpCode/bsp/com/%.o: ../ImpCode/bsp/com/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@ImpCode/bsp/com/bsp_can0.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


