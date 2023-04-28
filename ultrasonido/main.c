#include "serial.h"
#include "sleep.h"

#define ECHO_REC 0x02

volatile unsigned char *PIN_B = (unsigned char *)0x23;	  // direccion de PIN_B
volatile unsigned char *DDR_B = (unsigned char *)0x24;	  // direccion de DDR_B
volatile unsigned char *PUERTO_B = (unsigned char *)0x25; // direccion de PORT_B

void mostrar_distancia(int distancia_cm)
{
	serial_put_str("Distancia: \t");
	serial_put_int(distancia_cm, 3);
	serial_put_str("cm\r");
}

int main()
{
	unsigned int tiempo_us, distancia;
	volatile char echo = 0;
	char fuera_de_rango = 0;

	(*DDR_B) = 0b00000001; // setear direccion de datos
	serial_init();

	while (1)
	{
		distancia = 0;

		(*PUERTO_B) = (*PUERTO_B) | 0b00000001; // levanto trig
		sleep_10us();
		(*PUERTO_B) = (*PUERTO_B) & 0b11111110; // bajo trig

		tiempo_us = 0;
		while ((!((*PIN_B) & ECHO_REC)) && tiempo_us <= 38000)
		{
			sleep_10us();
			tiempo_us += 10;
		}
		if (tiempo_us < 38000) // verificar que no se pase de rango la señal
		{
			tiempo_us = 0;
			// mientras echo este en alto
			while ((*PIN_B) & ECHO_REC)
			{
				sleep_10us();
				tiempo_us = tiempo_us + 10;
			}
			distancia = tiempo_us / 46;
			mostrar_distancia(distancia);
		}
		sleep_ms(50);
	}

	return 0;
}
