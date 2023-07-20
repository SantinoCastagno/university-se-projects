package main

import (
	"fmt"
	"os"
	"os/exec"
	"time"
)

const device string = "/dev/ttyACM0"

func read_uart() {
	var valor_lectura []byte = make([]byte, 1)
	var valor byte
	exec.Command("stty", "-F", "/dev/ttyACM0", "speed", "9600").Run()
	time.Sleep(3 * time.Second)

	// open input file
	fi, err := os.Open(device)
	if err != nil {
		panic(err)
	}

	for {
		if _, err := fi.Read(valor_lectura); err != nil {
			panic(err)
		}
		valor = valor_lectura[0]
		fmt.Print((valor_lectura[0]))
		fmt.Print("\t" + string(valor) + "\n")
		defer func() {
			if err := fi.Close(); err != nil {
				panic(err)
			}
		}()
		// time.Sleep(100 * time.Millisecond)
	}
	// close fi on exit and check for its returned error

}

/*
Se utiliza el comando stty para configurar la terminal de linux
*/
func write_uart() {
	var tecla []byte = make([]byte, 1)
	// disable input buffering
	exec.Command("stty", "-F", "/dev/tty", "cbreak", "min", "1").Run()
	// do not display entered characters on the screen
	exec.Command("stty", "-F", "/dev/tty", "-echo").Run()

	defer func() {
		exec.Command("reset").Run()
	}()
	// open output file
	fo, err := os.Create(device)
	if err != nil {
		panic(err)
	}
	// close fo on exit and check for its returned error
	defer func() {
		if err := fo.Close(); err != nil {
			panic(err)
		}
	}()
	for {
		os.Stdin.Read(tecla)
		// write a chunk
		if _, err := fo.Write(tecla); err != nil {
			panic(err)
		}
	}
}

func main() {
	read_uart()
}

/*
* TODO: quizas sea necesario poner la velocidad de la comunicacion del puerto serie a 9600 en algun punto
 */
