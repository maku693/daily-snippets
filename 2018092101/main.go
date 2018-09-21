package main

import (
	"database/sql"
)

func main() {
	db, err := sql.Open("mysql", "")
	if err != nil {
		panic(err)
	}
	rows, err := db.Query("SELECT * FROM table")
	defer rows.Close()
}
