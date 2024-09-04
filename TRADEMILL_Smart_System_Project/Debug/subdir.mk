################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DCMOTOR_program.c \
../DIO_program.c \
../EXTI_program.c \
../GIE_program.c \
../PIR_program.c \
../TIMER_program.c \
../main.c 

OBJS += \
./DCMOTOR_program.o \
./DIO_program.o \
./EXTI_program.o \
./GIE_program.o \
./PIR_program.o \
./TIMER_program.o \
./main.o 

C_DEPS += \
./DCMOTOR_program.d \
./DIO_program.d \
./EXTI_program.d \
./GIE_program.d \
./PIR_program.d \
./TIMER_program.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


