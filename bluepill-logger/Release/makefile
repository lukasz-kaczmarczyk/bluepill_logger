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
	-cd /home/vadim/stm32/stm32eclipseworkspace/bluepill_stdperiph_lib/Release && $(MAKE) all

# Tool invocations
bluepill-logger.elf: $(OBJS) $(USER_OBJS) /home/vadim/stm32/stm32eclipseworkspace/bluepill_stdperiph_lib/Release/libbluepill_stdperiph_lib.a /home/vadim/stm32/stm32eclipseworkspace/bluepill-logger/LinkerScript.ld
	@echo 'Building target: $@'
	@echo 'Invoking: MCU GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -L"/home/vadim/stm32/stm32eclipseworkspace/bluepill_stdperiph_lib/Release" -T"/home/vadim/stm32/stm32eclipseworkspace/bluepill-logger/LinkerScript.ld" -Wl,-Map=output.map -Wl,--gc-sections -lm -o "bluepill-logger.elf" @"objects.list" $(USER_OBJS) $(LIBS)
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
	arm-none-eabi-size -B "bluepill-logger.elf"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build
/home/vadim/stm32/stm32eclipseworkspace/bluepill_stdperiph_lib/Release/libbluepill_stdperiph_lib.a:

-include ../makefile.targets
