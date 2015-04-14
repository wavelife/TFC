################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: SimpleDemo_usingLib.axf

# Tool invocations
SimpleDemo_usingLib.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/Users/wavelife/LPCXpresso/pfc/CMSISv2p00_LPC17xx/Debug" -L"/Users/wavelife/LPCXpresso/pfc/LPC1769_UOC_Library/Debug" -L"/Users/wavelife/LPCXpresso/pfc/FreeRTOS_Library/Debug" -Xlinker --gc-sections -Xlinker -Map=SimpleDemo_usingLib.map -mcpu=cortex-m3 -mthumb -T "SimpleDemo_Debug.ld" -o "SimpleDemo_usingLib.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) SimpleDemo_usingLib.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size SimpleDemo_usingLib.axf; # arm-none-eabi-objcopy -O ihex SimpleDemo_usingLib.axf SimpleDemo_usingLib.hex ;
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
