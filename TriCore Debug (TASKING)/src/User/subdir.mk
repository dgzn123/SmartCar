################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../src/User/Delay.c" \
"../src/User/Encoder.c" \
"../src/User/Flash.c" \
"../src/User/Gpio.c" \
"../src/User/Icar.c" \
"../src/User/Motor.c" \
"../src/User/Pid.c" \
"../src/User/Rgb.c" \
"../src/User/Servo.c" \
"../src/User/Soc.c" \
"../src/User/Usb.c" 

COMPILED_SRCS += \
"src/User/Delay.src" \
"src/User/Encoder.src" \
"src/User/Flash.src" \
"src/User/Gpio.src" \
"src/User/Icar.src" \
"src/User/Motor.src" \
"src/User/Pid.src" \
"src/User/Rgb.src" \
"src/User/Servo.src" \
"src/User/Soc.src" \
"src/User/Usb.src" 

C_DEPS += \
"./src/User/Delay.d" \
"./src/User/Encoder.d" \
"./src/User/Flash.d" \
"./src/User/Gpio.d" \
"./src/User/Icar.d" \
"./src/User/Motor.d" \
"./src/User/Pid.d" \
"./src/User/Rgb.d" \
"./src/User/Servo.d" \
"./src/User/Soc.d" \
"./src/User/Usb.d" 

OBJS += \
"src/User/Delay.o" \
"src/User/Encoder.o" \
"src/User/Flash.o" \
"src/User/Gpio.o" \
"src/User/Icar.o" \
"src/User/Motor.o" \
"src/User/Pid.o" \
"src/User/Rgb.o" \
"src/User/Servo.o" \
"src/User/Soc.o" \
"src/User/Usb.o" 


# Each subdirectory must supply rules for building sources it contributes
"src/User/Delay.src":"../src/User/Delay.c" "src/User/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc26xb "-fD:/Code/Infineon/TC264/SmartCar/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"src/User/Delay.o":"src/User/Delay.src" "src/User/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"src/User/Encoder.src":"../src/User/Encoder.c" "src/User/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc26xb "-fD:/Code/Infineon/TC264/SmartCar/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"src/User/Encoder.o":"src/User/Encoder.src" "src/User/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"src/User/Flash.src":"../src/User/Flash.c" "src/User/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc26xb "-fD:/Code/Infineon/TC264/SmartCar/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"src/User/Flash.o":"src/User/Flash.src" "src/User/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"src/User/Gpio.src":"../src/User/Gpio.c" "src/User/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc26xb "-fD:/Code/Infineon/TC264/SmartCar/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"src/User/Gpio.o":"src/User/Gpio.src" "src/User/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"src/User/Icar.src":"../src/User/Icar.c" "src/User/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc26xb "-fD:/Code/Infineon/TC264/SmartCar/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"src/User/Icar.o":"src/User/Icar.src" "src/User/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"src/User/Motor.src":"../src/User/Motor.c" "src/User/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc26xb "-fD:/Code/Infineon/TC264/SmartCar/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"src/User/Motor.o":"src/User/Motor.src" "src/User/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"src/User/Pid.src":"../src/User/Pid.c" "src/User/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc26xb "-fD:/Code/Infineon/TC264/SmartCar/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"src/User/Pid.o":"src/User/Pid.src" "src/User/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"src/User/Rgb.src":"../src/User/Rgb.c" "src/User/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc26xb "-fD:/Code/Infineon/TC264/SmartCar/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"src/User/Rgb.o":"src/User/Rgb.src" "src/User/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"src/User/Servo.src":"../src/User/Servo.c" "src/User/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc26xb "-fD:/Code/Infineon/TC264/SmartCar/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"src/User/Servo.o":"src/User/Servo.src" "src/User/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"src/User/Soc.src":"../src/User/Soc.c" "src/User/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc26xb "-fD:/Code/Infineon/TC264/SmartCar/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"src/User/Soc.o":"src/User/Soc.src" "src/User/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"src/User/Usb.src":"../src/User/Usb.c" "src/User/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc26xb "-fD:/Code/Infineon/TC264/SmartCar/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"src/User/Usb.o":"src/User/Usb.src" "src/User/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-src-2f-User

clean-src-2f-User:
	-$(RM) ./src/User/Delay.d ./src/User/Delay.o ./src/User/Delay.src ./src/User/Encoder.d ./src/User/Encoder.o ./src/User/Encoder.src ./src/User/Flash.d ./src/User/Flash.o ./src/User/Flash.src ./src/User/Gpio.d ./src/User/Gpio.o ./src/User/Gpio.src ./src/User/Icar.d ./src/User/Icar.o ./src/User/Icar.src ./src/User/Motor.d ./src/User/Motor.o ./src/User/Motor.src ./src/User/Pid.d ./src/User/Pid.o ./src/User/Pid.src ./src/User/Rgb.d ./src/User/Rgb.o ./src/User/Rgb.src ./src/User/Servo.d ./src/User/Servo.o ./src/User/Servo.src ./src/User/Soc.d ./src/User/Soc.o ./src/User/Soc.src ./src/User/Usb.d ./src/User/Usb.o ./src/User/Usb.src

.PHONY: clean-src-2f-User

