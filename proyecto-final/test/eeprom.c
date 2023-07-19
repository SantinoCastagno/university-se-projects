
/**********************************************************************
 *
 * eeprom.c - Driver de la memoria EEPROM
 *
 * META : ocultar el hardware a la aplicacion
 *
 **********************************************************************/

#include "eeprom.h"
#include "sleep.h"
#include <stdint.h>

#define INIT_CONTROL_REG 0x30 /* EEPM1|EEMP0 */
#define MASTER_WRITE_ENABLE_BIT 0x04
#define WRITE_ENABLE_BIT 0x02 /* EEPROM write enable bit */
#define READ_ENABLE_BIT 0x01  /* EEPROM read enable bit */
typedef struct
{
    uint8_t control_register;           // EECR
    uint8_t data_register;              // EEDR
    uint8_t address_register_low_byte;  // EEARL
    uint8_t address_register_high_byte; // EEARH
} volatile eeprom_t;
eeprom_t *memory_eeprom = (eeprom_t *)(0x3f); // puntero a la estructura de los registros de la memoria

#define SPMEN 0x01
volatile unsigned char *SPMCSR = (unsigned char *)0x37; // puntero al SPMCSR

void memory_init()
{
    memory_eeprom->address_register_high_byte = 0;
    memory_eeprom->address_register_low_byte = 0;
    memory_eeprom->data_register = 0;
    memory_eeprom->control_register = INIT_CONTROL_REG;
}

void memory_write(uint8_t address, uint8_t data)
{
    while (memory_eeprom->control_register & WRITE_ENABLE_BIT)
        ;

    while (*SPMCSR & SPMEN)
        ;

    memory_eeprom->address_register_low_byte = address;
    memory_eeprom->data_register = data;

    memory_eeprom->control_register |= MASTER_WRITE_ENABLE_BIT;
    memory_eeprom->control_register &= ~WRITE_ENABLE_BIT;

    sleep_10us();

    memory_eeprom->control_register |= WRITE_ENABLE_BIT;
}

uint8_t memory_read(uint8_t address)
{
    while (memory_eeprom->control_register & WRITE_ENABLE_BIT)
        ;

    memory_eeprom->address_register_low_byte = address;

    memory_eeprom->control_register |= READ_ENABLE_BIT;

    return memory_eeprom->data_register;
}
