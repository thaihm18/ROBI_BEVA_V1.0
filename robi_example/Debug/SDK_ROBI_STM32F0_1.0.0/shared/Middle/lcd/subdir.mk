################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Middle/lcd/GUI.c \
D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Middle/lcd/lcd.c 

OBJS += \
./SDK_ROBI_STM32F0_1.0.0/shared/Middle/lcd/GUI.o \
./SDK_ROBI_STM32F0_1.0.0/shared/Middle/lcd/lcd.o 

C_DEPS += \
./SDK_ROBI_STM32F0_1.0.0/shared/Middle/lcd/GUI.d \
./SDK_ROBI_STM32F0_1.0.0/shared/Middle/lcd/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
SDK_ROBI_STM32F0_1.0.0/shared/Middle/lcd/GUI.o: D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Middle/lcd/GUI.c SDK_ROBI_STM32F0_1.0.0/shared/Middle/lcd/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F030X8 -c -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Drivers/CMSIS/Include" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Drivers/CMSIS/Source" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Drivers/STM32F0xx_StdPeriph_Driver/inc" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Drivers/STM32F0xx_StdPeriph_Driver/src" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Middle/button" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Middle/buzzer" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Middle/lcd" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Middle/led" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Middle/motor" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Middle/rtos" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Middle/sensor" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Middle/serial" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Utilities" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
SDK_ROBI_STM32F0_1.0.0/shared/Middle/lcd/lcd.o: D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Middle/lcd/lcd.c SDK_ROBI_STM32F0_1.0.0/shared/Middle/lcd/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F030X8 -c -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Drivers/CMSIS/Include" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Drivers/CMSIS/Source" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Drivers/STM32F0xx_StdPeriph_Driver/inc" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Drivers/STM32F0xx_StdPeriph_Driver/src" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Middle/button" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Middle/buzzer" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Middle/lcd" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Middle/led" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Middle/motor" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Middle/rtos" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Middle/sensor" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Middle/serial" -I"D:/Lumi/ROBI_BEVA/ROBI_BEVA_STM32_18_09_2023/SDK_ROBI_STM32F0_1.0.0/shared/Utilities" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-SDK_ROBI_STM32F0_1-2e-0-2e-0-2f-shared-2f-Middle-2f-lcd

clean-SDK_ROBI_STM32F0_1-2e-0-2e-0-2f-shared-2f-Middle-2f-lcd:
	-$(RM) ./SDK_ROBI_STM32F0_1.0.0/shared/Middle/lcd/GUI.d ./SDK_ROBI_STM32F0_1.0.0/shared/Middle/lcd/GUI.o ./SDK_ROBI_STM32F0_1.0.0/shared/Middle/lcd/GUI.su ./SDK_ROBI_STM32F0_1.0.0/shared/Middle/lcd/lcd.d ./SDK_ROBI_STM32F0_1.0.0/shared/Middle/lcd/lcd.o ./SDK_ROBI_STM32F0_1.0.0/shared/Middle/lcd/lcd.su

.PHONY: clean-SDK_ROBI_STM32F0_1-2e-0-2e-0-2f-shared-2f-Middle-2f-lcd

