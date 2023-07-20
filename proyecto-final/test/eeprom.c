
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
#include "serial.h"

#define INIT_CONTROL_REG 0x00 /* EEPM1|EEMP0 */
#define MASTER_WRITE_ENABLE_BIT 0x04
#define WRITE_ENABLE_BIT 0x02 /* EEPROM write enable bit */
#define READ_ENABLE_BIT 0x01  /* EEPROM read enable bit */
typedef struct
{
    uint8_t control_register;      // EECR
    uint8_t data_register;         // EEDR
    uint8_t address_register_low;  // EEARL
    uint8_t address_register_high; // EEARH
} volatile eeprom_t;
eeprom_t *memory_eeprom = (eeprom_t *)(0x3f); // puntero a la estructura de los registros de la memoria

#define SPMEN 0x01
volatile unsigned char *SPMCSR = (unsigned char *)0x37; // puntero al SPMCSR

void memory_init()
{
    memory_eeprom->address_register_high = 0x00;
    memory_eeprom->address_register_low = 0x00;
    memory_eeprom->data_register = 0x00;
    memory_eeprom->control_register = INIT_CONTROL_REG;
}

// TODO: arreglar los errores de esta funcion
void memory_write(uint16_t address, uint8_t data)
{
    while (memory_eeprom->control_register && WRITE_ENABLE_BIT)
        ;

    while (*SPMCSR && SPMEN)
        ;

    memory_eeprom->address_register_high = (address >> 8);
    serial_put_char(memory_eeprom->address_register_high);
    memory_eeprom->address_register_low = address;
    serial_put_char(memory_eeprom->address_register_low);
    memory_eeprom->data_register = 'c';
    serial_put_char(memory_eeprom->data_register);

    memory_eeprom->control_register |= MASTER_WRITE_ENABLE_BIT;
    serial_put_char(memory_eeprom->control_register);
    memory_eeprom->control_register |= WRITE_ENABLE_BIT;
    serial_put_char(memory_eeprom->control_register);
}

uint8_t memory_read(uint16_t address)
{
    while (memory_eeprom->control_register && WRITE_ENABLE_BIT)
        ;

    memory_eeprom->address_register_high = (address >> 8);
    memory_eeprom->address_register_low = address & 0xff;

    memory_eeprom->control_register |= READ_ENABLE_BIT;
    return memory_eeprom->data_register;
}
