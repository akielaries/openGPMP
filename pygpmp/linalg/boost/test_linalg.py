import linalg
import numpy as np

mtx = linalg.Mtx()

print(type(mtx))

# Example usage for int matrices
A = np.array([1, 2, 3, 4], dtype=np.int32)
B = np.array([5, 6, 7, 8], dtype=np.int32)
C = np.zeros(4, dtype=np.int32)

rows = 2
cols = 2

mtx.mtx_add(A, B, C, rows, cols)
print(C)  # Should print [6, 8, 10, 12]


