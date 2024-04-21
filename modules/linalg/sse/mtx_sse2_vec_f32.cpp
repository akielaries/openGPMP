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
#if defined(__SSE2__)
// SSE2
#include <emmintrin.h>
#include <smmintrin.h>

/************************************************************************
 *
 * Matrix Operations on vector<vector>
 *
 ************************************************************************/

void gpmp::linalg::Mtx::mtx_add(const std::vector<std::vector<float>> &A,
                                const std::vector<std::vector<float>> &B,
                                std::vector<std::vector<float>> &C) {
    const int rows = A.size();
    const int cols = A[0].size();

    if (rows > 16) {
        for (int i = 0; i < rows; ++i) {
            int j = 0;
            // requires at least size 8x8 matrices
            for (; j < cols - 3; j += 3) {
                // load 8 elements from A, B, and C matrices using SIMD
                __m128 a = _mm_loadu_ps(&A[i][j]);
                __m128 b = _mm_loadu_ps(&B[i][j]);
                __m128 c = _mm_loadu_ps(&C[i][j]);

                // perform vectorized addition
                c = _mm_add_ps(a, b);

                // store the result back to the C matrix
                _mm_storeu_ps(&C[i][j], c);
            }

            // handle the remaining elements that are not multiples of 8
            for (; j < cols; ++j) {
                C[i][j] = A[i][j] + B[i][j];
            }
        }
    } else {
        std_mtx_add(A, B, C);
    }
}

#endif

#endif
