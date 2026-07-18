################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SDK/middleware/tcpip/tcpip_stack/apps/ccov/ccov.c 

OBJS += \
./SDK/middleware/tcpip/tcpip_stack/apps/ccov/ccov.o 

C_DEPS += \
./SDK/middleware/tcpip/tcpip_stack/apps/ccov/ccov.d 


# Each subdirectory must supply rules for building sources it contributes
SDK/middleware/tcpip/tcpip_stack/apps/ccov/%.o: ../SDK/middleware/tcpip/tcpip_stack/apps/ccov/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/middleware/tcpip/tcpip_stack/apps/ccov/ccov.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


