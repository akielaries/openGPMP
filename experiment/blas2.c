#include <cblas.h>
#include <chrono>
#include <iostream>

const int matrixSize = 8192;

void run_openblas_mtx_add();

int main() {
    run_openblas_mtx_add();
    return 0;
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
    auto start_time = std::chrono::steady_clock::now();

    // Use OpenBLAS to add matrices A and B and store the result in matrix C
    cblas_daxpy(matrixSize * matrixSize, 1.0, A, 1, C, 1);

    auto end_time = std::chrono::steady_clock::now();

    // Calculate and print the elapsed time
    std::cout << "OpenBLAS - Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time - start_time)
                     .count()
              << " ms" << std::endl;

    // Cleanup
    delete[] A;
    delete[] B;
    delete[] C;
}
