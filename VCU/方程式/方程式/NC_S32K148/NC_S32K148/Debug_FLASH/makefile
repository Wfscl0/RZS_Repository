################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include rzs10thnew2021b/2021b/rzs10thnew2021b_ert_rtw/subdir.mk
-include Sources/subdir.mk
-include SDK/rtos/osif/subdir.mk
-include SDK/rtos/FreeRTOS_S32K/Source/portable/MemMang/subdir.mk
-include SDK/rtos/FreeRTOS_S32K/Source/portable/GCC/ARM_CM4F/subdir.mk
-include SDK/rtos/FreeRTOS_S32K/Source/subdir.mk
-include SDK/platform/pal/src/uart/subdir.mk
-include SDK/platform/pal/src/spi/subdir.mk
-include SDK/platform/pal/src/pwm/subdir.mk
-include SDK/platform/pal/src/i2c/subdir.mk
-include SDK/platform/pal/src/can/subdir.mk
-include SDK/platform/pal/src/adc/subdir.mk
-include SDK/platform/drivers/src/trgmux/subdir.mk
-include SDK/platform/drivers/src/power/S32K1xx/subdir.mk
-include SDK/platform/drivers/src/power/subdir.mk
-include SDK/platform/drivers/src/pins/subdir.mk
-include SDK/platform/drivers/src/pdb/subdir.mk
-include SDK/platform/drivers/src/lpuart/subdir.mk
-include SDK/platform/drivers/src/lpspi/subdir.mk
-include SDK/platform/drivers/src/lpi2c/subdir.mk
-include SDK/platform/drivers/src/interrupt/subdir.mk
-include SDK/platform/drivers/src/ftm/subdir.mk
-include SDK/platform/drivers/src/flexio/subdir.mk
-include SDK/platform/drivers/src/flexcan/subdir.mk
-include SDK/platform/drivers/src/flash/subdir.mk
-include SDK/platform/drivers/src/enet/subdir.mk
-include SDK/platform/drivers/src/edma/subdir.mk
-include SDK/platform/drivers/src/clock/S32K1xx/subdir.mk
-include SDK/platform/drivers/src/adc/subdir.mk
-include SDK/platform/devices/S32K148/startup/subdir.mk
-include SDK/platform/devices/subdir.mk
-include SDK/middleware/tcpip/tcpip_stack/ports/platform/S32K148/subdir.mk
-include SDK/middleware/tcpip/tcpip_stack/ports/netif/enetif/subdir.mk
-include SDK/middleware/tcpip/tcpip_stack/ports/OS/subdir.mk
-include SDK/middleware/tcpip/tcpip_stack/demo/subdir.mk
-include SDK/middleware/tcpip/tcpip_stack/apps/udpecho_raw/subdir.mk
-include SDK/middleware/tcpip/tcpip_stack/apps/tcpecho/subdir.mk
-include SDK/middleware/tcpip/tcpip_stack/apps/snmp_private_mib/subdir.mk
-include SDK/middleware/tcpip/tcpip_stack/apps/smtp/subdir.mk
-include SDK/middleware/tcpip/tcpip_stack/apps/chargen/subdir.mk
-include SDK/middleware/tcpip/tcpip_stack/apps/ccov/subdir.mk
-include SDK/middleware/tcpip/tcpip_stack/addons/tcp_isn/subdir.mk
-include SDK/middleware/tcpip/lwip/src/netif/ppp/polarssl/subdir.mk
-include SDK/middleware/tcpip/lwip/src/netif/ppp/subdir.mk
-include SDK/middleware/tcpip/lwip/src/netif/subdir.mk
-include SDK/middleware/tcpip/lwip/src/core/ipv6/subdir.mk
-include SDK/middleware/tcpip/lwip/src/core/ipv4/subdir.mk
-include SDK/middleware/tcpip/lwip/src/core/subdir.mk
-include SDK/middleware/tcpip/lwip/src/apps/tftp/subdir.mk
-include SDK/middleware/tcpip/lwip/src/apps/snmp/subdir.mk
-include SDK/middleware/tcpip/lwip/src/apps/mqtt/subdir.mk
-include SDK/middleware/tcpip/lwip/src/apps/mdns/subdir.mk
-include SDK/middleware/tcpip/lwip/src/apps/lwiperf/subdir.mk
-include SDK/middleware/tcpip/lwip/src/api/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include ImpCode/os/subdir.mk
-include ImpCode/interface/subdir.mk
-include ImpCode/bsp/com/subdir.mk
-include ImpCode/bsp/base/subdir.mk
-include Generated_Code/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
NC_S32K148.hex \

SECONDARY_SIZE += \
NC_S32K148.siz \


# All Target
all: NC_S32K148.elf secondary-outputs

# Tool invocations
NC_S32K148.elf: $(OBJS) C:/Users/LENOVO/Desktop/NC_S32K148/NC_S32K148/Project_Settings/Linker_Files/S32K148_256_flash.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Standard S32DS C Linker'
	arm-none-eabi-gcc -o "NC_S32K148.elf" "@NC_S32K148.args"  $(USER_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

NC_S32K148.hex: NC_S32K148.elf
	@echo 'Invoking: Standard S32DS Create Flash Image'
	arm-none-eabi-objcopy -O ihex NC_S32K148.elf  "NC_S32K148.hex"
	@echo 'Finished building: $@'
	@echo ' '

NC_S32K148.siz: NC_S32K148.elf
	@echo 'Invoking: Standard S32DS Print Size'
	arm-none-eabi-size --format=berkeley NC_S32K148.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ./*
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
