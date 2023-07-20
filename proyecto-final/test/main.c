#include "eeprom.h"
#include "serial.h"
#include "sleep.h"
#include <stdint.h>
#include <avr/eeprom.h>

int main()
{
    uint16_t dir_a = 8, dir_b = 24;
    uint8_t value_a = 2;
    uint8_t res_value, i;
    sleep_ms_times(90,90);
    serial_init();
    memory_init();
    // TODO: Funciona la escritura utilizando la libreria y la lectura utilizando los registros directamente
    // eeprom_write_byte((uint8_t)dir_a, 'b');
    memory_write(dir_a, 'a');
    while (1){
        res_value = memory_read(dir_a);
        serial_put_char(res_value);
        sleep_ms_times(50, 50);
    }

    return 0;
}