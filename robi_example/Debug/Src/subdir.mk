################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F030X8 -c -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Drivers/CMSIS/Include" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Drivers/CMSIS/Source" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Drivers/STM32F0xx_StdPeriph_Driver/inc" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Drivers/STM32F0xx_StdPeriph_Driver/src" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Middle/button" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Middle/buzzer" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Middle/lcd" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Middle/led" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Middle/motor" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Middle/rtos" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Middle/sensor" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Middle/serial" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Utilities" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

