/*************************************************************************
 *
 *  Project
 *                         _____ _____  __  __ _____
 *                        / ____|  __ \|  \/  |  __ \
 *  ___  _ __   ___ _ __ | |  __| |__) | \  / | |__) |
 * / _ \| '_ \ / _ \ '_ \| | |_ |  ___/| |\/| |  ___/
 *| (_) | |_) |  __/ | | | |__| | |    | |  | | |
 * \___/| .__/ \___|_| |_|\_____|_|    |_|  |_|_|
 *      | |
 *      |_|
 *
 * Copyright (C) Akiel Aries, <akiel@akiel.org>, et al.
 *
 * This software is licensed as described in the file LICENSE, which
 * you should have received as part of this distribution. The terms
 * among other details are referenced in the official documentation
 * seen here : https://akielaries.github.io/openGPMP/ along with
 * important files seen in this project.
 *
 * You may opt to use, copy, modify, merge, publish, distribute
 * and/or sell copies of the Software, and permit persons to whom
 * the Software is furnished to do so, under the terms of the
 * LICENSE file. As this is an Open Source effort, all implementations
 * must be of the same methodology.
 *
 *
 *
 * This software is distributed on an AS IS basis, WITHOUT
 * WARRANTY OF ANY KIND, either express or implied.
 *
 ************************************************************************/
#include "../../include/linalg/mtx.hpp"
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

/************************************************************************
 *
 * Matrix Operations on Arrays using Fortran Subroutines 
 * in `mtx_routines.f90`
 *
 ************************************************************************/
extern "C" {
// Matrix add routine (FLOAT)
void mtx_add_routine_float_(float *A,
                            float *B,
                            float *C,
                            std::size_t *mtx_size);
// Matrix add routine (INT)
void mtx_add_routine_int_(int *A, int *B, int *C, std::size_t *mtx_size);
}

// C++ wrapper for Fortran mtx addition subroutine FLOAT
void gpmp::linalg::Mtx::mtx_add_f90(float *A,
                                    float *B,
                                    float *C,
                                    std::size_t mtx_size) {
    mtx_add_routine_float_(A, B, C, &mtx_size);
}

// C++ wrapper for Fortran mtx addition subroutine INT
void gpmp::linalg::Mtx::mtx_add_f90(int *A,
                                    int *B,
                                    int *C,
                                    std::size_t mtx_size) {
    mtx_add_routine_int_(A, B, C, &mtx_size);
}

#if defined(__x86_64__) || defined(__amd64__) || defined(__amd64)

#if defined(__AVX2__)

// AVX family intrinsics
#include <immintrin.h>

/************************************************************************
 *
 * Matrix Operations on Arrays
 *
 ************************************************************************/

// matrix addition using Intel intrinsics, accepts integer arrays as matrices
void gpmp::linalg::Mtx::mtx_add(const int* A, const int* B, int* C, int rows, int cols) {
    // BUG FIXME: this only works with size 184+ matrices 
    if (rows > 184) {
        for (int i = 0; i < rows; ++i) {
            int j = 0;
            // requires at least size 8x8 size matrices
            for (; j < cols - 7; j += 8) {
                // load 8 elements from A, B, and C matrices using SIMD
                __m256i a = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&A[i * cols + j]));
                __m256i b = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&B[i * cols + j]));
                __m256i c = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&C[i * cols + j]));

                // perform vectorized addition and accumulate the result
                c = _mm256_add_epi32(c, _mm256_add_epi32(a, b));

                // store the result back to the C matrix
                _mm256_storeu_si256(reinterpret_cast<__m256i*>(&C[i * cols + j]), c);
            }

            // handle the remaining elements that are not multiples of 8
            for (; j < cols; ++j) {
                C[i * cols + j] = A[i * cols + j] + B[i * cols + j];
            }
        }
    }
    else {
        // use standard matrix addition
        std_mtx_add(A, B, C, rows, cols);
    }
}

// matrix addition using Intel intrinsics, accepts double arrays as matrices
void gpmp::linalg::Mtx::mtx_add(const double* A, const double* B, double* C, int rows, int cols) {
    if (rows > 8) {
        for (int i = 0; i < rows; ++i) {
            int j = 0;
            // requires at least size 4x4 size matrices
            for (; j < cols - 3; j += 4) {
                // load 4 elements from A, B, and C matrices using SIMD
                __m256d a = _mm256_loadu_pd(&A[i * cols + j]);
                __m256d b = _mm256_loadu_pd(&B[i * cols + j]);
                __m256d c = _mm256_loadu_pd(&C[i * cols + j]);
                // perform vectorized addition and accumulate the result
                c = _mm256_add_pd(a, b);

                // store the result back to the C matrix
                _mm256_storeu_pd(&C[i * cols + j], c);
            }

            // handle the remaining elements that are not multiples of 8
            for (; j < cols; ++j) {
                C[i * cols + j] = A[i * cols + j] + B[i * cols + j];
            }
        }
    }
    else {
        // use standard matrix addition
        std_mtx_add(A, B, C, rows, cols);
    }
}

// matrix addition using Intel intrinsics, accepts float arrays as matrices
void gpmp::linalg::Mtx::mtx_add(const float* A, const float* B, float* C, int rows, int cols) {
    if (rows > 16) {
        for (int i = 0; i < rows; ++i) {
            int j = 0;
            // requires at least size 4x4 size matrices
            for (; j < cols - 7; j += 8) {
                // load 4 elements from A, B, and C matrices using SIMD
                __m256 a = _mm256_loadu_ps(&A[i * cols + j]);
                __m256 b = _mm256_loadu_ps(&B[i * cols + j]);
                __m256 c = _mm256_loadu_ps(&C[i * cols + j]);
                /*
                __m256d a = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&A[i * cols + j]));
                __m256d b = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&B[i * cols + j]));
                __m256d c = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(&C[i * cols + j]));
                */
                // perform vectorized addition and accumulate the result
                c = _mm256_add_ps(a, b);

                // store the result back to the C matrix
                //_mm256_storeu_si256(reinterpret_cast<__m256i*>(&C[i * cols + j]), c);
                _mm256_storeu_ps(&C[i * cols + j], c);
            }

            // handle the remaining elements that are not multiples of 8
            for (; j < cols; ++j) {
                C[i * cols + j] = A[i * cols + j] + B[i * cols + j];
            }
        }
    }
    else {
        // use standard matrix addition
        std_mtx_add(A, B, C, rows, cols);
    }
}

/************************************************************************
 *
 * Matrix Operations on vector<vector>
 *
 ************************************************************************/
// matrix addition using Intel intrinsic, accepts integer types
void gpmp::linalg::Mtx::mtx_add(const std::vector<std::vector<int>> &A,
                                const std::vector<std::vector<int>> &B,
                                std::vector<std::vector<int>> &C) {
    const int rows = A.size();
    const int cols = A[0].size();

    if (rows > 16) {
        for (int i = 0; i < rows; ++i) {
            int j = 0;
            // requires at least size 8x8 size matrices
            for (; j < cols - 7; j += 8) {
                // load 8 elements from A, B, and C matrices using SIMD
                __m256i a = _mm256_loadu_si256(
                    reinterpret_cast<const __m256i *>(&A[i][j]));
                __m256i b = _mm256_loadu_si256(
                    reinterpret_cast<const __m256i *>(&B[i][j]));
                __m256i c = _mm256_loadu_si256(
                    reinterpret_cast<const __m256i *>(&C[i][j]));

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

    // use standard matrix addition
    else {
        std_mtx_add(A, B, C);
    }
}

// matrix addition using Intel intrinsics, accepts type double
void gpmp::linalg::Mtx::mtx_add(const std::vector<std::vector<double>> &A,
                                const std::vector<std::vector<double>> &B,
                                std::vector<std::vector<double>> &C) {
    const int rows = A.size();
    const int cols = A[0].size();

    if (rows > 8) {
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
    else {
        std_mtx_add(A, B, C);
    }
}

// matrix addition using Intel intrinsics, accepts type float
void gpmp::linalg::Mtx::mtx_add(const std::vector<std::vector<float>> &A,
                                const std::vector<std::vector<float>> &B,
                                std::vector<std::vector<float>> &C) {
    const int rows = A.size();
    const int cols = A[0].size();

    if (rows > 16) {
    for (int i = 0; i < rows; ++i) {
        int j = 0;
        // requires at least size 8x8 matrices
        for (; j < cols - 7; j += 8) {
            // load 8 elements from A, B, and C matrices using SIMD
            __m256 a = _mm256_loadu_ps(&A[i][j]);
            __m256 b = _mm256_loadu_ps(&B[i][j]);
            __m256 c = _mm256_loadu_ps(&C[i][j]);

            // perform vectorized addition
            c = _mm256_add_ps(a, b);

            // store the result back to the C matrix
            _mm256_storeu_ps(&C[i][j], c);
        }

        // handle the remaining elements that are not multiples of 8
        for (; j < cols; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    }
    else {
        std_mtx_add(A, B, C);
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

// matrix multiplication using Intel intrinsics, accepts integer types
void gpmp::linalg::Mtx::mtx_mult(const std::vector<std::vector<int>> &A,
                                 const std::vector<std::vector<int>> &B,
                                 std::vector<std::vector<int>> &C) {
    const int rows_a = A.size();
    const int cols_a = A[0].size();
    const int cols_b = B[0].size();

    for (int i = 0; i < rows_a; ++i) {
        for (int j = 0; j < cols_b; j += 8) {
            // initialize a vector of zeros for the result
            __m256i c = _mm256_setzero_si256();

            for (int k = 0; k < cols_a; ++k) {
                // load 8 elements from matrices A and B using SIMD
                __m256i a = _mm256_set1_epi32(A[i][k]);
                __m256i b = _mm256_loadu_si256(
                    reinterpret_cast<const __m256i *>(&B[k][j]));

                // perform vectorized multiplication
                __m256i prod = _mm256_mullo_epi32(a, b);

                // perform vectorized addition
                c = _mm256_add_epi32(c, prod);
            }

            // store the result back to the C matrix
            _mm256_storeu_si256(reinterpret_cast<__m256i *>(&C[i][j]), c);
        }

        // handle the remaining elements that are not multiples of 8
        for (int j = cols_b - cols_b % 8; j < cols_b; ++j) {
            int sum = 0;

            for (int k = 0; k < cols_a; ++k) {
                sum += A[i][k] * B[k][j];
            }

            C[i][j] = sum;
        }
    }
}

// matrix multiplication using Intel intrinsics, accepts double types
void gpmp::linalg::Mtx::mtx_mult(const std::vector<std::vector<double>> &A,
                                 const std::vector<std::vector<double>> &B,
                                 std::vector<std::vector<double>> &C) {
    const int rows_a = A.size();
    const int cols_a = A[0].size();
    const int cols_b = B[0].size();

    for (int i = 0; i < rows_a; ++i) {
        for (int j = 0; j < cols_b; j += 4) {
            // initialize a vector of zeros for the result
            __m256d c = _mm256_setzero_pd();

            for (int k = 0; k < cols_a; ++k) {
                // load 4 elements from matrices A and B using SIMD
                __m256d a = _mm256_set1_pd(A[i][k]);
                __m256d b = _mm256_loadu_pd(&B[k][j]);

                // perform vectorized multiplication
                __m256d prod = _mm256_mul_pd(a, b);

                // perform vectorized addition
                c = _mm256_add_pd(c, prod);
            }

            // store the result back to the C matrix
            _mm256_storeu_pd(&C[i][j], c);
        }

        // handle the remaining elements that are not multiples of 4
        for (int j = cols_b - cols_b % 4; j < cols_b; ++j) {
            double sum = 0.0;

            for (int k = 0; k < cols_a; ++k) {
                sum += A[i][k] * B[k][j];
            }

            C[i][j] = sum;
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

#elif defined(__SSE2__)
// SSE2
#include <emmintrin.h>
#include <smmintrin.h>
/************************************************************************
 *
 * Matrix Operations on Arrays
 *
 ************************************************************************/

/************************************************************************
 *
 * Matrix Operations on vector<vector>
 *
 ************************************************************************/
void gpmp::linalg::Mtx::mtx_add(const std::vector<std::vector<int>> &A,
                                const std::vector<std::vector<int>> &B,
                                std::vector<std::vector<int>> &C) {
    const int rows = A.size();
    const int cols = A[0].size();

    if (rows > 4) { // Check for at least 4x4 matrices for SSE
        for (int i = 0; i < rows; ++i) {
            int j = 0;
            // requires at least size 4x4 matrices for SSE
            for (; j < cols - 3; j += 4) {
                // load 4 elements from A, B, and C matrices using SSE
                __m128i a = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&A[i][j]));
                __m128i b = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&B[i][j]));
                __m128i c = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&C[i][j]));

                // perform vectorized addition (SSE2)
                c = _mm_add_epi32(a, b);

                // store the result back to the C matrix
                _mm_storeu_si128(reinterpret_cast<__m128i *>(&C[i][j]), c);
            }

            // handle the remaining elements that are not multiples of 4
            for (; j < cols; ++j) {
                C[i][j] = A[i][j] + B[i][j];
            }
        }
    }
    else {
        // use standard matrix addition for smaller matrices
        std_mtx_add(A, B, C);
    }
}

void gpmp::linalg::Mtx::mtx_add(const std::vector<std::vector<double>> &A,
                                const std::vector<std::vector<double>> &B,
                                std::vector<std::vector<double>> &C) {
    const int rows = A.size();
    const int cols = A[0].size();

    for (int i = 0; i < rows; ++i) {
        int j = 0;
        // requires at least size 2x2 matrices for SSE2
        for (; j < cols - 1; j += 2) {
            // load 2 elements from A, B, and C matrices using SSE2
            __m128d a = _mm_loadu_pd(&A[i][j]);
            __m128d b = _mm_loadu_pd(&B[i][j]);
            __m128d c = _mm_loadu_pd(&C[i][j]);

            // perform vectorized addition
            c = _mm_add_pd(a, b);

            // store the result back to the C matrix
            _mm_storeu_pd(&C[i][j], c);
        }

        // handle the remaining elements that are not multiples of 2
        for (; j < cols; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void gpmp::linalg::Mtx::mtx_sub(const std::vector<std::vector<int>> &A,
                                const std::vector<std::vector<int>> &B,
                                std::vector<std::vector<int>> &C) {
    const int rows = A.size();
    const int cols = A[0].size();

    for (int i = 0; i < rows; ++i) {
        int j = 0;
        // requires at least size 4x4 matrices for SSE2
        for (; j < cols - 3; j += 4) {
            // load 4 elements from A, B, and C matrices using SSE2
            __m128i a = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&A[i][j]));
            __m128i b = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&B[i][j]));
            __m128i c = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&C[i][j]));

            // perform vectorized subtraction
            c = _mm_sub_epi32(a, b);

            // store the result back to the C matrix
            _mm_storeu_si128(reinterpret_cast<__m128i *>(&C[i][j]), c);
        }

        // handle the remaining elements that are not multiples of 4
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
        // requires at least size 2x2 matrices for SSE2
        for (; j < cols - 1; j += 2) {
            // load 2 elements from A, B, and C matrices using SSE2
            __m128d a = _mm_loadu_pd(&A[i][j]);
            __m128d b = _mm_loadu_pd(&B[i][j]);
            __m128d c = _mm_loadu_pd(&C[i][j]);

            // perform vectorized subtraction
            c = _mm_sub_pd(a, b);

            // store the result back to the C matrix
            _mm_storeu_pd(&C[i][j], c);
        }

        // handle the remaining elements that are not multiples of 2
        for (; j < cols; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void gpmp::linalg::Mtx::mtx_mult(const std::vector<std::vector<int>> &A,
                                 const std::vector<std::vector<int>> &B,
                                 std::vector<std::vector<int>> &C) {
    const int rows_a = A.size();
    const int cols_a = A[0].size();
    const int cols_b = B[0].size();

    for (int i = 0; i < rows_a; ++i) {
        for (int j = 0; j < cols_b; j += 4) {
            // initialize a vector of zeros for the result
            __m128i c = _mm_setzero_si128();

            for (int k = 0; k < cols_a; ++k) {
                // load 4 elements from matrices A and B using SSE2
                __m128i a = _mm_set1_epi32(A[i][k]);
                __m128i b = _mm_loadu_si128(
                    reinterpret_cast<const __m128i *>(&B[k][j]));

                // perform vectorized multiplication
                __m128i prod = _mm_mullo_epi32(a, b);

                // perform vectorized addition
                c = _mm_add_epi32(c, prod);
            }

            // store the result back to the C matrix
            _mm_storeu_si128(reinterpret_cast<__m128i *>(&C[i][j]), c);
        }

        // handle the remaining elements that are not multiples of 4
        for (int j = cols_b - cols_b % 4; j < cols_b; ++j) {
            int sum = 0;

            for (int k = 0; k < cols_a; ++k) {
                sum += A[i][k] * B[k][j];
            }

            C[i][j] = sum;
        }
    }
}

// matrix multiplication using Intel intrinsics, accepts double types
void gpmp::linalg::Mtx::mtx_mult(const std::vector<std::vector<double>> &A,
                                 const std::vector<std::vector<double>> &B,
                                 std::vector<std::vector<double>> &C) {
    const int rows_a = A.size();
    const int cols_a = A[0].size();
    const int cols_b = B[0].size();

    for (int i = 0; i < rows_a; ++i) {
        for (int j = 0; j < cols_b; j += 2) {
            // initialize a vector of zeros for the result
            __m128d c = _mm_setzero_pd();

            for (int k = 0; k < cols_a; ++k) {
                // load 2 elements from matrices A and B using SSE2
                __m128d a = _mm_set1_pd(A[i][k]);
                __m128d b = _mm_loadu_pd(&B[k][j]);

                // perform vectorized multiplication
                __m128d prod = _mm_mul_pd(a, b);

                // perform vectorized addition
                c = _mm_add_pd(c, prod);
            }

            // store the result back to the C matrix
            _mm_storeu_pd(&C[i][j], c);
        }

        // handle the remaining elements that are not multiples of 2
        for (int j = cols_b - cols_b % 2; j < cols_b; ++j) {
            double sum = 0.0;

            for (int k = 0; k < cols_a; ++k) {
                sum += A[i][k] * B[k][j];
            }

            C[i][j] = sum;
        }
    }
}

// transpose matrices of type int using Intel intrinsics
void gpmp::linalg::Mtx::mtx_tpose(std::vector<std::vector<int>> &matrix) {
    const int rows = matrix.size();
    const int cols = matrix[0].size();

    for (int i = 0; i < rows; i += 4) {
        for (int j = i; j < cols; j += 4) {
            __m128i row1 = _mm_loadu_si128(
                reinterpret_cast<const __m128i *>(&matrix[i][j]));
            __m128i row2 = _mm_loadu_si128(
                reinterpret_cast<const __m128i *>(&matrix[i + 1][j]));
            __m128i row3 = _mm_loadu_si128(
                reinterpret_cast<const __m128i *>(&matrix[i + 2][j]));
            __m128i row4 = _mm_loadu_si128(
                reinterpret_cast<const __m128i *>(&matrix[i + 3][j]));

            __m128i tmp1, tmp2, tmp3, tmp4;

            // transpose 4x4 submatrix
            tmp1 = _mm_unpacklo_epi32(row1, row2);
            tmp2 = _mm_unpacklo_epi32(row3, row4);
            tmp3 = _mm_unpackhi_epi32(row1, row2);
            tmp4 = _mm_unpackhi_epi32(row3, row4);

            row1 = _mm_unpacklo_epi64(tmp1, tmp2);
            row2 = _mm_unpackhi_epi64(tmp1, tmp2);
            row3 = _mm_unpacklo_epi64(tmp3, tmp4);
            row4 = _mm_unpackhi_epi64(tmp3, tmp4);

            // store the transposed 4x4 submatrix back to the matrix
            _mm_storeu_si128(reinterpret_cast<__m128i *>(&matrix[i][j]), row1);
            _mm_storeu_si128(reinterpret_cast<__m128i *>(&matrix[i + 1][j]), row2);
            _mm_storeu_si128(reinterpret_cast<__m128i *>(&matrix[i + 2][j]), row3);
            _mm_storeu_si128(reinterpret_cast<__m128i *>(&matrix[i + 3][j]), row4);
        }
    }
}

// transpose matrices of type double using Intel intrinsics
void gpmp::linalg::Mtx::mtx_tpose(std::vector<std::vector<double>> &matrix) {
    const int rows = matrix.size();
    const int cols = matrix[0].size();

    for (int i = 0; i < rows; i += 2) {
        for (int j = i; j < cols; j += 2) {
            __m128d row1 = _mm_loadu_pd(&matrix[i][j]);
            __m128d row2 = _mm_loadu_pd(&matrix[i + 1][j]);

            // transpose 2x2 submatrix
            __m128d tmp1 = _mm_unpacklo_pd(row1, row2);
            __m128d tmp2 = _mm_unpackhi_pd(row1, row2);

            // store the transposed 2x2 submatrix back to the matrix
            _mm_storeu_pd(&matrix[i][j], tmp1);
            _mm_storeu_pd(&matrix[i + 1][j], tmp2);
        }
    }
}

/************************************************************************
 *
 * Matrix Operations for MMX ISA
 *
 ************************************************************************/
#elif define(__MMX__)
#include <mmintrin.h>

// SSE
#endif

// x86
#endif

/************************************************************************
 *
 * Matrix Operations for ARM NEON CPUs
 *
 ************************************************************************/
#if defined(__ARM_ARCH_ISA_A64) || defined(__ARM_NEON) ||                    \
    defined(__ARM_ARCH) || defined(__aarch64__)

// ARM intrinsic function header
#include <arm_neon.h>
/************************************************************************
 *
 * Matrix Operations on arrays
 *
 ************************************************************************/


/************************************************************************
 *
 * Matrix Operations on vector<vector> 
 *
 ************************************************************************/
// matrix addition using ARM instrinsics, accepts integer types
void gpmp::linalg::Mtx::mtx_add(const std::vector<std::vector<int>> &A,
                                const std::vector<std::vector<int>> &B,
                                std::vector<std::vector<int>> &C) {
    const int rows = A.size();
    const int cols = A[0].size();

    for (int i = 0; i < rows; ++i) {
        int j = 0;

        // requires matrices of size of at least 8x8
        for (; j < cols - 15; j += 16) {
            // Load 16 elements from A, B, and C matrices using NEON intrinsics
            int32x4x4_t a = vld1q_s32_x4(&A[i][j]);
            int32x4x4_t b = vld1q_s32_x4(&B[i][j]);

            // Perform vectorized addition
            int32x4x4_t c;
            c.val[0] = vaddq_s32(a.val[0], b.val[0]);
            c.val[1] = vaddq_s32(a.val[1], b.val[1]);
            c.val[2] = vaddq_s32(a.val[2], b.val[2]);
            c.val[3] = vaddq_s32(a.val[3], b.val[3]);

            // Store the result back to the C matrix using NEON intrinsics
            vst1q_s32_x4(&C[i][j], c);
        }

        // Handle the remaining elements that are not multiples of 16
        for (; j < cols; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// matrix addition using ARM intrinsics, accepts float types
void gpmp::linalg::Mtx::mtx_add(const std::vector<std::vector<float>> &A,
                                const std::vector<std::vector<float>> &B,
                                std::vector<std::vector<float>> &C) {
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
void gpmp::linalg::Mtx::mtx_sub(const std::vector<std::vector<float>> &A,
                                const std::vector<std::vector<float>> &B,
                                std::vector<std::vector<float>> &C) {
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

/************************************************************************
 *
 * Standard/Naive Matrix Operations on Arrays
 *
 ************************************************************************/
// naive matrix addition algorithm on arrays
template <typename T>
void gpmp::linalg::Mtx::std_mtx_add(const T *A, const T *B, T *C, int rows, int cols) {
    // MTX A AND B MUST BE SAME SIZE
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // perform matrix addition
            C[i * cols + j] = A[i * cols + j] + B[i * cols + j];
        }
    }
}

// instantiations for types accepted by templated std_mtx_add function for
// flat arrays
template void gpmp::linalg::Mtx::std_mtx_add(const int *A, const int *B, int *C, int rows, int cols);

template void gpmp::linalg::Mtx::std_mtx_add(const double *A, const double *B, double *C, int rows, int cols);

template void gpmp::linalg::Mtx::std_mtx_add(const float *A, const float *B, float *C, int rows, int cols);

/************************************************************************
 *
 * Standard/Naive Matrix Operations on vector<>
 *
 ************************************************************************/
// naive matrix addition algorithm on vector<>
template <typename T>
void gpmp::linalg::Mtx::std_mtx_add(const std::vector<T> &A,
                                    const std::vector<T> &B,
                                    std::vector<T> &C) {
    // MTX A AND B MUST BE SAME SIZE
    int rows = A.size(); 
    int cols = rows > 0 ? A.size() / rows : 0; 

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // perform matrix addition
            C[i * cols + j] = A[i * cols + j] + B[i * cols + j];
        }
    }
}

// instantiations for types accepted by templated std_mtx_add function for 
// flat vectors
template void gpmp::linalg::Mtx::std_mtx_add(const std::vector<int> &A, 
                                            const std::vector<int> &B, 
                                            std::vector<int> &C);

template void gpmp::linalg::Mtx::std_mtx_add(const std::vector<double> &A,  
                                            const std::vector<double> &B,  
                                            std::vector<double> &C); 

template void gpmp::linalg::Mtx::std_mtx_add(const std::vector<float> &A,  
                                            const std::vector<float> &B,  
                                            std::vector<float> &C); 


/************************************************************************
 *
 * Standard/Naive Matrix Operations on vector<vector>
 *
 ************************************************************************/
// naive matrix addition algorithm on vector<vector>
template <typename T>
void gpmp::linalg::Mtx::std_mtx_add(const std::vector<std::vector<T>> &A,
                                    const std::vector<std::vector<T>> &B,
                                    std::vector<std::vector<T>> &C) {
    const int size = A.size();

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            // perform matrix addition
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// instantiations for types accepted by templated std_mtx_add function
template void
gpmp::linalg::Mtx::std_mtx_add(const std::vector<std::vector<int>> &A,
                               const std::vector<std::vector<int>> &B,
                               std::vector<std::vector<int>> &C);

template void
gpmp::linalg::Mtx::std_mtx_add(const std::vector<std::vector<double>> &A,
                               const std::vector<std::vector<double>> &B,
                               std::vector<std::vector<double>> &C);

template void
gpmp::linalg::Mtx::std_mtx_add(const std::vector<std::vector<float>> &A,
                               const std::vector<std::vector<float>> &B,
                               std::vector<std::vector<float>> &C);

// naive matrix subtraction algorithm
template <typename T>
void gpmp::linalg::Mtx::std_mtx_sub(const std::vector<std::vector<T>> &A,
                                    const std::vector<std::vector<T>> &B,
                                    std::vector<std::vector<T>> &C) {
    const int size = A.size();

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            // Perform matrix subtraction
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// instantiations for types accepted by templated std_mtx_sub function
template void
gpmp::linalg::Mtx::std_mtx_sub(const std::vector<std::vector<int>> &A,
                               const std::vector<std::vector<int>> &B,
                               std::vector<std::vector<int>> &C);

template void
gpmp::linalg::Mtx::std_mtx_sub(const std::vector<std::vector<double>> &A,
                               const std::vector<std::vector<double>> &B,
                               std::vector<std::vector<double>> &C);

template void
gpmp::linalg::Mtx::std_mtx_sub(const std::vector<std::vector<float>> &A,
                               const std::vector<std::vector<float>> &B,
                               std::vector<std::vector<float>> &C);

// naive matrix multiplication algorithm
template <typename T>
void gpmp::linalg::Mtx::std_mtx_mult(const std::vector<std::vector<T>> &A,
                                     const std::vector<std::vector<T>> &B,
                                     std::vector<std::vector<T>> &C) {
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

// instantiations for types accepted by templated std_mtx_mult function
template void
gpmp::linalg::Mtx::std_mtx_mult(const std::vector<std::vector<int>> &A,
                                const std::vector<std::vector<int>> &B,
                                std::vector<std::vector<int>> &C);

template void
gpmp::linalg::Mtx::std_mtx_mult(const std::vector<std::vector<double>> &A,
                                const std::vector<std::vector<double>> &B,
                                std::vector<std::vector<double>> &C);

template void
gpmp::linalg::Mtx::std_mtx_mult(const std::vector<std::vector<float>> &A,
                                const std::vector<std::vector<float>> &B,
                                std::vector<std::vector<float>> &C);

/*
// naive implementation of Strassen matrix multiplication algorithm
void gpmp::linalg::Mtx::std_mtx_mult_strass(
    const std::vector<std::vector<int>> &A,
    const std::vector<std::vector<int>> &B, std::vector<std::vector<int>> &C) {
    int n = A.size();

    // base case: If the matrix size is 1x1, perform regular multiplication
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
    }

    // splitting the matrices into quadrants
    int half = n / 2;
    std::vector<std::vector<int>> A11(half, std::vector<int>(half));
    std::vector<std::vector<int>> A12(half, std::vector<int>(half));
    std::vector<std::vector<int>> A21(half, std::vector<int>(half));
    std::vector<std::vector<int>> A22(half, std::vector<int>(half));
    std::vector<std::vector<int>> B11(half, std::vector<int>(half));
    std::vector<std::vector<int>> B12(half, std::vector<int>(half));
    std::vector<std::vector<int>> B21(half, std::vector<int>(half));
    std::vector<std::vector<int>> B22(half, std::vector<int>(half));
    std::vector<std::vector<int>> C11(half, std::vector<int>(half));
    std::vector<std::vector<int>> C12(half, std::vector<int>(half));
    std::vector<std::vector<int>> C21(half, std::vector<int>(half));
    std::vector<std::vector<int>> C22(half, std::vector<int>(half));

    // dividing the input matrices into quadrants
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + half];
            A21[i][j] = A[i + half][j];
            A22[i][j] = A[i + half][j + half];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + half];
            B21[i][j] = B[i + half][j];
            B22[i][j] = B[i + half][j + half];
        }
    }

    // recursive calls for sub-matrix multiplication
    std::vector<std::vector<int>> M1(half, std::vector<int>(half));
    std::vector<std::vector<int>> M2(half, std::vector<int>(half));
    std::vector<std::vector<int>> M3(half, std::vector<int>(half));
    std::vector<std::vector<int>> M4(half, std::vector<int>(half));
    std::vector<std::vector<int>> M5(half, std::vector<int>(half));
    std::vector<std::vector<int>> M6(half, std::vector<int>(half));
    std::vector<std::vector<int>> M7(half, std::vector<int>(half));

    // M1 = (A11 + A22) * (B11 + B22)
    std_mtx_mult_strass(std_mtx_add(A11, A22), std_mtx_add(B11, B22), M1);
    // M2 = (A21 + A22) * B11
    std_mtx_mult_strass(std_mtx_add(A21, A22), B11, M2);
    // M3 = A11 * (B12 - B22)
    std_mtx_mult_strass(A11, std_mtx_sub(B12, B22), M3);
    // M4 = A22 * (B21 - B11)
    std_mtx_mult_strass(A22, std_mtx_sub(B21, B11), M4);
    // M5 = (A11 + A12) * B22
    std_mtx_mult_strass(std_mtx_add(A11, A12), B22, M5);
    // M6 = (A21 - A11) * (B11 + B12)
    std_mtx_mult_strass(std_mtx_sub(A21, A11), std_mtx_add(B11, B12), M6);
    // M7 = (A12 - A22) * (B21 + B22)
    std_mtx_mult_strass(std_mtx_sub(A12, A22), std_mtx_add(B21, B22), M7);

    // Computing the sub-matrices of the result matrix
    std::vector<std::vector<int>> C11_temp =

    std_mtx_add(std_mtx_sub(std_mtx_add(M1, M4), M5), M7);

    std::vector<std::vector<int>> C12_temp = std_mtx_add(M3, M5);
    std::vector<std::vector<int>> C21_temp = std_mtx_add(M2, M4);
    std::vector<std::vector<int>> C22_temp =
        std_mtx_add(std_mtx_sub(std_mtx_add(M1, M3), M2), M6);

    // Combining the sub-matrices to form the resulting matrix
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i][j] = C11_temp[i][j];
            C[i][j + half] = C12_temp[i][j];
            C[i + half][j] = C21_temp[i][j];
            C[i + half][j + half] = C22_temp[i][j];
        }
    }
}*/
