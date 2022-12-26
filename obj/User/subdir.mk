################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/ch32v30x_it.c \
../User/keys.c \
../User/leds.c \
../User/main.c \
../User/oled.c \
../User/rng.c \
../User/system_ch32v30x.c \
../User/usart_hmi.c 

OBJS += \
./User/ch32v30x_it.o \
./User/keys.o \
./User/leds.o \
./User/main.o \
./User/oled.o \
./User/rng.o \
./User/system_ch32v30x.o \
./User/usart_hmi.o 

C_DEPS += \
./User/ch32v30x_it.d \
./User/keys.d \
./User/leds.d \
./User/main.d \
./User/oled.d \
./User/rng.d \
./User/system_ch32v30x.d \
./User/usart_hmi.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\Users\die天下无敌\Desktop\EVT\EXAM\SRC\Debug" -I"D:\Users\die天下无敌\Desktop\EVT\EXAM\SRC\Core" -I"D:\Users\die天下无敌\Desktop\EVT\EXAM\GPIO\随机抽取及按键抢答\User" -I"D:\Users\die天下无敌\Desktop\EVT\EXAM\SRC\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

