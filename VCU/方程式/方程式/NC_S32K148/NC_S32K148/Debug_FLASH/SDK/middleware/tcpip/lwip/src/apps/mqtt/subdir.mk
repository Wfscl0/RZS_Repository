################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SDK/middleware/tcpip/lwip/src/apps/mqtt/mqtt.c 

OBJS += \
./SDK/middleware/tcpip/lwip/src/apps/mqtt/mqtt.o 

C_DEPS += \
./SDK/middleware/tcpip/lwip/src/apps/mqtt/mqtt.d 


# Each subdirectory must supply rules for building sources it contributes
SDK/middleware/tcpip/lwip/src/apps/mqtt/%.o: ../SDK/middleware/tcpip/lwip/src/apps/mqtt/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/middleware/tcpip/lwip/src/apps/mqtt/mqtt.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


