package main

import "testing"

type iface interface {
	Int() int
}

type impl struct {
	mock
}

func (impl) Int() int {
	return mock.Called().Return(0)
}

type expectation map[interface{}]interface{}

type mock map[string]expectation

func (m mock) Called(args... interface{}) {
	return m[]
}

func TestIfaceGeneration(t *testing.T) {

}
