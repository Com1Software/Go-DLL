using System;
using System.Runtime.InteropServices;

class Program
{
    [DllImport("/Go-DLL/DLL/mydll.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr SayHello(string name);

    [DllImport("/Go-DLL/DLL/mydll.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern int Add(int a, int b);

    static void Main()
    {
        // Call the SayHello function
        string name = "From C#";
        IntPtr messagePtr = SayHello(name);
        string message = Marshal.PtrToStringAnsi(messagePtr);
        Console.WriteLine(message);
        Marshal.FreeHGlobal(messagePtr); // Free the memory allocated by the DLL

        // Call the Add function
        int result = Add(3, 4);
        Console.WriteLine("Result of Add: " + result);
    }
}
