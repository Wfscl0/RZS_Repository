################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SDK/platform/pal/src/i2c/i2c_pal.c 

OBJS += \
./SDK/platform/pal/src/i2c/i2c_pal.o 

C_DEPS += \
./SDK/platform/pal/src/i2c/i2c_pal.d 


# Each subdirectory must supply rules for building sources it contributes
SDK/platform/pal/src/i2c/%.o: ../SDK/platform/pal/src/i2c/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/platform/pal/src/i2c/i2c_pal.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


