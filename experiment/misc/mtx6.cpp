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

    // Process multiple rows per iteration
    for (int i = 0; i < rows; i += 8) {
        int j = 0;
        for (; j < cols; j += 8) {
            // Load elements from A, B, and C matrices using aligned load
            __m256i a0 =
                _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&A[i][j]));
            __m256i a1 = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&A[i + 1][j]));
            __m256i a2 = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&A[i + 2][j]));
            __m256i a3 = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&A[i + 3][j]));
            __m256i a4 = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&A[i + 4][j]));
            __m256i a5 = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&A[i + 5][j]));
            __m256i a6 = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&A[i + 6][j]));
            __m256i a7 = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&A[i + 7][j]));

            __m256i b0 =
                _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&B[i][j]));
            __m256i b1 = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&B[i + 1][j]));
            __m256i b2 = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&B[i + 2][j]));
            __m256i b3 = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&B[i + 3][j]));
            __m256i b4 = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&B[i + 4][j]));
            __m256i b5 = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&B[i + 5][j]));
            __m256i b6 = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&B[i + 6][j]));
            __m256i b7 = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&B[i + 7][j]));

            __m256i c0 =
                _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&C[i][j]));
            __m256i c1 = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&C[i + 1][j]));
            __m256i c2 = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&C[i + 2][j]));
            __m256i c3 = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&C[i + 3][j]));
            __m256i c4 = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&C[i + 3][j]));
            __m256i c5 = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&C[i + 4][j]));
            __m256i c6 = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&C[i + 5][j]));
            __m256i c7 = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&C[i + 6][j]));
            __m256i c8 = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&C[i + 7][j]));

            // Perform vectorized addition
            c0 = _mm256_add_epi32(a0, b0);
            c1 = _mm256_add_epi32(a1, b1);
            c2 = _mm256_add_epi32(a2, b2);
            c3 = _mm256_add_epi32(a3, b3);
            c4 = _mm256_add_epi32(a4, b4);
            c5 = _mm256_add_epi32(a5, b5);
            c6 = _mm256_add_epi32(a6, b6);
            c7 = _mm256_add_epi32(a7, b7);

            // Store the result back to the C matrix using aligned store
            _mm256_storeu_si256(reinterpret_cast<__m256i *>(&C[i][j]), c0);
            _mm256_storeu_si256(reinterpret_cast<__m256i *>(&C[i + 1][j]), c1);
            _mm256_storeu_si256(reinterpret_cast<__m256i *>(&C[i + 2][j]), c2);
            _mm256_storeu_si256(reinterpret_cast<__m256i *>(&C[i + 3][j]), c3);
            _mm256_storeu_si256(reinterpret_cast<__m256i *>(&C[i + 4][j]), c4);
            _mm256_storeu_si256(reinterpret_cast<__m256i *>(&C[i + 5][j]), c5);
            _mm256_storeu_si256(reinterpret_cast<__m256i *>(&C[i + 6][j]), c6);
            _mm256_storeu_si256(reinterpret_cast<__m256i *>(&C[i + 7][j]), c7);
        }
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

    /*    std::cout << "Matrix A:" << std::endl;
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
