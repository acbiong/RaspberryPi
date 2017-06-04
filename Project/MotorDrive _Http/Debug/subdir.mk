################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../serial.c 

CPP_SRCS += \
../SCSProtocol.cpp \
../SCServo.cpp \
../motortest.cpp 

OBJS += \
./SCSProtocol.o \
./SCServo.o \
./motortest.o \
./serial.o 

C_DEPS += \
./serial.d 

CPP_DEPS += \
./SCSProtocol.d \
./SCServo.d \
./motortest.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I"/home/brainco/RaspberryPi/Project/MotorDrive _Http/" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -I"/home/brainco/RaspberryPi/Project/MotorDrive _Http/" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


