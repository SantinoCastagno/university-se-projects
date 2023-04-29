/**********************************************************************
 *
 * main.c - the main program test file for the serial driver
 *
 **********************************************************************/

#include "serial.h"
#include "sleep.h"
#include <stdint.h>

#define ECHO_REC 0x02
#define HIGH_TRIG 0x01
#define LOW_TRIG 0xFE
#define INIT_DDR 0x1D

volatile unsigned char *PIN_B = (unsigned char *)0x23;    // direccion de PIN_B
volatile unsigned char *DDR_B = (unsigned char *)0x24;    // direccion de DDR_B
volatile unsigned char *PUERTO_B = (unsigned char *)0x25; // direccion de PORT_B

mostrar_distancia(int distancia_cm)
{
    serial_put_string("Distancia: \t");
    serial_put_int(distancia_cm, 3);
    serial_put_string("cm\r");
}

/*TO DO: Hay un error con el ultrasound por el que imprime un valor de distancia mas grande del que deberia.*/
int ultrasound()
{
    unsigned int tiempo_us, distancia;
    char fuera_de_rango = 0, flag = 1;

    while (flag)
    {
        distancia = 0;
        tiempo_us = 0;

        (*PUERTO_B) = (*PUERTO_B) | HIGH_TRIG; // levanto trig
        sleep_10us();
        (*PUERTO_B) = (*PUERTO_B) & LOW_TRIG; // bajo trig

        while ((!((*PIN_B) & ECHO_REC)) && tiempo_us <= 38000) // esperar la señal
        {
            sleep_10us();
            tiempo_us += 10;
        }
        if (tiempo_us < 38000) // verifico que la señal no se vaya de rango
        {
            tiempo_us = 0;
            while ((*PIN_B) & ECHO_REC) // mientras echo este en alto
            {
                sleep_10us();
                tiempo_us += 10;
            }
            distancia = tiempo_us / 46;
            mostrar_distancia(distancia);
            flag = 0;
        }
        sleep_ms(50);
    }

    return 0;
}

int knight_rider(char status)
{
    unsigned char state = 0, time = 0, input;

    *(PUERTO_B) = *(PUERTO_B) & ~(0b111 << 2);
    while (1)
    {
        /*TO DO: verificar por que se realizaba esta asignacion.*/
        input = (*(PIN_B)) & 0b00100000;
        sleep_ms(50);
        if (input != 0b00100000)
        {
            if (state == 0)
                state = 1;
            else
                state = 0;
        }
        /*TO DO: aparentemente las asignaciones de los bits para encender los leds estarían funcionando, pero puede fallar.*/
        if (state == 1)
        {
            switch (time)
            {
            case 0:
                *(PUERTO_B) = *(PUERTO_B) | (0b001 << 2);
                time = 1;
                break;
            case 1:
                *(PUERTO_B) = *(PUERTO_B) & ~(0b110 << 2);
                time = 2;
                break;
            case 2:
                *(PUERTO_B) = *(PUERTO_B) | (0b010 << 2);
                time = 3;
                break;
            case 3:
                *(PUERTO_B) = *(PUERTO_B) & ~(0b101 << 2);
                time = 4;
                break;
            case 4:
                *(PUERTO_B) = *(PUERTO_B) | (0b100 << 2);
                time = 5;
                break;
            case 5:
                *(PUERTO_B) = *(PUERTO_B) & ~(0b011 << 2);
                time = 6;
                break;
            case 6:
                *(PUERTO_B) = *(PUERTO_B) | (0b010 << 2);
                time = 7;
                break;
            case 7:
                *(PUERTO_B) = *(PUERTO_B) & ~(0b101 << 2);
                time = 0;
                break;
            default:
                *(PUERTO_B) = *(PUERTO_B) & ~(0b111 << 2);
                break;
            }
        }
        else
        {
            *(PUERTO_B) = *(PUERTO_B) & ~(0b111 << 2);
        }
        sleep_ms_times(90, 4);
    }
    return 0;
}

int main(void)
{
    *(DDR_B) = INIT_DDR; // Configura la direccion de datos del registro B (bit 1-3 Knight rider y bit 0-1 para ultrasonido)
    serial_init();       // Configura el UART para el driver serial
    char rcvChar = 0, kr_status = 0;

    serial_put_string("starting the program\r\n");
    while (1)
    {
        if (serial_get_char_ready())
        {
            rcvChar = serial_get_char();
            switch (rcvChar)
            {
            case 'u':
                ultrasound();
                break;
            case 'k':
                kr_status = ~kr_status;
                break;
            default:
                break;
            }
        }
        knight_rider(kr_status);

        serial_put_char('\r');
        serial_put_char('\n');
        sleep_ms_times(50, 20);
    }

    // for (;;)
    //     ;

    return 0;
}
