package main

import "C"

//export SayHello
func SayHello(name *C.char) *C.char {
	helloMessage := "Hello, " + C.GoString(name) + "!test123"
	return C.CString(helloMessage)
}

//export Add
func Add(a, b int) int {
	return a + b
}

func main() {}
