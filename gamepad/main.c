#include "serial.h"
#include "sleep.h"
#include "adc.h"
#include <stdint.h>

#define INIT_DATA_DIRECTION 0x00
#define INIT_PULL_UP 0x03
#define HIGH_BTN_SHOOT 0x01

volatile unsigned char *PIN_B = (unsigned char *)0x23;    // direccion de PIN_B
volatile unsigned char *DDR_B = (unsigned char *)0x24;    // direccion de DDR_B
volatile unsigned char *PUERTO_B = (unsigned char *)0x25; // direccion de PORT_B

int main()
{
    uint8_t input_btn, input_adc;
    (*DDR_B) = INIT_DATA_DIRECTION;
    (*PUERTO_B) = INIT_PULL_UP;
    serial_init();
    adc_init();
    sleep_ms_times(90, 10);

    /* inf loop */
    while (1)
    {
        input_btn = (*PIN_B);
        sleep_ms(20);

        input_adc = adc_get(0);
        serial_put_int(input_adc, 4);
        serial_put_string("\r\n");
        sleep_ms(90);

        if (!(input_btn & HIGH_BTN_SHOOT))
        {
            serial_put_char(0x20);
        }
    };
    return 0;
}