#include <windows.h>

extern "C" __declspec(dllexport) int ShowMessage(const char* message)
{
    int msgboxID = MessageBox(NULL, message, "Message", MB_YESNO | MB_ICONQUESTION);
    return msgboxID;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}