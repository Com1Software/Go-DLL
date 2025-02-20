import ctypes
import tkinter as tk
from tkinter import messagebox

# Load the DLL
mydll = ctypes.WinDLL('/Go-DLL/DLL/mydll.dll')

# Define the Add function
mydll.Add.argtypes = [ctypes.c_int, ctypes.c_int]
mydll.Add.restype = ctypes.c_int

# Define the SayHello function
mydll.SayHello.argtypes = [ctypes.c_char_p]
mydll.SayHello.restype = ctypes.c_char_p

def call_add():
    try:
        num1 = int(entry_num1.get())
        num2 = int(entry_num2.get())
        result = mydll.Add(num1, num2)
        messagebox.showinfo("Add Result", f"The result is: {result}")
    except ValueError:
        messagebox.showerror("Input Error", "Please enter valid integers.")

def call_say_hello():
    input_string = entry_message.get()
    input_bytes = input_string.encode('utf-8')
    resultx = mydll.SayHello(input_bytes)
    result_string = resultx.decode('utf-8')
    messagebox.showinfo("SayHello Result", result_string)

# Create the main window with larger size
root = tk.Tk()
root.title("Go DLL with Python GUI")
root.geometry("400x300")  # Set window size to 400x300

# Create and place widgets
tk.Label(root, text="Number 1:").grid(row=0, column=0)
entry_num1 = tk.Entry(root)
entry_num1.grid(row=0, column=1)

tk.Label(root, text="Number 2:").grid(row=1, column=0)
entry_num2 = tk.Entry(root)
entry_num2.grid(row=1, column=1)

tk.Button(root, text="Add", command=call_add).grid(row=2, columnspan=2)

tk.Label(root, text="Message:").grid(row=3, column=0)
entry_message = tk.Entry(root)
entry_message.grid(row=3, column=1)

tk.Button(root, text="SayHello", command=call_say_hello).grid(row=4, columnspan=2)

# Start the GUI event loop
root.mainloop()
