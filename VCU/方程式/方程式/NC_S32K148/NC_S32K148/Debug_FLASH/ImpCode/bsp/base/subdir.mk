################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ImpCode/bsp/base/bsp_adc.c \
../ImpCode/bsp/base/bsp_ads1115.c \
../ImpCode/bsp/base/bsp_adsch8.c \
../ImpCode/bsp/base/bsp_at24c256.c \
../ImpCode/bsp/base/bsp_bootld.c \
../ImpCode/bsp/base/bsp_max31865.c \
../ImpCode/bsp/base/bsp_mc33879.c \
../ImpCode/bsp/base/bsp_pflash.c \
../ImpCode/bsp/base/bsp_pin.c \
../ImpCode/bsp/base/bsp_tlf35584.c \
../ImpCode/bsp/base/bsp_ucc27517.c 

OBJS += \
./ImpCode/bsp/base/bsp_adc.o \
./ImpCode/bsp/base/bsp_ads1115.o \
./ImpCode/bsp/base/bsp_adsch8.o \
./ImpCode/bsp/base/bsp_at24c256.o \
./ImpCode/bsp/base/bsp_bootld.o \
./ImpCode/bsp/base/bsp_max31865.o \
./ImpCode/bsp/base/bsp_mc33879.o \
./ImpCode/bsp/base/bsp_pflash.o \
./ImpCode/bsp/base/bsp_pin.o \
./ImpCode/bsp/base/bsp_tlf35584.o \
./ImpCode/bsp/base/bsp_ucc27517.o 

C_DEPS += \
./ImpCode/bsp/base/bsp_adc.d \
./ImpCode/bsp/base/bsp_ads1115.d \
./ImpCode/bsp/base/bsp_adsch8.d \
./ImpCode/bsp/base/bsp_at24c256.d \
./ImpCode/bsp/base/bsp_bootld.d \
./ImpCode/bsp/base/bsp_max31865.d \
./ImpCode/bsp/base/bsp_mc33879.d \
./ImpCode/bsp/base/bsp_pflash.d \
./ImpCode/bsp/base/bsp_pin.d \
./ImpCode/bsp/base/bsp_tlf35584.d \
./ImpCode/bsp/base/bsp_ucc27517.d 


# Each subdirectory must supply rules for building sources it contributes
ImpCode/bsp/base/%.o: ../ImpCode/bsp/base/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@ImpCode/bsp/base/bsp_adc.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


