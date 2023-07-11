package main

import (
	"os"
	"os/exec"
)

func lectura() {
	// open input file
	fi, err := os.Open("./input.txt")
	if err != nil {
		panic(err)
	}
	// close fi on exit and check for its returned error
	defer func() {
		if err := fi.Close(); err != nil {
			panic(err)
		}
	}()
}

func escritura() {
	var tecla []byte = make([]byte, 1)
	// disable input buffering
	exec.Command("stty", "-F", "/dev/tty", "cbreak", "min", "1").Run()
	// do not display entered characters on the screen
	exec.Command("stty", "-F", "/dev/tty", "-echo").Run()

	// open output file
	fo, err := os.Create("./output.txt")
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
	escritura()
	defer func() {
		exec.Command("reset").Run() // Don't work
	}()
}
