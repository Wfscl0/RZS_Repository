################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SDK/middleware/tcpip/lwip/src/netif/ppp/polarssl/arc4.c \
../SDK/middleware/tcpip/lwip/src/netif/ppp/polarssl/des.c \
../SDK/middleware/tcpip/lwip/src/netif/ppp/polarssl/md4.c \
../SDK/middleware/tcpip/lwip/src/netif/ppp/polarssl/md5.c \
../SDK/middleware/tcpip/lwip/src/netif/ppp/polarssl/sha1.c 

OBJS += \
./SDK/middleware/tcpip/lwip/src/netif/ppp/polarssl/arc4.o \
./SDK/middleware/tcpip/lwip/src/netif/ppp/polarssl/des.o \
./SDK/middleware/tcpip/lwip/src/netif/ppp/polarssl/md4.o \
./SDK/middleware/tcpip/lwip/src/netif/ppp/polarssl/md5.o \
./SDK/middleware/tcpip/lwip/src/netif/ppp/polarssl/sha1.o 

C_DEPS += \
./SDK/middleware/tcpip/lwip/src/netif/ppp/polarssl/arc4.d \
./SDK/middleware/tcpip/lwip/src/netif/ppp/polarssl/des.d \
./SDK/middleware/tcpip/lwip/src/netif/ppp/polarssl/md4.d \
./SDK/middleware/tcpip/lwip/src/netif/ppp/polarssl/md5.d \
./SDK/middleware/tcpip/lwip/src/netif/ppp/polarssl/sha1.d 


# Each subdirectory must supply rules for building sources it contributes
SDK/middleware/tcpip/lwip/src/netif/ppp/polarssl/%.o: ../SDK/middleware/tcpip/lwip/src/netif/ppp/polarssl/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/middleware/tcpip/lwip/src/netif/ppp/polarssl/arc4.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


