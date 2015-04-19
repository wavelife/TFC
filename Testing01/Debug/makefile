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
all: Testing01.axf

# Tool invocations
Testing01.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/Users/wavelife/Documents/UOC/TFC/pfc/CMSISv2p00_LPC17xx/Debug" -L"/Users/wavelife/Documents/UOC/TFC/pfc/LPC1769_UOC_Library/Debug" -L"/Users/wavelife/Documents/UOC/TFC/pfc/FreeRTOS_Library/Debug" -Xlinker --gc-sections -Xlinker -Map=Testing01.map -mcpu=cortex-m3 -mthumb -T "Example01_0_Debug.ld" -o "Testing01.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) Testing01.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size Testing01.axf; # arm-none-eabi-objcopy -O ihex Testing01.axf Testing01.hex ;
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
