#define SLEEP_1 100000
#define SLEEP_2 200000
#define SLEEP_5 500000

int main(void)
{
	volatile unsigned char *PIN_B = (unsigned char *)0x23;	  // direccion de PIN_B
	volatile unsigned char *DDR_B = (unsigned char *)0x24;	  // direccion de DDR_B
	volatile unsigned char *PUERTO_B = (unsigned char *)0x25; // direccion de PORT_B

	*(DDR_B) = 0b00100111; // setear direccion de datos
	int a;
	volatile long i;
	volatile char aux, input;
	while (1)
	{
		input = (*(PIN_B)) & 0b00001000;
		my_sleep();
		if (input == 00000000)
		{
			*(PUERTO_B) = *(PUERTO_B)&0b11111000; // setear led en encendido
			for (i = 0; i < SLEEP_1; i++)
			{
				a = 2;
			}
		}
		else
		{
			*(PUERTO_B) = *(PUERTO_B) | 0b00000111; // setear led en encendido
			for (i = 0; i < SLEEP_1; i++)
			{
				a = 1;
			}
		}
	}
	return 0;
}

void my_sleep()
{
	int i, j;
	for (i = 0; i < 1000; i++)
	{
		j = i;
	}
}