#include "serial.h"
#include "sleep.h"

volatile unsigned char *PIN_B = (unsigned char *)0x23;	  // direccion de PIN_B
volatile unsigned char *DDR_B = (unsigned char *)0x24;	  // direccion de DDR_B
volatile unsigned char *PUERTO_B = (unsigned char *)0x25; // direccion de PORT_B

void test_put()
{
	serial_init();
	while (1)
	{
		serial_put_str("\n\rHOLA MUNDO\n");
		serial_put_int(123, 4);
		sleep_ms(500);
	}
}

void mostrar_valor(int valor)
{
	serial_put_str("\rvalor: \t");
	serial_put_int(valor, 4);
	serial_put_str("\n");
}

void mostrar_distancia(int distancia_cm)
{
	serial_put_str("\rDistancia: \t");
	serial_put_int(distancia_cm, 4);
	serial_put_str("cm\n");
}

int main()
{
	*(DDR_B) = 0b00000001;	  // setear direccion de datos (0-input y 1-output)
	// *(PUERTO_B) = 0b00000010; // setear bit de pull-up para los input
	int distancia_cm;
	unsigned int tiempo_us;
	volatile int echo;
	volatile unsigned int t;

	serial_init();
	while (1)
	{
		distancia_cm = 0;
		tiempo_us;
		t = 0;

		*(PUERTO_B) = *(PUERTO_B) | 0b00000001;
		sleep_10us();
		*(PUERTO_B) = *(PUERTO_B)&0b11111110;

		echo = *(PIN_B)&0b00000010;
		while (echo)
		{
			t++;
			sleep_10us();
			echo = *(PIN_B)&0b00000010;
			// mostrar_valor(*(PIN_B));
		}

		tiempo_us = t * 10;
		distancia_cm = tiempo_us / 58;
		mostrar_distancia(distancia_cm);
		sleep_ms(500);
	}

	return 0;
}
