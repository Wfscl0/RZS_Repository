################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SDK/platform/pal/src/adc/adc_irq.c \
../SDK/platform/pal/src/adc/adc_pal.c 

OBJS += \
./SDK/platform/pal/src/adc/adc_irq.o \
./SDK/platform/pal/src/adc/adc_pal.o 

C_DEPS += \
./SDK/platform/pal/src/adc/adc_irq.d \
./SDK/platform/pal/src/adc/adc_pal.d 


# Each subdirectory must supply rules for building sources it contributes
SDK/platform/pal/src/adc/%.o: ../SDK/platform/pal/src/adc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/platform/pal/src/adc/adc_irq.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


