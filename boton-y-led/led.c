#define SLEEP_1 100000
#define SLEEP_2 200000
#define SLEEP_5 500000

int main(void)
{
	// volatile unsigned char *DDR_B = (unsigned char *) 0x24; /* direccion de DDR B*/
	// volatile unsigned char *PUERTO_B = (unsigned char *) 0x25; /* direccion de PUERTO B*/
	volatile unsigned char *DDR_B = (unsigned char *)0x24;	  /* direccion de DDR B*/
	volatile unsigned char *PUERTO_B = (unsigned char *)0x25; /* direccion de PUERTO B*/

	*(DDR_B) = 0b00000111; // setear direccion de datos
	int a;
	volatile long i;
	volatile char aux;
	while (1)
	{
		if (*(PUERTO_B)&0b00001000 == 0b00001000)
		{
			*(PUERTO_B) = *(PUERTO_B) | 0b00000111; // setear led en encendido
			for (i = 0; i < SLEEP_2; i++)
			{
				a = 1;
			}
		}
		else
		{
			*(PUERTO_B) = *(PUERTO_B)&0b00000000; // setear led en encendido
			for (i = 0; i < SLEEP_2; i++)
			{
				a = 2;
			}
		}
	}
	return 0;
}
