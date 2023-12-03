#include <chrono>
#include <cstdlib>
#include <iostream>
#include <random>

extern "C" void matrix_addition(float *A, float *B, float *C, int matrixSize);

void initialize_matrix_random(float *matrix, int matrixSize) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(1.0, 100.0);

    for (int i = 0; i < matrixSize * matrixSize; ++i) {
        matrix[i] = distribution(gen);
    }
}

void print_matrix(const char *name, float *matrix, int matrixSize) {
    std::cout << name << ":\n";
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            std::cout << matrix[i * matrixSize + j] << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int main() {
    // Matrix dimensions (assuming 4x4 matrices)
    int matrixSize = 8192;

    std::chrono::steady_clock::time_point gen_start_time =
        std::chrono::steady_clock::now();

    // Allocate memory for matrices A, B, and C
    float *A = new float[matrixSize * matrixSize];
    float *B = new float[matrixSize * matrixSize];
    float *C = new float[matrixSize * matrixSize];
    /*
    float *A = static_cast<float*>(aligned_alloc(16, matrixSize * matrixSize *
    sizeof(float))); float *B = static_cast<float*>(aligned_alloc(16, matrixSize
    * matrixSize * sizeof(float))); float *C =
    static_cast<float*>(aligned_alloc(16, matrixSize * matrixSize *
    sizeof(float)));
    */

    // Initialize matrices A and B with random values
    initialize_matrix_random(A, matrixSize);
    initialize_matrix_random(B, matrixSize);

    std::chrono::steady_clock::time_point mtx_start_time =
        std::chrono::steady_clock::now();

    // Print matrices A and B
    // print_matrix("Matrix A", A, matrixSize);
    // print_matrix("Matrix B", B, matrixSize);

    // Call the matrix addition function in assembly
    matrix_addition(A, B, C, matrixSize);

    std::chrono::steady_clock::time_point end_time =
        std::chrono::steady_clock::now();

    // Display the result matrix C
    // print_matrix("Result Matrix C", C, matrixSize);

    std::cout << "Generating random matrices (ARRAYS) - Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     mtx_start_time - gen_start_time)
                     .count()
              << " ms" << std::endl;

    std::cout << "Mtx add using ASM - Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time - mtx_start_time)
                     .count()
              << " ms" << std::endl;

    // Free allocated memory
    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}
