package main

import (
  "encoding/json"
  "fmt"
  "io/ioutils"
  "path/filepath"
  "os/user"
  "time"
)

type Config struct {
  StorePath string
}

type Entry struct {
  Hash string
  Name string
  StartedAt Time `json:",string"`
  EndedAt Time `json:",string"`
}

type Store struct {
  Entries []Entry
}

func configPath() string {
  return filepath.Join(user.HomeDir, ".ttconfig")
}

func loadConfig() (*File, error) {
  var user, err := user.Current()
  if err != nil {
    log.Fatal(err)
  }

  return io.ReadFile(configPath())
}

func createConfig() error {
  return io.WriteFile(configPath)
}

func loadOrCreateConfig() (*File, error) {
  if (
}

func loadStore() {
}

func updateStore() {
}

func main() {
}
