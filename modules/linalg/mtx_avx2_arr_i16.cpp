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
 * Matrix Operations on Arrays
 *
 ************************************************************************/
// matrix addition for 16-bit integers using 256-bit SIMD registers
void gpmp::linalg::Mtx::mtx_add(const int16_t *A,
                                const int16_t *B,
                                int16_t *C,
                                int rows,
                                int cols) {
    // BUG FIXME
    for (int i = 0; i < rows; ++i) {
        int j = 0;
        for (; j < cols - 15; j += 16) {
            __m256i a = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&A[i * cols + j]));
            __m256i b = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&B[i * cols + j]));
            __m256i c = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&C[i * cols + j]));

            // Perform vectorized addition and accumulate the result
            c = _mm256_add_epi16(c, _mm256_add_epi16(a, b));

            // Store the result back to the C matrix
            _mm256_storeu_si256(reinterpret_cast<__m256i *>(&C[i * cols + j]),
                                c);
        }

        for (; j < cols; ++j) {
            C[i * cols + j] = A[i * cols + j] + B[i * cols + j];
        }
    }
}

#endif

// x86
#endif
