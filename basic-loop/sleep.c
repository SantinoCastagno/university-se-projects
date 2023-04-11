#include "sleep.h"

void sleep_ms(unsigned int tiempo)
{
	unsigned int limite = tiempo * 695;
	volatile unsigned int i;
	for (i = 0; i < limite; i++)
	{
	}
}

void sleep_10us() // Aun no funciona
{
	unsigned int limite = 2;
	long i = 0;
	i = i + 1;
	i++;
	i++;
	i++;
	i = 0;
	i = 1;
}

// void delay_ms(int milliseconds)
// {
// 	volatile unsigned long cycles = (milliseconds * CYCLES_PER_MS);
// 	while (cycles != 0)
// 		cycles--;
// }