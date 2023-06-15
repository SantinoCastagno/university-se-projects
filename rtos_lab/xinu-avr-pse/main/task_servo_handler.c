
extern volatile unsigned char *PIN_B;    // direccion de PIN_B
extern volatile unsigned char *DDR_B;    // direccion de DDR_B
extern volatile unsigned char *PUERTO_B; // direccion de PORT_B

#include <xinu.h>
#include "serial.h"
#include "timer1.h"

extern unsigned char servo_angle;

/**
 * tarea encargada de manipular el angulo del servo
 */
int servo_handler(void)
{
    while (1)
    {
        input = adc_get(0);
        motor_speed = input / 10; // para simplificar la operacion de motor_speed = input * 100 / 1024
        timer1a_pwm_move_to(servo_angle);
        sleepms(100);
    }
}
