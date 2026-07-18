################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ImpCode/os/os_task.c \
../ImpCode/os/os_task_CanOut.c \
../ImpCode/os/os_task_CoreApp.c \
../ImpCode/os/os_task_Debug.c \
../ImpCode/os/os_task_VcuCtrl.c \
../ImpCode/os/os_task_getComIn.c \
../ImpCode/os/os_task_getIn.c 

OBJS += \
./ImpCode/os/os_task.o \
./ImpCode/os/os_task_CanOut.o \
./ImpCode/os/os_task_CoreApp.o \
./ImpCode/os/os_task_Debug.o \
./ImpCode/os/os_task_VcuCtrl.o \
./ImpCode/os/os_task_getComIn.o \
./ImpCode/os/os_task_getIn.o 

C_DEPS += \
./ImpCode/os/os_task.d \
./ImpCode/os/os_task_CanOut.d \
./ImpCode/os/os_task_CoreApp.d \
./ImpCode/os/os_task_Debug.d \
./ImpCode/os/os_task_VcuCtrl.d \
./ImpCode/os/os_task_getComIn.d \
./ImpCode/os/os_task_getIn.d 


# Each subdirectory must supply rules for building sources it contributes
ImpCode/os/%.o: ../ImpCode/os/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@ImpCode/os/os_task.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


