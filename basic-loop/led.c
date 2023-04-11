#include "sleep.h"

volatile unsigned char *DDR_B = (unsigned char *)0x24;	  // direccion de DDR_B
volatile unsigned char *PUERTO_B = (unsigned char *)0x25; // direccion de PORT_B

int main()
{
	*(DDR_B) = 0b00000011; // setear direccion de datos

	while (1)
	{
		*(PUERTO_B) = 0b00000000; // Apaga los leds
		sleep_10us();
		*(PUERTO_B) = 0b00000011; // Enciende los leds
		sleep_10us();
	}
	return 0;
}
