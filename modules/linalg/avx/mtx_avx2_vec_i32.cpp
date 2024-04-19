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

#endif

#endif
