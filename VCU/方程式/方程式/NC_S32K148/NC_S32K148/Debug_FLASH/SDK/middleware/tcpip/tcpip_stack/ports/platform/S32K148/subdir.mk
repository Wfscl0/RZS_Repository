################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SDK/middleware/tcpip/tcpip_stack/ports/platform/S32K148/platform.c 

OBJS += \
./SDK/middleware/tcpip/tcpip_stack/ports/platform/S32K148/platform.o 

C_DEPS += \
./SDK/middleware/tcpip/tcpip_stack/ports/platform/S32K148/platform.d 


# Each subdirectory must supply rules for building sources it contributes
SDK/middleware/tcpip/tcpip_stack/ports/platform/S32K148/%.o: ../SDK/middleware/tcpip/tcpip_stack/ports/platform/S32K148/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/middleware/tcpip/tcpip_stack/ports/platform/S32K148/platform.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


