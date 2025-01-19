package main

import "C"
import "fmt"

//---------------------------------------------------------
func Add(a, b int) int {
	return a + b
}

//--------------------------------------------------------
func SayHello(name *C.char) *C.char {
	helloMessage := "Hello, " + C.GoString(name) + "!test123"
	return C.CString(helloMessage)
}

//--------------------------------------------------------
func ParseOut(data, mapdata *C.char, number C.int) *C.char {
	results := fmt.Sprintf("Data, %s! MapData: %s, Number: %d", C.GoString(data), C.GoString(mapdata), int(number))
	return C.CString(results)
}

func main() {}
