# Name: Makefile
# Author: Scott Perry <dev@numist.net>
# Copyright: 2015
# License: MIT

# You should at least check the settings for
# DEVICE ....... The AVR device you compile for
# CLOCK ........ Target AVR clock rate in Hertz
# OBJECTS ...... The object files created from your source files. This list is
#                usually the same as the list of source files with suffix ".o".
# PROGRAMMER ... Options to avrdude which define the hardware you use for
#                uploading to the AVR and the interface where this hardware
#                is connected. We recommend that you leave it undefined and
#                add settings like this to your ~/.avrduderc file:
#                   default_programmer = "dragon_isp";
#                   default_serial = "usb";
# FUSES ........ Parameters for avrdude to flash the fuses appropriately.

# To override any of these for your local setup, create a file Makefile.local
# (ignored by git)
-include Makefile.local

# See avr-help for all possible devices
DEVICE     ?= attiny88

# 8Mhz
CLOCK      ?= 8000000

# Add something like this to Makefile.local if you haven't yet set up ~/.avrduderc with a default programmer.
# PROGRAMMER = -c usbtiny -P usb
# PROGRAMMER = -c dragon_isp -P usb

# Add more objects for each .c file here
OBJECTS    =  twi_slave.o

# For computing fuse byte values for other devices and options see
# the fuse bit calculator at http://www.engbedded.com/fusecalc/
FUSES      = -U lfuse:w:0xee:m -U hfuse:w:0xdd:m -U efuse:w:0xfe:m

AVRDUDE_PATH ?= avrdude
GCC_PATH ?= avr-gcc
# Tune the lines below only if you know what you are doing:

# Optimize for many things (including perf)
#OPTIMIZATION = -O2

# Optimize, but focus on keeping code size small
OPTIMIZATION = -Os



AVRDUDE = $(AVRDUDE_PATH) $(PROGRAMMER) -p $(DEVICE)
COMPILE = $(GCC_PATH) -Wall -Wextra -Werror -pedantic $(OPTIMIZATION) -std=gnu11 -flto -mmcu=$(DEVICE) -DF_CPU=$(CLOCK)  -Wl,--section-start=.text=0x1C00

# symbolic targets:
all:	twi_slave.hex

.c.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@
# "-x assembler-with-cpp" should not be necessary since this is the default
# file type for the .S (with capital S) extension. However, upper case
# characters are not always preserved on Windows. To ensure WinAVR
# compatibility define the file type manually.

.c.s:
	$(COMPILE) -S $< -o $@

flash:	all
	$(AVRDUDE) -B 2 -U flash:w:twi_slave.hex:i

fuse:
	$(AVRDUDE) -B 100 $(FUSES)

# Xcode uses the Makefile targets "", "clean" and "install"
install: flash fuse

# if you use a bootloader, change the command below appropriately:
load: all
	bootloadHID twi_slave.hex

clean:
	rm -f twi_slave.hex twi_slave.elf $(OBJECTS)

# file targets:
twi_slave.elf: $(OBJECTS)
	$(COMPILE) -o twi_slave.elf $(OBJECTS)

twi_slave.hex: twi_slave.elf
	rm -f twi_slave.hex
	avr-objcopy -j .text -j .data -O ihex twi_slave.elf twi_slave.hex
	avr-size --format=avr --mcu=$(DEVICE) twi_slave.elf
	# write bootloader jump vector to beginning
	sed -i'' -e '$$ d' twi_slave.hex # two dollar signs because Make otherwise interprets them
	# write a new vector table to jump to the bootloader
	# rjmp to 0x1C00, etc.
	echo ':02000000FFCD32' >> twi_slave.hex
	echo ':02000200FFCD30' >> twi_slave.hex
	echo ':02000400FFCD2E' >> twi_slave.hex
	echo ':02000600FFCD2C' >> twi_slave.hex
	echo ':02000800FFCD2A' >> twi_slave.hex
	echo ':02000A00FFCD28' >> twi_slave.hex
	echo ':02000C00FFCD26' >> twi_slave.hex
	echo ':02000E00FFCD24' >> twi_slave.hex
	echo ':02001000FFCD22' >> twi_slave.hex
	echo ':02001200FFCD20' >> twi_slave.hex
	echo ':02001400FFCD1E' >> twi_slave.hex
	echo ':02001600FFCD1C' >> twi_slave.hex
	echo ':02001800FFCD1A' >> twi_slave.hex
	echo ':02001A00FFCD18' >> twi_slave.hex
	echo ':02001C00FFCD16' >> twi_slave.hex
	echo ':02001E00FFCD14' >> twi_slave.hex
	echo ':02002000FFCD12' >> twi_slave.hex
	echo ':02002200FFCD10' >> twi_slave.hex
	echo ':02002400FFCD0E' >> twi_slave.hex
	echo ':02002600FFCD0C' >> twi_slave.hex
	echo ':02002800FFCD0A' >> twi_slave.hex
	echo ':00000001FF' >> twi_slave.hex
# If you have an EEPROM section, you must also create a hex file for the
# EEPROM and add it to the "flash" target.

# Targets for code debugging and analysis:
disasm:	twi_slave.elf
	avr-objdump -d twi_slave.elf

size-map: twi_slave.elf
	avr-nm --size-sort -C -r -l twi_slave.elf

cpp:
	$(COMPILE) -E main.c

astyle:
	find . -type f -name \*.c |xargs -n 1 astyle --style=google
	find . -type f -name \*.h |xargs -n 1 astyle --style=google
