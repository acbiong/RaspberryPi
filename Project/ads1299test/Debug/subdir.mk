################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ads1299.c \
../ads1299test.c \
../bcm2835.c \
../boardconfig.c \
../socket2plot.c 

OBJS += \
./ads1299.o \
./ads1299test.o \
./bcm2835.o \
./boardconfig.o \
./socket2plot.o 

C_DEPS += \
./ads1299.d \
./ads1299test.d \
./bcm2835.d \
./boardconfig.d \
./socket2plot.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


