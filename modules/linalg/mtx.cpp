#include "../../include/linalg/mtx.hpp"
#include <cassert>
#include <chrono>
#include <cstdint>

// if sys is Intel-based
#if defined(__x86_64__) || defined(i386) || defined(__i386__) ||               \
    defined(__i386) || defined(__amd64__) || defined(__amd64)
// include Intel intrinsics
#include <immintrin.h>

// if sys is ARM-based
#elif defined(__ARM_ARCH_ISA_A64) || defined(__ARM_NEON) ||                    \
    defined(__ARM_ARCH) || defined(__aarch64__)
// include ARM intrinsics
#include <arm_neon.h>

#endif

#include <iostream>
#include <random>
#include <vector>

/*void mult();
void add();

extern "C" {
void mtx_add_(double *a, double *b, double *c, int64_t *nrows, int64_t *ncols);
void mtx_mult_(float *matrix1, float *matrix2, float *res, int *nrows1,
               int *ncols1, int *ncols2);
}*/

// for testing matrix sizes
constexpr int matrixSize = 32;

#if defined(__x86_64__) || defined(i386) || defined(__i386__) ||               \
    defined(__i386) || defined(__amd64__) || defined(__amd64)

// matrix addition using intrinsic functions
// TODO: this should be templated and possibly return a vector
void gpmp::linalg::Mtx::mtx_add(const std::vector<std::vector<int>> &A,
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

#elif defined(__ARM_ARCH_ISA_A64) || defined(__ARM_NEON) ||                    \
    defined(__ARM_ARCH) || defined(__aarch64__)

void gpmp::linalg::Mtx::mtx_add(const std::vector<std::vector<int>> &A,
                           const std::vector<std::vector<int>> &B,
                           std::vector<std::vector<int>> &C) {
    const int rows = A.size();
    const int cols = A[0].size();

    for (int i = 0; i < rows; ++i) {
        int j = 0;
        // requires matrices of size of at least 8x8
        for (; j < cols - 7; j += 8) {
            // Load 8 elements from A, B, and C matrices using NEON intrinsics
            int32x4_t a_low = vld1q_s32(&A[i][j]);
            int32x4_t a_high = vld1q_s32(&A[i][j + 4]);
            int32x4_t b_low = vld1q_s32(&B[i][j]);
            int32x4_t b_high = vld1q_s32(&B[i][j + 4]);

            // Perform vectorized addition
            int32x4_t c_low = vaddq_s32(a_low, b_low);
            int32x4_t c_high = vaddq_s32(a_high, b_high);

            // Store the result back to the C matrix using NEON intrinsics
            vst1q_s32(&C[i][j], c_low);
            vst1q_s32(&C[i][j + 4], c_high);
        }

        // Handle the remaining elements that are not multiples of 8
        for (; j < cols; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

#endif

// naive matrix addition algorithm
void gpmp::linalg::Mtx::std_mtx_add(const std::vector<std::vector<int>> &A, 
                      const std::vector<std::vector<int>> &B, 
                      std::vector<std::vector<int>> &C) {
    const int size = A.size();

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            // Perform matrix addition
            C[i][j] = A[i][j] + B[i][j];
        }
    }   
}


// naive matrix multiplication algorithm
void gpmp::linalg::Mtx::std_mtx_mult(const std::vector<std::vector<int>> &A,
                           const std::vector<std::vector<int>> &B,
                           std::vector<std::vector<int>> &C) {
    assert(A.size() == B.size());
    assert(A[0].size() == B[0].size());

    int64_t nrows = A.size();
    int64_t ncols = A[0].size();

    for (int64_t i = 0; i < nrows; ++i) {
        for (int64_t j = 0; j < ncols; ++j) {
            C[i][j] = 0.0;
            for (int64_t k = 0; k < ncols; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void run_mtx_add() {
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
    gpmp::linalg::Mtx mtx;
    mtx.mtx_add(A, B, C);
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
}

