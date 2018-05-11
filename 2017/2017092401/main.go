package main

import (
	"io"
	"log"
	"net/http"
)

func rootHandler(w http.ResponseWriter, r *http.Request) {
	io.WriteString(w, "こんちわ～\n")
}

func main() {
	log.Fatal(http.ListenAndServe(":8080", http.HandlerFunc(rootHandler)))
}
