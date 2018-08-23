package main

import (
	"fmt"
)

func main() {
	for {
		fmt.Print("> ")

		var in string
		fmt.Scanln(&in)

		val, err := eval(in)
		var out string
		if err != nil {
			out = err.Error()
		} else {
			out = val
		}

		fmt.Println(out)
	}
}

func eval(str string) (string, error) {
	return str, nil
}
