#include "sleep.h"

volatile unsigned char *DDR_B = (unsigned char *)0x24;	  // direccion de DDR_B
volatile unsigned char *PUERTO_B = (unsigned char *)0x25; // direccion de PORT_B

int main()
{
	*(DDR_B) = 0b00000111; // setear direccion de datos

	while (1)
	{
		*(PUERTO_B) = 0b00000000; // Apaga los leds
		sleep_ms(1000);
		*(PUERTO_B) = 0b00000111; // Enciende los leds
		sleep_ms(1000);
	}
	return 0;
}
