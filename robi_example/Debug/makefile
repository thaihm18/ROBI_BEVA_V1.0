################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include SDK_ROBI_STM32F0_1.0.0/shared/Utilities/subdir.mk
-include SDK_ROBI_STM32F0_1.0.0/shared/Middle/serial/subdir.mk
-include SDK_ROBI_STM32F0_1.0.0/shared/Middle/sensor/subdir.mk
-include SDK_ROBI_STM32F0_1.0.0/shared/Middle/rtos/subdir.mk
-include SDK_ROBI_STM32F0_1.0.0/shared/Middle/motor/subdir.mk
-include SDK_ROBI_STM32F0_1.0.0/shared/Middle/led/subdir.mk
-include SDK_ROBI_STM32F0_1.0.0/shared/Middle/lcd/subdir.mk
-include SDK_ROBI_STM32F0_1.0.0/shared/Middle/buzzer/subdir.mk
-include SDK_ROBI_STM32F0_1.0.0/shared/Middle/button/subdir.mk
-include SDK_ROBI_STM32F0_1.0.0/shared/Drivers/STM32F0xx_StdPeriph_Driver/src/subdir.mk
-include SDK_ROBI_STM32F0_1.0.0/shared/Drivers/CMSIS/Source/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := robi_exam
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
robi_exam.elf \

MAP_FILES += \
robi_exam.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
robi_exam.list \


# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: robi_exam.elf secondary-outputs

# Tool invocations
robi_exam.elf robi_exam.map: $(OBJS) $(USER_OBJS) D:\Lumi\ROBI_BEVA\ROBI_BEVA_STM32_18_09_2023\robi_example\STM32F030C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "robi_exam.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0 -T"D:\Lumi\ROBI_BEVA\ROBI_BEVA_STM32_18_09_2023\robi_example\STM32F030C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="robi_exam.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

robi_exam.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "robi_exam.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout robi_exam.elf robi_exam.list robi_exam.map
	-@echo ' '

post-build:
	arm-none-eabi-objcopy -O ihex robi_exam.elf robi_exam.hex
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified post-build

-include ../makefile.targets
