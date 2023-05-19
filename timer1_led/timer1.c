/**********************************************************************
 *
 * timer1.c - Driver del TIMER 1 (16 bits) del atmega328p
 *
 * META : ocultar el hardware a la aplicacion
 *
 **********************************************************************/

#include <stdint.h> // para los tipos de datos. Ej.: uint8_t
#include <avr/interrupt.h>
#include "timer1.h"

/* Macros para la configuracion de los registros de control */
#define CONF_CONTROL_REG_A_FPWM 0b00000010; // fast PWM
#define CONF_CONTROL_REG_B_FPWM 0b00011011; // fast PWM - CS02|CS01|CS00 (preescalar de 64)
#define CONF_CONTROL_REG_C_FPWM 0b00000000; //
#define CONF_CONTROL_REG_A_CTC 0b00000000;  // CTC
#define CONF_CONTROL_REG_B_CTC 0b00011011;  // CTC - CS02|CS01|CS00 (preescalar de 64)
#define CONF_CONTROL_REG_C_CTC 0b00000000;  //
#define CONF_MASK_COMP_A 0x02;
#define CONF_MASK_COMP_B 0x04;
#define CONF_MASK_COMP_BOTH (CONF_MASK_COMP_A | CONF_MASK_COMP_B)

/* Macros de valores */
#define SYSTEM_TICKS 16000000
#define PRESCALAR 64
#define TICKS_PER_SECOND 1000
#define TIMER0_OCR1A ((SYSTEM_TICKS / PRESCALAR) / TICKS_PER_SECOND) // 0xfa

/* Estructura de datos del driver TIMER */
typedef struct
{
        uint8_t control_reg_a;      // TCC1RA
        uint8_t control_reg_b;      // TCC1RB
        uint8_t control_reg_c;      // TCC1RC
        uint8_t _reserved1;         //
        uint8_t _reserved2;         //
        uint8_t counter_reg_l;      // TCNT1L
        uint8_t counter_reg_h;      // TCNT1H
        uint8_t in_capture_reg_l;   // ICR1L
        uint8_t in_capture_reg_h;   // ICR1H
        uint8_t out_compare_reg_al; // OCR1AL
        uint8_t out_compare_reg_ah; // OCR1AH
        uint8_t out_compare_reg_bl; // OCR1BL
        uint8_t out_compare_reg_bh; // OCR1BH
} volatile timer1_t;
volatile timer1_t *timer = (timer1_t *)0x80; // Direccion base

volatile uint8_t *timer_interrupt_mask_reg = (uint8_t *)0x6f; // TIMSK (no se si sirve de algo)
volatile uint8_t *timer_interrupt_flag_reg = (uint8_t *)0x36; // TIFR1 (no se si sirve de algo)

volatile int ticks;
extern volatile int task_sync;

int timer1_init(uint8_t mode)
{
        if (mode == 0)
        {
                timer->control_reg_a |= CONF_CONTROL_REG_A_FPWM;
                timer->control_reg_b |= CONF_CONTROL_REG_B_FPWM;
                timer->control_reg_c |= CONF_CONTROL_REG_C_FPWM;
        }
        else if (mode == 1)
        {
                timer->control_reg_a |= CONF_CONTROL_REG_A_CTC;
                timer->control_reg_b |= CONF_CONTROL_REG_B_CTC;
                timer->control_reg_c |= CONF_CONTROL_REG_C_CTC;
        }
        else
        {
                return 1;
        }
        timer->out_compare_reg_ah = 0x00;
        timer->out_compare_reg_al = TIMER0_OCR1A;
        *(timer_interrupt_mask_reg) |= CONF_MASK_COMP_A;
        ticks = 0;
        return 0;
}

ISR(TIMER1_COMPA_vect)
{
        ticks++;
        task_sync++;
        if (ticks == TICKS_PER_SECOND)
        {
                ticks = 0;
        }
}

// ISR(TIMER1_COMPB_vect)
// {
//         ticks++;
//         task_sync++;
//         if (ticks == 1000)
//         {
//                 ticks = 0;
//         }
// }
