#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

typedef char* (__stdcall *SayHelloFunc)(char*);
typedef int (__stdcall *AddFunc)(int, int);

HINSTANCE hInstLibrary;
SayHelloFunc SayHello;
AddFunc Add;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE: {
        CreateWindow("BUTTON", "Say Hello", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                     50, 50, 100, 30, hwnd, (HMENU)1, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        CreateWindow("BUTTON", "Add", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                     50, 100, 100, 30, hwnd, (HMENU)2, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        break;
    }
    case WM_COMMAND: {
        switch (LOWORD(wParam)) {
        case 1: {
            char name[] = "World";
            char* message = SayHello(name);
            MessageBox(hwnd, message, "SayHello Result", MB_OK);
            free(message);
            break;
        }
        case 2: {
            int result = Add(3, 4);
            char buffer[50];
            sprintf(buffer, "Result of Add: %d", result);
            MessageBox(hwnd, buffer, "Add Result", MB_OK);
            break;
        }
        }
        break;
    }
    case WM_DESTROY: {
        FreeLibrary(hInstLibrary);
        PostQuitMessage(0);
        break;
    }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Load the DLL
    hInstLibrary = LoadLibrary(TEXT("/Go-DLL/DLL/mydll.dll"));
    if (!hInstLibrary) {
        MessageBox(NULL, "Could not load the DLL", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    // Get the addresses of the functions
    SayHello = (SayHelloFunc)GetProcAddress(hInstLibrary, "SayHello");
    Add = (AddFunc)GetProcAddress(hInstLibrary, "Add");

    if (!SayHello || !Add) {
        MessageBox(NULL, "Could not locate the functions", "Error", MB_OK | MB_ICONERROR);
        FreeLibrary(hInstLibrary);
        return 1;
    }

    // Register the window class
    const char CLASS_NAME[] = "Sample Window Class";
    WNDCLASS wc = { 0 };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        "DLL Function Caller",          // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop
    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
