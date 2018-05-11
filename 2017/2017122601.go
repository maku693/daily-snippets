package main

import "fmt"
import "math/rand"
import "strconv"
import "time"

func main() {
	s := ""
	rand.Seed(time.Now().UnixNano())
	for i := 0; i < 4; i++ {
		s += strconv.FormatUint(rand.Uint64(), 36)[0:8]
	}
	fmt.Println(s)
}
