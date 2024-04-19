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

#include "../../../include/linalg/vector.hpp"
#include <cmath>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <vector>

#if defined(__x86_64__) || defined(__amd64__) || defined(__amd64)

/************************************************************************
 *
 * Vector Operations for AVX ISA
 *
 ************************************************************************/
#if defined(__AVX2__)

// AVX family intrinsics
#include <immintrin.h>

/************************************************************************
 *
 * Vector Operations on Vectors
 *
 ************************************************************************/

void gpmp::linalg::vector_add(const std::vector<double> &vec1,
                              const std::vector<double> &vec2,
                              std::vector<double> &result) {
    const size_t size = vec1.size();
    const double *data1 = vec1.data();
    const double *data2 = vec2.data();
    double *result_data = result.data();

    if (size > 4) {
        size_t i = 0;
        // perform vectorized addition as long as there are at least 4 elements
        // remaining
        for (; i < size - 3; i += 4) {
            // Load 4 elements from vec1 and vec2
            __m256d a = _mm256_loadu_pd(data1 + i);
            __m256d b = _mm256_loadu_pd(data2 + i);

            __m256d c = _mm256_add_pd(a, b);

            // Store the result back to result vector
            _mm256_storeu_pd(result_data + i, c);
        }

        // Perform standard addition on the remaining elements
        for (; i < size; ++i) {
            result_data[i] = data1[i] + data2[i];
        }
    } else { // If size is not greater than 4, perform standard addition
        for (size_t i = 0; i < size; ++i) {
            result_data[i] = data1[i] + data2[i];
        }
    }
}

// Vector subtraction using AVX2 intrinsics, operates on double types
void gpmp::linalg::vector_sub(const std::vector<double> &vec1,
                              const std::vector<double> &vec2,
                              std::vector<double> &result) {
    const int vecSize = vec1.size();
    const int remainder = vecSize % 4;
    const int vecSizeAligned = vecSize - remainder;

    if (vecSize > 4) {
        for (int i = 0; i < vecSizeAligned; i += 4) {
            __m256d vec1Data = _mm256_loadu_pd(&vec1[i]);
            __m256d vec2Data = _mm256_loadu_pd(&vec2[i]);
            __m256d sub = _mm256_sub_pd(vec1Data, vec2Data);
            _mm256_storeu_pd(&result[i], sub);
        }

        // Perform standard subtraction on the remaining elements
        for (int i = vecSizeAligned; i < vecSize; ++i) {
            result[i] = vec1[i] - vec2[i];
        }
    } else {
        for (int i = 0; i < vecSize; ++i) {
            result[i] = vec1[i] - vec2[i];
        }
    }
}

void gpmp::linalg::scalar_mult(const std::vector<double> &vec,
                               double scalar,
                               std::vector<double> &result) {
    const int vecSize = vec.size();
    const int remainder = vecSize % 4;
    const int vecSizeAligned = vecSize - remainder;

    // Set the scalar value into a vector register
    __m256d scalarVector = _mm256_set1_pd(scalar);

    // Process aligned part of the vector
    for (int i = 0; i < vecSizeAligned; i += 4) {
        // Load 4 double elements from the vector into a AVX register
        __m256d vecData = _mm256_loadu_pd(&vec[i]);

        // Multiply the elements with the scalar
        __m256d resultData = _mm256_mul_pd(vecData, scalarVector);

        // Store the result back to the result vector
        _mm256_storeu_pd(&result[i], resultData);
    }

    // Process the remaining part of the vector
    for (int i = vecSizeAligned; i < vecSize; ++i) {
        result[i] = vec[i] * scalar;
    }
}

double gpmp::linalg::dot_product(const std::vector<double> &vec1,
                                 const std::vector<double> &vec2) {
    const int vecSize = vec1.size();
    const int remainder = vecSize % 4;
    const int vecSizeAligned = vecSize - remainder;

    // Initialize the result to zero
    __m256d dotProduct = _mm256_setzero_pd();

    // Process aligned part of the vectors
    for (int i = 0; i < vecSizeAligned; i += 4) {
        // Load 4 double elements from each vector into AVX registers
        __m256d vec1Data = _mm256_loadu_pd(&vec1[i]);
        __m256d vec2Data = _mm256_loadu_pd(&vec2[i]);

        // Multiply the elements pairwise and accumulate the result
        dotProduct =
            _mm256_add_pd(dotProduct, _mm256_mul_pd(vec1Data, vec2Data));
    }

    // Sum up the elements in the dotProduct register
    double result = 0.0;
    alignas(32) double temp[4];
    _mm256_store_pd(temp, dotProduct);
    for (int i = 0; i < 4; ++i) {
        result += temp[i];
    }

    // Process the remaining part of the vectors
    for (int i = vecSizeAligned; i < vecSize; ++i) {
        result += vec1[i] * vec2[i];
    }

    return result;
}

#endif

#endif
