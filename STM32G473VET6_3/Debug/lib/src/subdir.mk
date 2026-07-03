################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/src/74hc595.c \
../lib/src/BT_Command.c \
../lib/src/arm_systick.c \
../lib/src/buffer.c \
../lib/src/explode.c \
../lib/src/function.c \
../lib/src/st7789.c \
../lib/src/st7789_font.c \
../lib/src/stm32g473vet6.c \
../lib/src/stm32gxxx_adc1.c \
../lib/src/stm32gxxx_rcc.c \
../lib/src/stm32gxxx_rtc.c \
../lib/src/stm32gxxx_tim1.c \
../lib/src/stm32gxxx_usart1.c \
../lib/src/stm32xtool.c \
../lib/src/template_instance.c \
../lib/src/template_singleton.c \
../lib/src/timer_irq.c \
../lib/src/znpid.c 

OBJS += \
./lib/src/74hc595.o \
./lib/src/BT_Command.o \
./lib/src/arm_systick.o \
./lib/src/buffer.o \
./lib/src/explode.o \
./lib/src/function.o \
./lib/src/st7789.o \
./lib/src/st7789_font.o \
./lib/src/stm32g473vet6.o \
./lib/src/stm32gxxx_adc1.o \
./lib/src/stm32gxxx_rcc.o \
./lib/src/stm32gxxx_rtc.o \
./lib/src/stm32gxxx_tim1.o \
./lib/src/stm32gxxx_usart1.o \
./lib/src/stm32xtool.o \
./lib/src/template_instance.o \
./lib/src/template_singleton.o \
./lib/src/timer_irq.o \
./lib/src/znpid.o 

C_DEPS += \
./lib/src/74hc595.d \
./lib/src/BT_Command.d \
./lib/src/arm_systick.d \
./lib/src/buffer.d \
./lib/src/explode.d \
./lib/src/function.d \
./lib/src/st7789.d \
./lib/src/st7789_font.d \
./lib/src/stm32g473vet6.d \
./lib/src/stm32gxxx_adc1.d \
./lib/src/stm32gxxx_rcc.d \
./lib/src/stm32gxxx_rtc.d \
./lib/src/stm32gxxx_tim1.d \
./lib/src/stm32gxxx_usart1.d \
./lib/src/stm32xtool.d \
./lib/src/template_instance.d \
./lib/src/template_singleton.d \
./lib/src/timer_irq.d \
./lib/src/znpid.d 


# Each subdirectory must supply rules for building sources it contributes
lib/src/%.o lib/src/%.su lib/src/%.cyclo: ../lib/src/%.c lib/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32G473VETx -DSTM32 -DSTM32G4 -c -I"D:/Embedded/STM32G473VET6/STM32G473VET6_3/Inc" -I"D:/Embedded/STM32G473VET6/STM32G473VET6_3/lib/src" -I"D:/Embedded/STM32G473VET6/STM32G473VET6_3/Drivers/CMSIS/Device/ST/STM32G4xx/Include" -I"D:/Embedded/STM32G473VET6/STM32G473VET6_3/Drivers/CMSIS/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lib-2f-src

clean-lib-2f-src:
	-$(RM) ./lib/src/74hc595.cyclo ./lib/src/74hc595.d ./lib/src/74hc595.o ./lib/src/74hc595.su ./lib/src/BT_Command.cyclo ./lib/src/BT_Command.d ./lib/src/BT_Command.o ./lib/src/BT_Command.su ./lib/src/arm_systick.cyclo ./lib/src/arm_systick.d ./lib/src/arm_systick.o ./lib/src/arm_systick.su ./lib/src/buffer.cyclo ./lib/src/buffer.d ./lib/src/buffer.o ./lib/src/buffer.su ./lib/src/explode.cyclo ./lib/src/explode.d ./lib/src/explode.o ./lib/src/explode.su ./lib/src/function.cyclo ./lib/src/function.d ./lib/src/function.o ./lib/src/function.su ./lib/src/st7789.cyclo ./lib/src/st7789.d ./lib/src/st7789.o ./lib/src/st7789.su ./lib/src/st7789_font.cyclo ./lib/src/st7789_font.d ./lib/src/st7789_font.o ./lib/src/st7789_font.su ./lib/src/stm32g473vet6.cyclo ./lib/src/stm32g473vet6.d ./lib/src/stm32g473vet6.o ./lib/src/stm32g473vet6.su ./lib/src/stm32gxxx_adc1.cyclo ./lib/src/stm32gxxx_adc1.d ./lib/src/stm32gxxx_adc1.o ./lib/src/stm32gxxx_adc1.su ./lib/src/stm32gxxx_rcc.cyclo ./lib/src/stm32gxxx_rcc.d ./lib/src/stm32gxxx_rcc.o ./lib/src/stm32gxxx_rcc.su ./lib/src/stm32gxxx_rtc.cyclo ./lib/src/stm32gxxx_rtc.d ./lib/src/stm32gxxx_rtc.o ./lib/src/stm32gxxx_rtc.su ./lib/src/stm32gxxx_tim1.cyclo ./lib/src/stm32gxxx_tim1.d ./lib/src/stm32gxxx_tim1.o ./lib/src/stm32gxxx_tim1.su ./lib/src/stm32gxxx_usart1.cyclo ./lib/src/stm32gxxx_usart1.d ./lib/src/stm32gxxx_usart1.o ./lib/src/stm32gxxx_usart1.su ./lib/src/stm32xtool.cyclo ./lib/src/stm32xtool.d ./lib/src/stm32xtool.o ./lib/src/stm32xtool.su ./lib/src/template_instance.cyclo ./lib/src/template_instance.d ./lib/src/template_instance.o ./lib/src/template_instance.su ./lib/src/template_singleton.cyclo ./lib/src/template_singleton.d ./lib/src/template_singleton.o ./lib/src/template_singleton.su ./lib/src/timer_irq.cyclo ./lib/src/timer_irq.d ./lib/src/timer_irq.o ./lib/src/timer_irq.su ./lib/src/znpid.cyclo ./lib/src/znpid.d ./lib/src/znpid.o ./lib/src/znpid.su

.PHONY: clean-lib-2f-src

