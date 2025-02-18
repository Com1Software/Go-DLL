import ctypes

# Test message
msg = "Testing the Go DLL"
print(msg)

# Load the DLL
mydll = ctypes.WinDLL('/Go-DLL/DLL/mydll.dll')

# Define the Add function
mydll.Add.argtypes = [ctypes.c_int, ctypes.c_int]
mydll.Add.restype = ctypes.c_int

# Call the Add function
result = mydll.Add(10, 14)
print("Add result:", result)

# Define the SayHello function
mydll.SayHello.argtypes = [ctypes.c_char_p]
mydll.SayHello.restype = ctypes.c_char_p

# Call the SayHello function
input_string = "Hello from Python"
input_bytes = input_string.encode('utf-8')
resultx = mydll.SayHello(input_bytes)

# Decode the result from bytes to string
result_string = resultx.decode('utf-8')
print("SayHello result:", result_string)
