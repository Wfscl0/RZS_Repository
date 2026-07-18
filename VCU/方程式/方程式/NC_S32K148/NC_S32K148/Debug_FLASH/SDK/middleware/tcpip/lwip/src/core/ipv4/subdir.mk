################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SDK/middleware/tcpip/lwip/src/core/ipv4/autoip.c \
../SDK/middleware/tcpip/lwip/src/core/ipv4/dhcp.c \
../SDK/middleware/tcpip/lwip/src/core/ipv4/etharp.c \
../SDK/middleware/tcpip/lwip/src/core/ipv4/icmp.c \
../SDK/middleware/tcpip/lwip/src/core/ipv4/igmp.c \
../SDK/middleware/tcpip/lwip/src/core/ipv4/ip4.c \
../SDK/middleware/tcpip/lwip/src/core/ipv4/ip4_addr.c \
../SDK/middleware/tcpip/lwip/src/core/ipv4/ip4_frag.c 

OBJS += \
./SDK/middleware/tcpip/lwip/src/core/ipv4/autoip.o \
./SDK/middleware/tcpip/lwip/src/core/ipv4/dhcp.o \
./SDK/middleware/tcpip/lwip/src/core/ipv4/etharp.o \
./SDK/middleware/tcpip/lwip/src/core/ipv4/icmp.o \
./SDK/middleware/tcpip/lwip/src/core/ipv4/igmp.o \
./SDK/middleware/tcpip/lwip/src/core/ipv4/ip4.o \
./SDK/middleware/tcpip/lwip/src/core/ipv4/ip4_addr.o \
./SDK/middleware/tcpip/lwip/src/core/ipv4/ip4_frag.o 

C_DEPS += \
./SDK/middleware/tcpip/lwip/src/core/ipv4/autoip.d \
./SDK/middleware/tcpip/lwip/src/core/ipv4/dhcp.d \
./SDK/middleware/tcpip/lwip/src/core/ipv4/etharp.d \
./SDK/middleware/tcpip/lwip/src/core/ipv4/icmp.d \
./SDK/middleware/tcpip/lwip/src/core/ipv4/igmp.d \
./SDK/middleware/tcpip/lwip/src/core/ipv4/ip4.d \
./SDK/middleware/tcpip/lwip/src/core/ipv4/ip4_addr.d \
./SDK/middleware/tcpip/lwip/src/core/ipv4/ip4_frag.d 


# Each subdirectory must supply rules for building sources it contributes
SDK/middleware/tcpip/lwip/src/core/ipv4/%.o: ../SDK/middleware/tcpip/lwip/src/core/ipv4/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/middleware/tcpip/lwip/src/core/ipv4/autoip.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


