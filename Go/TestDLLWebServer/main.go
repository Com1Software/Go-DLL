package main

import (
	"C"
	"net"
	"net/http"
	"os/exec"
	"runtime"
	"syscall"
	"unsafe"

	"fmt"
	"os"
)
import "strconv"

// ----------------------------------------------------------------
func main() {
	fmt.Println("Test DLL Go Web Server")
	fmt.Printf("Operating System : %s\n", runtime.GOOS)
	xip := fmt.Sprintf("%s", GetOutboundIP())
	port := "8080"
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

	name := "The whole Big World on a Web Server"
	cName := syscall.StringBytePtr(name)
	ret, _, _ := syscall.Syscall(proc, 1, uintptr(unsafe.Pointer(cName)), 0, 0)
	helloMessage := C.GoString((*C.char)(unsafe.Pointer(ret)))

	proc, err = syscall.GetProcAddress(dll, "Add")
	if err != nil {
		fmt.Println("test exit")

		fmt.Println(err)
	}
	// Call the function
	ret, _, _ = syscall.Syscall(proc, 100, 123, 455, 0)

	a, b := 2, 3
	ret, _, _ = syscall.Syscall(proc, 2, uintptr(a), uintptr(b), 0)
	str := strconv.FormatUint(uint64(ret), 10)

	switch {
	//-------------------------------------------------------------
	case len(os.Args) == 2:

		fmt.Println("Not")

		//-------------------------------------------------------------
	default:

		fmt.Println("Server running....")

		fmt.Println("")
		http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
			xdata := InitPage(helloMessage, str)
			fmt.Fprint(w, xdata)
		})
		//------------------------------------------------- Start Server
		Openbrowser(xip + ":" + port)
		if err := http.ListenAndServe(xip+":"+port, nil); err != nil {
			panic(err)
		}
	}
}

// Openbrowser : Opens default web browser to specified url
func Openbrowser(url string) error {
	var cmd string
	var args []string
	switch runtime.GOOS {
	case "windows":
		cmd = "cmd"
		args = []string{"/c", "start msedge"}
	case "linux":
		cmd = "chromium-browser"
		args = []string{""}

	case "darwin":
		cmd = "open"
	default:
		cmd = "xdg-open"
	}
	args = append(args, url)
	return exec.Command(cmd, args...).Start()
}

func InitPage(helloMessage string, ret string) string {
	//---------------------------------------------------------------------------
	//----------------------------------------------------------------------------

	xdata := "<!DOCTYPE html>"
	xdata = xdata + "<html>"
	xdata = xdata + "<head>"
	//------------------------------------------------------------------------
	xdata = xdata + "<title>Test DLL Go Web Server</title>"
	//------------------------------------------------------------------------
	xdata = xdata + "</head>"
	//------------------------------------------------------------------------
	xdata = xdata + "<body>"
	xdata = xdata + "<H1>Test DLL Go Web Server.</H1>"
	//---------

	xdata = xdata + "<BR><BR>Test DLL Go Web Server....<BR><BR>"
	xdata = xdata + "Message back = " + helloMessage + "<BR><BR> Add value back =" + ret

	//------------------------------------------------------------------------
	xdata = xdata + " </body>"
	xdata = xdata + " </html>"
	return xdata
}

func GetOutboundIP() net.IP {
	conn, err := net.Dial("udp", "8.8.8.8:80")
	if err != nil {
		fmt.Println(err)
	}
	defer conn.Close()

	localAddr := conn.LocalAddr().(*net.UDPAddr)

	return localAddr.IP
}
