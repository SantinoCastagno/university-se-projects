/**********************************************************************
 *
 * main.c - the main program test file for the serial driver
 *
 **********************************************************************/

#include "serial.h"
#include "sleep.h"

int main(void)
{
    char rcvChar = 0;
    /* Configure the UART for the serial driver */
    serial_init();

    serial_put_string("start\r\n");
    serial_put_string("xd");

    while (rcvChar != 'q')
    {
        rcvChar = serial_get_char();
        sleep_ms_times(50, 20);
        serial_put_char(rcvChar);
        serial_put_char(rcvChar);
        serial_put_char(rcvChar);
        // serial_put_char('a');
        serial_put_char('\r');
        serial_put_char('\n');
    }

    for (;;)
        ;

    return 0;
}
