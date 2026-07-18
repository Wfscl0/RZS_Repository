################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SDK/platform/drivers/src/adc/adc_driver.c 

OBJS += \
./SDK/platform/drivers/src/adc/adc_driver.o 

C_DEPS += \
./SDK/platform/drivers/src/adc/adc_driver.d 


# Each subdirectory must supply rules for building sources it contributes
SDK/platform/drivers/src/adc/%.o: ../SDK/platform/drivers/src/adc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/platform/drivers/src/adc/adc_driver.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


