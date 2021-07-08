################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/time.c \
../src/utilstools.c 

OBJS += \
./src/time.o \
./src/utilstools.o 

C_DEPS += \
./src/time.d \
./src/utilstools.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/vagrant/eclipse-workspace/github/utilstools/src" -I"/home/vagrant/git/utilstools/utilstoolslib/inc" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


