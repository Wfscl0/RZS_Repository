################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SDK/platform/drivers/src/lpspi/lpspi_hw_access.c \
../SDK/platform/drivers/src/lpspi/lpspi_irq.c \
../SDK/platform/drivers/src/lpspi/lpspi_master_driver.c \
../SDK/platform/drivers/src/lpspi/lpspi_shared_function.c \
../SDK/platform/drivers/src/lpspi/lpspi_slave_driver.c 

OBJS += \
./SDK/platform/drivers/src/lpspi/lpspi_hw_access.o \
./SDK/platform/drivers/src/lpspi/lpspi_irq.o \
./SDK/platform/drivers/src/lpspi/lpspi_master_driver.o \
./SDK/platform/drivers/src/lpspi/lpspi_shared_function.o \
./SDK/platform/drivers/src/lpspi/lpspi_slave_driver.o 

C_DEPS += \
./SDK/platform/drivers/src/lpspi/lpspi_hw_access.d \
./SDK/platform/drivers/src/lpspi/lpspi_irq.d \
./SDK/platform/drivers/src/lpspi/lpspi_master_driver.d \
./SDK/platform/drivers/src/lpspi/lpspi_shared_function.d \
./SDK/platform/drivers/src/lpspi/lpspi_slave_driver.d 


# Each subdirectory must supply rules for building sources it contributes
SDK/platform/drivers/src/lpspi/%.o: ../SDK/platform/drivers/src/lpspi/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/platform/drivers/src/lpspi/lpspi_hw_access.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


