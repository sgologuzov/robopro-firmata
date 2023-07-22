# Arduino CLI executable name
ARDUINO_CLI = arduino-cli.exe

# Library path
LIBRARIES_PATH = ./libraries

# Optional verbose compile/upload trigger
V ?= 0
VERBOSE=

# Build path -- used to store built binary and object files
BUILD_DIR=build
BUILD_PATH=./$@_$(BUILD_DIR)

ifneq ($(V), 0)
	VERBOSE=-v
endif

COMMON_COMPILE_ARG = $(VERBOSE) --libraries ${LIBRARIES_PATH} --output-dir=$(BUILD_PATH)

.PHONY: all clean

.Boards.patched.flag:
	git apply patch/Boards.patch
	echo true > .Boards.patched.flag

all: arduinoUno arduinoUnoUltra arduinoMega2560

arduinoUno:
	$(ARDUINO_CLI) compile $(COMMON_COMPILE_ARG) -b arduino:avr:uno ConfigurableFirmata.ino

arduinoUnoUltra: .Boards.patched.flag
	$(ARDUINO_CLI) compile $(COMMON_COMPILE_ARG) -b arduino:avr:uno --build-property build.extra_flags=-DARDUINO_UNO_ULTRA ConfigurableFirmata.ino 

arduinoMega2560:
	$(ARDUINO_CLI) compile $(COMMON_COMPILE_ARG) -b arduino:avr:mega:cpu=atmega2560 ConfigurableFirmata.ino

clean:
	@rm -rf *_$(BUILD_DIR)
