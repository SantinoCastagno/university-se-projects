#include "sleep.h"
#define CYCLES_PER_MS 442;

void sleep_ms(long tiempo)
{
	volatile unsigned long limite = tiempo * CYCLES_PER_MS;
	volatile long i;
	for (i = 0; i < limite; i++)
	{
	}
}

void sleep_ms_original(int tiempo)
{
	unsigned int limite = tiempo * CYCLES_PER_MS;
	volatile long i;
	for (i = 0; i < limite; i++)
	{
	}
}

void sleep_10us() // Aun no funciona
{
	unsigned int limite = 1 * 3 * (0 * 3);
	volatile long i;
	for (i = 0; i < limite; i++)
	{
	}
}

// void delay_ms(int milliseconds)
// {
// 	volatile unsigned long cycles = (milliseconds * CYCLES_PER_MS);
// 	while (cycles != 0)
// 		cycles--;
// }