Modules
====
1. Arithmetic
2. Calculus
   - Differential
3. Linear Algebra
   - Vector Operations
   - Matrix Operations
```
    DGEMM (Double-precision General Matrix-Matrix product) 
    operations on arrays and vectors call tree:

    modules/linalg/mtx.cpp
                |
                |
    modules/linalg/dgemm_arr.cpp
                |
                |
    modules/linalg/dgemm_kernel_4x4_sse.S

```
    Where:
    - `mtx.cpp`: main interface for matrix arithmetic operations
    - `dgemm_arr.cpp`: DGEMM implementation for matrices as arrays
    - `dgemm_kernel_4x4_sse.S`: 4x4 block micro kernel SSE implementation

4. Machine/Deep Learning
   - Regression
   - Cross-Validation
   - K-Nearest Neighbors
   - Neural Networks
   - Classifiers
5. Number Theory
   - Primality Tests
   - Primality Generation
   - Integer Factorization
   - Euclidean Division
   - Logarithms
   - Greatest Common Divisors
   - Squares
   - Cryptography
6. Topology/Complex
   - Dynamical Systems
   - Topology
   - Spline
