package main

import (
	"fmt"
	"os"
	"os/exec"
	"time"
)

const device string = "/dev/ttyACM0"

func lectura() {

}

func main() {
	var valor_lectura []byte = make([]byte, 1)
	var valor byte
	var keypress int
	exec.Command("stty", "-F", "/dev/ttyACM0", "speed", "9600").Run()
	time.Sleep(5 * time.Second)
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
		switch valor {
		case 48:
			if keypress != 0 {
				exec.Command("xdotool", "keyup", "a").Run()
				exec.Command("xdotool", "keyup", "d").Run()
				keypress = 0
			}
		case 49:
			if keypress != 1 {
				exec.Command("xdotool", "keydown", "-d", "0", "a").Run()
				keypress = 1
			}
		case 50:
			if keypress != 2 {
				exec.Command("xdotool", "keydown", "-d", "0", "d").Run()
				keypress = 2
			}
		case 51:
			exec.Command("xdotool", "key", "-d", "0", "f").Run()
			exec.Command("xdotool", "keydown", "-d", "0", "a").Run()
		case 52:
			exec.Command("xdotool", "key", "-d", "0", "f").Run()
			exec.Command("xdotool", "keydown", "-d", "0", "d").Run()
		case 53:
			if keypress != 0 {
				exec.Command("xdotool", "keyup", "a").Run()
				exec.Command("xdotool", "keyup", "d").Run()
				keypress = 0
			}
			exec.Command("xdotool", "key", "-d", "0", "f").Run()
		default:
			fmt.Println("Invalid option")
		}

		defer func() {
			if err := fi.Close(); err != nil {
				panic(err)
			}
		}()
		// time.Sleep(100 * time.Millisecond)
	}
}
