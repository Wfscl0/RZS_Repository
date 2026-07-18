################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SDK/rtos/FreeRTOS_S32K/Source/croutine.c \
../SDK/rtos/FreeRTOS_S32K/Source/event_groups.c \
../SDK/rtos/FreeRTOS_S32K/Source/list.c \
../SDK/rtos/FreeRTOS_S32K/Source/queue.c \
../SDK/rtos/FreeRTOS_S32K/Source/stream_buffer.c \
../SDK/rtos/FreeRTOS_S32K/Source/tasks.c \
../SDK/rtos/FreeRTOS_S32K/Source/timers.c 

OBJS += \
./SDK/rtos/FreeRTOS_S32K/Source/croutine.o \
./SDK/rtos/FreeRTOS_S32K/Source/event_groups.o \
./SDK/rtos/FreeRTOS_S32K/Source/list.o \
./SDK/rtos/FreeRTOS_S32K/Source/queue.o \
./SDK/rtos/FreeRTOS_S32K/Source/stream_buffer.o \
./SDK/rtos/FreeRTOS_S32K/Source/tasks.o \
./SDK/rtos/FreeRTOS_S32K/Source/timers.o 

C_DEPS += \
./SDK/rtos/FreeRTOS_S32K/Source/croutine.d \
./SDK/rtos/FreeRTOS_S32K/Source/event_groups.d \
./SDK/rtos/FreeRTOS_S32K/Source/list.d \
./SDK/rtos/FreeRTOS_S32K/Source/queue.d \
./SDK/rtos/FreeRTOS_S32K/Source/stream_buffer.d \
./SDK/rtos/FreeRTOS_S32K/Source/tasks.d \
./SDK/rtos/FreeRTOS_S32K/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
SDK/rtos/FreeRTOS_S32K/Source/%.o: ../SDK/rtos/FreeRTOS_S32K/Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/rtos/FreeRTOS_S32K/Source/croutine.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


