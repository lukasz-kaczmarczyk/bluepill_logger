################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32.s 

OBJS += \
./startup/startup_stm32.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -I"/home/vadim/stm32/stm32eclipseworkspace/bluepill_stdperiph_lib" -I"/home/vadim/stm32/stm32eclipseworkspace/bluepill-logger/inc" -I"/home/vadim/stm32/stm32eclipseworkspace/bluepill_stdperiph_lib/StdPeriph_Driver/inc" -I"/home/vadim/stm32/stm32eclipseworkspace/bluepill_stdperiph_lib/CMSIS/core" -I"/home/vadim/stm32/stm32eclipseworkspace/bluepill_stdperiph_lib/CMSIS/device" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


