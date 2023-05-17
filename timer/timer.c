/**********************************************************************
 *
 * adc.c - Driver del TIMER del atmega328p
 *
 * META : ocultar el hardware a la aplicacion
 *
 **********************************************************************/

#include <stdint.h> // para los tipos de datos. Ej.: uint8_t
#include <avr/interrupt.h>
#include "timer.h"

/* Macros para la configuracion de los registros de control */
#define CONF_CONTROL_REG_A 0b00000000;
#define CONF_CONTROL_REG_B 0b00011101; // fast PWM - preescalar de 256
#define CONF_CONTROL_REG_C 0b00000010; // fast PWM

/* Estructura de datos del driver TIMER */
typedef struct
{
        uint8_t control_reg_a;      // TCC1RA
        uint8_t control_reg_b;      // TCC1RB
        uint8_t control_reg_c;      // TCC1RC
        uint8_t _reserved;          //
        uint8_t _reserved;          //
        uint8_t counter_reg_l;      // TCNT1L
        uint8_t counter_reg_h;      // TCNT1H
        uint8_t in_capture_reg_l;   // ICR1L
        uint8_t in_capture_reg_h;   // ICR1H
        uint8_t out_compare_reg_al; // OCR1AL
        uint8_t out_compare_reg_ah; // OCR1AH
        uint8_t out_compare_reg_bl; // OCR1BL
        uint8_t out_compare_reg_bh; // OCR1BH
} volatile timer_t;
volatile timer_t *timer = (timer_t *)(0x80); // Direccion base

volatile uint8_t *timer_interrupt_mask_reg = (unsigned char *)0x6f; // TIMSK
volatile uint8_t *timer_interrupt_flag_reg = (unsigned char *)0x36; // TIFR1

void timer1_init()
{
        timer->control_reg_a = CONF_CONTROL_REG_A;
        timer->control_reg_b = CONF_CONTROL_REG_B;
        timer->control_reg_c = CONF_CONTROL_REG_C;
        (*timer_interrupt_mask_reg) |= 0x
}
