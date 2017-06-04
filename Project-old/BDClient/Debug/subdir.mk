################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rfcomm-client.c 

OBJS += \
./rfcomm-client.o 

C_DEPS += \
./rfcomm-client.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -I"/home/brainco/Engineering/workspace/raspberrypi/Project/BDClient/" -I"/home/brainco/Engineering/workspace/raspberrypi/Project/BDClient/../../Library" -I"/home/brainco/Engineering/workspace/raspberrypi/Project/BDClient/../../Library/bluetooth" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


