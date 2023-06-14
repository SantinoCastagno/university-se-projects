#include <avr/interrupt.h>
#include "timer1.h"
#include "sleep.h"
#include "serial.h"

volatile unsigned char *PIN_B = (unsigned char *)0x23;	  // direccion de PIN_B
volatile unsigned char *DDR_B = (unsigned char *)0x24;	  // direccion de DDR_B
volatile unsigned char *PUERTO_B = (unsigned char *)0x25; // direccion de PORT_B

#define RUN 0
#define DBG 1

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
	while (RUN)
	{
		input = ((*PIN_B) & 0b00001100) >> 2;
		sleep_ms(5);
		switch (input)
		{
		case 1:
			if (pos < 260)
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
	while (DBG)
	{
		timer1_pwm_move_to(200);
		sleep_ms_times(50, 50);
		timer1_pwm_max();
		sleep_ms_times(50, 50);
		timer1_pwm_min();
		sleep_ms_times(50, 50);
		// sleep_ms_times(50, 50);
		// timer1_pwm_move_to(0);
		// sleep_ms_times(50, 50);
		// timer1_pwm_move_to(180);
		// sleep_ms_times(50, 50);
		// timer1_pwm_move_to(200);
		// sleep_ms_times(50, 50);
		// timer1_pwm_move_to(180);
		// sleep_ms_times(50, 50);
		// timer1_pwm_move_to(180);
	}

	for (;;)
	{
		;
	}
	return 0;
}
