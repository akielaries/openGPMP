Modules
====
* Core
    - DataTable
    - Threads
    - Logging
    - Misc. Utils
* Arithmetic
* Calculus
    - Differential
    - Numerical Analysis
    - Integral ***TODO***
* Discrete
    - Graphs
* Linear Algebra
    - Linear Systems
    - Eigenvalues & Operations
    - Singular Value Decomposition (SVD)
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
    * `mtx.cpp`: main interface for matrix arithmetic operations
    * `dgemm_arr.cpp`: DGEMM implementation for matrices as arrays
    * `dgemm_kernel_4x4_sse.S`: 4x4 block micro kernel SSE implementation
    - Tensor Operations ***TODO***

* Machine/Deep Learning
    - Activations
    - Bayes Classifier
    - Bayes Network
    - Encoders
    - Kohonen Network (SEO)
    - Linear Regression
    - Logistic Regression
    - Cross-Validation
    - K-Nearest Neighbors
    - Multi-Layer Perceptron
    - Regularizers
    - Support Vector Machine
    - Trainers

* Number Theory
    - Primality Tests
    - Primality Generation
    - Integer Factorization
    - Euclidean Division
    - Logarithms
    - Greatest Common Divisors
    - Squares
    - Randomization
    - RC4, RC5, RC6

* Optimization
    - Quasi-Newton Methods
    - Functions

* Statistics
    - Descriptive
    - Probility Distribution

* Topology/Complex ***TODO***
    - Dynamical Systems
    - Topology
    - Spline
