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

/************************************************************************
 *
 * Matrix Operations for ARM NEON CPUs
 *
 ************************************************************************/
#if defined(__ARM_ARCH_ISA_A64) || defined(__ARM_NEON) ||                      \
    defined(__ARM_ARCH) || defined(__aarch64__)

// ARM intrinsic function header
#include <arm_neon.h>

/************************************************************************
 *
 * Matrix Operations on vector<vector>
 *
 ************************************************************************/
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

void gpmp::linalg::Mtx::mtx_tpose(std::vector<std::vector<double>> &matrix) {
    const int rows = matrix.size();
    const int cols = matrix[0].size();

    for (int i = 0; i < rows; i += 2) {
        for (int j = i; j < cols; j += 2) {
            float64x2x2_t row1 = vld2q_f64(&matrix[i][j]);
            float64x2x2_t row2 = vld2q_f64(&matrix[i + 1][j]);

            // Transpose 2x2 submatrix
            float64x2x2_t transposed;
            transposed.val[0] = vcombine_f64(vget_low_f64(row1.val[0]),
                                             vget_low_f64(row2.val[0]));
            transposed.val[1] = vcombine_f64(vget_low_f64(row1.val[1]),
                                             vget_low_f64(row2.val[1]));

            // Store the transposed 2x2 submatrix back to the matrix
            vst2q_f64(&matrix[i][j], transposed);
        }
    }
}

#endif
