################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ImpCode/interface/CAN_Node.c 

OBJS += \
./ImpCode/interface/CAN_Node.o 

C_DEPS += \
./ImpCode/interface/CAN_Node.d 


# Each subdirectory must supply rules for building sources it contributes
ImpCode/interface/%.o: ../ImpCode/interface/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@ImpCode/interface/CAN_Node.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


