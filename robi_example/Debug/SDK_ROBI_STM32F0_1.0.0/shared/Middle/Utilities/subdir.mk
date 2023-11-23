################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Lumi/ROBI_BEVA/Library/IOT-Programming-with-ROBI-main/SDK_ROBI_STM32F0_1.0.0/shared/Middle/Utilities/buff.c \
D:/Lumi/ROBI_BEVA/Library/IOT-Programming-with-ROBI-main/SDK_ROBI_STM32F0_1.0.0/shared/Middle/Utilities/utilities.c 

OBJS += \
./SDK_ROBI_STM32F0_1.0.0/shared/Middle/Utilities/buff.o \
./SDK_ROBI_STM32F0_1.0.0/shared/Middle/Utilities/utilities.o 

C_DEPS += \
./SDK_ROBI_STM32F0_1.0.0/shared/Middle/Utilities/buff.d \
./SDK_ROBI_STM32F0_1.0.0/shared/Middle/Utilities/utilities.d 


# Each subdirectory must supply rules for building sources it contributes
SDK_ROBI_STM32F0_1.0.0/shared/Middle/Utilities/buff.o: D:/Lumi/ROBI_BEVA/Library/IOT-Programming-with-ROBI-main/SDK_ROBI_STM32F0_1.0.0/shared/Middle/Utilities/buff.c SDK_ROBI_STM32F0_1.0.0/shared/Middle/Utilities/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F0 -DSTM32F030X8 -DSTM32F030C8Tx -c -I"D:/Lumi/ROBI_BEVA/Library/IOT-Programming-with-ROBI-main/SDK_ROBI_STM32F0_1.0.0/shared/Drivers/CMSIS/Include" -I"D:/Lumi/ROBI_BEVA/Library/IOT-Programming-with-ROBI-main/SDK_ROBI_STM32F0_1.0.0/shared/Drivers/STM32F401RE_StdPeriph_Driver/inc" -I"D:/Lumi/ROBI_BEVA/Library/IOT-Programming-with-ROBI-main/SDK_ROBI_STM32F0_1.0.0/shared/Middle/button" -I"D:/Lumi/ROBI_BEVA/Library/IOT-Programming-with-ROBI-main/SDK_ROBI_STM32F0_1.0.0/shared/Middle/rtos" -I"D:/Lumi/ROBI_BEVA/Library/IOT-Programming-with-ROBI-main/SDK_ROBI_STM32F0_1.0.0/shared/Middle/serial" -I"D:/Lumi/ROBI_BEVA/Library/IOT-Programming-with-ROBI-main/SDK_ROBI_STM32F0_1.0.0/shared/Middle/buzzer" -I"D:/Lumi/ROBI_BEVA/Library/IOT-Programming-with-ROBI-main/SDK_ROBI_STM32F0_1.0.0/shared/Middle/led" -I"D:/Lumi/ROBI_BEVA/Library/IOT-Programming-with-ROBI-main/SDK_ROBI_STM32F0_1.0.0/shared/Middle/sensor" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
SDK_ROBI_STM32F0_1.0.0/shared/Middle/Utilities/utilities.o: D:/Lumi/ROBI_BEVA/Library/IOT-Programming-with-ROBI-main/SDK_ROBI_STM32F0_1.0.0/shared/Middle/Utilities/utilities.c SDK_ROBI_STM32F0_1.0.0/shared/Middle/Utilities/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F0 -DSTM32F030X8 -DSTM32F030C8Tx -c -I"D:/Lumi/ROBI_BEVA/Library/IOT-Programming-with-ROBI-main/SDK_ROBI_STM32F0_1.0.0/shared/Drivers/CMSIS/Include" -I"D:/Lumi/ROBI_BEVA/Library/IOT-Programming-with-ROBI-main/SDK_ROBI_STM32F0_1.0.0/shared/Drivers/STM32F401RE_StdPeriph_Driver/inc" -I"D:/Lumi/ROBI_BEVA/Library/IOT-Programming-with-ROBI-main/SDK_ROBI_STM32F0_1.0.0/shared/Middle/button" -I"D:/Lumi/ROBI_BEVA/Library/IOT-Programming-with-ROBI-main/SDK_ROBI_STM32F0_1.0.0/shared/Middle/rtos" -I"D:/Lumi/ROBI_BEVA/Library/IOT-Programming-with-ROBI-main/SDK_ROBI_STM32F0_1.0.0/shared/Middle/serial" -I"D:/Lumi/ROBI_BEVA/Library/IOT-Programming-with-ROBI-main/SDK_ROBI_STM32F0_1.0.0/shared/Middle/buzzer" -I"D:/Lumi/ROBI_BEVA/Library/IOT-Programming-with-ROBI-main/SDK_ROBI_STM32F0_1.0.0/shared/Middle/led" -I"D:/Lumi/ROBI_BEVA/Library/IOT-Programming-with-ROBI-main/SDK_ROBI_STM32F0_1.0.0/shared/Middle/sensor" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-SDK_ROBI_STM32F0_1-2e-0-2e-0-2f-shared-2f-Middle-2f-Utilities

clean-SDK_ROBI_STM32F0_1-2e-0-2e-0-2f-shared-2f-Middle-2f-Utilities:
	-$(RM) ./SDK_ROBI_STM32F0_1.0.0/shared/Middle/Utilities/buff.d ./SDK_ROBI_STM32F0_1.0.0/shared/Middle/Utilities/buff.o ./SDK_ROBI_STM32F0_1.0.0/shared/Middle/Utilities/buff.su ./SDK_ROBI_STM32F0_1.0.0/shared/Middle/Utilities/utilities.d ./SDK_ROBI_STM32F0_1.0.0/shared/Middle/Utilities/utilities.o ./SDK_ROBI_STM32F0_1.0.0/shared/Middle/Utilities/utilities.su

.PHONY: clean-SDK_ROBI_STM32F0_1-2e-0-2e-0-2f-shared-2f-Middle-2f-Utilities

