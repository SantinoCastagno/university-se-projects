/**********************************************************************
 *
 * timer1.c - Driver del TIMER 1 (16 bits) del atmega328p
 *
 * META : ocultar el hardware a la aplicacion
 *
 **********************************************************************/

#include <stdint.h>
#include <avr/interrupt.h>
#include "timer1.h"
#include "serial.h"

/* Macros para la configuracion de los registros de control */
#define CONF_CONTROL_REG_A_FPWM 0b10000010; // [COM1A1|COM1A2]  clear on match  - [WGM11|WGM10]         fast PWM
#define CONF_CONTROL_REG_B_FPWM 0b00011010; // [WGM13|WGM12]    fast PWM        - [CS02|CS01|CS00]      preescale 8
#define CONF_CONTROL_REG_C_FPWM 0b00000000; //

/********************** Calculos de valores ***************************
 *
 * f_cpu/prescalar = 16000000/8 = 2000000 t/s
 * FREQ: 2000000 t/s * 0.020  = 39999 = 0x9c3f
 * MIN:  2000000 t/s * 0.001  = 2000  = 0x07d0
 * MAX:  2000000 t/s * 0.002  = 3999  = 0x0f9f
 * 2000000 t/s * 0.0025  = 3999  = 0x1194
 **********************************************************************/

/* Macros de valores */
#define MIN_PWM_8P 2000
#define MAX_PWM_8P 3999
#define TIMER1_FREQ_H 0x9c
#define TIMER1_FREQ_L 0x3f
#define TIMER1_0CR1AH_POS 0x0f
#define TIMER1_0CR1AL_POS 0x9f

/* Estructura de datos del driver TIMER */
typedef struct
{
        uint8_t control_reg_a;      // TCC1RA
        uint8_t control_reg_b;      // TCC1RB
        uint8_t control_reg_c;      // TCC1RC
        uint8_t _reserved;          //
        uint8_t counter_reg_l;      // TCNT1L
        uint8_t counter_reg_h;      // TCNT1H
        uint8_t in_capture_regl;    // ICR1L
        uint8_t in_capture_regh;    // ICR1H
        uint8_t out_compare_reg_al; // OCR1AL
        uint8_t out_compare_reg_ah; // OCR1AH
        uint8_t out_compare_reg_bl; // OCR1BL
        uint8_t out_compare_reg_bh; // OCR1BH
} volatile timer1_t;
volatile timer1_t *timer = (timer1_t *)0x80; // Direccion base

volatile uint8_t *timer_interrupt_mask_reg = (uint8_t *)0x6f; // TIMSK
volatile uint8_t *timer_interrupt_flag_reg = (uint8_t *)0x36; // TIFR1 (no se si sirve de algo)

volatile int ticks;

int timer1_init()
{
        /* setear la configuracion del timer1  */
        timer->control_reg_a |= CONF_CONTROL_REG_A_FPWM;
        timer->control_reg_b |= CONF_CONTROL_REG_B_FPWM;
        timer->control_reg_c |= CONF_CONTROL_REG_C_FPWM;

        /* determinar la frecuencia con el registro ICR  */
        timer->in_capture_regh = TIMER1_FREQ_H;
        timer->in_capture_regl = TIMER1_FREQ_L;

        /* determinamos el ancho de la senial en alto en cada ciclo con el registro OCR1A */
        timer->out_compare_reg_ah = TIMER1_0CR1AH_POS;
        timer->out_compare_reg_al = TIMER1_0CR1AL_POS;

        /* reiniciamos los registros del contador (por las dudas) */
        timer->counter_reg_l = 0;
        timer->counter_reg_h = 0;
        return 0;
}

/**
 * GRADE: para posicionar el servo (min 0 y max 180)
 */
int timer1_pwm_move_to(int grade)
{
        long int init_value, temp;
        uint8_t low, high;

        // if (grade < 0 || grade > 180)
        //         return 1;

        init_value = grade * 100 / 180;
        temp = MIN_PWM_8P + (MAX_PWM_8P - MIN_PWM_8P) / 100 * init_value;
        high = (temp >> 8);
        low = temp;

        /* determinamos el ancho de la senial en alto en cada ciclo con el registro OCR1A */
        timer->out_compare_reg_ah = high;
        timer->out_compare_reg_al = low;

        return 0;
}
