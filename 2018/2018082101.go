package daily-snippets

import (
	"fmt"
)

interface Event {
	func Invoke()
}

struct Test {}

func (t* Test) Invoke() {
	fmt.Println("aaa")
}
