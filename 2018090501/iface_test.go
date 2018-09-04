package iface

import (
	"regexp"
	"runtime"
	"testing"
)

var methodNameRegexp *regexp.Regexp

func init() {
	var err error
	methodNameRegexp, err = regexp.Compile("s")
	if err != nil {
		panic(err)
	}
}

type mock map[string]expectation

func (m mock) Called(args ...interface{}) expectation {
	pc, _, _, _ := runtime.Caller(0)
	fname := runtime.FuncForPC(pc).Name()
	mname := methodNameRegexp.FindString(fname)
	return m[mname]
}

func (m mock) On(method string, args ...interface{}) {

}

type expectation []interface{}

func (e expectation) Return(args ...interface{}) interface{} {
	return expectation(args)
}

type impl struct {
	mock
}

func (i impl) Int() int {
	return i.mock.Called().Return(0).(int)
}

type iface interface {
	Int() int
}

func useIface(v iface) int {
	return v.Int()
}

func TestMocking(t *testing.T) {
	i := impl{}

	if useIface(i) != 42 {
		t.Fail()
	}
}
