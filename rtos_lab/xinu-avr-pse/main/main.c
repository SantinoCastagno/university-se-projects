/* main.c: programa ejemplo con tres tareas concurrentes.
 *
 * tarea_led: prioridad 20, pila 64 bytes.
 * tarea_comunicaciones: prioridad 20, pila 256 bytes
 * tarea_main: prioridad 20, pila 256 bytes
 *
 * dos semaforos para sincronizar una alternancia de uso del UART
 */

#include <xinu.h>
#include "serial.h"

/* definicion de tareas (cuyo codigo fuente es externo) */
extern int led_placa(void);
extern int comunicacion(void);

/* nombre para dos semaforos a utilizar */
#define SEM_COM 0
#define SEM_PROD 1


/* main es una tarea independiente y se la utiliza como tal */
int main(void)
{

	serial_init();

	/* inicializamos los semaforos */
	sync_set(SEM_COM, 1);
	sync_set(SEM_PROD, 0);

	/* creamos y ponemos a ejecutar dos tareas */
	resume(create(led_placa, 64, 10, "led", 0));
	resume(create(comunicacion, 256, 20, "comm", 0));


	while(1) {
		sleep(1);

                /* como esta tarea comparte el serial con otra tarea, 
                 * se lo sincroniza estilo productor-consumidor,
                 * para que cada uno envie un mensaje de manera
                 * alternada. Un mutex podría haber sido utilizado
		 * si no es necesaria la alternancia.
                 */

		sync_wait(SEM_COM);
			serial_put_str("hola mundo version 0.2\n");
		sync_signal(SEM_PROD);
		
		
	}

	return 0;
}

