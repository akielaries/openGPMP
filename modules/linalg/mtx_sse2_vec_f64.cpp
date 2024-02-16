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
 * Matrix Operations for SSE ISA
 *
 ************************************************************************/
#elif defined(__SSE2__)
// SSE2
#include <emmintrin.h>
#include <smmintrin.h>

/************************************************************************
 *
 * Matrix Operations on vector<vector>
 *
 ************************************************************************/

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

#endif

#endif
