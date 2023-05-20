#include <avr/interrupt.h>
#include "timer1.h"
#include "sleep.h"
#include "serial.h"

volatile unsigned char *DDR_B = (unsigned char *)0x24; // direccion de DDR_B

int main(void)
{
	(*DDR_B) |= 0b00000010; // setear direccion de datos
	timer1_init();
	serial_init();
	while (1)
	{
		timer1_pwm_move_to(0);
		sleep_ms_times(50, 20);
		timer1_pwm_move_to(180);
		sleep_ms_times(50, 20);
	}

	for (;;)
	{
		;
	}
	return 0;
}
