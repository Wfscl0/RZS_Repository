################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SDK/platform/drivers/src/lpi2c/lpi2c_driver.c \
../SDK/platform/drivers/src/lpi2c/lpi2c_hw_access.c \
../SDK/platform/drivers/src/lpi2c/lpi2c_irq.c 

OBJS += \
./SDK/platform/drivers/src/lpi2c/lpi2c_driver.o \
./SDK/platform/drivers/src/lpi2c/lpi2c_hw_access.o \
./SDK/platform/drivers/src/lpi2c/lpi2c_irq.o 

C_DEPS += \
./SDK/platform/drivers/src/lpi2c/lpi2c_driver.d \
./SDK/platform/drivers/src/lpi2c/lpi2c_hw_access.d \
./SDK/platform/drivers/src/lpi2c/lpi2c_irq.d 


# Each subdirectory must supply rules for building sources it contributes
SDK/platform/drivers/src/lpi2c/%.o: ../SDK/platform/drivers/src/lpi2c/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/platform/drivers/src/lpi2c/lpi2c_driver.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


