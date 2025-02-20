#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef char* (__stdcall *SayHelloFunc)(char*);
typedef int (__stdcall *AddFunc)(int, int);

int main() {
    // Load the DLL
    HINSTANCE hInstLibrary = LoadLibrary(TEXT("mydll.dll"));
    if (!hInstLibrary) {
        fprintf(stderr, "Could not load the DLL\n");
        return 1;
    }

    // Get the addresses of the functions
    SayHelloFunc SayHello = (SayHelloFunc)GetProcAddress(hInstLibrary, "SayHello");
    AddFunc Add = (AddFunc)GetProcAddress(hInstLibrary, "Add");

    if (!SayHello || !Add) {
        fprintf(stderr, "Could not locate the function\n");
        FreeLibrary(hInstLibrary);
        return 1;
    }

    // Call the SayHello function
    char name[] = "World";
    char* message = SayHello(name);
    printf("%s\n", message);
    free(message); // Free the memory allocated by the DLL

    // Call the Add function
    int result = Add(3, 4);
    printf("Result of Add: %d\n", result);

    // Free the DLL
    FreeLibrary(hInstLibrary);
    return 0;
}
