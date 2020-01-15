package main

import (
	"encoding/base32"
	"encoding/base64"
	"fmt"
	"log"

	"github.com/google/uuid"
)

func init() {
	log.SetFlags(0)
}

func main() {
	u := uuid.New()
	b, err := u.MarshalBinary()
	if err != nil {
		log.Fatalln(err)
	}

	prints := [...]struct {
		Name  string
		Value string
	}{
		{"original", u.String()},
		{"base32.StdEncoding", base32.StdEncoding.EncodeToString(b)},
		{"base32.StdEncoding.WithPadding(base32.NoPadding)", base32.StdEncoding.WithPadding(base32.NoPadding).EncodeToString(b)},
		{"base32.HexEncoding", base32.HexEncoding.EncodeToString(b)},
		{"base32.HexEncoding.WithPadding(base32.NoPadding)", base32.HexEncoding.WithPadding(base32.NoPadding).EncodeToString(b)},
		{"base64.StdEncoding", base64.StdEncoding.EncodeToString(b)},
		{"base64.RawStdEncoding", base64.RawStdEncoding.EncodeToString(b)},
		{"base64.URLEncoding", base64.URLEncoding.EncodeToString(b)},
		{"base64.RawURLEncoding", base64.RawURLEncoding.EncodeToString(b)},
	}

	for _, print := range prints {
		fmt.Printf("%s:\t%s\t%d\n", print.Name, print.Value, len(print.Value))
	}
}
