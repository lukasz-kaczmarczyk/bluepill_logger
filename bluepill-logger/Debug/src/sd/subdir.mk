################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/sd/ccsbcs.c \
../src/sd/diskio.c \
../src/sd/ff.c \
../src/sd/ffsystem.c 

OBJS += \
./src/sd/ccsbcs.o \
./src/sd/diskio.o \
./src/sd/ff.o \
./src/sd/ffsystem.o 

C_DEPS += \
./src/sd/ccsbcs.d \
./src/sd/diskio.d \
./src/sd/ff.d \
./src/sd/ffsystem.d 


# Each subdirectory must supply rules for building sources it contributes
src/sd/%.o: ../src/sd/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32F1 -DSTM32F103C8Tx -DSTM32 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F10X_MD -I"C:/Users/rcc/Documents/stm32_sw4stmProject/bluepil-logger-poc/bluepill_stdperiph_lib" -I"C:/Users/rcc/Documents/stm32_sw4stmProject/bluepil-logger-poc/bluepill-logger/inc/sd" -I"C:/Users/rcc/Documents/stm32_sw4stmProject/bluepil-logger-poc/bluepill-logger/inc" -I"C:/Users/rcc/Documents/stm32_sw4stmProject/bluepil-logger-poc/bluepill_stdperiph_lib/StdPeriph_Driver/inc" -I"C:/Users/rcc/Documents/stm32_sw4stmProject/bluepil-logger-poc/bluepill_stdperiph_lib/CMSIS/core" -I"C:/Users/rcc/Documents/stm32_sw4stmProject/bluepil-logger-poc/bluepill_stdperiph_lib/CMSIS/device" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


