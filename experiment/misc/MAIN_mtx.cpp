#include <chrono>
#include <immintrin.h> // Include the necessary header for SIMD operations
#include <iostream>
#include <random>
#include <vector>
//
constexpr int matrixSize = 8912;

void matrixAddition_u(const std::vector<std::vector<int>> &A,
                      const std::vector<std::vector<int>> &B,
                      std::vector<std::vector<int>> &C) {
    const int rows = A.size();
    const int cols = A[0].size();

    for (int i = 0; i < rows; ++i) {
        int j = 0;
        // requires matrices of size of at least 8x8
        for (; j < cols - 7; j += 8) {
            // Load 8 elements from A, B, and C matrices using SIMD
            __m256i a =
                _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&A[i][j]));
            __m256i b =
                _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&B[i][j]));
            __m256i c =
                _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&C[i][j]));

            // Perform vectorized addition
            c = _mm256_add_epi32(a, b);

            // Store the result back to the C matrix
            _mm256_storeu_si256(reinterpret_cast<__m256i *>(&C[i][j]), c);
        }

        // Handle the remaining elements that are not multiples of 8
        for (; j < cols; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

int main() {
    std::vector<std::vector<int>> A(matrixSize, std::vector<int>(matrixSize));
    std::vector<std::vector<int>> B(matrixSize, std::vector<int>(matrixSize));
    std::vector<std::vector<int>> C(matrixSize, std::vector<int>(matrixSize));

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    // Populate matrices A and B with random values
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            A[i][j] = distribution(gen);
            B[i][j] = distribution(gen);
        }
    }

    std::chrono::steady_clock::time_point start_time_u =
        std::chrono::steady_clock::now();
    // Perform matrix addition
    matrixAddition_u(A, B, C);
    std::chrono::steady_clock::time_point end_time_u =
        std::chrono::steady_clock::now();

    /*
        std::cout << "Matrix A:" << std::endl;
        for (int i = 0; i < matrixSize; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                std::cout << A[i][j] << " ";
            }
            std::cout << std::endl;
        }

        std::cout << "Matrix B:" << std::endl;
        for (int i = 0; i < matrixSize; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                std::cout << B[i][j] << " ";
            }
            std::cout << std::endl;
        }
        // Display the result
        std::cout << "Matrix C after addition:" << std::endl;
        for (int i = 0; i < matrixSize; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                std::cout << C[i][j] << " ";
            }
            std::cout << std::endl;
        }
    */

    std::cout << "Loop Unrolling - Time elapsed: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time_u - start_time_u)
                     .count()
              << " ms" << std::endl;

    return 0;
}
