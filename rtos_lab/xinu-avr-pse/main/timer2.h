/**********************************************************************
 *
 * Filename:    timer2.h
 *
 * API para la aplicacion embebida
 * META : ocultar el hardware a la aplicacion
 *
 **********************************************************************/
#ifndef _timer2_H
#define _timer2_H

int timer2_init();
int timer2_pwm_move_to(int speed);
int timer2_pwm_max();
int timer2_pwm_min();

#endif /* _timer2_H */