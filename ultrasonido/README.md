
# ultrasonido

Este programa utiliza el sensor de ultrasonido HC-SR04 para sensar un objeto que tiene delante y calcular la distancia apróximada hacía dicho objeto. Utiliza el *portb bit 0* para emitir la señal que activar el sensor y el *portb bit 1* para captar la señal de echo del sensor.
## Running Tests

Para probar el programa, ejecute los siguientes comandos:

```bash
  make clean
  make
```

En caso de que no funcione, ejecutar:

```bash
  dmesg
```

Y observar cuál es la interfaz TTY asociada a la placa Arduino conectada por USB. Luego, cambiar dicha variable en el Makefile.
## Authors

- [@Santino Castagno](https://www.github.com/SantinoCastagno)

