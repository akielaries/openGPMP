#include <cblas.h>
#include <chrono>
#include <iostream>
#include <random>

const int mtx_size = 356;

void run_openblas_mtx_add();
void run_openblas_mtx_mul();

int main() {
    run_openblas_mtx_add();
    run_openblas_mtx_mul();

    return 0;
}

void run_openblas_mtx_mul() {
    // Create matrices A, B, and C
    double *A = new double[mtx_size * mtx_size];
    double *B = new double[mtx_size * mtx_size];
    double *C = new double[mtx_size * mtx_size];
    // initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribution(1.0, 100.0);

    // Initialize matrices A and B with random values
    // populate matrices A and B with random values
    for (int i = 0; i < mtx_size; ++i) {
        for (int j = 0; j < mtx_size; ++j) {
            A[i * mtx_size + j] = distribution(gen);
            B[i * mtx_size + j] = distribution(gen);
        }
    }

    // Measure the time for matrix multiplication using OpenBLAS
    auto start_std = std::chrono::high_resolution_clock::now();

    // Use OpenBLAS to multiply matrices A and B and store the result in matrix
    // C
    cblas_dgemm(CblasRowMajor,
                CblasNoTrans,
                CblasNoTrans,
                mtx_size,
                mtx_size,
                mtx_size,
                1.0,
                A,
                mtx_size,
                B,
                mtx_size,
                0.0,
                C,
                mtx_size);

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
    double *A = new double[mtx_size * mtx_size];
    double *B = new double[mtx_size * mtx_size];
    double *C = new double[mtx_size * mtx_size];

    // Initialize matrices A and B with random values
    for (int i = 0; i < mtx_size * mtx_size; ++i) {
        A[i] = rand() % 100;
        B[i] = rand() % 100;
    }

    // Measure the time for matrix addition using OpenBLAS
    // auto start_time = std::chrono::steady_clock::now();
    auto start_std = std::chrono::high_resolution_clock::now();

    // Use OpenBLAS to add matrices A and B and store the result in matrix C
    cblas_daxpy(mtx_size * mtx_size, 1.0, A, 1, C, 1);

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
