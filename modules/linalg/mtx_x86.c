#include <stdio.h>

extern void matrix_multiply(double* A, double* B, double* C, int dimension);

int main() {
    // Matrix dimensions
    int dimension = 3;

    // Allocate memory for matrices A, B, and C
    double A[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double B[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    double C[9] = {0};

    // Call the matrix multiplication routine
    matrix_multiply(A, B, C, dimension);

    // Display the result matrix C
    printf("Result Matrix C:\n");
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            printf("%f\t", C[i * dimension + j]);
        }
        printf("\n");
    }

    return 0;
}

