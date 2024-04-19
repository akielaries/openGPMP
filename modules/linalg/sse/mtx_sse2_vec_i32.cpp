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
#include "../../../include/linalg/mtx.hpp"
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
#if defined(__SSE2__)
// SSE2
#include <emmintrin.h>
#include <smmintrin.h>

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
                __m128i a = _mm_loadu_si128(
                    reinterpret_cast<const __m128i *>(&A[i][j]));
                __m128i b = _mm_loadu_si128(
                    reinterpret_cast<const __m128i *>(&B[i][j]));
                __m128i c = _mm_loadu_si128(
                    reinterpret_cast<const __m128i *>(&C[i][j]));

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
    } else {
        // use standard matrix addition for smaller matrices
        std_mtx_add(A, B, C);
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
            __m128i a =
                _mm_loadu_si128(reinterpret_cast<const __m128i *>(&A[i][j]));
            __m128i b =
                _mm_loadu_si128(reinterpret_cast<const __m128i *>(&B[i][j]));
            __m128i c =
                _mm_loadu_si128(reinterpret_cast<const __m128i *>(&C[i][j]));

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
            _mm_storeu_si128(reinterpret_cast<__m128i *>(&matrix[i + 1][j]),
                             row2);
            _mm_storeu_si128(reinterpret_cast<__m128i *>(&matrix[i + 2][j]),
                             row3);
            _mm_storeu_si128(reinterpret_cast<__m128i *>(&matrix[i + 3][j]),
                             row4);
        }
    }
}

#endif

#endif
