
int main(void)
{
	volatile unsigned char *DDR_B = (unsigned char *) 0x24;	  /* direccion de DDR B*/
	volatile unsigned char *PUERTO_B = (unsigned char *) 0x25; /* direccion de PUERTO B*/

	*(DDR_B) = 0b00100000;
	*(PUERTO_B) = 0b00100000;
	int a;
	while (1)
	{
		volatile long i;
		for (i = 0; i < 1000000; i++)
		{
			a = 1;
		}
		*(PUERTO_B) = 0b00100000; // Setear led en encendido
		for (i = 0; i < 100000; i++){
			a = 2;
		}
		*(PUERTO_B) = 0b00000000; // Setear led en apagado
	}
	return 0;
}
