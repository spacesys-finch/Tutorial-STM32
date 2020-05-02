################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/ksb22/STM32Cube/Repository/STM32Cube_FW_G4_V1.2.0/Drivers/BSP/STM32G4xx_Nucleo/stm32g4xx_nucleo.c 

OBJS += \
./STM32G4xx_Nucleo/stm32g4xx_nucleo.o 

C_DEPS += \
./STM32G4xx_Nucleo/stm32g4xx_nucleo.d 


# Each subdirectory must supply rules for building sources it contributes
STM32G4xx_Nucleo/stm32g4xx_nucleo.o: C:/Users/ksb22/STM32Cube/Repository/STM32Cube_FW_G4_V1.2.0/Drivers/BSP/STM32G4xx_Nucleo/stm32g4xx_nucleo.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32G474xx -DDEBUG -c -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I"C:/Users/ksb22/STM32Cube/Repository/STM32Cube_FW_G4_V1.2.0/Drivers/BSP/STM32G4xx_Nucleo" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"STM32G4xx_Nucleo/stm32g4xx_nucleo.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

