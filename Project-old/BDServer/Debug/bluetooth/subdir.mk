################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/brainco/Engineering/workspace/raspberrypi/Library/bluetooth/bluetooth.c \
/home/brainco/Engineering/workspace/raspberrypi/Library/bluetooth/hci.c \
/home/brainco/Engineering/workspace/raspberrypi/Library/bluetooth/pi_bluetooth.c \
/home/brainco/Engineering/workspace/raspberrypi/Library/bluetooth/sdp.c \
/home/brainco/Engineering/workspace/raspberrypi/Library/bluetooth/uuid.c 

OBJS += \
./bluetooth/bluetooth.o \
./bluetooth/hci.o \
./bluetooth/pi_bluetooth.o \
./bluetooth/sdp.o \
./bluetooth/uuid.o 

C_DEPS += \
./bluetooth/bluetooth.d \
./bluetooth/hci.d \
./bluetooth/pi_bluetooth.d \
./bluetooth/sdp.d \
./bluetooth/uuid.d 


# Each subdirectory must supply rules for building sources it contributes
bluetooth/bluetooth.o: /home/brainco/Engineering/workspace/raspberrypi/Library/bluetooth/bluetooth.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/brainco/Engineering/workspace/raspberrypi/Project/BDServer/" -I"/home/brainco/Engineering/workspace/raspberrypi/Project/BDServer/../../Library" -I"/home/brainco/Engineering/workspace/raspberrypi/Project/BDServer/../../Library/bluetooth" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

bluetooth/hci.o: /home/brainco/Engineering/workspace/raspberrypi/Library/bluetooth/hci.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/brainco/Engineering/workspace/raspberrypi/Project/BDServer/" -I"/home/brainco/Engineering/workspace/raspberrypi/Project/BDServer/../../Library" -I"/home/brainco/Engineering/workspace/raspberrypi/Project/BDServer/../../Library/bluetooth" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

bluetooth/pi_bluetooth.o: /home/brainco/Engineering/workspace/raspberrypi/Library/bluetooth/pi_bluetooth.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/brainco/Engineering/workspace/raspberrypi/Project/BDServer/" -I"/home/brainco/Engineering/workspace/raspberrypi/Project/BDServer/../../Library" -I"/home/brainco/Engineering/workspace/raspberrypi/Project/BDServer/../../Library/bluetooth" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

bluetooth/sdp.o: /home/brainco/Engineering/workspace/raspberrypi/Library/bluetooth/sdp.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/brainco/Engineering/workspace/raspberrypi/Project/BDServer/" -I"/home/brainco/Engineering/workspace/raspberrypi/Project/BDServer/../../Library" -I"/home/brainco/Engineering/workspace/raspberrypi/Project/BDServer/../../Library/bluetooth" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

bluetooth/uuid.o: /home/brainco/Engineering/workspace/raspberrypi/Library/bluetooth/uuid.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/brainco/Engineering/workspace/raspberrypi/Project/BDServer/" -I"/home/brainco/Engineering/workspace/raspberrypi/Project/BDServer/../../Library" -I"/home/brainco/Engineering/workspace/raspberrypi/Project/BDServer/../../Library/bluetooth" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


