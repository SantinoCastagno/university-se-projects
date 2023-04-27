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

    serial_init(); // Configure the UART for the serial driver
    serial_put_char('s');
    serial_put_char('t');
    serial_put_char('a');
    serial_put_char('r');
    serial_put_char('t');
    serial_put_char('\r');
    serial_put_char('\n');

    while (rcvChar != 'q')
    {
        rcvChar = serial_get_char(); //  Wait for an incoming character
        sleep_ms_times(50, 10);
        serial_put_char(rcvChar); // Echo the character back along with a carriage return and line feed
        serial_put_char('\n');
    }

    for (;;)
        ;

    return 0;
}
