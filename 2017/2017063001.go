package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"log"
	"os"
	"os/user"
	"path/filepath"
	"time"
)

const configTemplate = `{
	StorePath: "%s/.tt/store"
}`

type Config struct {
	StorePath string
}

type Entry struct {
	Hash      string
	Name      string
	StartedAt time.Time `json:",string"`
	EndedAt   time.Time `json:",string"`
}

type Store struct {
	Entries []Entry
}

func configPath(user *user.User) string {
	return filepath.Join(user.HomeDir, ".tt/config")
}

func loadConfigFile(user *user.User) ([]byte, error) {
	return ioutil.ReadFile(configPath(user))
}

func createConfigFile(user *user.User) error {
	configContent := fmt.Sprintf(configTemplate, user.HomeDir)
	return ioutil.WriteFile(configPath(user), []byte(configContent), 0644)
}

func loadOrCreateConfigFile(user *user.User) ([]byte, error) {
	// Create the config file if it isn't exist
	if _, err := os.Stat(configPath(user)); os.IsNotExist(err) {
		err = createConfigFile(user)
		if err != nil {
			return nil, err
		}
	} else if err != nil {
		return nil, err
	}

	file, err := loadConfigFile(user)
	if err != nil {
		return nil, err
	}

	return file, nil
}

func getConfig(user *user.User) (*Config, error) {
	file, err := loadOrCreateConfigFile(user)
	if err != nil {
		return nil, err
	}

	var config Config
	if err := json.Unmarshal(file, &config); err != nil {
		return nil, err
	}

	return &config, nil
}

func loadStore() {
}

func updateStore() {
}

func main() {
	user, err := user.Current()
	if err != nil {
		log.Fatal(err)
	}

	config, err := getConfig(user)
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("%v", config)
}
