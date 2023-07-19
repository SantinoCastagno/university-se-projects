#include <stdint.h>

#ifndef EEPROM
#define EEPROM

void memory_init();
void memory_write(uint8_t address, uint8_t data);
uint8_t memory_read(uint8_t address);

#endif