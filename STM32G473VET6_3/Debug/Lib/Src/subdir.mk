################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lib/Src/74hc595.c \
../Lib/Src/BT_Command.c \
../Lib/Src/arm_systick.c \
../Lib/Src/buffer.c \
../Lib/Src/dma_irq.c \
../Lib/Src/explode.c \
../Lib/Src/function.c \
../Lib/Src/i2c_irq.c \
../Lib/Src/l293d.c \
../Lib/Src/rtc_irq.c \
../Lib/Src/spi_irq.c \
../Lib/Src/st7789.c \
../Lib/Src/stm32g4_dev.c \
../Lib/Src/stm32gxxx_adc1.c \
../Lib/Src/stm32gxxx_i2c1.c \
../Lib/Src/stm32gxxx_rcc.c \
../Lib/Src/stm32gxxx_rtc.c \
../Lib/Src/stm32gxxx_tim1.c \
../Lib/Src/stm32gxxx_usart1.c \
../Lib/Src/stm32x_cordic.c \
../Lib/Src/stm32x_gpio.c \
../Lib/Src/stm32x_irq.c \
../Lib/Src/stm32x_tool.c \
../Lib/Src/timer_irq.c \
../Lib/Src/usart_irq.c \
../Lib/Src/znpid.c 

OBJS += \
./Lib/Src/74hc595.o \
./Lib/Src/BT_Command.o \
./Lib/Src/arm_systick.o \
./Lib/Src/buffer.o \
./Lib/Src/dma_irq.o \
./Lib/Src/explode.o \
./Lib/Src/function.o \
./Lib/Src/i2c_irq.o \
./Lib/Src/l293d.o \
./Lib/Src/rtc_irq.o \
./Lib/Src/spi_irq.o \
./Lib/Src/st7789.o \
./Lib/Src/stm32g4_dev.o \
./Lib/Src/stm32gxxx_adc1.o \
./Lib/Src/stm32gxxx_i2c1.o \
./Lib/Src/stm32gxxx_rcc.o \
./Lib/Src/stm32gxxx_rtc.o \
./Lib/Src/stm32gxxx_tim1.o \
./Lib/Src/stm32gxxx_usart1.o \
./Lib/Src/stm32x_cordic.o \
./Lib/Src/stm32x_gpio.o \
./Lib/Src/stm32x_irq.o \
./Lib/Src/stm32x_tool.o \
./Lib/Src/timer_irq.o \
./Lib/Src/usart_irq.o \
./Lib/Src/znpid.o 

C_DEPS += \
./Lib/Src/74hc595.d \
./Lib/Src/BT_Command.d \
./Lib/Src/arm_systick.d \
./Lib/Src/buffer.d \
./Lib/Src/dma_irq.d \
./Lib/Src/explode.d \
./Lib/Src/function.d \
./Lib/Src/i2c_irq.d \
./Lib/Src/l293d.d \
./Lib/Src/rtc_irq.d \
./Lib/Src/spi_irq.d \
./Lib/Src/st7789.d \
./Lib/Src/stm32g4_dev.d \
./Lib/Src/stm32gxxx_adc1.d \
./Lib/Src/stm32gxxx_i2c1.d \
./Lib/Src/stm32gxxx_rcc.d \
./Lib/Src/stm32gxxx_rtc.d \
./Lib/Src/stm32gxxx_tim1.d \
./Lib/Src/stm32gxxx_usart1.d \
./Lib/Src/stm32x_cordic.d \
./Lib/Src/stm32x_gpio.d \
./Lib/Src/stm32x_irq.d \
./Lib/Src/stm32x_tool.d \
./Lib/Src/timer_irq.d \
./Lib/Src/usart_irq.d \
./Lib/Src/znpid.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/Src/%.o Lib/Src/%.su Lib/Src/%.cyclo: ../Lib/Src/%.c Lib/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32G473VETx -c -I"C:/Embedded/STM32G473VET6/STM32G473VET6_3/Drivers/CMSIS/Include" -I"C:/Embedded/STM32G473VET6/STM32G473VET6_3/Drivers/CMSIS/Device/ST/STM32G4xx/Include" -I"C:/Embedded/STM32G473VET6/STM32G473VET6_3/Lib/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Lib-2f-Src

clean-Lib-2f-Src:
	-$(RM) ./Lib/Src/74hc595.cyclo ./Lib/Src/74hc595.d ./Lib/Src/74hc595.o ./Lib/Src/74hc595.su ./Lib/Src/BT_Command.cyclo ./Lib/Src/BT_Command.d ./Lib/Src/BT_Command.o ./Lib/Src/BT_Command.su ./Lib/Src/arm_systick.cyclo ./Lib/Src/arm_systick.d ./Lib/Src/arm_systick.o ./Lib/Src/arm_systick.su ./Lib/Src/buffer.cyclo ./Lib/Src/buffer.d ./Lib/Src/buffer.o ./Lib/Src/buffer.su ./Lib/Src/dma_irq.cyclo ./Lib/Src/dma_irq.d ./Lib/Src/dma_irq.o ./Lib/Src/dma_irq.su ./Lib/Src/explode.cyclo ./Lib/Src/explode.d ./Lib/Src/explode.o ./Lib/Src/explode.su ./Lib/Src/function.cyclo ./Lib/Src/function.d ./Lib/Src/function.o ./Lib/Src/function.su ./Lib/Src/i2c_irq.cyclo ./Lib/Src/i2c_irq.d ./Lib/Src/i2c_irq.o ./Lib/Src/i2c_irq.su ./Lib/Src/l293d.cyclo ./Lib/Src/l293d.d ./Lib/Src/l293d.o ./Lib/Src/l293d.su ./Lib/Src/rtc_irq.cyclo ./Lib/Src/rtc_irq.d ./Lib/Src/rtc_irq.o ./Lib/Src/rtc_irq.su ./Lib/Src/spi_irq.cyclo ./Lib/Src/spi_irq.d ./Lib/Src/spi_irq.o ./Lib/Src/spi_irq.su ./Lib/Src/st7789.cyclo ./Lib/Src/st7789.d ./Lib/Src/st7789.o ./Lib/Src/st7789.su ./Lib/Src/stm32g4_dev.cyclo ./Lib/Src/stm32g4_dev.d ./Lib/Src/stm32g4_dev.o ./Lib/Src/stm32g4_dev.su ./Lib/Src/stm32gxxx_adc1.cyclo ./Lib/Src/stm32gxxx_adc1.d ./Lib/Src/stm32gxxx_adc1.o ./Lib/Src/stm32gxxx_adc1.su ./Lib/Src/stm32gxxx_i2c1.cyclo ./Lib/Src/stm32gxxx_i2c1.d ./Lib/Src/stm32gxxx_i2c1.o ./Lib/Src/stm32gxxx_i2c1.su ./Lib/Src/stm32gxxx_rcc.cyclo ./Lib/Src/stm32gxxx_rcc.d ./Lib/Src/stm32gxxx_rcc.o ./Lib/Src/stm32gxxx_rcc.su ./Lib/Src/stm32gxxx_rtc.cyclo ./Lib/Src/stm32gxxx_rtc.d ./Lib/Src/stm32gxxx_rtc.o ./Lib/Src/stm32gxxx_rtc.su ./Lib/Src/stm32gxxx_tim1.cyclo ./Lib/Src/stm32gxxx_tim1.d ./Lib/Src/stm32gxxx_tim1.o ./Lib/Src/stm32gxxx_tim1.su ./Lib/Src/stm32gxxx_usart1.cyclo ./Lib/Src/stm32gxxx_usart1.d ./Lib/Src/stm32gxxx_usart1.o ./Lib/Src/stm32gxxx_usart1.su ./Lib/Src/stm32x_cordic.cyclo ./Lib/Src/stm32x_cordic.d ./Lib/Src/stm32x_cordic.o ./Lib/Src/stm32x_cordic.su ./Lib/Src/stm32x_gpio.cyclo ./Lib/Src/stm32x_gpio.d ./Lib/Src/stm32x_gpio.o ./Lib/Src/stm32x_gpio.su ./Lib/Src/stm32x_irq.cyclo ./Lib/Src/stm32x_irq.d ./Lib/Src/stm32x_irq.o ./Lib/Src/stm32x_irq.su ./Lib/Src/stm32x_tool.cyclo ./Lib/Src/stm32x_tool.d ./Lib/Src/stm32x_tool.o ./Lib/Src/stm32x_tool.su ./Lib/Src/timer_irq.cyclo ./Lib/Src/timer_irq.d ./Lib/Src/timer_irq.o ./Lib/Src/timer_irq.su ./Lib/Src/usart_irq.cyclo ./Lib/Src/usart_irq.d ./Lib/Src/usart_irq.o ./Lib/Src/usart_irq.su ./Lib/Src/znpid.cyclo ./Lib/Src/znpid.d ./Lib/Src/znpid.o ./Lib/Src/znpid.su

.PHONY: clean-Lib-2f-Src

