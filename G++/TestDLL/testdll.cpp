#include <iostream>
#include <windows.h>

typedef char* (__stdcall *SayHelloFunc)(char*);
typedef int (__stdcall *AddFunc)(int, int);

int main() {
    // Load the DLL
    HINSTANCE hInstLibrary = LoadLibrary(TEXT("/Go-DLL/DLL/mydll.dll"));
    if (!hInstLibrary) {
        std::cerr << "Could not load the DLL" << std::endl;
        return 1;
    }

    // Get the addresses of the functions
    SayHelloFunc SayHello = (SayHelloFunc)GetProcAddress(hInstLibrary, "SayHello");
    AddFunc Add = (AddFunc)GetProcAddress(hInstLibrary, "Add");

    if (!SayHello || !Add) {
        std::cerr << "Could not locate the function" << std::endl;
        FreeLibrary(hInstLibrary);
        return 1;
    }

    // Call the SayHello function
    char name[] = "From G++";
    char* message = SayHello(name);
    std::cout << message << std::endl;
    free(message); // Free the memory allocated by the DLL

    // Call the Add function
    int result = Add(3, 4);
    std::cout << "Result of Add: " << result << std::endl;

    // Free the DLL
    FreeLibrary(hInstLibrary);
    return 0;
}
