package main

import (
	"C"
	"fmt"
	"syscall"
)
import "unsafe"

func main() {
	// Load the DLL
	dll, err := syscall.LoadLibrary("/Go-DLL/DLL/mydll.dll")
	if err != nil {
		panic(err)
	}
	defer syscall.FreeLibrary(dll)
	//Get a handle to the function
	proc, err := syscall.GetProcAddress(dll, "SayHello")
	if err != nil {
		fmt.Println(err)
	}

	name := "The whole Big World"
	cName := syscall.StringBytePtr(name)
	ret, _, _ := syscall.Syscall(proc, 1, uintptr(unsafe.Pointer(cName)), 0, 0)
	helloMessage := C.GoString((*C.char)(unsafe.Pointer(ret)))
	fmt.Println("Returned message:", helloMessage)

	proc, err = syscall.GetProcAddress(dll, "Add")
	if err != nil {
		fmt.Println("test exit")

		fmt.Println(err)
	}
	// Call the function
	ret, _, _ = syscall.Syscall(proc, 100, 123, 455, 0)
	fmt.Println("Return value:", ret)

	a, b := 2, 3
	ret, _, _ = syscall.Syscall(proc, 2, uintptr(a), uintptr(b), 0)
	fmt.Println("Result:", int(ret))
}
