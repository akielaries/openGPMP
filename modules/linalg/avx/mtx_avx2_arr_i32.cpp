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
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <openGPMP/linalg/mtx.hpp>
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
 * Matrix Operations on Arrays
 *
 ************************************************************************/

// matrix addition using Intel intrinsics, accepts integer arrays as matrices
void gpmp::linalg::Mtx::mtx_add(const int *A,
                                const int *B,
                                int *C,
                                int rows,
                                int cols) {
    // BUG FIXME: this only works with size 184+ matrices
    if (rows > 184) {
        for (int i = 0; i < rows; ++i) {
            int j = 0;
            // requires at least size 8x8 size matrices
            for (; j < cols - 7; j += 8) {
                // load 8 elements from A, B, and C matrices using SIMD
                __m256i a = _mm256_loadu_si256(
                    reinterpret_cast<const __m256i *>(&A[i * cols + j]));
                __m256i b = _mm256_loadu_si256(
                    reinterpret_cast<const __m256i *>(&B[i * cols + j]));
                __m256i c = _mm256_loadu_si256(
                    reinterpret_cast<const __m256i *>(&C[i * cols + j]));

                // perform vectorized addition and accumulate the result
                c = _mm256_add_epi32(c, _mm256_add_epi32(a, b));

                // store the result back to the C matrix
                _mm256_storeu_si256(
                    reinterpret_cast<__m256i *>(&C[i * cols + j]),
                    c);
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

void gpmp::linalg::Mtx::mtx_sub(const int *A,
                                const int *B,
                                int *C,
                                int rows,
                                int cols) {
    for (int i = 0; i < rows; ++i) {
        int j = 0;
        for (; j < cols - 7; j += 8) {
            __m256i a = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&A[i * cols + j]));
            __m256i b = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&B[i * cols + j]));
            __m256i c = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&C[i * cols + j]));

            // Perform vectorized subtraction and accumulate the result
            c = _mm256_sub_epi32(a, b);

            // Store the result back to the C matrix
            _mm256_storeu_si256(reinterpret_cast<__m256i *>(&C[i * cols + j]),
                                c);
        }

        for (; j < cols; ++j) {
            C[i * cols + j] = A[i * cols + j] - B[i * cols + j];
        }
    }
}

void gpmp::linalg::Mtx::mtx_mult(const int *A,
                                 const int *B,
                                 int *C,
                                 int rows_a,
                                 int cols_a,
                                 int cols_b) {
    for (int i = 0; i < rows_a; ++i) {
        for (int j = 0; j < cols_b; j += 8) {
            __m256i c = _mm256_setzero_si256();

            for (int k = 0; k < cols_a; ++k) {
                __m256i a = _mm256_set1_epi32(A[i * cols_a + k]);
                __m256i b = _mm256_loadu_si256(
                    reinterpret_cast<const __m256i *>(&B[k * cols_b + j]));

                __m256i prod = _mm256_mullo_epi32(a, b);
                c = _mm256_add_epi32(c, prod);
            }

            _mm256_storeu_si256(reinterpret_cast<__m256i *>(&C[i * cols_b + j]),
                                c);
        }

        // Handle remaining elements
        for (int j = cols_b - cols_b % 8; j < cols_b; ++j) {
            int sum = 0;

            for (int k = 0; k < cols_a; ++k) {
                sum += A[i * cols_a + k] * B[k * cols_b + j];
            }

            C[i * cols_b + j] = sum;
        }
    }
}

void gpmp::linalg::Mtx::mtx_mult(const int *A,
                                 const int *B,
                                 int64_t *C,
                                 int rows_a,
                                 int cols_a,
                                 int cols_b) {

    for (int i = 0; i < rows_a; ++i) {
        for (int j = 0; j < cols_b; j += 4) {
            __m256i c_lo = _mm256_setzero_si256();
            __m256i c_hi = _mm256_setzero_si256();

            for (int k = 0; k < cols_a; ++k) {
                __m256i a = _mm256_set1_epi32(A[i * cols_a + k]);
                __m256i b = _mm256_loadu_si256(
                    reinterpret_cast<const __m256i *>(&B[k * cols_b + j]));

                // Perform 32-bit integer multiplication
                __m256i prod = _mm256_mullo_epi32(a, b);

                // Extract low and high 32-bit integers
                __m256i prod_lo =
                    _mm256_cvtepi32_epi64(_mm256_extractf128_si256(prod, 0));
                __m256i prod_hi =
                    _mm256_cvtepi32_epi64(_mm256_extractf128_si256(prod, 1));

                // Add to the accumulator
                c_lo = _mm256_add_epi64(c_lo, prod_lo);
                c_hi = _mm256_add_epi64(c_hi, prod_hi);
            }

            // Store the result back to the C matrix
            _mm256_storeu_si256(reinterpret_cast<__m256i *>(&C[i * cols_b + j]),
                                c_lo);
            _mm256_storeu_si256(
                reinterpret_cast<__m256i *>(&C[i * cols_b + j + 4]),
                c_hi);
        }

        // Handle remaining elements
        for (int j = cols_b - cols_b % 4; j < cols_b; ++j) {
            int64_t sum = 0;

            for (int k = 0; k < cols_a; ++k) {
                sum +=
                    static_cast<int64_t>(A[i * cols_a + k]) * B[k * cols_b + j];
            }

            C[i * cols_b + j] = sum;
        }
    }
}

void gpmp::linalg::Mtx::mtx_tpose(const int *A, int *C, int rows, int cols) {
    // Transpose 8x8 blocks using AVX2 intrinsics
    for (int i = 0; i < rows; i += 8) {
        for (int j = 0; j < cols; j += 8) {
            // Load 8x8 block from A
            __m256i a0 = _mm256_loadu_si256(
                (__m256i *)(const_cast<int *>(A) + i * cols + j));
            __m256i a1 = _mm256_loadu_si256(
                (__m256i *)(const_cast<int *>(A) + (i + 1) * cols + j));
            __m256i a2 = _mm256_loadu_si256(
                (__m256i *)(const_cast<int *>(A) + (i + 2) * cols + j));
            __m256i a3 = _mm256_loadu_si256(
                (__m256i *)(const_cast<int *>(A) + (i + 3) * cols + j));
            __m256i a4 = _mm256_loadu_si256(
                (__m256i *)(const_cast<int *>(A) + (i + 4) * cols + j));
            __m256i a5 = _mm256_loadu_si256(
                (__m256i *)(const_cast<int *>(A) + (i + 5) * cols + j));
            __m256i a6 = _mm256_loadu_si256(
                (__m256i *)(const_cast<int *>(A) + (i + 6) * cols + j));
            __m256i a7 = _mm256_loadu_si256(
                (__m256i *)(const_cast<int *>(A) + (i + 7) * cols + j));

            // Transpose 8x8 block
            __m256i t0 = _mm256_unpacklo_epi32(a0, a1);
            __m256i t1 = _mm256_unpacklo_epi32(a2, a3);
            __m256i t2 = _mm256_unpacklo_epi32(a4, a5);
            __m256i t3 = _mm256_unpacklo_epi32(a6, a7);
            __m256i t4 = _mm256_unpackhi_epi32(a0, a1);
            __m256i t5 = _mm256_unpackhi_epi32(a2, a3);
            __m256i t6 = _mm256_unpackhi_epi32(a4, a5);
            __m256i t7 = _mm256_unpackhi_epi32(a6, a7);

            __m256i tt0 = _mm256_unpacklo_epi64(t0, t1);
            __m256i tt1 = _mm256_unpackhi_epi64(t0, t1);
            __m256i tt2 = _mm256_unpacklo_epi64(t2, t3);
            __m256i tt3 = _mm256_unpackhi_epi64(t2, t3);
            __m256i tt4 = _mm256_unpacklo_epi64(t4, t5);
            __m256i tt5 = _mm256_unpackhi_epi64(t4, t5);
            __m256i tt6 = _mm256_unpacklo_epi64(t6, t7);
            __m256i tt7 = _mm256_unpackhi_epi64(t6, t7);

            __m256i ttt0 = _mm256_permute2x128_si256(tt0, tt2, 0x20);
            __m256i ttt1 = _mm256_permute2x128_si256(tt1, tt3, 0x20);
            __m256i ttt2 = _mm256_permute2x128_si256(tt4, tt6, 0x20);
            __m256i ttt3 = _mm256_permute2x128_si256(tt5, tt7, 0x20);
            __m256i ttt4 = _mm256_permute2x128_si256(tt0, tt2, 0x31);
            __m256i ttt5 = _mm256_permute2x128_si256(tt1, tt3, 0x31);
            __m256i ttt6 = _mm256_permute2x128_si256(tt4, tt6, 0x31);
            __m256i ttt7 = _mm256_permute2x128_si256(tt5, tt7, 0x31);

            // Store transposed block to C
            _mm256_storeu_si256((__m256i *)(C + j * rows + i), ttt0);
            _mm256_storeu_si256((__m256i *)(C + (j + 1) * rows + i), ttt1);
            _mm256_storeu_si256((__m256i *)(C + (j + 2) * rows + i), ttt2);
            _mm256_storeu_si256((__m256i *)(C + (j + 3) * rows + i), ttt3);
            _mm256_storeu_si256((__m256i *)(C + (j + 4) * rows + i), ttt4);
            _mm256_storeu_si256((__m256i *)(C + (j + 5) * rows + i), ttt5);
            _mm256_storeu_si256((__m256i *)(C + (j + 6) * rows + i), ttt6);
            _mm256_storeu_si256((__m256i *)(C + (j + 7) * rows + i), ttt7);
        }
    }

    // Transpose remaining elements
    for (int i = rows - (rows % 8); i < rows; ++i) {
        for (int j = cols - (cols % 8); j < cols; ++j) {
            C[j * rows + i] = A[i * cols + j];
        }
    }
}

#endif

// x86
#endif
