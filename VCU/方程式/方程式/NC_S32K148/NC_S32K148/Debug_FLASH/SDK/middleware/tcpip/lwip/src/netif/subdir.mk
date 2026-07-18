################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SDK/middleware/tcpip/lwip/src/netif/ethernet.c \
../SDK/middleware/tcpip/lwip/src/netif/ethernetif.c \
../SDK/middleware/tcpip/lwip/src/netif/lowpan6.c \
../SDK/middleware/tcpip/lwip/src/netif/slipif.c 

OBJS += \
./SDK/middleware/tcpip/lwip/src/netif/ethernet.o \
./SDK/middleware/tcpip/lwip/src/netif/ethernetif.o \
./SDK/middleware/tcpip/lwip/src/netif/lowpan6.o \
./SDK/middleware/tcpip/lwip/src/netif/slipif.o 

C_DEPS += \
./SDK/middleware/tcpip/lwip/src/netif/ethernet.d \
./SDK/middleware/tcpip/lwip/src/netif/ethernetif.d \
./SDK/middleware/tcpip/lwip/src/netif/lowpan6.d \
./SDK/middleware/tcpip/lwip/src/netif/slipif.d 


# Each subdirectory must supply rules for building sources it contributes
SDK/middleware/tcpip/lwip/src/netif/%.o: ../SDK/middleware/tcpip/lwip/src/netif/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/middleware/tcpip/lwip/src/netif/ethernet.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


