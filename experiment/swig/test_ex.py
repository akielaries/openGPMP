import example
import array
import numpy as np
from ctypes import c_int, POINTER

# Create an instance of MathOperations
math_ops = example.MathOperations()

# Test the overloaded methods
print("Addition (int):", math_ops.add(5, 3))
print("Addition (double):", math_ops.add(5.5, 3.3))

print("Subtraction (int):", math_ops.subtract(5, 3))
print("Subtraction (double):", math_ops.subtract(5.5, 3.3))

print("Multiplication (int):", math_ops.multiply(5, 3))
print("Multiplication (double):", math_ops.multiply(5.5, 3.3))

print("Division (int):", math_ops.divide(10, 2))
print("Division (double):", math_ops.divide(10.0, 2.0))

# Create an instance of MathOperations
math_operations = example.MathOperations()

# Create arrays in Python
rows = 3
cols = 3

A = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9], dtype=np.int32)
B = np.array([9, 8, 7, 6, 5, 4, 3, 2, 1], dtype=np.int32)
C = np.zeros((rows, cols), dtype=np.int32)

# Call the C function using the SWIG-generated wrapper
math_operations.std_mtx_add(A, B, C, rows, cols)

# Print the result
print("Resultant C array:", C)

