#include <windows.h>
#include <iostream>
#include <tchar.h>

typedef char* (__stdcall *SayHelloFunc)(char*);
typedef int (__stdcall *AddFunc)(int, int);

HINSTANCE hInstLibrary;
SayHelloFunc SayHello;
AddFunc Add;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case 1: {
                    char name[] = "From G++";
                    char* message = SayHello(name);
                    MessageBox(hwnd, message, "SayHello Result", MB_OK);
                    free(message); // Free the memory allocated by the DLL
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
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Load the DLL
    hInstLibrary = LoadLibrary(TEXT("/Go-DLL/DLL/mydll.dll"));
    if (!hInstLibrary) {
        MessageBox(NULL, "Could not load the DLL", "Error", MB_OK);
        return 1;
    }

    // Get the addresses of the functions
    SayHello = (SayHelloFunc)GetProcAddress(hInstLibrary, "SayHello");
    Add = (AddFunc)GetProcAddress(hInstLibrary, "Add");

    if (!SayHello || !Add) {
        MessageBox(NULL, "Could not locate the functions", "Error", MB_OK);
        FreeLibrary(hInstLibrary);
        return 1;
    }

    // Create and register the window class
    const char CLASS_NAME[] = "Sample Window Class";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "DLL Function Calls",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Create buttons
    CreateWindow(
        "BUTTON", "SayHello",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10, 10, 100, 30,
        hwnd, (HMENU)1, hInstance, NULL
    );

    CreateWindow(
        "BUTTON", "Add",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10, 50, 100, 30,
        hwnd, (HMENU)2, hInstance, NULL
    );

    // Run the message loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Free the DLL
    FreeLibrary(hInstLibrary);

    return 0;
}
