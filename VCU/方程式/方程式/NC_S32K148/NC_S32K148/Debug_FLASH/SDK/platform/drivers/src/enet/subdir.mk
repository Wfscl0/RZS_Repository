################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SDK/platform/drivers/src/enet/enet_driver.c \
../SDK/platform/drivers/src/enet/enet_hw_access.c \
../SDK/platform/drivers/src/enet/enet_irq.c 

OBJS += \
./SDK/platform/drivers/src/enet/enet_driver.o \
./SDK/platform/drivers/src/enet/enet_hw_access.o \
./SDK/platform/drivers/src/enet/enet_irq.o 

C_DEPS += \
./SDK/platform/drivers/src/enet/enet_driver.d \
./SDK/platform/drivers/src/enet/enet_hw_access.d \
./SDK/platform/drivers/src/enet/enet_irq.d 


# Each subdirectory must supply rules for building sources it contributes
SDK/platform/drivers/src/enet/%.o: ../SDK/platform/drivers/src/enet/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/platform/drivers/src/enet/enet_driver.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


