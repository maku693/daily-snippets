package daily-snippets

import (
	"fmt"
	"os"
	"os/signal"
	"path"
	"runtime"
	"time"
)

func homeDir() string {
	if runtime.GOOS == "windows" {
		return os.Getenv("USERPROFILE")
	}
	return os.Getenv("HOME")
}

func main() {
	t := time.Now()

	tthist, ok := os.LookupEnv("TT_HIST_FILE")
	if !ok {
		tthist = path.Join(homeDir(), ".tthist")
	}

	if len(os.Args) != 2 {
		fmt.Println("usage: tt taskname")
		os.Exit(1)
	}

	taskname := os.Args[1]
	fmt.Printf("start tracking: %s\n", taskname)

	ch := make(chan os.Signal, 1)
	signal.Notify(ch, os.Interrupt)
	<-ch

	elapsed := time.Since(t)

	fmt.Printf("tracking finished: %s: %v\n", taskname, elapsed.Round(time.Second))

	f, err := os.OpenFile(tthist, os.O_APPEND|os.O_WRONLY|os.O_CREATE, 0600)
	defer f.Close()
	if err != nil {
		panic(err)
	}

	if _, err := f.WriteString(fmt.Sprintf("%s\t%d", taskname, elapsed.Seconds())); err != nil {
		panic(err)
	}
}
