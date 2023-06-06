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

// TODO: this should be templated and possibly return a vector
// matrix addition using Intel intrinsic, accepts integer types
void gpmp::linalg::Mtx::mtx_add(const std::vector<std::vector<int>> &A,
                                const std::vector<std::vector<int>> &B,
                                std::vector<std::vector<int>> &C) {
    const int rows = A.size();
    const int cols = A[0].size();

    for (int i = 0; i < rows; ++i) {
        int j = 0;
        // requires at least size 8x8 size matrices
        for (; j < cols - 7; j += 8) {
            // load 8 elements from A, B, and C matrices using SIMD
            __m256i a =
                _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&A[i][j]));
            __m256i b =
                _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&B[i][j]));
            __m256i c =
                _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&C[i][j]));

            // perform vectorized addition
            c = _mm256_add_epi32(a, b);

            // store the result back to the C matrix
            _mm256_storeu_si256(reinterpret_cast<__m256i *>(&C[i][j]), c);
        }

        // handle the remaining elements that are not multiples of 8
        for (; j < cols; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// matrix addition using Intel intrinsics, accepts double types
void gpmp::linalg::Mtx::mtx_add(const std::vector<std::vector<double>> &A,
                                const std::vector<std::vector<double>> &B,
                                std::vector<std::vector<double>> &C) {
    const int rows = A.size();
    const int cols = A[0].size();

    for (int i = 0; i < rows; ++i) {
        int j = 0;
        // requires at least size 4x4 matrices
        for (; j < cols - 3; j += 4) {
            // load 4 elements from A, B, and C matrices using SIMD
            __m256d a = _mm256_loadu_pd(&A[i][j]);
            __m256d b = _mm256_loadu_pd(&B[i][j]);
            __m256d c = _mm256_loadu_pd(&C[i][j]);

            // perform vectorized addition
            c = _mm256_add_pd(a, b);

            // store the result back to the C matrix
            _mm256_storeu_pd(&C[i][j], c);
        }

        // handle the remaining elements that are not multiples of 4
        for (; j < cols; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// matrix subtraction using Intel intrinsics, accepts integer types
void gpmp::linalg::Mtx::mtx_sub(const std::vector<std::vector<int>> &A,
                                const std::vector<std::vector<int>> &B,
                                std::vector<std::vector<int>> &C) {
    const int rows = A.size();
    const int cols = A[0].size();

    for (int i = 0; i < rows; ++i) {
        int j = 0;
        // requires at least size 8x8 size matrices
        for (; j < cols - 7; j += 8) {
            // load 8 elements from A, B, and C matrices using SIMD
            __m256i a =
                _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&A[i][j]));
            __m256i b =
                _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&B[i][j]));
            __m256i c =
                _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&C[i][j]));

            // perform vectorized subtraction
            c = _mm256_sub_epi32(a, b);

            // store the result back to the C matrix
            _mm256_storeu_si256(reinterpret_cast<__m256i *>(&C[i][j]), c);
        }

        // handle the remaining elements that are not multiples of 8
        for (; j < cols; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// matrix subtraction using Intel intrinsics, accepts double types
void gpmp::linalg::Mtx::mtx_sub(const std::vector<std::vector<double>> &A,
                                const std::vector<std::vector<double>> &B,
                                std::vector<std::vector<double>> &C) {
    const int rows = A.size();
    const int cols = A[0].size();

    for (int i = 0; i < rows; ++i) {
        int j = 0;
        // requires at least size 4x4 matrices
        for (; j < cols - 3; j += 4) {
            // load 4 elements from A, B, and C matrices using SIMD
            __m256d a = _mm256_loadu_pd(&A[i][j]);
            __m256d b = _mm256_loadu_pd(&B[i][j]);
            __m256d c = _mm256_loadu_pd(&C[i][j]);

            // perform vectorized subtraction
            c = _mm256_sub_pd(a, b);

            // store the result back to the C matrix
            _mm256_storeu_pd(&C[i][j], c);
        }

        // handle the remaining elements that are not multiples of 4
        for (; j < cols; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// transpose matrices of type int using Intel intrinsics
void gpmp::linalg::Mtx::mtx_tpose(std::vector<std::vector<int>> &matrix) {
    const int rows = matrix.size();
    const int cols = matrix[0].size();

    for (int i = 0; i < rows; i += 8) {
        for (int j = i; j < cols; j += 8) {
            __m256i row1 = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&matrix[i][j]));
            __m256i row2 = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&matrix[i + 1][j]));
            __m256i row3 = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&matrix[i + 2][j]));
            __m256i row4 = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&matrix[i + 3][j]));
            __m256i row5 = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&matrix[i + 4][j]));
            __m256i row6 = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&matrix[i + 5][j]));
            __m256i row7 = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&matrix[i + 6][j]));
            __m256i row8 = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&matrix[i + 7][j]));

            __m256i tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8;

            // transpose 8x8 submatrix
            tmp1 = _mm256_unpacklo_epi32(row1, row2);
            tmp2 = _mm256_unpacklo_epi32(row3, row4);
            tmp3 = _mm256_unpacklo_epi32(row5, row6);
            tmp4 = _mm256_unpacklo_epi32(row7, row8);
            tmp5 = _mm256_unpackhi_epi32(row1, row2);
            tmp6 = _mm256_unpackhi_epi32(row3, row4);
            tmp7 = _mm256_unpackhi_epi32(row5, row6);
            tmp8 = _mm256_unpackhi_epi32(row7, row8);

            row1 = _mm256_unpacklo_epi64(tmp1, tmp2);
            row2 = _mm256_unpacklo_epi64(tmp3, tmp4);
            row3 = _mm256_unpackhi_epi64(tmp1, tmp2);
            row4 = _mm256_unpackhi_epi64(tmp3, tmp4);
            row5 = _mm256_unpacklo_epi64(tmp5, tmp6);
            row6 = _mm256_unpacklo_epi64(tmp7, tmp8);
            row7 = _mm256_unpackhi_epi64(tmp5, tmp6);
            row8 = _mm256_unpackhi_epi64(tmp7, tmp8);

            // store the transposed 8x8 submatrix back to the matrix
            _mm256_storeu_si256(reinterpret_cast<__m256i *>(&matrix[i][j]),
                                row1);
            _mm256_storeu_si256(reinterpret_cast<__m256i *>(&matrix[i + 1][j]),
                                row2);
            _mm256_storeu_si256(reinterpret_cast<__m256i *>(&matrix[i + 2][j]),
                                row3);
            _mm256_storeu_si256(reinterpret_cast<__m256i *>(&matrix[i + 3][j]),
                                row4);
            _mm256_storeu_si256(reinterpret_cast<__m256i *>(&matrix[i + 4][j]),
                                row5);
            _mm256_storeu_si256(reinterpret_cast<__m256i *>(&matrix[i + 5][j]),
                                row6);
            _mm256_storeu_si256(reinterpret_cast<__m256i *>(&matrix[i + 6][j]),
                                row7);
            _mm256_storeu_si256(reinterpret_cast<__m256i *>(&matrix[i + 7][j]),
                                row8);
        }
    }
}

#elif defined(__ARM_ARCH_ISA_A64) || defined(__ARM_NEON) ||                    \
    defined(__ARM_ARCH) || defined(__aarch64__)
// matrix addition using ARM instrinsics, accepts integer types
void gpmp::linalg::Mtx::mtx_add(const std::vector<std::vector<int>> &A,
                                const std::vector<std::vector<int>> &B,
                                std::vector<std::vector<int>> &C) {
    const int rows = A.size();
    const int cols = A[0].size();

    for (int i = 0; i < rows; ++i) {
        int j = 0;
        // requires matrices of size of at least 8x8
        for (; j < cols - 7; j += 8) {
            // load 8 elements from A, B, and C matrices using NEON intrinsics
            int32x4_t a_low = vld1q_s32(&A[i][j]);
            int32x4_t a_high = vld1q_s32(&A[i][j + 4]);
            int32x4_t b_low = vld1q_s32(&B[i][j]);
            int32x4_t b_high = vld1q_s32(&B[i][j + 4]);

            // perform vectorized addition
            int32x4_t c_low = vaddq_s32(a_low, b_low);
            int32x4_t c_high = vaddq_s32(a_high, b_high);

            // store the result back to the C matrix using NEON intrinsics
            vst1q_s32(&C[i][j], c_low);
            vst1q_s32(&C[i][j + 4], c_high);
        }

        // handle the remaining elements that are not multiples of 8
        for (; j < cols; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// matrix addition using ARM intrinsics, accepts double types
void gpmp::linalg::Mtx::mtx_add(const std::vector<std::vector<double>> &A,
                                const std::vector<std::vector<double>> &B,
                                std::vector<std::vector<double>> &C) {
    const int rows = A.size();
    const int cols = A[0].size();

    for (int i = 0; i < rows; ++i) {
        int j = 0;
        // requires matrices of size of at least 4x4
        for (; j < cols - 3; j += 4) {
            // load 4 elements from A, B, and C matrices using NEON intrinsics
            float32x4_t a = vld1q_f32(&A[i][j]);
            float32x4_t b = vld1q_f32(&B[i][j]);
            float32x4_t c = vld1q_f32(&C[i][j]);

            // perform vectorized addition
            c = vaddq_f32(a, b);

            // store the result back to the C matrix using NEON intrinsics
            vst1q_f32(&C[i][j], c);
        }

        // handle the remaining elements that are not multiples of 4
        for (; j < cols; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// matrix addition using ARM instrinsics, accepts integer types
void gpmp::linalg::Mtx::mtx_sub(const std::vector<std::vector<int>> &A,
                                const std::vector<std::vector<int>> &B,
                                std::vector<std::vector<int>> &C) {
    const int rows = A.size();
    const int cols = A[0].size();

    for (int i = 0; i < rows; ++i) {
        int j = 0;
        // requires matrices of size of at least 8x8
        for (; j < cols - 7; j += 8) {
            // load 8 elements from A, B, and C matrices using NEON intrinsics
            int32x4_t a_low = vld1q_s32(&A[i][j]);
            int32x4_t a_high = vld1q_s32(&A[i][j + 4]);
            int32x4_t b_low = vld1q_s32(&B[i][j]);
            int32x4_t b_high = vld1q_s32(&B[i][j + 4]);

            // perform vectorized addition
            int32x4_t c_low = vsubq_s32(a_low, b_low);
            int32x4_t c_high = vsubq_s32(a_high, b_high);

            // store the result back to the C matrix using NEON intrinsics
            vst1q_s32(&C[i][j], c_low);
            vst1q_s32(&C[i][j + 4], c_high);
        }

        // handle the remaining elements that are not multiples of 8
        for (; j < cols; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// matrix subtraction using ARM intrinsics, accepts double types
void gpmp::linalg::Mtx::mtx_sub(const std::vector<std::vector<double>> &A,
                                const std::vector<std::vector<double>> &B,
                                std::vector<std::vector<double>> &C) {
    const int rows = A.size();
    const int cols = A[0].size();

    for (int i = 0; i < rows; ++i) {
        int j = 0;
        // requires matrices of size of at least 4x4
        for (; j < cols - 3; j += 4) {
            // load 4 elements from A, B, and C matrices using NEON intrinsics
            float32x4_t a = vld1q_f32(&A[i][j]);
            float32x4_t b = vld1q_f32(&B[i][j]);
            float32x4_t c = vld1q_f32(&C[i][j]);

            // perform vectorized subtraction
            c = vsubq_f32(a, b);

            // store the result back to the C matrix using NEON intrinsics
            vst1q_f32(&C[i][j], c);
        }

        // handle the remaining elements that are not multiples of 4
        for (; j < cols; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// transpose matrices of type int using ARM intrinsics
void gpmp::linalg::Mtx::mtx_tpose(std::vector<std::vector<int>> &matrix) {
    const int rows = matrix.size();
    const int cols = matrix[0].size();

    for (int i = 0; i < rows; i += 8) {
        for (int j = i; j < cols; j += 8) {
            int32x4x2_t row1 = vld2q_s32(&matrix[i][j]);
            int32x4x2_t row2 = vld2q_s32(&matrix[i + 1][j]);
            int32x4x2_t row3 = vld2q_s32(&matrix[i + 2][j]);
            int32x4x2_t row4 = vld2q_s32(&matrix[i + 3][j]);
            int32x4x2_t row5 = vld2q_s32(&matrix[i + 4][j]);
            int32x4x2_t row6 = vld2q_s32(&matrix[i + 5][j]);
            int32x4x2_t row7 = vld2q_s32(&matrix[i + 6][j]);
            int32x4x2_t row8 = vld2q_s32(&matrix[i + 7][j]);

            // transpose 8x8 submatrix
            std::swap(row1.val[1], row2.val[0]);
            std::swap(row3.val[1], row4.val[0]);
            std::swap(row5.val[1], row6.val[0]);
            std::swap(row7.val[1], row8.val[0]);
            std::swap(row1.val[2], row3.val[0]);
            std::swap(row5.val[2], row7.val[0]);
            std::swap(row2.val[2], row4.val[0]);
            std::swap(row6.val[2], row8.val[0]);
            std::swap(row1.val[3], row5.val[0]);
            std::swap(row2.val[3], row6.val[0]);
            std::swap(row3.val[3], row7.val[0]);
            std::swap(row4.val[3], row8.val[0]);
            std::swap(row5.val[3], row7.val[2]);
            std::swap(row6.val[3], row8.val[2]);

            // store the transposed 8x8 submatrix back to the matrix
            vst2q_s32(&matrix[i][j], row1);
            vst2q_s32(&matrix[i + 1][j], row2);
            vst2q_s32(&matrix[i + 2][j], row3);
            vst2q_s32(&matrix[i + 3][j], row4);
            vst2q_s32(&matrix[i + 4][j], row5);
            vst2q_s32(&matrix[i + 5][j], row6);
            vst2q_s32(&matrix[i + 6][j], row7);
            vst2q_s32(&matrix[i + 7][j], row8);
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

// naive matrix subtraction algorithm
void gpmp::linalg::Mtx::std_mtx_sub(const std::vector<std::vector<int>> &A,
                                    const std::vector<std::vector<int>> &B,
                                    std::vector<std::vector<int>> &C) {
    const int size = A.size();

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            // Perform matrix subtraction
            C[i][j] = A[i][j] - B[i][j];
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
