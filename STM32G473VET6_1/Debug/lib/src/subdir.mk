################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/src/74hc595.c \
../lib/src/BT_Commands.c \
../lib/src/armfunction.c \
../lib/src/armsystick.c \
../lib/src/buffer.c \
../lib/src/explode.c \
../lib/src/st7789.c \
../lib/src/st7789_fonts.c \
../lib/src/stm32g473vet6.c \
../lib/src/stm32gxxx_tim1.c \
../lib/src/stm32gxxxrcc.c \
../lib/src/stm32gxxxrtc.c \
../lib/src/stm32gxxxusart1.c \
../lib/src/stm32xtool.c \
../lib/src/timer_irq.c \
../lib/src/znpid.c 

OBJS += \
./lib/src/74hc595.o \
./lib/src/BT_Commands.o \
./lib/src/armfunction.o \
./lib/src/armsystick.o \
./lib/src/buffer.o \
./lib/src/explode.o \
./lib/src/st7789.o \
./lib/src/st7789_fonts.o \
./lib/src/stm32g473vet6.o \
./lib/src/stm32gxxx_tim1.o \
./lib/src/stm32gxxxrcc.o \
./lib/src/stm32gxxxrtc.o \
./lib/src/stm32gxxxusart1.o \
./lib/src/stm32xtool.o \
./lib/src/timer_irq.o \
./lib/src/znpid.o 

C_DEPS += \
./lib/src/74hc595.d \
./lib/src/BT_Commands.d \
./lib/src/armfunction.d \
./lib/src/armsystick.d \
./lib/src/buffer.d \
./lib/src/explode.d \
./lib/src/st7789.d \
./lib/src/st7789_fonts.d \
./lib/src/stm32g473vet6.d \
./lib/src/stm32gxxx_tim1.d \
./lib/src/stm32gxxxrcc.d \
./lib/src/stm32gxxxrtc.d \
./lib/src/stm32gxxxusart1.d \
./lib/src/stm32xtool.d \
./lib/src/timer_irq.d \
./lib/src/znpid.d 


# Each subdirectory must supply rules for building sources it contributes
lib/src/%.o lib/src/%.su lib/src/%.cyclo: ../lib/src/%.c lib/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32G473VETx -DSTM32 -DSTM32G4 -c -I"D:/Embedded/STM32G473VET6/STM32G473VET6_1/Inc" -I"D:/Embedded/STM32G473VET6/STM32G473VET6_1/Drivers/STM32G4xx_HAL_Driver/Inc" -I"D:/Embedded/STM32G473VET6/STM32G473VET6_1/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy" -I"D:/Embedded/STM32G473VET6/STM32G473VET6_1/Drivers/CMSIS/Device/ST/STM32G4xx/Include" -I"D:/Embedded/STM32G473VET6/STM32G473VET6_1/Drivers/CMSIS/Include" -I"D:/Embedded/STM32G473VET6/STM32G473VET6_1/lib/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lib-2f-src

clean-lib-2f-src:
	-$(RM) ./lib/src/74hc595.cyclo ./lib/src/74hc595.d ./lib/src/74hc595.o ./lib/src/74hc595.su ./lib/src/BT_Commands.cyclo ./lib/src/BT_Commands.d ./lib/src/BT_Commands.o ./lib/src/BT_Commands.su ./lib/src/armfunction.cyclo ./lib/src/armfunction.d ./lib/src/armfunction.o ./lib/src/armfunction.su ./lib/src/armsystick.cyclo ./lib/src/armsystick.d ./lib/src/armsystick.o ./lib/src/armsystick.su ./lib/src/buffer.cyclo ./lib/src/buffer.d ./lib/src/buffer.o ./lib/src/buffer.su ./lib/src/explode.cyclo ./lib/src/explode.d ./lib/src/explode.o ./lib/src/explode.su ./lib/src/st7789.cyclo ./lib/src/st7789.d ./lib/src/st7789.o ./lib/src/st7789.su ./lib/src/st7789_fonts.cyclo ./lib/src/st7789_fonts.d ./lib/src/st7789_fonts.o ./lib/src/st7789_fonts.su ./lib/src/stm32g473vet6.cyclo ./lib/src/stm32g473vet6.d ./lib/src/stm32g473vet6.o ./lib/src/stm32g473vet6.su ./lib/src/stm32gxxx_tim1.cyclo ./lib/src/stm32gxxx_tim1.d ./lib/src/stm32gxxx_tim1.o ./lib/src/stm32gxxx_tim1.su ./lib/src/stm32gxxxrcc.cyclo ./lib/src/stm32gxxxrcc.d ./lib/src/stm32gxxxrcc.o ./lib/src/stm32gxxxrcc.su ./lib/src/stm32gxxxrtc.cyclo ./lib/src/stm32gxxxrtc.d ./lib/src/stm32gxxxrtc.o ./lib/src/stm32gxxxrtc.su ./lib/src/stm32gxxxusart1.cyclo ./lib/src/stm32gxxxusart1.d ./lib/src/stm32gxxxusart1.o ./lib/src/stm32gxxxusart1.su ./lib/src/stm32xtool.cyclo ./lib/src/stm32xtool.d ./lib/src/stm32xtool.o ./lib/src/stm32xtool.su ./lib/src/timer_irq.cyclo ./lib/src/timer_irq.d ./lib/src/timer_irq.o ./lib/src/timer_irq.su ./lib/src/znpid.cyclo ./lib/src/znpid.d ./lib/src/znpid.o ./lib/src/znpid.su

.PHONY: clean-lib-2f-src

