################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lib/Src/font/font12.c \
../Lib/Src/font/font16.c \
../Lib/Src/font/font20.c \
../Lib/Src/font/font24.c \
../Lib/Src/font/font8.c \
../Lib/Src/font/st7789_font.c 

OBJS += \
./Lib/Src/font/font12.o \
./Lib/Src/font/font16.o \
./Lib/Src/font/font20.o \
./Lib/Src/font/font24.o \
./Lib/Src/font/font8.o \
./Lib/Src/font/st7789_font.o 

C_DEPS += \
./Lib/Src/font/font12.d \
./Lib/Src/font/font16.d \
./Lib/Src/font/font20.d \
./Lib/Src/font/font24.d \
./Lib/Src/font/font8.d \
./Lib/Src/font/st7789_font.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/Src/font/%.o Lib/Src/font/%.su Lib/Src/font/%.cyclo: ../Lib/Src/font/%.c Lib/Src/font/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32G473VETx -DSTM32 -DSTM32G4 -c -I"C:/Embedded/STM32G473VET6/STM32G473VET6_4/Inc" -I"C:/Embedded/STM32G473VET6/STM32G473VET6_4/Lib/Inc" -I"C:/Embedded/STM32G473VET6/STM32G473VET6_4/Drivers/CMSIS/Device/ST/STM32G4xx/Include" -I"C:/Embedded/STM32G473VET6/STM32G473VET6_4/Drivers/CMSIS/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Lib-2f-Src-2f-font

clean-Lib-2f-Src-2f-font:
	-$(RM) ./Lib/Src/font/font12.cyclo ./Lib/Src/font/font12.d ./Lib/Src/font/font12.o ./Lib/Src/font/font12.su ./Lib/Src/font/font16.cyclo ./Lib/Src/font/font16.d ./Lib/Src/font/font16.o ./Lib/Src/font/font16.su ./Lib/Src/font/font20.cyclo ./Lib/Src/font/font20.d ./Lib/Src/font/font20.o ./Lib/Src/font/font20.su ./Lib/Src/font/font24.cyclo ./Lib/Src/font/font24.d ./Lib/Src/font/font24.o ./Lib/Src/font/font24.su ./Lib/Src/font/font8.cyclo ./Lib/Src/font/font8.d ./Lib/Src/font/font8.o ./Lib/Src/font/font8.su ./Lib/Src/font/st7789_font.cyclo ./Lib/Src/font/st7789_font.d ./Lib/Src/font/st7789_font.o ./Lib/Src/font/st7789_font.su

.PHONY: clean-Lib-2f-Src-2f-font

