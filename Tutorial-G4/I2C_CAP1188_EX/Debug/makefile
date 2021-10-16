################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32G4xx_HAL_Driver/Src/subdir.mk
-include Drivers/BSP/STM32G4xx_Nucleo/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
I2C_CAP1188_EX.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
I2C_CAP1188_EX.list \

OBJCOPY_BIN += \
I2C_CAP1188_EX.bin \


# All Target
all: I2C_CAP1188_EX.elf secondary-outputs

# Tool invocations
I2C_CAP1188_EX.elf: $(OBJS) $(USER_OBJS) C:\Users\ksb22\STM32CubeIDE\UTAT_Finch\I2C_CAP1188_EX\STM32G474RETX_FLASH.ld
	arm-none-eabi-gcc -o "I2C_CAP1188_EX.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\ksb22\STM32CubeIDE\UTAT_Finch\I2C_CAP1188_EX\STM32G474RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="I2C_CAP1188_EX.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

I2C_CAP1188_EX.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "I2C_CAP1188_EX.list"
	@echo 'Finished building: $@'
	@echo ' '

I2C_CAP1188_EX.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "I2C_CAP1188_EX.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
