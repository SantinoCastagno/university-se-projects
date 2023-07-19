#include "eeprom.h"
#include <stdint.h>
int main()
{
    uint8_t dir_a = 1, dir_b = 24;
    uint8_t value_a = 4;

    memory_init();
    memory_write(dir_a, value_a);

    while (1)
        ;

    return 0;
}
