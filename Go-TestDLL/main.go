package main

import (
	"C"
	"fmt"
	"syscall"
	"unsafe"
)

func main() {
	// Load the DLL
	dll, err := syscall.LoadLibrary("/xParser-DLL-Development/DLL/mydll.dll")
	if err != nil {
		panic(err)
	}
	defer syscall.FreeLibrary(dll)

	// Get a handle to the function
	proc, err := syscall.GetProcAddress(dll, "SayHello")
	if err != nil {
		panic(err)
	}

	name := "The whole Big World"
	cName := syscall.StringBytePtr(name)
	ret, _, _ := syscall.Syscall(proc, 1, uintptr(unsafe.Pointer(cName)), 0, 0)
	helloMessage := C.GoString((*C.char)(unsafe.Pointer(ret)))
	fmt.Println("Returned message:", helloMessage)

	proc, _ = syscall.GetProcAddress(dll, "Add")
	// Call the function
	ret, _, _ = syscall.Syscall(proc, 100, 123, 455, 0)
	fmt.Println("Return value:", ret)
}
