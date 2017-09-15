package main

import (
	"fmt"
)

type Enum int8

const (
	A Enum = iota
	B
	C
)

func main() {
	fmt.Println(A, B, C)
}
