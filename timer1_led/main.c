#include <avr/interrupt.h>

#include "timer1.h"
#include "utils.h"
#include "tasks.h"

int main(void)
{
    timer1_init(1);
    leds_init();
    tasks_init();
    tasks_def(5000, toggle13); // definimos una tarea periódica a 300ms
    sei();                     // habilitamos las interrupciones
    while (1)
    {
        tasks_do();
    }
    return 0;
}
