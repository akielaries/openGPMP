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
