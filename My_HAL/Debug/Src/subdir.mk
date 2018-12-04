################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCP23017.c \
../Src/MCP_button.c \
../Src/MCP_encoder.c \
../Src/button.c \
../Src/dig_LED.c \
../Src/dma.c \
../Src/encoder.c \
../Src/gpio.c \
../Src/i2c.c \
../Src/lcd.c \
../Src/main.c \
../Src/reg.c \
../Src/sequencer.c \
../Src/spi.c \
../Src/stm32f1xx_hal_msp.c \
../Src/stm32f1xx_it.c \
../Src/system_stm32f1xx.c \
../Src/tim.c \
../Src/usart.c 

OBJS += \
./Src/MCP23017.o \
./Src/MCP_button.o \
./Src/MCP_encoder.o \
./Src/button.o \
./Src/dig_LED.o \
./Src/dma.o \
./Src/encoder.o \
./Src/gpio.o \
./Src/i2c.o \
./Src/lcd.o \
./Src/main.o \
./Src/reg.o \
./Src/sequencer.o \
./Src/spi.o \
./Src/stm32f1xx_hal_msp.o \
./Src/stm32f1xx_it.o \
./Src/system_stm32f1xx.o \
./Src/tim.o \
./Src/usart.o 

C_DEPS += \
./Src/MCP23017.d \
./Src/MCP_button.d \
./Src/MCP_encoder.d \
./Src/button.d \
./Src/dig_LED.d \
./Src/dma.d \
./Src/encoder.d \
./Src/gpio.d \
./Src/i2c.d \
./Src/lcd.d \
./Src/main.d \
./Src/reg.d \
./Src/sequencer.d \
./Src/spi.d \
./Src/stm32f1xx_hal_msp.d \
./Src/stm32f1xx_it.d \
./Src/system_stm32f1xx.d \
./Src/tim.d \
./Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"D:/Projects/Synthesizer/My_HAL/Inc" -I"D:/Projects/Synthesizer/My_HAL/Drivers/STM32F1xx_HAL_Driver/Inc" -I"D:/Projects/Synthesizer/My_HAL/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"D:/Projects/Synthesizer/My_HAL/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"D:/Projects/Synthesizer/My_HAL/Drivers/CMSIS/Include" -I../MT_WH1602  -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


