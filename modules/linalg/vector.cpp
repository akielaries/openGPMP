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

// Vector addition using AVX2 intrinsics, operates on integer types
void gpmp::linalg::vector_add(const std::vector<int> &vec1,
                              const std::vector<int> &vec2,
                              std::vector<int> &result) {
    const size_t size = vec1.size();
    const int *data1 = vec1.data();
    const int *data2 = vec2.data();
    int *result_data = result.data();

    // Check if size is a multiple of 8
    if (size % 8 == 0) {
        for (size_t i = 0; i < size; i += 8) {
            // Load 8 elements from vec1 and vec2
            __m256i a = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(data1 + i));
            __m256i b = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(data2 + i));

            // Perform vectorized addition
            __m256i c = _mm256_add_epi32(a, b);

            // Store the result back to result vector
            _mm256_storeu_si256(reinterpret_cast<__m256i *>(result_data + i),
                                c);
        }
    } else {
        // If size is not a multiple of 8, perform standard addition
        for (size_t i = 0; i < size; ++i) {
            result_data[i] = data1[i] + data2[i];
        }
    }
}

void gpmp::linalg::vector_add(const std::vector<double> &vec1,
                              const std::vector<double> &vec2,
                              std::vector<double> &result) {
    const size_t size = vec1.size();
    const double *data1 = vec1.data();
    const double *data2 = vec2.data();
    double *result_data = result.data();

    // Check if size is a multiple of 4
    if (size % 4 == 0) {
        for (size_t i = 0; i < size; i += 4) {
            // Load 4 elements from vec1 and vec2
            __m256d a = _mm256_loadu_pd(data1 + i);
            __m256d b = _mm256_loadu_pd(data2 + i);

            // Perform vectorized addition
            __m256d c = _mm256_add_pd(a, b);

            // Store the result back to result vector
            _mm256_storeu_pd(result_data + i, c);
        }
    } else {
        // If size is not a multiple of 4, perform standard addition
        for (size_t i = 0; i < size; ++i) {
            result_data[i] = data1[i] + data2[i];
        }
    }
}

void gpmp::linalg::vector_sub(const std::vector<int> &vec1,
                              const std::vector<int> &vec2,
                              std::vector<int> &result) {
    const int vecSize = vec1.size();
    const int remainder = vecSize % 8;
    const int vecSizeAligned = vecSize - remainder;

    for (int i = 0; i < vecSizeAligned; i += 8) {
        __m256i vec1Data =
            _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&vec1[i]));
        __m256i vec2Data =
            _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&vec2[i]));
        __m256i sub = _mm256_sub_epi32(vec1Data, vec2Data);
        _mm256_storeu_si256(reinterpret_cast<__m256i *>(&result[i]), sub);
    }

    for (int i = vecSizeAligned; i < vecSize; ++i) {
        result[i] = vec1[i] - vec2[i];
    }
}

void gpmp::linalg::vector_sub(const std::vector<double> &vec1,
                              const std::vector<double> &vec2,
                              std::vector<double> &result) {
    const int vecSize = vec1.size();
    const int remainder = vecSize % 4;
    const int vecSizeAligned = vecSize - remainder;

    for (int i = 0; i < vecSizeAligned; i += 4) {
        __m256d vec1Data = _mm256_loadu_pd(&vec1[i]);
        __m256d vec2Data = _mm256_loadu_pd(&vec2[i]);
        __m256d sub = _mm256_sub_pd(vec1Data, vec2Data);
        _mm256_storeu_pd(&result[i], sub);
    }

    for (int i = vecSizeAligned; i < vecSize; ++i) {
        result[i] = vec1[i] - vec2[i];
    }
}

// Vector multiplication using AVX2 intrinsics, operates on integer types
void gpmp::linalg::vector_mult(const std::vector<int> &vec,
                               int scalar,
                               std::vector<int> &result) {
    const size_t size = vec.size();
    const int *data = vec.data();
    int *result_data = result.data();

    // Check if size is a multiple of 8
    if (size % 8 == 0) {
        __m256i scalar_vec = _mm256_set1_epi32(scalar);
        for (size_t i = 0; i < size; i += 8) {
            // Load 8 elements from vec
            __m256i a =
                _mm256_loadu_si256(reinterpret_cast<const __m256i *>(data + i));

            // Perform vectorized multiplication
            __m256i c = _mm256_mullo_epi32(a, scalar_vec);

            // Store the result back to result vector
            _mm256_storeu_si256(reinterpret_cast<__m256i *>(result_data + i),
                                c);
        }
    } else {
        // If size is not a multiple of 8, perform standard multiplication
        for (size_t i = 0; i < size; ++i) {
            result_data[i] = data[i] * scalar;
        }
    }
}

void gpmp::linalg::vector_mult(const std::vector<double> &vec,
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

// Dot product using AVX2 intrinsics, operates on integer types
int gpmp::linalg::dot_product(const std::vector<int> &vec1,
                              const std::vector<int> &vec2) {
    const size_t size = vec1.size();
    const int *data1 = vec1.data();
    const int *data2 = vec2.data();
    int result = 0;

    // Check if size is a multiple of 8
    if (size % 8 == 0) {
        for (size_t i = 0; i < size; i += 8) {
            // Load 8 elements from vec1 and vec2
            __m256i a = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(data1 + i));
            __m256i b = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(data2 + i));

            // Perform vectorized multiplication and addition
            __m256i c = _mm256_mullo_epi32(a, b);
            __m256i sum = _mm256_hadd_epi32(c, c);
            sum = _mm256_hadd_epi32(sum, sum);

            // Accumulate the result
            result += _mm256_extract_epi32(sum, 0);
            result += _mm256_extract_epi32(sum, 4);
        }
    } else {
        // If size is not a multiple of 8, perform standard dot product
        for (size_t i = 0; i < size; ++i) {
            result += data1[i] * data2[i];
        }
    }

    return result;
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

/************************************************************************
 *
 * Vector Operations for SSE ISA
 *
 ************************************************************************/
#elif defined(__SSE2__)
// SSE2
#include <emmintrin.h>
#include <smmintrin.h>
/************************************************************************
 *
 * Vector Operations on Vectors
 *
 ************************************************************************/

/************************************************************************
 *
 * Vector Operations for MMX ISA
 *
 ************************************************************************/
#elif define(__MMX__)
#include <mmintrin.h>

// SSE
#endif

// x86
#endif

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

// Vector multiplication using ARM NEON intrinsics, operates on integer types
void gpmp::linalg::vector_mult(const std::vector<int> &vec,
                               int scalar,
                               std::vector<int> &result) {
    const size_t size = vec.size();
    const int *data = vec.data();
    int *result_data = result.data();

    const int32x4_t scalarVector = vdupq_n_s32(scalar);

    for (size_t i = 0; i < size; i += 4) {
        int32x4_t vecData = vld1q_s32(data + i);

        int32x4_t mulResult = vmulq_s32(vecData, scalarVector);

        vst1q_s32(result_data + i, mulResult);
    }
}

// Vector multiplication using ARM NEON intrinsics, operates on double types
void gpmp::linalg::vector_mult(const std::vector<double> &vec,
                               double scalar,
                               std::vector<double> &result) {
    const int vecSize = vec.size();
    const int remainder = vecSize % 2;
    const int vecSizeAligned = vecSize - remainder;

    const float64x2_t scalarVector = vdupq_n_f64(scalar);

    for (int i = 0; i < vecSizeAligned; i += 2) {
        float64x2_t vecData = vld1q_f64(&vec[i]);

        float64x2_t mulResult = vmulq_f64(vecData, scalarVector);

        vst1q_f64(&result[i], mulResult);
    }

    for (int i = vecSizeAligned; i < vecSize; ++i) {
        result[i] = vec[i] * scalar;
    }
}

// Dot product using ARM NEON intrinsics, operates on integer types
int gpmp::linalg::dot_product(const std::vector<int> &vec1,
                              const std::vector<int> &vec2) {
    const int vecSize = vec1.size();
    const int32_t *data1 = vec1.data();
    const int32_t *data2 = vec2.data();

    int32x4_t sumVec = vdupq_n_s32(0);

    for (int i = 0; i < vecSize; i += 4) {
        int32x4_t vec1Data = vld1q_s32(data1 + i);
        int32x4_t vec2Data = vld1q_s32(data2 + i);

        int32x4_t mulResult = vmulq_s32(vec1Data, vec2Data);

        sumVec = vaddq_s32(sumVec, mulResult);
    }

    int32_t sum = vgetq_lane_s32(sumVec, 0) + vgetq_lane_s32(sumVec, 1) +
                  vgetq_lane_s32(sumVec, 2) + vgetq_lane_s32(sumVec, 3);

    for (int i = vecSize & ~3; i < vecSize; ++i) {
        sum += data1[i] * data2[i];
    }

    return sum;
}

// Dot product using ARM NEON intrinsics, operates on double types
double gpmp::linalg::dot_product(const std::vector<double> &vec1,
                                 const std::vector<double> &vec2) {
    const int vecSize = vec1.size();
    const double *data1 = vec1.data();
    const double *data2 = vec2.data();

    float64x2_t sumVec = vdupq_n_f64(0);

    for (int i = 0; i < vecSize; i += 2) {
        float64x2_t vec1Data = vld1q_f64(data1 + i);
        float64x2_t vec2Data = vld1q_f64(data2 + i);

        float64x2_t mulResult = vmulq_f64(vec1Data, vec2Data);

        sumVec = vaddq_f64(sumVec, mulResult);
    }

    double sum = vgetq_lane_f64(sumVec, 0) + vgetq_lane_f64(sumVec, 1);

    for (int i = vecSize & ~1; i < vecSize; ++i) {
        sum += data1[i] * data2[i];
    }

    return sum;
}

// ARM NEON
#endif

/************************************************************************
 *
 * Standard/Naive Vector  Operations on vector<>
 *
 ************************************************************************/

void gpmp::linalg::std_vector_add(const std::vector<double> &vec1,
                                  const std::vector<double> &vec2,
                                  std::vector<double> &result) {
    if (vec1.size() != vec2.size()) {
        // handle error, throw exception, or take appropriate action
        return;
    }

    result.resize(vec1.size());
    for (size_t i = 0; i < vec1.size(); ++i) {
        result[i] = vec1[i] + vec2[i];
    }
}

// function to subtract one vector from another
void gpmp::linalg::std_vector_sub(const std::vector<double> &vec1,
                                  const std::vector<double> &vec2,
                                  std::vector<double> &result) {
    if (vec1.size() != vec2.size()) {
        // handle error, throw exception, or take appropriate action
        return;
    }

    result.resize(vec1.size());
    for (size_t i = 0; i < vec1.size(); ++i) {
        result[i] = vec1[i] - vec2[i];
    }
}

// function to multiply each element of a vector by a scalar
void gpmp::linalg::std_vector_mult(const std::vector<double> &vec,
                                   double scalar,
                                   std::vector<double> &result) {
    result.resize(vec.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        result[i] = vec[i] * scalar;
    }
}

// function to compute the dot product of two vectors
double gpmp::linalg::std_dot_product(const std::vector<double> &vec1,
                                     const std::vector<double> &vec2) {
    if (vec1.size() != vec2.size()) {
        throw std::invalid_argument(
            "Vector dimensions must match for dot product");
    }

    double result = 0.0;
    for (size_t i = 0; i < vec1.size(); ++i) {
        result += vec1[i] * vec2[i];
    }
    return result;
}

// function to compute the cross product of two 3D vectors
void gpmp::linalg::std_cross_product(const std::vector<double> &vec1,
                                     const std::vector<double> &vec2,
                                     std::vector<double> &result) {
    if (vec1.size() != 3 || vec2.size() != 3) {
        throw std::invalid_argument(
            "Cross product is defined only for 3D vectors");
    }

    result[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
    result[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
    result[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
}

double gpmp::linalg::std_vector_norm(const std::vector<double> &vec) {
    double norm = 0.0;
    for (double value : vec) {
        norm += value * value;
    }
    return std::sqrt(norm);
}

// function to normalize a vector to have unit length
void gpmp::linalg::std_vector_normalize(const std::vector<double> &vec,
                                        std::vector<double> &result) {
    double norm = gpmp::linalg::std_vector_norm(vec);
    result.resize(vec.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        result[i] = vec[i] / norm;
    }
}

// function to compute the projection of one vector onto another
void gpmp::linalg::std_vector_projection(const std::vector<double> &vec,
                                         const std::vector<double> &onto_vec,
                                         std::vector<double> &result) {
    double dot = std_dot_product(vec, onto_vec);
    double onto_vec_norm_sq = std_dot_product(onto_vec, onto_vec);

    result.resize(onto_vec.size());
    for (size_t i = 0; i < onto_vec.size(); ++i) {
        result[i] = (dot / onto_vec_norm_sq) * onto_vec[i];
    }
}

void gpmp::linalg::std_vector_add(const std::vector<int> &vec1,
                                  const std::vector<int> &vec2,
                                  std::vector<int> &result) {
    if (vec1.size() != vec2.size()) {
        throw std::invalid_argument(
            "Vector dimensions must match for addition");
    }

    result.resize(vec1.size());
    for (size_t i = 0; i < vec1.size(); ++i) {
        result[i] = vec1[i] + vec2[i];
    }
}

// function to subtract one vector of integers from another
void gpmp::linalg::std_vector_sub(const std::vector<int> &vec1,
                                  const std::vector<int> &vec2,
                                  std::vector<int> &result) {
    if (vec1.size() != vec2.size()) {
        throw std::invalid_argument(
            "Vector dimensions must match for subtraction");
    }

    result.resize(vec1.size());
    for (size_t i = 0; i < vec1.size(); ++i) {
        result[i] = vec1[i] - vec2[i];
    }
}

// function to multiply each element of a vector of integers by a scalar
void gpmp::linalg::std_vector_mult(const std::vector<int> &vec,
                                   int scalar,
                                   std::vector<int> &result) {
    result.resize(vec.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        result[i] = vec[i] * scalar;
    }
}

// function to compute the dot product of two vectors of integers
int gpmp::linalg::std_dot_product(const std::vector<int> &vec1,
                                  const std::vector<int> &vec2) {
    if (vec1.size() != vec2.size()) {
        throw std::invalid_argument(
            "Vector dimensions must match for dot product");
    }

    int result = 0;
    for (size_t i = 0; i < vec1.size(); ++i) {
        result += vec1[i] * vec2[i];
    }
    return result;
}

// function to compute the cross product of two 3D vectors of integers
void gpmp::linalg::std_cross_product(const std::vector<int> &vec1,
                                     const std::vector<int> &vec2,
                                     std::vector<int> &result) {
    if (vec1.size() != 3 || vec2.size() != 3) {
        throw std::invalid_argument(
            "Cross product is defined only for 3D vectors");
    }

    result.resize(3);
    result[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
    result[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
    result[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
}

double gpmp::linalg::std_vector_norm(const std::vector<int> &vec) {
    double norm = 0.0;
    for (int value : vec) {
        norm += value * value;
    }
    return std::sqrt(norm);
}

// function to normalize a vector of integers to have unit length
void gpmp::linalg::std_vector_normalize(const std::vector<int> &vec,
                                        std::vector<double> &result) {
    double norm = std_vector_norm(vec);
    result.resize(vec.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        result[i] = static_cast<double>(vec[i]) / norm;
    }
}

// function to compute the projection of one vector of integers onto another
void gpmp::linalg::std_vector_projection(const std::vector<int> &vec,
                                         const std::vector<int> &onto_vec,
                                         std::vector<double> &result) {
    double dot = std_dot_product(vec, onto_vec);
    double onto_vec_norm_sq = std_dot_product(onto_vec, onto_vec);

    result.resize(onto_vec.size());
    for (size_t i = 0; i < onto_vec.size(); ++i) {
        result[i] = (dot / onto_vec_norm_sq) * onto_vec[i];
    }
}
