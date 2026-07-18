################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SDK/middleware/tcpip/tcpip_stack/apps/tcpecho/tcpecho.c 

OBJS += \
./SDK/middleware/tcpip/tcpip_stack/apps/tcpecho/tcpecho.o 

C_DEPS += \
./SDK/middleware/tcpip/tcpip_stack/apps/tcpecho/tcpecho.d 


# Each subdirectory must supply rules for building sources it contributes
SDK/middleware/tcpip/tcpip_stack/apps/tcpecho/%.o: ../SDK/middleware/tcpip/tcpip_stack/apps/tcpecho/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/middleware/tcpip/tcpip_stack/apps/tcpecho/tcpecho.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


