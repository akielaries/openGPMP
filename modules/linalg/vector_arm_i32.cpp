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

#include "../../include/linalg/vector.hpp"
#include <cmath>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <vector>

/************************************************************************
 *
 * Vector Operations for ARM NEON CPUs
 *
 ************************************************************************/
#if defined(__ARM_ARCH_ISA_A64) || defined(__ARM_NEON) ||                      \
    defined(__ARM_ARCH) || defined(__aarch64__)

// ARM intrinsic function header
#include <arm_neon.h>
/************************************************************************
 *
 * Vector Operations on Vectors
 *
 ************************************************************************/

// Vector addition using ARM NEON intrinsics, operates on integer types
void gpmp::linalg::vector_add(const std::vector<int> &vec1,
                              const std::vector<int> &vec2,
                              std::vector<int> &result) {
    const size_t size = vec1.size();
    const int *data1 = vec1.data();
    const int *data2 = vec2.data();
    int *result_data = result.data();

    // Check if size is a multiple of 4
    if (size % 4 == 0) {
        for (size_t i = 0; i < size; i += 4) {
            // Load 4 elements from vec1 and vec2
            int32x4_t a = vld1q_s32(data1 + i);
            int32x4_t b = vld1q_s32(data2 + i);

            // Perform vectorized addition
            int32x4_t c = vaddq_s32(a, b);

            // Store the result back to result vector
            vst1q_s32(result_data + i, c);
        }
    } else {
        // If size is not a multiple of 4, perform standard addition
        for (size_t i = 0; i < size; ++i) {
            result_data[i] = data1[i] + data2[i];
        }
    }
}

// Vector subtraction using ARM NEON intrinsics, operates on integer types
void gpmp::linalg::vector_sub(const std::vector<int> &vec1,
                              const std::vector<int> &vec2,
                              std::vector<int> &result) {
    const int vecSize = vec1.size();
    const int remainder = vecSize % 8;
    const int vecSizeAligned = vecSize - remainder;

    for (int i = 0; i < vecSizeAligned; i += 8) {
        int32x4_t vec1Data1 = vld1q_s32(&vec1[i]);
        int32x4_t vec1Data2 = vld1q_s32(&vec1[i + 4]);
        int32x4_t vec2Data1 = vld1q_s32(&vec2[i]);
        int32x4_t vec2Data2 = vld1q_s32(&vec2[i + 4]);

        int32x4_t sub1 = vsubq_s32(vec1Data1, vec2Data1);
        int32x4_t sub2 = vsubq_s32(vec1Data2, vec2Data2);

        vst1q_s32(&result[i], sub1);
        vst1q_s32(&result[i + 4], sub2);
    }

    for (int i = vecSizeAligned; i < vecSize; ++i) {
        result[i] = vec1[i] - vec2[i];
    }
}

// Vector multiplication using ARM NEON intrinsics, operates on integer types
void gpmp::linalg::scalar_mult(const std::vector<int> &vec,
                               int scalar,
                               std::vector<int> &result) {
    const size_t size = vec.size();
    const int32_t *data = vec.data();
    int32_t *result_data = result.data();

    if (size >= 4) {
        int32x4_t scalar_vec = vdupq_n_s32(scalar);
        size_t i = 0;
        for (; i < size - 3; i += 4) {
            // Load 4 elements from vec
            int32x4_t a = vld1q_s32(data + i);

            // Perform vectorized multiplication
            int32x4_t c = vmulq_s32(a, scalar_vec);

            // Store the result back to result vector
            vst1q_s32(result_data + i, c);
        }

        // Perform standard multiplication on the remaining elements
        for (; i < size; ++i) {
            result_data[i] = data[i] * scalar;
        }
    } else {
        for (size_t i = 0; i < size; ++i) {
            result_data[i] = data[i] * scalar;
        }
    }
}

// Dot product using ARM NEON intrinsics, operates on integer types
int gpmp::linalg::dot_product(const std::vector<int> &vec1,
                              const std::vector<int> &vec2) {
    const size_t size = vec1.size();
    const int32_t *data1 = vec1.data();
    const int32_t *data2 = vec2.data();
    int result = 0;

    if (size >= 4) {
        int32x4_t sum_vec = vdupq_n_s32(0);
        size_t i = 0;
        for (; i < size - 3; i += 4) {
            // Load 4 elements from vec1 and vec2
            int32x4_t a = vld1q_s32(data1 + i);
            int32x4_t b = vld1q_s32(data2 + i);

            int32x4_t mul = vmulq_s32(a, b);

            // Accumulate the results
            sum_vec = vaddq_s32(sum_vec, mul);
        }

        // sum the results across the vector
        int32_t temp[4];
        vst1q_s32(temp, sum_vec);
        result = temp[0] + temp[1] + temp[2] + temp[3];

        // process remaining elements if any
        for (; i < size; ++i) {
            result += data1[i] * data2[i];
        }
    }
    // performs std dot product
    else {
        for (size_t i = 0; i < size; ++i) {
            result += data1[i] * data2[i];
        }
    }

    return result;
}

// ARM NEON
#endif
