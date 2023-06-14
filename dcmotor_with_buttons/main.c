#include <avr/interrupt.h>
#include "timer1.h"
#include "sleep.h"
#include "serial.h"

volatile unsigned char *PIN_B = (unsigned char *)0x23;	  // direccion de PIN_B
volatile unsigned char *DDR_B = (unsigned char *)0x24;	  // direccion de DDR_B
volatile unsigned char *PUERTO_B = (unsigned char *)0x25; // direccion de PORT_B

#define RUN 1

int main(void)
{
	int speed = 0;
	char input, left_btn, right_btn;
	/* configurar entrada/salida de datos */
	(*DDR_B) |= 0b00000100;
	/* configurar bits de pull ups para los pulsadores */
	(*PUERTO_B) |= 0b00011000;

	timer1_init();
	serial_init();
	while (RUN)
	{
		input = ((*PIN_B) & 0b00011000) >> 3;
		sleep_ms(5);
		switch (input)
		{
		case 1:
			if (speed < 100)
			{
				speed += 10;
				timer1_pwm_move_to(speed);
			}
			break;
		case 2:
			if (speed > 0)
			{
				speed -= 10;
				timer1_pwm_move_to(speed);
			}
			break;
		default:
			break;
		}
		sleep_ms(90);
	}

	timer1_pwm_max();
	for (;;)
	{
		;
	}
	return 0;
}
