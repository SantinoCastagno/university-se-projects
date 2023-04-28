#include "sleep.h"

volatile unsigned char *PIN_B = (unsigned char *)0x23;	  // direccion de PIN_B
volatile unsigned char *DDR_B = (unsigned char *)0x24;	  // direccion de DDR_B
volatile unsigned char *PUERTO_B = (unsigned char *)0x25; // direccion de PORT_B

void leds_off()
{
	*(PUERTO_B) = *(PUERTO_B)&0b11100011;
}

int main(void)
{
	*(DDR_B) = 0b00011100;	  // setear direccion de datos
	*(PUERTO_B) = 0b00100000; // setear bit de pull-up
	unsigned char state = 0, time = 0, input;

	leds_off();
	while (1)
	{
		input = (*(PIN_B)) & 0b00100000;
		sleep_ms(50);
		// if (input != 0b00100000)
		// {
		// 	if (state == 0)
		// 		state = 1;
		// 	else
		// 		state = 0;
		// }
		state = 1;
		if (state == 1)
		{
			switch (time)
			{
			case 0:
				*(PUERTO_B) = *(PUERTO_B) | (0b001 << 2);
				time = 1;
				break;
			case 1:
				*(PUERTO_B) = *(PUERTO_B) & ~(0b110 << 2);
				time = 2;
				break;
			case 2:
				*(PUERTO_B) = *(PUERTO_B) | (0b010 << 2);
				time = 3;
				break;
			case 3:
				*(PUERTO_B) = *(PUERTO_B) & ~(0b101 << 2);
				time = 4;
				break;
			case 4:
				*(PUERTO_B) = *(PUERTO_B) | (0b100 << 2);
				time = 5;
				break;
			case 5:
				*(PUERTO_B) = *(PUERTO_B) & ~(0b011 << 2);
				time = 6;
				break;
			case 6:
				*(PUERTO_B) = *(PUERTO_B) | (0b010 << 2);
				time = 7;
				break;
			case 7:
				*(PUERTO_B) = *(PUERTO_B) & ~(0b101 << 2);
				time = 0;
				break;
			default:
				leds_off();
				break;
			}
		}
		else
		{
			leds_off();
		}
		sleep_ms_times(94, 3);
	}
	return 0;
}
