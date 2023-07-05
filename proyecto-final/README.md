# Proyecto final: invernadero de interior automatizado

- Profesor: Rafael Zurita
- Alumno: Santino Castagno

La idea del proyecto es crear un mini invernadero automático capaz de cuidar a plantas de interior

## Requisitos funcionales

Se listaron los siguientes requisitos funcionales:
1. Cada determinada cantidad de tiempo (fijada inicialmente) se debe almacenar un registro con los valores de los sensores actuales (posiblemente normalizados) en la memoria EEPROM del Arduino.
2. En caso de activarse un actuador, se debe almacenar un registro en la memoria EEPROM con la hora actual y el actuador activado.
3. Cada una cantidad de tiempo, se debe utilizar un módulo de comunicación wifi para comunicar los registros almacenados en la memoria EEPROM a una pagina web.
4.  Se debe sensar la temperatura regularmente (1 minuto o 5 minutos) para saber si se deben encender los ventiladores y refrigerar o si se debe encender un foco para caldear.
5.  Se debe sensar la humedad regularmente (1 minuto o 5 minutos) para activar un sistema de riego y hidratar la planta.

## Inventario

Se deben utilizar los siguientes materiales:
- Arduino uno o Arduino nano
- Breadboard
- Cables
- Rele
- Sensor de temperatura
- Sensor de humedad del ambiente
- Sensor de humedad del suelo
- Sensor de intensidad luminosa (posiblemente resistencia)
- Bombillos (para iluminación)
- Resistencia de temperatura (para caldear)
- Ventiladores (para refrigerar)

## Variables, sensores y actuadores

Las variables a controlar fueron las siguientes:
1. Temperatura del ambiente
2. Humedad de la tierra
3. Luz

| Sensor | Actuador |
|--------|------|
| Temperatura baja | Se encienden bombillos o resistencias de calor |
| Temperatura alta | Se encienden ventiladores |
| Humedad baja | Se regaran las plantas |
| Luz | Se encenderan pequeños bombillos distribuidos |
| Ph | ? |
| CO2 | ? |
| - | Se escribira un registro en nuevo en la memoria EEPROM |
