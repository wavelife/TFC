################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cr_startup_lpc17.c \
../log.c \
../main.c \
../printf.c \
../uart.c 

OBJS += \
./cr_startup_lpc17.o \
./log.o \
./main.o \
./printf.o \
./uart.o 

C_DEPS += \
./cr_startup_lpc17.d \
./log.d \
./main.d \
./printf.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__REDLIB__ -I"/Users/wavelife/Documents/UOC/TFC/pfc/CMSISv2p00_LPC17xx/inc" -I"/Users/wavelife/Documents/UOC/TFC/pfc/FreeRTOS_Library/demo_code" -I"/Users/wavelife/Documents/UOC/TFC/pfc/FreeRTOS_Library/include" -I"/Users/wavelife/Documents/UOC/TFC/pfc/FreeRTOS_Library/portable" -I"/Users/wavelife/Documents/UOC/TFC/pfc/Example01/inc" -O1 -g3 -fsigned-char -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

printf.o: ../printf.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__REDLIB__ -I"/Users/wavelife/Documents/UOC/TFC/pfc/CMSISv2p00_LPC17xx/inc" -I"/Users/wavelife/Documents/UOC/TFC/pfc/FreeRTOS_Library/demo_code" -I"/Users/wavelife/Documents/UOC/TFC/pfc/FreeRTOS_Library/include" -I"/Users/wavelife/Documents/UOC/TFC/pfc/FreeRTOS_Library/portable" -I"/Users/wavelife/Documents/UOC/TFC/pfc/Example01/inc" -O0 -g3 -fsigned-char -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"printf.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


