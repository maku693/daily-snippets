package daily-snippets

import "time"

func main() {
	ch := make(chan struct {})
	go func() {
		ch <- time.Tick(time.Second)
	}()
	<-ch
}
