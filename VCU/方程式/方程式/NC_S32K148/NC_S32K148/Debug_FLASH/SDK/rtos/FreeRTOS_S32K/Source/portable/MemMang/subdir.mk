################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SDK/rtos/FreeRTOS_S32K/Source/portable/MemMang/heap_4.c 

OBJS += \
./SDK/rtos/FreeRTOS_S32K/Source/portable/MemMang/heap_4.o 

C_DEPS += \
./SDK/rtos/FreeRTOS_S32K/Source/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
SDK/rtos/FreeRTOS_S32K/Source/portable/MemMang/%.o: ../SDK/rtos/FreeRTOS_S32K/Source/portable/MemMang/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/rtos/FreeRTOS_S32K/Source/portable/MemMang/heap_4.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


