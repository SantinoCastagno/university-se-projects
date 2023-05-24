#include <avr/interrupt.h>
#include "timer1.h"
#include "sleep.h"
#include "serial.h"

volatile unsigned char *PIN_B = (unsigned char *)0x23;	  // direccion de PIN_B
volatile unsigned char *DDR_B = (unsigned char *)0x24;	  // direccion de DDR_B
volatile unsigned char *PUERTO_B = (unsigned char *)0x25; // direccion de PORT_B

int main(void)
{
	int pos = 0;
	char input, left_btn, right_btn;
	/* configurar entrada/salida de datos */
	(*DDR_B) |= 0b00000010;
	/* configurar bits de pull ups para los pulsadores */
	(*PUERTO_B) |= 0b00001100;

	timer1_init();
	serial_init();
	while (1)
	{
		input = ((*PIN_B) & 0b00001100) >> 2;
		sleep_ms(5);
		switch (input)
		{
		case 1:
			if (pos < 180)
			{
				pos += 10;
			}
			break;
		case 2:
			if (pos > 0)
			{
				pos -= 10;
			}
			break;
		default:
			break;
		}
		timer1_pwm_move_to(pos);
		sleep_ms(20);
	}

	for (;;)
	{
		;
	}
	return 0;
}
