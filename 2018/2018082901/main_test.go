package main

import (
	"testing"
)

func TestScan(t *testing.T) {
	src := "( a . ( b c ) )"
	tests := []struct {
		tok Token
		lit string
	}{
		{LPAREN, ""},
		{SYMBOL, "a"},
		{PERIOD, ""},
		{LPAREN, ""},
		{SYMBOL, "b"},
		{SYMBOL, "c"},
		{RPAREN, ""},
		{RPAREN, ""},
		{EOF, ""},
	}
	s := NewScanner(src)
	for _, test := range tests {
		tok, lit := s.Scan()
		if test.tok != tok {
			t.Errorf("token type doesn't match: expected: %s actual: %s", test.tok, tok)
		}
		if test.lit != lit {
			t.Errorf("token literal doesn't match: expected: %s actual: %s", test.lit, lit)
		}
	}
}
