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
void gpmp::linalg::vector_add_i16(const T *data1,
                                  const T *data2,
                                  T *result_data,
                                  size_t size) {
    size_t i = 0;
    if (size > 32) {
        for (; i < size - 15; i += 16) {
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

void gpmp::linalg::vector_add(const std::vector<int16_t> &vec1,
                              const std::vector<int16_t> &vec2,
                              std::vector<int16_t> &result) {

    const size_t size = vec1.size();
    vector_add_i16(vec1.data(), vec2.data(), result.data(), size);
}

void gpmp::linalg::vector_add(const std::vector<uint16_t> &vec1,
                              const std::vector<uint16_t> &vec2,
                              std::vector<uint16_t> &result) {
    const size_t size = vec1.size();
    vector_add_i16(vec1.data(), vec2.data(), result.data(), size);
}

#endif // AVX2

#endif // x86
