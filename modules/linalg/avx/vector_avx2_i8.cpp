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
#include <openGPMP/linalg/vector.hpp>
#include <cmath>
#include <cstdint>
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

/*****************************************************************************/

template <typename T>
void gpmp::linalg::vector_add_i8(const T *data1,
                                 const T *data2,
                                 T *result_data,
                                 size_t size) {
    size_t i = 0;
    if (size > 64) {
        for (; i < size - 31; i += 32) {
            __m256i a = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(data1 + i));
            __m256i b = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(data2 + i));
            __m256i c = _mm256_add_epi8(a, b);
            _mm256_storeu_si256(reinterpret_cast<__m256i *>(result_data + i),
                                c);
        }
    }
    for (; i < size; ++i) {
        result_data[i] = data1[i] + data2[i];
    }
}

void gpmp::linalg::vector_add(const std::vector<int8_t> &vec1,
                              const std::vector<int8_t> &vec2,
                              std::vector<int8_t> &result) {

    const size_t size = vec1.size();
    vector_add_i8(vec1.data(), vec2.data(), result.data(), size);
}

void gpmp::linalg::vector_add(const std::vector<uint8_t> &vec1,
                              const std::vector<uint8_t> &vec2,
                              std::vector<uint8_t> &result) {
    const size_t size = vec1.size();
    vector_add_i8(vec1.data(), vec2.data(), result.data(), size);
}

template <typename T>
void gpmp::linalg::vector_sub_i8(const T *data1,
                                 const T *data2,
                                 T *result_data,
                                 size_t size) {
    size_t i = 0;

    if (size > 64) {
        for (; i < size - 31; i += 32) {
            __m256i a = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(data1 + i));
            __m256i b = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(data2 + i));
            __m256i c = _mm256_sub_epi8(a, b);
            _mm256_storeu_si256(reinterpret_cast<__m256i *>(result_data + i),
                                c);
        }
    }

    // Perform standard subtraction on the remaining elements
    for (; i < size; ++i) {
        result_data[i] = data1[i] - data2[i];
    }
}

void gpmp::linalg::vector_sub(const std::vector<int8_t> &vec1,
                              const std::vector<int8_t> &vec2,
                              std::vector<int8_t> &result) {

    const size_t size = vec1.size();
    vector_sub_i8(vec1.data(), vec2.data(), result.data(), size);
}

void gpmp::linalg::vector_sub(const std::vector<uint8_t> &vec1,
                              const std::vector<uint8_t> &vec2,
                              std::vector<uint8_t> &result) {
    const size_t size = vec1.size();
    vector_sub_i8(vec1.data(), vec2.data(), result.data(), size);
}

template <typename T>
void gpmp::linalg::scalar_mult_i8(const T *data,
                                  int scalar,
                                  T *result_data,
                                  size_t size) {
    size_t i = 0;

    if (size > 64) {
        __m256i scalar_vec = _mm256_set1_epi16(scalar);

        for (; i < size - 31; i += 32) {
            // Load 32 elements from vec
            __m256i a =
                _mm256_loadu_si256(reinterpret_cast<const __m256i *>(data + i));

            // Split the 16-bit values into two 8-bit halves
            __m256i a_low = _mm256_unpacklo_epi8(a, _mm256_setzero_si256());
            __m256i a_high = _mm256_unpackhi_epi8(a, _mm256_setzero_si256());

            // Perform vectorized multiplication of 16-bit integers
            __m256i c_low = _mm256_mullo_epi16(a_low, scalar_vec);
            __m256i c_high = _mm256_mullo_epi16(a_high, scalar_vec);

            // Pack the 16-bit integers back to 8-bit integers
            __m256i c = _mm256_packus_epi16(c_low, c_high);

            // Store the result back to result vector
            _mm256_storeu_si256(reinterpret_cast<__m256i *>(result_data + i),
                                c);
        }
    }
    for (; i < size; ++i) {
        result_data[i] = data[i] * scalar;
    }
}

// TODO/FIXME : the result should be templated too
void gpmp::linalg::scalar_mult(const std::vector<int8_t> &vec1,
                               int scalar,
                               std::vector<int8_t> &result) {

    const size_t size = vec1.size();
    scalar_mult_i8(vec1.data(), scalar, result.data(), size);
}

void gpmp::linalg::scalar_mult(const std::vector<uint8_t> &vec1,
                               int scalar,
                               std::vector<uint8_t> &result) {
    const size_t size = vec1.size();
    scalar_mult_i8(vec1.data(), scalar, result.data(), size);
}

template <typename T>
T gpmp::linalg::dot_product_i8(const T *vec1, const T *vec2, size_t size) {
    int result = 0;
    if (size > 32) {
        size_t i = 0;
        // Perform vectorized multiplication and addition as long as there are
        // at least 16 elements remaining
        for (; i < size - 15; i += 16) {
            // Load 16 elements from vec1 and vec2, unpacking them to 16-bit
            // integers
            __m256i a = _mm256_cvtepu8_epi16(
                _mm_loadu_si128(reinterpret_cast<const __m128i *>(vec1 + i)));
            __m256i b = _mm256_cvtepu8_epi16(
                _mm_loadu_si128(reinterpret_cast<const __m128i *>(vec2 + i)));

            // Perform vectorized multiplication and addition
            __m256i c = _mm256_mullo_epi16(a, b);
            __m256i sum = _mm256_hadd_epi16(c, c);
            sum = _mm256_hadd_epi16(sum, sum);
            sum = _mm256_hadd_epi16(sum, sum);

            // Accumulate the result
            result += _mm256_extract_epi16(sum, 0);
            result += _mm256_extract_epi16(sum, 8);
        }

        // Perform standard dot product on the remaining elements
        for (; i < size; ++i) {
            result += vec1[i] * vec2[i];
        }
    } else {
        for (size_t i = 0; i < size; ++i) {
            result += vec1[i] * vec2[i];
        }
    }

    return result;
}

int gpmp::linalg::dot_product(const std::vector<int8_t> &vec1,
                              const std::vector<int8_t> &vec2) {
    const size_t size = vec1.size();
    return dot_product_i8(vec1.data(), vec2.data(), size);
}

int gpmp::linalg::dot_product(const std::vector<uint8_t> &vec1,
                              const std::vector<uint8_t> &vec2) {
    const size_t size = vec1.size();
    return dot_product_i8(vec1.data(), vec2.data(), size);
}

#endif // INTRINS

// x86
#endif
