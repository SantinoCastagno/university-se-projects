#include <avr/interrupt.h>

#include "timer1.h"
volatile unsigned char *DDR_B = (unsigned char *)0x24; // direccion de DDR_B

int main(void)
{
	(*DDR_B) |= 0b00000010; // setear direccion de datos
	timer1_init();
	while (1)
	{
		;
		;
	}

	for (;;)
	{
		;
	}
	return 0;
}
