################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ds18b20.c \
../src/main.c \
../src/one_wire.c \
../src/syscalls.c \
../src/system_stm32f10x.c \
../src/utils.c 

OBJS += \
./src/ds18b20.o \
./src/main.o \
./src/one_wire.o \
./src/syscalls.o \
./src/system_stm32f10x.o \
./src/utils.o 

C_DEPS += \
./src/ds18b20.d \
./src/main.d \
./src/one_wire.d \
./src/syscalls.d \
./src/system_stm32f10x.d \
./src/utils.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32F1 -DSTM32F103C8Tx -DSTM32 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F10X_MD -I"C:/Users/rcc/Documents/stm32_sw4stmProject/bluepil-logger-poc/bluepill_stdperiph_lib" -I"C:/Users/rcc/Documents/stm32_sw4stmProject/bluepil-logger-poc/bluepill-logger/inc/sd" -I"C:/Users/rcc/Documents/stm32_sw4stmProject/bluepil-logger-poc/bluepill-logger/inc" -I"C:/Users/rcc/Documents/stm32_sw4stmProject/bluepil-logger-poc/bluepill_stdperiph_lib/StdPeriph_Driver/inc" -I"C:/Users/rcc/Documents/stm32_sw4stmProject/bluepil-logger-poc/bluepill_stdperiph_lib/CMSIS/core" -I"C:/Users/rcc/Documents/stm32_sw4stmProject/bluepil-logger-poc/bluepill_stdperiph_lib/CMSIS/device" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


