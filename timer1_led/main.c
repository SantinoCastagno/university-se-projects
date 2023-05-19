#include <avr/interrupt.h>

#include "timer1.h"
volatile unsigned char *DDR_B = (unsigned char *)0x24;	  // direccion de DDR_B

int main(void)
{
    (*DDR_B) = 0b00000111;	  // setear direccion de datos
    timer1_init(1);
    // leds_init();
    // tasks_init();
    // tasks_def(5000, toggle13); // definimos una tarea periódica a 300ms
    // sei();                     // habilitamos las interrupciones
    while (1)
    {  
        ;;
    }
    return 0;
}
