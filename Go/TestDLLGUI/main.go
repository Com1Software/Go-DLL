package main

import (
	"C"
	"fmt"
	"syscall"
	"unsafe"
)

const (
	IDYES = 6
	IDNO  = 7
)

func main() {
	// Load the DLL
	guidll, err := syscall.LoadLibrary("/Go-DLL/Go/TestDLLGUI/GUIDLL/gui.dll")
	if err != nil {
		panic(err)
	}
	defer syscall.FreeLibrary(guidll)
	dll, err := syscall.LoadLibrary("/Go-DLL/DLL/mydll.dll")
	if err != nil {
		panic(err)
	}
	defer syscall.FreeLibrary(dll)
	proc, err := syscall.GetProcAddress(dll, "SayHello")
	if err != nil {
		fmt.Println(err)
	}
	name := "The whole Big World"
	cName := syscall.StringBytePtr(name)
	ret, _, _ := syscall.Syscall(proc, 1, uintptr(unsafe.Pointer(cName)), 0, 0)
	helloMessage := C.GoString((*C.char)(unsafe.Pointer(ret)))
	fmt.Println("Returned message:", helloMessage)

	// Get a handle to the ShowMessage function
	proc, err = syscall.GetProcAddress(guidll, "ShowMessage")
	if err != nil {
		fmt.Println(err)
	}

	// Prepare the message
	message := helloMessage
	msgPtr := uintptr(unsafe.Pointer(syscall.StringBytePtr(message)))

	// Call the ShowMessage function
	ret, _, _ = syscall.Syscall(proc, 1, msgPtr, 0, 0)

	// Interpret the return value
	if ret == IDYES {
		fmt.Println("User clicked Yes")
	} else if ret == IDNO {
		fmt.Println("User clicked No")
	} else {
		fmt.Println("DLL function call failed")
	}
}
