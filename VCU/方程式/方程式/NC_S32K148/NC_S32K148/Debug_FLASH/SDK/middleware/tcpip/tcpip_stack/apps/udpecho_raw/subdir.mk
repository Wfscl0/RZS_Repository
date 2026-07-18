################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SDK/middleware/tcpip/tcpip_stack/apps/udpecho_raw/udpecho_raw.c 

OBJS += \
./SDK/middleware/tcpip/tcpip_stack/apps/udpecho_raw/udpecho_raw.o 

C_DEPS += \
./SDK/middleware/tcpip/tcpip_stack/apps/udpecho_raw/udpecho_raw.d 


# Each subdirectory must supply rules for building sources it contributes
SDK/middleware/tcpip/tcpip_stack/apps/udpecho_raw/%.o: ../SDK/middleware/tcpip/tcpip_stack/apps/udpecho_raw/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/middleware/tcpip/tcpip_stack/apps/udpecho_raw/udpecho_raw.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


