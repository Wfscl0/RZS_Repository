################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/Cpu.c \
../Generated_Code/Flash1.c \
../Generated_Code/adc0.c \
../Generated_Code/can0.c \
../Generated_Code/can1.c \
../Generated_Code/can2.c \
../Generated_Code/clockMan1.c \
../Generated_Code/dmaController1.c \
../Generated_Code/flexio_uart_rx.c \
../Generated_Code/flexio_uart_tx.c \
../Generated_Code/i2c0_ads15.c \
../Generated_Code/i2c1_at24c.c \
../Generated_Code/pin_mux.c \
../Generated_Code/pwm1_ucc27.c \
../Generated_Code/pwm5.c \
../Generated_Code/pwm6_tlf35.c \
../Generated_Code/pwrMan1.c \
../Generated_Code/spi0_tlf35.c \
../Generated_Code/spi1_max318.c \
../Generated_Code/spi2_mc338.c \
../Generated_Code/uart0_iot.c \
../Generated_Code/uart1_jy60.c \
../Generated_Code/uart2_sbus.c 

OBJS += \
./Generated_Code/Cpu.o \
./Generated_Code/Flash1.o \
./Generated_Code/adc0.o \
./Generated_Code/can0.o \
./Generated_Code/can1.o \
./Generated_Code/can2.o \
./Generated_Code/clockMan1.o \
./Generated_Code/dmaController1.o \
./Generated_Code/flexio_uart_rx.o \
./Generated_Code/flexio_uart_tx.o \
./Generated_Code/i2c0_ads15.o \
./Generated_Code/i2c1_at24c.o \
./Generated_Code/pin_mux.o \
./Generated_Code/pwm1_ucc27.o \
./Generated_Code/pwm5.o \
./Generated_Code/pwm6_tlf35.o \
./Generated_Code/pwrMan1.o \
./Generated_Code/spi0_tlf35.o \
./Generated_Code/spi1_max318.o \
./Generated_Code/spi2_mc338.o \
./Generated_Code/uart0_iot.o \
./Generated_Code/uart1_jy60.o \
./Generated_Code/uart2_sbus.o 

C_DEPS += \
./Generated_Code/Cpu.d \
./Generated_Code/Flash1.d \
./Generated_Code/adc0.d \
./Generated_Code/can0.d \
./Generated_Code/can1.d \
./Generated_Code/can2.d \
./Generated_Code/clockMan1.d \
./Generated_Code/dmaController1.d \
./Generated_Code/flexio_uart_rx.d \
./Generated_Code/flexio_uart_tx.d \
./Generated_Code/i2c0_ads15.d \
./Generated_Code/i2c1_at24c.d \
./Generated_Code/pin_mux.d \
./Generated_Code/pwm1_ucc27.d \
./Generated_Code/pwm5.d \
./Generated_Code/pwm6_tlf35.d \
./Generated_Code/pwrMan1.d \
./Generated_Code/spi0_tlf35.d \
./Generated_Code/spi1_max318.d \
./Generated_Code/spi2_mc338.d \
./Generated_Code/uart0_iot.d \
./Generated_Code/uart1_jy60.d \
./Generated_Code/uart2_sbus.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Generated_Code/Cpu.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


