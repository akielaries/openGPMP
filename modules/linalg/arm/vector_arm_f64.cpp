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
#include <cmath>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <openGPMP/linalg/vector.hpp>
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

// Vector addition using ARM NEON intrinsics, operates on double types
void gpmp::linalg::vector_add(const std::vector<double> &vec1,
                              const std::vector<double> &vec2,
                              std::vector<double> &result) {
    const size_t size = vec1.size();
    const double *data1 = vec1.data();
    const double *data2 = vec2.data();
    double *result_data = result.data();

    // Check if size is a multiple of 2
    if (size % 2 == 0) {
        for (size_t i = 0; i < size; i += 2) {
            // Load 2 elements from vec1 and vec2
            float64x2_t a = vld1q_f64(data1 + i);
            float64x2_t b = vld1q_f64(data2 + i);

            // Perform vectorized addition
            float64x2_t c = vaddq_f64(a, b);

            // Store the result back to result vector
            vst1q_f64(result_data + i, c);
        }
    } else {
        // If size is not a multiple of 2, perform standard addition
        for (size_t i = 0; i < size; ++i) {
            result_data[i] = data1[i] + data2[i];
        }
    }
}

// Vector subtraction using ARM NEON intrinsics, operates on double types
void gpmp::linalg::vector_sub(const std::vector<double> &vec1,
                              const std::vector<double> &vec2,
                              std::vector<double> &result) {
    const int vecSize = vec1.size();
    const int remainder = vecSize % 4;
    const int vecSizeAligned = vecSize - remainder;

    for (int i = 0; i < vecSizeAligned; i += 4) {
        float64x2_t vec1Data1 = vld1q_f64(&vec1[i]);
        float64x2_t vec1Data2 = vld1q_f64(&vec1[i + 2]);
        float64x2_t vec2Data1 = vld1q_f64(&vec2[i]);
        float64x2_t vec2Data2 = vld1q_f64(&vec2[i + 2]);

        float64x2_t sub1 = vsubq_f64(vec1Data1, vec2Data1);
        float64x2_t sub2 = vsubq_f64(vec1Data2, vec2Data2);

        vst1q_f64(&result[i], sub1);
        vst1q_f64(&result[i + 2], sub2);
    }

    for (int i = vecSizeAligned; i < vecSize; ++i) {
        result[i] = vec1[i] - vec2[i];
    }
}

// Vector multiplication using ARM NEON intrinsics, operates on double types
void gpmp::linalg::scalar_mult(const std::vector<double> &vec,
                               double scalar,
                               std::vector<double> &result) {
    const size_t size = vec.size();
    const double *data = vec.data();
    double *result_data = result.data();

    if (size >= 2) {
        float64x2_t scalar_vec = vdupq_n_f64(scalar);
        size_t i = 0;
        for (; i < size - 1; i += 2) {
            // Load 2 elements from vec
            float64x2_t a = vld1q_f64(data + i);

            // Perform vectorized multiplication
            float64x2_t c = vmulq_f64(a, scalar_vec);

            // Store the result back to result vector
            vst1q_f64(result_data + i, c);
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

// Dot product using ARM NEON intrinsics, operates on double types
double gpmp::linalg::dot_product(const std::vector<double> &vec1,
                                 const std::vector<double> &vec2) {
    const size_t size = vec1.size();
    const double *data1 = vec1.data();
    const double *data2 = vec2.data();
    double result = 0.0;

    if (size >= 2) {
        float64x2_t sum_vec = vdupq_n_f64(0.0);
        size_t i = 0;
        for (; i < size - 1; i += 2) {
            // Load 2 elements from vec1 and vec2
            float64x2_t a = vld1q_f64(data1 + i);
            float64x2_t b = vld1q_f64(data2 + i);

            // Perform vectorized multiplication
            float64x2_t mul = vmulq_f64(a, b);

            // Accumulate the results
            sum_vec = vaddq_f64(sum_vec, mul);
        }

        // Sum the results across the vector
        double temp[2];
        vst1q_f64(temp, sum_vec);
        result = temp[0] + temp[1];

        // Process remaining elements if any
        for (; i < size; ++i) {
            result += data1[i] * data2[i];
        }
    } else {
        for (size_t i = 0; i < size; ++i) {
            result += data1[i] * data2[i];
        }
    }

    return result;
}

// ARM NEON
#endif
