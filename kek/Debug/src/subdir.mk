################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/adc1.c \
../src/codec.c \
../src/encoder.c \
../src/leds.c \
../src/main.c \
../src/spi.c \
../src/syscalls.c \
../src/system_stm32f4xx.c \
../src/timer4.c 

OBJS += \
./src/adc1.o \
./src/codec.o \
./src/encoder.o \
./src/leds.o \
./src/main.o \
./src/spi.o \
./src/syscalls.o \
./src/system_stm32f4xx.o \
./src/timer4.o 

C_DEPS += \
./src/adc1.d \
./src/codec.d \
./src/encoder.d \
./src/leds.d \
./src/main.d \
./src/spi.d \
./src/syscalls.d \
./src/system_stm32f4xx.d \
./src/timer4.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F407VGTx -DDEBUG -D__FPU_USED '-D__FPU_USED=1' -DSTM32F40XX -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -DARM_MATH_CM4 -I"C:/Workspace_sheet/kek/StdPeriph_Driver/inc" -I"C:/Workspace_sheet/kek/inc" -I"C:/Workspace_sheet/kek/CMSIS/device" -I"C:/Workspace_sheet/kek/CMSIS/core" -I"C:/Workspace_sheet/kek/modules/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


