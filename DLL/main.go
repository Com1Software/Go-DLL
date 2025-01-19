package main

import "C"

// Important Note: There is an export comment line
// located above each function to make it visible in the DLL.
// Do not remove or change these comment lines.

//export SayHello
func SayHello(name *C.char) *C.char {
	helloMessage := "Hello1, " + C.GoString(name) + "!test123 "
	helloMessage = SayHelloIn(helloMessage)
	return C.CString(helloMessage)
}
func SayHelloIn(name string) string {
	helloMessage := "Hello2 from HelloIn, " + name + " Bye"
	return helloMessage
}

//export Add
func Add(a, b int) int {
	return a + b
}

func main() {}
