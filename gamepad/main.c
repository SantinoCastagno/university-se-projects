#include "serial.h"
#include "sleep.h"
#include <stdint.h>

#define INIT_DATA_DIRECTION 0x00
#define INIT_PULL_UP 0x03
#define HIGH_BTN_Z 0x02
#define HIGH_BTN_X 0x01

volatile unsigned char *PIN_B = (unsigned char *)0x23;    // direccion de PIN_B
volatile unsigned char *DDR_B = (unsigned char *)0x24;    // direccion de DDR_B
volatile unsigned char *PUERTO_B = (unsigned char *)0x25; // direccion de PORT_B

int main()
{
    uint8_t input;
    (*DDR_B) = INIT_DATA_DIRECTION;
    (*PUERTO_B) = INIT_PULL_UP;
    serial_init();
    sleep_ms_times(90,10);
    serial_put_char(0x20);
    /* inf loop */
    while (1)
    {

        input = (*PIN_B);
        sleep_ms(20);
        // serial_put_string("input:");
        // serial_put_int(input, 2);
        // serial_put_string("\n");
        if (!(input & HIGH_BTN_Z))
        {
            serial_put_char('h');
        }
        if (!(input & HIGH_BTN_X))
        {
            serial_put_char('l');
        }
    };
    return 0;
}