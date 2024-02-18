#include <cblas.h>
#include <chrono>
#include <iostream>

const int matrixSize = 1024;

void run_openblas_mtx_add();
void run_openblas_mtx_mul();

int main() {
    run_openblas_mtx_add();
    run_openblas_mtx_mul();

    return 0;
}

void run_openblas_mtx_mul() {
    // Create matrices A, B, and C
    double *A = new double[matrixSize * matrixSize];
    double *B = new double[matrixSize * matrixSize];
    double *C = new double[matrixSize * matrixSize];

    // Initialize matrices A and B with random values
    for (int i = 0; i < matrixSize * matrixSize; ++i) {
        A[i] = rand() % 100;
        B[i] = rand() % 100;
    }

    // Measure the time for matrix multiplication using OpenBLAS
    auto start_std = std::chrono::high_resolution_clock::now();

    // Use OpenBLAS to multiply matrices A and B and store the result in matrix
    // C
    cblas_dgemm(CblasRowMajor,
                CblasNoTrans,
                CblasNoTrans,
                matrixSize,
                matrixSize,
                matrixSize,
                1.0,
                A,
                matrixSize,
                B,
                matrixSize,
                0.0,
                C,
                matrixSize);

    auto end_std = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_seconds_std = end_std - start_std;

    // Calculate and print the elapsed time
    std::cout << "Matrix multiplication using OpenBLAS took "
              << elapsed_seconds_std.count() << " seconds." << std::endl;

    // Cleanup
    delete[] A;
    delete[] B;
    delete[] C;
}

void run_openblas_mtx_add() {
    // Create matrices A, B, and C
    double *A = new double[matrixSize * matrixSize];
    double *B = new double[matrixSize * matrixSize];
    double *C = new double[matrixSize * matrixSize];

    // Initialize matrices A and B with random values
    for (int i = 0; i < matrixSize * matrixSize; ++i) {
        A[i] = rand() % 100;
        B[i] = rand() % 100;
    }

    // Measure the time for matrix addition using OpenBLAS
    // auto start_time = std::chrono::steady_clock::now();
    auto start_std = std::chrono::high_resolution_clock::now();

    // Use OpenBLAS to add matrices A and B and store the result in matrix C
    cblas_daxpy(matrixSize * matrixSize, 1.0, A, 1, C, 1);

    // auto end_time = std::chrono::steady_clock::now();
    auto end_std = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_seconds_std = end_std - start_std;

    // Calculate and print the elapsed time
    std::cout << "TIME-ELAPSED: " << elapsed_seconds_std.count() << "seconds"
              << std::endl;

    // Cleanup
    delete[] A;
    delete[] B;
    delete[] C;
}
