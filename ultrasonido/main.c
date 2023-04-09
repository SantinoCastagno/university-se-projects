
#include "serial.h"

int main()
{
	volatile unsigned int i;

	serial_init();
	
	while(1) {

		serial_put_str("\n\rHOLA MUNDO\n ");
        	serial_put_int(123,4);
        	for (i=0; i<10000; i++);
	}
}
