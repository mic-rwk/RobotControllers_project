################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/GUI_Paint.c \
../Core/Src/IL3895.c \
../Core/Src/barcodeImage.c \
../Core/Src/demo_2_13ich.c \
../Core/Src/gpio.c \
../Core/Src/logo250x48.c \
../Core/Src/logo250x48_H.c \
../Core/Src/logo375x72.c \
../Core/Src/main.c \
../Core/Src/number303.c \
../Core/Src/pwr_logo.c \
../Core/Src/spi.c \
../Core/Src/stm32l4xx_hal_msp.c \
../Core/Src/stm32l4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l4xx.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/GUI_Paint.o \
./Core/Src/IL3895.o \
./Core/Src/barcodeImage.o \
./Core/Src/demo_2_13ich.o \
./Core/Src/gpio.o \
./Core/Src/logo250x48.o \
./Core/Src/logo250x48_H.o \
./Core/Src/logo375x72.o \
./Core/Src/main.o \
./Core/Src/number303.o \
./Core/Src/pwr_logo.o \
./Core/Src/spi.o \
./Core/Src/stm32l4xx_hal_msp.o \
./Core/Src/stm32l4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l4xx.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/GUI_Paint.d \
./Core/Src/IL3895.d \
./Core/Src/barcodeImage.d \
./Core/Src/demo_2_13ich.d \
./Core/Src/gpio.d \
./Core/Src/logo250x48.d \
./Core/Src/logo250x48_H.d \
./Core/Src/logo375x72.d \
./Core/Src/main.d \
./Core/Src/number303.d \
./Core/Src/pwr_logo.d \
./Core/Src/spi.d \
./Core/Src/stm32l4xx_hal_msp.d \
./Core/Src/stm32l4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l4xx.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/GUI_Paint.cyclo ./Core/Src/GUI_Paint.d ./Core/Src/GUI_Paint.o ./Core/Src/GUI_Paint.su ./Core/Src/IL3895.cyclo ./Core/Src/IL3895.d ./Core/Src/IL3895.o ./Core/Src/IL3895.su ./Core/Src/barcodeImage.cyclo ./Core/Src/barcodeImage.d ./Core/Src/barcodeImage.o ./Core/Src/barcodeImage.su ./Core/Src/demo_2_13ich.cyclo ./Core/Src/demo_2_13ich.d ./Core/Src/demo_2_13ich.o ./Core/Src/demo_2_13ich.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/logo250x48.cyclo ./Core/Src/logo250x48.d ./Core/Src/logo250x48.o ./Core/Src/logo250x48.su ./Core/Src/logo250x48_H.cyclo ./Core/Src/logo250x48_H.d ./Core/Src/logo250x48_H.o ./Core/Src/logo250x48_H.su ./Core/Src/logo375x72.cyclo ./Core/Src/logo375x72.d ./Core/Src/logo375x72.o ./Core/Src/logo375x72.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/number303.cyclo ./Core/Src/number303.d ./Core/Src/number303.o ./Core/Src/number303.su ./Core/Src/pwr_logo.cyclo ./Core/Src/pwr_logo.d ./Core/Src/pwr_logo.o ./Core/Src/pwr_logo.su ./Core/Src/spi.cyclo ./Core/Src/spi.d ./Core/Src/spi.o ./Core/Src/spi.su ./Core/Src/stm32l4xx_hal_msp.cyclo ./Core/Src/stm32l4xx_hal_msp.d ./Core/Src/stm32l4xx_hal_msp.o ./Core/Src/stm32l4xx_hal_msp.su ./Core/Src/stm32l4xx_it.cyclo ./Core/Src/stm32l4xx_it.d ./Core/Src/stm32l4xx_it.o ./Core/Src/stm32l4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32l4xx.cyclo ./Core/Src/system_stm32l4xx.d ./Core/Src/system_stm32l4xx.o ./Core/Src/system_stm32l4xx.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su

.PHONY: clean-Core-2f-Src

