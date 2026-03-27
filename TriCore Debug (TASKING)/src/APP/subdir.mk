################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../src/APP/LQ_CCU6_Timer.c" \
"../src/APP/LQ_GPIO_KEY.c" \
"../src/APP/LQ_GPIO_LED.c" \
"../src/APP/LQ_OLED096.c" \
"../src/APP/LQ_TFT18.c" \
"../src/APP/LQ_TFT2.c" \
"../src/APP/LQ_TFTPicFont.c" 

COMPILED_SRCS += \
"src/APP/LQ_CCU6_Timer.src" \
"src/APP/LQ_GPIO_KEY.src" \
"src/APP/LQ_GPIO_LED.src" \
"src/APP/LQ_OLED096.src" \
"src/APP/LQ_TFT18.src" \
"src/APP/LQ_TFT2.src" \
"src/APP/LQ_TFTPicFont.src" 

C_DEPS += \
"./src/APP/LQ_CCU6_Timer.d" \
"./src/APP/LQ_GPIO_KEY.d" \
"./src/APP/LQ_GPIO_LED.d" \
"./src/APP/LQ_OLED096.d" \
"./src/APP/LQ_TFT18.d" \
"./src/APP/LQ_TFT2.d" \
"./src/APP/LQ_TFTPicFont.d" 

OBJS += \
"src/APP/LQ_CCU6_Timer.o" \
"src/APP/LQ_GPIO_KEY.o" \
"src/APP/LQ_GPIO_LED.o" \
"src/APP/LQ_OLED096.o" \
"src/APP/LQ_TFT18.o" \
"src/APP/LQ_TFT2.o" \
"src/APP/LQ_TFTPicFont.o" 


# Each subdirectory must supply rules for building sources it contributes
"src/APP/LQ_CCU6_Timer.src":"../src/APP/LQ_CCU6_Timer.c" "src/APP/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc26xb "-fD:/Code/Infineon/TC264/SmartCar/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"src/APP/LQ_CCU6_Timer.o":"src/APP/LQ_CCU6_Timer.src" "src/APP/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"src/APP/LQ_GPIO_KEY.src":"../src/APP/LQ_GPIO_KEY.c" "src/APP/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc26xb "-fD:/Code/Infineon/TC264/SmartCar/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"src/APP/LQ_GPIO_KEY.o":"src/APP/LQ_GPIO_KEY.src" "src/APP/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"src/APP/LQ_GPIO_LED.src":"../src/APP/LQ_GPIO_LED.c" "src/APP/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc26xb "-fD:/Code/Infineon/TC264/SmartCar/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"src/APP/LQ_GPIO_LED.o":"src/APP/LQ_GPIO_LED.src" "src/APP/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"src/APP/LQ_OLED096.src":"../src/APP/LQ_OLED096.c" "src/APP/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc26xb "-fD:/Code/Infineon/TC264/SmartCar/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"src/APP/LQ_OLED096.o":"src/APP/LQ_OLED096.src" "src/APP/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"src/APP/LQ_TFT18.src":"../src/APP/LQ_TFT18.c" "src/APP/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc26xb "-fD:/Code/Infineon/TC264/SmartCar/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"src/APP/LQ_TFT18.o":"src/APP/LQ_TFT18.src" "src/APP/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"src/APP/LQ_TFT2.src":"../src/APP/LQ_TFT2.c" "src/APP/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc26xb "-fD:/Code/Infineon/TC264/SmartCar/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"src/APP/LQ_TFT2.o":"src/APP/LQ_TFT2.src" "src/APP/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"src/APP/LQ_TFTPicFont.src":"../src/APP/LQ_TFTPicFont.c" "src/APP/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2012 -D__CPU__=tc26xb "-fD:/Code/Infineon/TC264/SmartCar/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
"src/APP/LQ_TFTPicFont.o":"src/APP/LQ_TFTPicFont.src" "src/APP/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-src-2f-APP

clean-src-2f-APP:
	-$(RM) ./src/APP/LQ_CCU6_Timer.d ./src/APP/LQ_CCU6_Timer.o ./src/APP/LQ_CCU6_Timer.src ./src/APP/LQ_GPIO_KEY.d ./src/APP/LQ_GPIO_KEY.o ./src/APP/LQ_GPIO_KEY.src ./src/APP/LQ_GPIO_LED.d ./src/APP/LQ_GPIO_LED.o ./src/APP/LQ_GPIO_LED.src ./src/APP/LQ_OLED096.d ./src/APP/LQ_OLED096.o ./src/APP/LQ_OLED096.src ./src/APP/LQ_TFT18.d ./src/APP/LQ_TFT18.o ./src/APP/LQ_TFT18.src ./src/APP/LQ_TFT2.d ./src/APP/LQ_TFT2.o ./src/APP/LQ_TFT2.src ./src/APP/LQ_TFTPicFont.d ./src/APP/LQ_TFTPicFont.o ./src/APP/LQ_TFTPicFont.src

.PHONY: clean-src-2f-APP

