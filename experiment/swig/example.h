// example.h

#ifndef EXAMPLE_H
#define EXAMPLE_H

class MathOperations {
  public:
    // Overloaded methods
    int add(int a, int b);
    double add(double a, double b);

    int subtract(int a, int b);
    double subtract(double a, double b);

    int multiply(int a, int b);
    double multiply(double a, double b);

    int divide(int a, int b);
    double divide(double a, double b);

    // std mtx operations specific to the Python API
    void std_mtx_add(int *A, int *B, int *C, int rows, int cols);

    void std_mtx_add(double *A, double *B, double *C, int rows, int cols);

    void std_mtx_add(float *A, float *B, float *C, int rows, int cols);
};

#endif // EXAMPLE_H
