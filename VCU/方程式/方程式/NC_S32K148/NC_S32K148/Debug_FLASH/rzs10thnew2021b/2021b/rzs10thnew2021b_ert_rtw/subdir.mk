################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rzs10thnew2021b/2021b/rzs10thnew2021b_ert_rtw/rtGetInf.c \
../rzs10thnew2021b/2021b/rzs10thnew2021b_ert_rtw/rtGetNaN.c \
../rzs10thnew2021b/2021b/rzs10thnew2021b_ert_rtw/rt_nonfinite.c \
../rzs10thnew2021b/2021b/rzs10thnew2021b_ert_rtw/rtmodel.c \
../rzs10thnew2021b/2021b/rzs10thnew2021b_ert_rtw/rzs10thnew2021b.c \
../rzs10thnew2021b/2021b/rzs10thnew2021b_ert_rtw/rzs10thnew2021b_data.c 

OBJS += \
./rzs10thnew2021b/2021b/rzs10thnew2021b_ert_rtw/rtGetInf.o \
./rzs10thnew2021b/2021b/rzs10thnew2021b_ert_rtw/rtGetNaN.o \
./rzs10thnew2021b/2021b/rzs10thnew2021b_ert_rtw/rt_nonfinite.o \
./rzs10thnew2021b/2021b/rzs10thnew2021b_ert_rtw/rtmodel.o \
./rzs10thnew2021b/2021b/rzs10thnew2021b_ert_rtw/rzs10thnew2021b.o \
./rzs10thnew2021b/2021b/rzs10thnew2021b_ert_rtw/rzs10thnew2021b_data.o 

C_DEPS += \
./rzs10thnew2021b/2021b/rzs10thnew2021b_ert_rtw/rtGetInf.d \
./rzs10thnew2021b/2021b/rzs10thnew2021b_ert_rtw/rtGetNaN.d \
./rzs10thnew2021b/2021b/rzs10thnew2021b_ert_rtw/rt_nonfinite.d \
./rzs10thnew2021b/2021b/rzs10thnew2021b_ert_rtw/rtmodel.d \
./rzs10thnew2021b/2021b/rzs10thnew2021b_ert_rtw/rzs10thnew2021b.d \
./rzs10thnew2021b/2021b/rzs10thnew2021b_ert_rtw/rzs10thnew2021b_data.d 


# Each subdirectory must supply rules for building sources it contributes
rzs10thnew2021b/2021b/rzs10thnew2021b_ert_rtw/%.o: ../rzs10thnew2021b/2021b/rzs10thnew2021b_ert_rtw/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@rzs10thnew2021b/2021b/rzs10thnew2021b_ert_rtw/rtGetInf.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


