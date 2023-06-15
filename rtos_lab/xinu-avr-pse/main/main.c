/**
 *
 * task_knob_motor:  	Toma como entrada la posicion del knob y modifica la velocidad del motor.
 * task_led_observer: 	Lee la velocidad actual del motor y enciende el led a una frecuencia proporcional.
 * task_operator:		Obtiene la entrada de la consola del operador del sistema.
 * task_reporter:		Reporta constantemente el estado del sistema al operador. (main)
 * task_servo_handler:	Manipula la posicion del servo
 *
 */

#include <xinu.h>
#include "serial.h"

unsigned char motor_speed = 0;
unsigned char servo_angle = 0;
unsigned char clock = 0;
unsigned char input_op = 0;

volatile unsigned char *PIN_B = (unsigned char *)0x23;	  // direccion de PIN_B
volatile unsigned char *DDR_B = (unsigned char *)0x24;	  // direccion de DDR_B
volatile unsigned char *PUERTO_B = (unsigned char *)0x25; // direccion de PORT_B

/* definicion de tareas (cuyo codigo fuente es externo) */
// extern int led_observer(void);
extern int operator(void);
extern int comunicacion(void);
extern int knob_motor(void);

/* nombre para dos semaforos a utilizar */
#define SEM_OP 0

/* main es una tarea independiente y se la utiliza como tal */
int main(void)
{
	serial_init();
	adc_init();
	timer1_init();
	/* configurar entrada/salida de datos */
	(*DDR_B) |= 0b00000100;

	// /* inicializamos los semaforos */
	sync_set(SEM_OP, 1);

	/* creamos y ponemos a ejecutar las tareas */
	resume(create(knob_motor, 256, 10, "knob_motor", 0));
	resume(create(operator, 64, 10, "operator", 0));
	resume(create(servo_handler, 64, 10, "operator", 0));

	while (1)
	{
		sleep(1);
		serial_put_str("velocidad ");
		serial_put_int(motor_speed, 3);
		serial_put_str("%");
		serial_put_str("\n\r");
	}

	return 0;
}
