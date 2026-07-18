################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SDK/middleware/tcpip/lwip/src/apps/lwiperf/lwiperf.c 

OBJS += \
./SDK/middleware/tcpip/lwip/src/apps/lwiperf/lwiperf.o 

C_DEPS += \
./SDK/middleware/tcpip/lwip/src/apps/lwiperf/lwiperf.d 


# Each subdirectory must supply rules for building sources it contributes
SDK/middleware/tcpip/lwip/src/apps/lwiperf/%.o: ../SDK/middleware/tcpip/lwip/src/apps/lwiperf/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/middleware/tcpip/lwip/src/apps/lwiperf/lwiperf.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


