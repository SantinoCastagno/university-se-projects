#include "sleep.h"
#include "adc.h"
#include "serial.h"

int main(){
    int rec;
    adc_init();
    serial_init();
    while (1)
    {
        rec = adc_get(0);
        serial_put_int(rec,4);
        serial_put_string("\r\n");
        sleep_ms(90);
    }
    
    return 0;
}