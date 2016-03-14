#!/bin/bash
avr-gcc -mmcu=atmega8 -g -DF_CPU=8000000 -Wall -Os -Werror -Wextra -o input.o input.cpp
avr-objcopy -j .text -j .data -O ihex input.o input.flash.hex
avrdude -c usbasp -p m8 -v -U flash:w:input.flash.hex