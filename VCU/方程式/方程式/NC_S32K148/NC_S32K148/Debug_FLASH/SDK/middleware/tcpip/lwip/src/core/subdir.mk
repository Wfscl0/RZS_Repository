################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SDK/middleware/tcpip/lwip/src/core/def.c \
../SDK/middleware/tcpip/lwip/src/core/dns.c \
../SDK/middleware/tcpip/lwip/src/core/inet_chksum.c \
../SDK/middleware/tcpip/lwip/src/core/init.c \
../SDK/middleware/tcpip/lwip/src/core/ip.c \
../SDK/middleware/tcpip/lwip/src/core/mem.c \
../SDK/middleware/tcpip/lwip/src/core/memp.c \
../SDK/middleware/tcpip/lwip/src/core/netif.c \
../SDK/middleware/tcpip/lwip/src/core/pbuf.c \
../SDK/middleware/tcpip/lwip/src/core/raw.c \
../SDK/middleware/tcpip/lwip/src/core/stats.c \
../SDK/middleware/tcpip/lwip/src/core/sys.c \
../SDK/middleware/tcpip/lwip/src/core/tcp.c \
../SDK/middleware/tcpip/lwip/src/core/tcp_in.c \
../SDK/middleware/tcpip/lwip/src/core/tcp_out.c \
../SDK/middleware/tcpip/lwip/src/core/timeouts.c \
../SDK/middleware/tcpip/lwip/src/core/udp.c 

OBJS += \
./SDK/middleware/tcpip/lwip/src/core/def.o \
./SDK/middleware/tcpip/lwip/src/core/dns.o \
./SDK/middleware/tcpip/lwip/src/core/inet_chksum.o \
./SDK/middleware/tcpip/lwip/src/core/init.o \
./SDK/middleware/tcpip/lwip/src/core/ip.o \
./SDK/middleware/tcpip/lwip/src/core/mem.o \
./SDK/middleware/tcpip/lwip/src/core/memp.o \
./SDK/middleware/tcpip/lwip/src/core/netif.o \
./SDK/middleware/tcpip/lwip/src/core/pbuf.o \
./SDK/middleware/tcpip/lwip/src/core/raw.o \
./SDK/middleware/tcpip/lwip/src/core/stats.o \
./SDK/middleware/tcpip/lwip/src/core/sys.o \
./SDK/middleware/tcpip/lwip/src/core/tcp.o \
./SDK/middleware/tcpip/lwip/src/core/tcp_in.o \
./SDK/middleware/tcpip/lwip/src/core/tcp_out.o \
./SDK/middleware/tcpip/lwip/src/core/timeouts.o \
./SDK/middleware/tcpip/lwip/src/core/udp.o 

C_DEPS += \
./SDK/middleware/tcpip/lwip/src/core/def.d \
./SDK/middleware/tcpip/lwip/src/core/dns.d \
./SDK/middleware/tcpip/lwip/src/core/inet_chksum.d \
./SDK/middleware/tcpip/lwip/src/core/init.d \
./SDK/middleware/tcpip/lwip/src/core/ip.d \
./SDK/middleware/tcpip/lwip/src/core/mem.d \
./SDK/middleware/tcpip/lwip/src/core/memp.d \
./SDK/middleware/tcpip/lwip/src/core/netif.d \
./SDK/middleware/tcpip/lwip/src/core/pbuf.d \
./SDK/middleware/tcpip/lwip/src/core/raw.d \
./SDK/middleware/tcpip/lwip/src/core/stats.d \
./SDK/middleware/tcpip/lwip/src/core/sys.d \
./SDK/middleware/tcpip/lwip/src/core/tcp.d \
./SDK/middleware/tcpip/lwip/src/core/tcp_in.d \
./SDK/middleware/tcpip/lwip/src/core/tcp_out.d \
./SDK/middleware/tcpip/lwip/src/core/timeouts.d \
./SDK/middleware/tcpip/lwip/src/core/udp.d 


# Each subdirectory must supply rules for building sources it contributes
SDK/middleware/tcpip/lwip/src/core/%.o: ../SDK/middleware/tcpip/lwip/src/core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/middleware/tcpip/lwip/src/core/def.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


