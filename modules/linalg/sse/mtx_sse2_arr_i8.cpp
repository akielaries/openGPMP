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
#include <openGPMP/linalg/mtx.hpp>
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
 * Matrix Operations on Arrays
 *
 ************************************************************************/
// matrix addition for 8-bit integers using SSE and 128-bit SIMD registers
void gpmp::linalg::Mtx::mtx_add(const int8_t *A,
                                const int8_t *B,
                                int8_t *C,
                                int rows,
                                int cols) {
    for (int i = 0; i < rows; ++i) {
        int j = 0;
        for (; j < cols - 15; j += 16) {
            __m128i a = _mm_loadu_si128(
                reinterpret_cast<const __m128i *>(&A[i * cols + j]));
            __m128i b = _mm_loadu_si128(
                reinterpret_cast<const __m128i *>(&B[i * cols + j]));
            __m128i c = _mm_loadu_si128(
                reinterpret_cast<const __m128i *>(&C[i * cols + j]));

            // Perform vectorized addition and accumulate the result
            c = _mm_add_epi8(c, _mm_add_epi8(a, b));

            // Store the result back to the C matrix
            _mm_storeu_si128(reinterpret_cast<__m128i *>(&C[i * cols + j]), c);
        }

        for (; j < cols; ++j) {
            C[i * cols + j] = A[i * cols + j] + B[i * cols + j];
        }
    }
}

#endif

#endif
