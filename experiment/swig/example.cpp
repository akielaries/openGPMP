// example.cpp
#include "example.h"
#include <cstdint>

// Overloaded methods for addition
int MathOperations::add(int a, int b) {
    return a + b;
}

double MathOperations::add(double a, double b) {
    return a + b;
}

// Overloaded methods for subtraction
int MathOperations::subtract(int a, int b) {
    return a - b;
}

double MathOperations::subtract(double a, double b) {
    return a - b;
}

// Overloaded methods for multiplication
int MathOperations::multiply(int a, int b) {
    return a * b;
}

double MathOperations::multiply(double a, double b) {
    return a * b;
}

// Overloaded methods for division
int MathOperations::divide(int a, int b) {
    if (b != 0) {
        return a / b;
    } else {
        // Handle division by zero (you can throw an exception or handle it in
        // your preferred way)
        return 0;
    }
}

double MathOperations::divide(double a, double b) {
    if (b != 0.0) {
        return a / b;
    } else {
        // Handle division by zero (you can throw an exception or handle it in
        // your preferred way)
        return 0.0;
    }
}

void MathOperations::std_mtx_add(int *A, int *B, int *C, int rows, int cols) {
    // MTX A AND B MUST BE SAME SIZE
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // perform matrix addition
            C[i * cols + j] = A[i * cols + j] + B[i * cols + j];
        }
    }
}

void MathOperations::std_mtx_add(double *A,
                                 double *B,
                                 double *C,
                                 int rows,
                                 int cols) {
    // MTX A AND B MUST BE SAME SIZE
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // perform matrix addition
            C[i * cols + j] = A[i * cols + j] + B[i * cols + j];
        }
    }
}

void MathOperations::std_mtx_add(float *A,
                                 float *B,
                                 float *C,
                                 int rows,
                                 int cols) {
    // MTX A AND B MUST BE SAME SIZE
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // perform matrix addition
            C[i * cols + j] = A[i * cols + j] + B[i * cols + j];
        }
    }
}
