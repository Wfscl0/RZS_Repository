################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SDK/middleware/tcpip/lwip/src/api/api_lib.c \
../SDK/middleware/tcpip/lwip/src/api/api_msg.c \
../SDK/middleware/tcpip/lwip/src/api/err.c \
../SDK/middleware/tcpip/lwip/src/api/netbuf.c \
../SDK/middleware/tcpip/lwip/src/api/netdb.c \
../SDK/middleware/tcpip/lwip/src/api/netifapi.c \
../SDK/middleware/tcpip/lwip/src/api/sockets.c \
../SDK/middleware/tcpip/lwip/src/api/tcpip.c 

OBJS += \
./SDK/middleware/tcpip/lwip/src/api/api_lib.o \
./SDK/middleware/tcpip/lwip/src/api/api_msg.o \
./SDK/middleware/tcpip/lwip/src/api/err.o \
./SDK/middleware/tcpip/lwip/src/api/netbuf.o \
./SDK/middleware/tcpip/lwip/src/api/netdb.o \
./SDK/middleware/tcpip/lwip/src/api/netifapi.o \
./SDK/middleware/tcpip/lwip/src/api/sockets.o \
./SDK/middleware/tcpip/lwip/src/api/tcpip.o 

C_DEPS += \
./SDK/middleware/tcpip/lwip/src/api/api_lib.d \
./SDK/middleware/tcpip/lwip/src/api/api_msg.d \
./SDK/middleware/tcpip/lwip/src/api/err.d \
./SDK/middleware/tcpip/lwip/src/api/netbuf.d \
./SDK/middleware/tcpip/lwip/src/api/netdb.d \
./SDK/middleware/tcpip/lwip/src/api/netifapi.d \
./SDK/middleware/tcpip/lwip/src/api/sockets.d \
./SDK/middleware/tcpip/lwip/src/api/tcpip.d 


# Each subdirectory must supply rules for building sources it contributes
SDK/middleware/tcpip/lwip/src/api/%.o: ../SDK/middleware/tcpip/lwip/src/api/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/middleware/tcpip/lwip/src/api/api_lib.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


