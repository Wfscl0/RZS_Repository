################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SDK/middleware/tcpip/lwip/src/core/ipv6/dhcp6.c \
../SDK/middleware/tcpip/lwip/src/core/ipv6/ethip6.c \
../SDK/middleware/tcpip/lwip/src/core/ipv6/icmp6.c \
../SDK/middleware/tcpip/lwip/src/core/ipv6/inet6.c \
../SDK/middleware/tcpip/lwip/src/core/ipv6/ip6.c \
../SDK/middleware/tcpip/lwip/src/core/ipv6/ip6_addr.c \
../SDK/middleware/tcpip/lwip/src/core/ipv6/ip6_frag.c \
../SDK/middleware/tcpip/lwip/src/core/ipv6/mld6.c \
../SDK/middleware/tcpip/lwip/src/core/ipv6/nd6.c 

OBJS += \
./SDK/middleware/tcpip/lwip/src/core/ipv6/dhcp6.o \
./SDK/middleware/tcpip/lwip/src/core/ipv6/ethip6.o \
./SDK/middleware/tcpip/lwip/src/core/ipv6/icmp6.o \
./SDK/middleware/tcpip/lwip/src/core/ipv6/inet6.o \
./SDK/middleware/tcpip/lwip/src/core/ipv6/ip6.o \
./SDK/middleware/tcpip/lwip/src/core/ipv6/ip6_addr.o \
./SDK/middleware/tcpip/lwip/src/core/ipv6/ip6_frag.o \
./SDK/middleware/tcpip/lwip/src/core/ipv6/mld6.o \
./SDK/middleware/tcpip/lwip/src/core/ipv6/nd6.o 

C_DEPS += \
./SDK/middleware/tcpip/lwip/src/core/ipv6/dhcp6.d \
./SDK/middleware/tcpip/lwip/src/core/ipv6/ethip6.d \
./SDK/middleware/tcpip/lwip/src/core/ipv6/icmp6.d \
./SDK/middleware/tcpip/lwip/src/core/ipv6/inet6.d \
./SDK/middleware/tcpip/lwip/src/core/ipv6/ip6.d \
./SDK/middleware/tcpip/lwip/src/core/ipv6/ip6_addr.d \
./SDK/middleware/tcpip/lwip/src/core/ipv6/ip6_frag.d \
./SDK/middleware/tcpip/lwip/src/core/ipv6/mld6.d \
./SDK/middleware/tcpip/lwip/src/core/ipv6/nd6.d 


# Each subdirectory must supply rules for building sources it contributes
SDK/middleware/tcpip/lwip/src/core/ipv6/%.o: ../SDK/middleware/tcpip/lwip/src/core/ipv6/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/middleware/tcpip/lwip/src/core/ipv6/dhcp6.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


