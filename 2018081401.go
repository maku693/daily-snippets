package main

import (
	"fmt"
	"io/ioutil"
)

func main() {
	f, err := ioutil.ReadFile("/LISENCE")
	if err != nil {
		panic(err)
	}
	fmt.Println(f)
}
