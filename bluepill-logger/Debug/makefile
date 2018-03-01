################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include src/sd/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: bluepill-logger.elf

dependents:
	-cd C:/Users/rcc/Documents/stm32_sw4stmProject/bluepil-logger-poc/bluepill_stdperiph_lib/Debug && $(MAKE) all

# Tool invocations
bluepill-logger.elf: $(OBJS) $(USER_OBJS) C:/Users/rcc/Documents/stm32_sw4stmProject/bluepil-logger-poc/bluepill_stdperiph_lib/Debug/libbluepill_stdperiph_lib.a C:\Users\rcc\Documents\stm32_sw4stmProject\bluepil-logger-poc\bluepill-logger\LinkerScript.ld
	@echo 'Building target: $@'
	@echo 'Invoking: MCU GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -L"C:\Users\rcc\Documents\stm32_sw4stmProject\bluepil-logger-poc\bluepill_stdperiph_lib\Debug" -T"C:\Users\rcc\Documents\stm32_sw4stmProject\bluepil-logger-poc\bluepill-logger\LinkerScript.ld" -Wl,-Map=output.map -Wl,--gc-sections -o "bluepill-logger.elf" @"objects.list" $(USER_OBJS) $(LIBS) -lm
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	-@echo 'Generating binary and Printing size information:'
	arm-none-eabi-objcopy -O binary "bluepill-logger.elf" "bluepill-logger.bin"
	arm-none-eabi-size "bluepill-logger.elf"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build
C:/Users/rcc/Documents/stm32_sw4stmProject/bluepil-logger-poc/bluepill_stdperiph_lib/Debug/libbluepill_stdperiph_lib.a:

-include ../makefile.targets
