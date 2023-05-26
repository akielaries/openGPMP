Here is a simple flow chart:

```mermaid
flowchart TD;
    J[Vect & Mtx Arith]-->A
    K[Scalar]-->A

    A{Linear Algebra Module}-->B;
    A-->D
    A-->E
    E-->F
    E-->G
    G-->I
    D-->C
    F-->H
    B[C++ Matrix template class];
    C[Fortran subroutines];
    D[Fortran C++ wrappers];
    E[GPU accl]
    F[OpenCL C++ wrappers]
    G[CUDA C++ wrappers]
    H[OpenCL C kernels]
    I[CUDA kernels]
```
