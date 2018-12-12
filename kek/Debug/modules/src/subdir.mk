################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../modules/src/ADSR.c \
../modules/src/ADSRwave.c \
../modules/src/DAC.c \
../modules/src/LFO.c \
../modules/src/LFOfld.c \
../modules/src/Osc.c \
../modules/src/button.c \
../modules/src/module_template.c \
../modules/src/wire.c 

OBJS += \
./modules/src/ADSR.o \
./modules/src/ADSRwave.o \
./modules/src/DAC.o \
./modules/src/LFO.o \
./modules/src/LFOfld.o \
./modules/src/Osc.o \
./modules/src/button.o \
./modules/src/module_template.o \
./modules/src/wire.o 

C_DEPS += \
./modules/src/ADSR.d \
./modules/src/ADSRwave.d \
./modules/src/DAC.d \
./modules/src/LFO.d \
./modules/src/LFOfld.d \
./modules/src/Osc.d \
./modules/src/button.d \
./modules/src/module_template.d \
./modules/src/wire.d 


# Each subdirectory must supply rules for building sources it contributes
modules/src/%.o: ../modules/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F407VGTx -DDEBUG -D__FPU_USED '-D__FPU_USED=1' -DSTM32F40XX -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -DARM_MATH_CM4 -I"C:/Synthesizer/kek/StdPeriph_Driver/inc" -I"C:/Synthesizer/kek/inc" -I"C:/Synthesizer/kek/CMSIS/device" -I"C:/Synthesizer/kek/CMSIS/core" -I"C:/Synthesizer/kek/modules/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


