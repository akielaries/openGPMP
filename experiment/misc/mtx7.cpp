#include <chrono>
#include <immintrin.h> // Include the necessary header for SIMD operations
#include <iostream>
#include <random>
#include <vector>
//
constexpr int matrixSize = 8912;

void matrixAddition_u(const int *A, const int *B, int *C, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        int j = 0;
        for (; j < cols - 7; j += 8) {
            __m256i a = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&A[i * cols + j]));
            __m256i b = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&B[i * cols + j]));
            __m256i c = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&C[i * cols + j]));

            c = _mm256_add_epi32(a, b);

            _mm256_storeu_si256(reinterpret_cast<__m256i *>(&C[i * cols + j]),
                                c);
        }

        for (; j < cols; ++j) {
            C[i * cols + j] = A[i * cols + j] + B[i * cols + j];
        }
    }
}

int main() {
    int *A = new int[matrixSize * matrixSize];
    int *B = new int[matrixSize * matrixSize];
    int *C = new int[matrixSize * matrixSize];

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    // Populate matrices A and B with random values
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            A[i * matrixSize + j] = distribution(gen);
            B[i * matrixSize + j] = distribution(gen);
        }
    }

    std::chrono::steady_clock::time_point start_time_u =
        std::chrono::steady_clock::now();
    // Perform matrix addition
    matrixAddition_u(A, B, C, matrixSize, matrixSize);
    std::chrono::steady_clock::time_point end_time_u =
        std::chrono::steady_clock::now();

    /*    std::cout << "Matrix A:" << std::endl;
        for (int i = 0; i < matrixSize; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                std::cout << A[i * matrixSize + j] << " ";
            }
            std::cout << std::endl;
        }

        std::cout << "Matrix B:" << std::endl;
        for (int i = 0; i < matrixSize; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                std::cout << B[i * matrixSize + j] << " ";
            }
            std::cout << std::endl;
        }

        // Display the result
        std::cout << "Matrix C after addition:" << std::endl;
        for (int i = 0; i < matrixSize; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                std::cout << C[i * matrixSize + j] << " ";
            }
            std::cout << std::endl;
        }
    */
    std::cout << "Loop Unrolling - Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time_u - start_time_u)
                     .count()
              << " ms" << std::endl;

    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}
