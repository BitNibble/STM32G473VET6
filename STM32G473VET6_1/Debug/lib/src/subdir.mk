################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/src/stm32g473vet6.c \
../lib/src/stm32gxxxrcc.c \
../lib/src/stm32xtool.c \
../lib/src/timer_irq.c 

OBJS += \
./lib/src/stm32g473vet6.o \
./lib/src/stm32gxxxrcc.o \
./lib/src/stm32xtool.o \
./lib/src/timer_irq.o 

C_DEPS += \
./lib/src/stm32g473vet6.d \
./lib/src/stm32gxxxrcc.d \
./lib/src/stm32xtool.d \
./lib/src/timer_irq.d 


# Each subdirectory must supply rules for building sources it contributes
lib/src/%.o lib/src/%.su lib/src/%.cyclo: ../lib/src/%.c lib/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32G473VETx -DSTM32 -DSTM32G4 -c -I"D:/Embedded/STM32G473VET6/STM32G473VET6_1/Inc" -I"D:/Embedded/STM32G473VET6/STM32G473VET6_1/Drivers/STM32G4xx_HAL_Driver/Inc" -I"D:/Embedded/STM32G473VET6/STM32G473VET6_1/Drivers/STM32G4xx_HAL_Driver/Inc/Legacy" -I"D:/Embedded/STM32G473VET6/STM32G473VET6_1/Drivers/CMSIS/Device/ST/STM32G4xx/Include" -I"D:/Embedded/STM32G473VET6/STM32G473VET6_1/Drivers/CMSIS/Include" -I"D:/Embedded/STM32G473VET6/STM32G473VET6_1/lib/src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lib-2f-src

clean-lib-2f-src:
	-$(RM) ./lib/src/stm32g473vet6.cyclo ./lib/src/stm32g473vet6.d ./lib/src/stm32g473vet6.o ./lib/src/stm32g473vet6.su ./lib/src/stm32gxxxrcc.cyclo ./lib/src/stm32gxxxrcc.d ./lib/src/stm32gxxxrcc.o ./lib/src/stm32gxxxrcc.su ./lib/src/stm32xtool.cyclo ./lib/src/stm32xtool.d ./lib/src/stm32xtool.o ./lib/src/stm32xtool.su ./lib/src/timer_irq.cyclo ./lib/src/timer_irq.d ./lib/src/timer_irq.o ./lib/src/timer_irq.su

.PHONY: clean-lib-2f-src

