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

#if defined(__x86_64__) || defined(__amd64__) || defined(__amd64)

/************************************************************************
 *
 * Matrix Operations for AVX ISA
 *
 ************************************************************************/
#if defined(__AVX2__)

// AVX family intrinsics
#include <immintrin.h>

/************************************************************************
 *
 * Matrix Operations on vector<vector>
 *
 ************************************************************************/
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
    } else {
        std_mtx_add(A, B, C);
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

void gpmp::linalg::Mtx::mtx_tpose(std::vector<std::vector<double>> &matrix) {
    const int rows = matrix.size();
    const int cols = matrix[0].size();

    for (int i = 0; i < rows; i += 4) {
        for (int j = i; j < cols; j += 4) {
            __m256d row1 = _mm256_loadu_pd(&matrix[i][j]);
            __m256d row2 = _mm256_loadu_pd(&matrix[i + 1][j]);
            __m256d row3 = _mm256_loadu_pd(&matrix[i + 2][j]);
            __m256d row4 = _mm256_loadu_pd(&matrix[i + 3][j]);

            __m256d tmp1, tmp2, tmp3, tmp4;

            // Transpose 4x4 submatrix
            tmp1 = _mm256_unpacklo_pd(row1, row2);
            tmp2 = _mm256_unpackhi_pd(row1, row2);
            tmp3 = _mm256_unpacklo_pd(row3, row4);
            tmp4 = _mm256_unpackhi_pd(row3, row4);

            row1 = _mm256_permute2f128_pd(tmp1, tmp3, 0x20);
            row2 = _mm256_permute2f128_pd(tmp2, tmp4, 0x20);
            row3 = _mm256_permute2f128_pd(tmp1, tmp3, 0x31);
            row4 = _mm256_permute2f128_pd(tmp2, tmp4, 0x31);

            // Store the transposed 4x4 submatrix back to the matrix
            _mm256_storeu_pd(&matrix[i][j], row1);
            _mm256_storeu_pd(&matrix[i + 1][j], row2);
            _mm256_storeu_pd(&matrix[i + 2][j], row3);
            _mm256_storeu_pd(&matrix[i + 3][j], row4);
        }
    }
}

#endif

#endif
