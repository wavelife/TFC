################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/gpio.c \
../src/led.c \
../src/log.c \
../src/printf.c \
../src/uart.c 

OBJS += \
./src/gpio.o \
./src/led.o \
./src/log.o \
./src/printf.o \
./src/uart.o 

C_DEPS += \
./src/gpio.d \
./src/led.d \
./src/log.d \
./src/printf.d \
./src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSISv2p00_LPC17xx -D__LPC17XX__ -I"/Users/wavelife/Documents/UOC/TFC/pfc/LPC1769_UOC_Library/inc" -I"/Users/wavelife/Documents/UOC/TFC/pfc/CMSISv2p00_LPC17xx/inc" -I"/Users/wavelife/Documents/UOC/TFC/pfc/FreeRTOS_Library/include" -I"/Users/wavelife/Documents/UOC/TFC/pfc/FreeRTOS_Library/portable" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


