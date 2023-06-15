
#include <xinu.h>
#include "serial.h"
#include "timer1.h"

extern unsigned char input_op;
/**
 * tarea encargada de recibir la entrada del operador
 */
int operator(void)
{
    while (1)
    {
        input_op = serial_get_char();
    }
}
