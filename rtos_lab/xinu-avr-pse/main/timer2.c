/**********************************************************************
 *
 * timer2.c - Driver del TIMER 1 (8 bits) del atmega328p
 *
 * META : ocultar el hardware a la aplicacion
 *
 **********************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>

#define TIMER0_CS 0x03  /* prescalar=64 CS02|CS01|CS00 = 0b011 */
#define TIMER0_CTC 0x02 /* CTC = WGM = 0b010 : modo CTC es comparar y volver a cero*/

#define SYSTEM_TICKS 16000000
#define PRESCALAR 64
#define TICKS_PER_SECOND 1000

#define TIMER0_OCR0A (SYSTEM_TICKS / PRESCALAR / TICKS_PER_SECOND)

typedef struct
{
    uint8_t tccr0a; /* Registro de control A del timer0 */
    uint8_t tccr0b; /* Registro de control B del timer0 */
    uint8_t tcnt0;  /* Registro timer/contador */
    uint8_t ocr0a;  /* Registro comparador A */
    uint8_t ocr0b;  /* Registro comparador B */

} volatile timer0_t;

volatile timer0_t *timer0 = (timer0_t *)(0x44);

/* registro mascara de interrupciones timer 0 */
volatile unsigned char *timer0_timsk0 = (unsigned char *)(0x6E);

volatile int ticks = 0;

extern volatile int task_sync;

void timer2_init(void)
{
    timer0->tccr0a |= TIMER0_CTC;
    timer0->tccr0b |= TIMER0_CS;
    timer0->ocr0a = TIMER0_OCR0A; /* valor contra el cual comparar */
    (*timer0_timsk0) |= 0x02;     /* 0x02: compara contra registro OCR0A
                         y genera interrupcion si hay un match */
    ticks = 0;
}
