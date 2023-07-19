TTY=/dev/ttyACM0
#TTY=/dev/ttyUSB0

all:
	avr-gcc -c -o sleep.o sleep.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o main.o main.c
	avr-gcc -mmcu=atmega328p main.o -o main.elf sleep.o
	avr-objcopy -O ihex -R .eeprom main.elf main.hex

flash:
	sudo avrdude -v -v -v -v -p atmega328p -c arduino -P $(TTY) -b 115200 -D -U flash:w:main.hex:i
	
clean:
	rm main.elf led.hex main.o sleep.o