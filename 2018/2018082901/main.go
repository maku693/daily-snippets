package main

import (
	"fmt"
	"strings"
	"unicode"
)

// prompt is REPL prompt text.
const prompt = "> "

func main() {
	for {
		fmt.Print(prompt)

		var in string
		fmt.Scanln(&in)

		val, err := eval(in)
		var out string
		if err != nil {
			out = err.Error()
		} else {
			out = val
		}

		fmt.Println(out)
	}
}

// eval evaluates the input string as s-expression and returns the result.
func eval(src string) (string, error) {
	scanner := NewScanner(src)

	var tokens []string
	for {
		tok, _ := scanner.Scan()
		tokens = append(tokens, tok.String())
		if tok == EOF {
			break
		}
	}

	return strings.Join(tokens, ", "), nil
}

// Token is lexical tokens of lisp.
type Token int

// The list of tokens.
const (
	// Special tokens
	ILLEGAL Token = iota
	EOF

	SYMBOL // NIL
	LPAREN // (
	RPAREN // )
	PERIOD // .
)

var tokens = [...]string{
	ILLEGAL: "ILLEGAL",
	EOF:     "EOF",

	SYMBOL: "SYMBOL",
	LPAREN: "(",
	RPAREN: ")",
	PERIOD: ".",
}

// String returns string representation of the token t.
func (t Token) String() string {
	return tokens[t]
}

// A Scanner scans s-expressions. It must be initialized via `NewScanner`.
type Scanner struct {
	src string

	r        rune
	offset   int
	rdOffset int
}

// NewScanner initialize and return a scanner for given string.
func NewScanner(src string) *Scanner {
	s := new(Scanner)
	s.src = src
	s.next()
	return s
}

// next reads the next character to s.r.
func (s *Scanner) next() {
	if s.rdOffset < len(s.src) {
		s.offset = s.rdOffset
		r := rune(s.src[s.offset])
		s.r = r
		s.rdOffset++
	} else {
		s.r = -1 // EOF
	}
}

func (s *Scanner) skipWhiteSpace() {
	for unicode.IsSpace(s.r) {
		s.next()
	}
}

func (s *Scanner) scanSymbol() string {
	offs := s.offset
	for isSymbol(s.r) {
		s.next()
	}
	return s.src[offs:s.offset]
}

func isSymbol(r rune) bool {
	return !(r == -1 || r == '(' || r == ')' || r == '.' || unicode.IsSpace(r))
}

// Scan scans the next token and returns the token and the its literal string.
// The literal string is valid only if the token is a SYMBOL.
func (s *Scanner) Scan() (tok Token, lit string) {
	s.skipWhiteSpace()

	if isSymbol(s.r) {
		tok = SYMBOL
		lit = s.scanSymbol()
	} else {
		switch s.r {
		case -1:
			tok = EOF
		case '(':
			tok = LPAREN
		case ')':
			tok = RPAREN
		case '.':
			tok = PERIOD
		default:
			tok = ILLEGAL
		}
		s.next()
	}

	return
}
