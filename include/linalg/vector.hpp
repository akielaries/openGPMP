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

#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <cstdint>
#include <vector>

namespace gpmp {

namespace linalg {

template <typename T>
void vector_add_i8(const T *data1, const T *data2, T *result_data, size_t size);

template <typename T>
void vector_add_i16(const T *data1,
                    const T *data2,
                    T *result_data,
                    size_t size);

template <typename T>
void vector_add_i32(const T *data1,
                    const T *data2,
                    T *result_data,
                    size_t size);

template <typename T>
void vector_add_i64(const T *data1,
                    const T *data2,
                    T *result_data,
                    size_t size);

void vector_add(const std::vector<int8_t> &vec1,
                const std::vector<int8_t> &vec2,
                std::vector<int8_t> &result);

void vector_add(const std::vector<uint8_t> &vec1,
                const std::vector<uint8_t> &vec2,
                std::vector<uint8_t> &result);

void vector_add(const std::vector<int16_t> &vec1,
                const std::vector<int16_t> &vec2,
                std::vector<int16_t> &result);

void vector_add(const std::vector<uint16_t> &vec1,
                const std::vector<uint16_t> &vec2,
                std::vector<uint16_t> &result);

void vector_add(const std::vector<int32_t> &vec1,
                const std::vector<int32_t> &vec2,
                std::vector<int32_t> &result);

void vector_add(const std::vector<uint32_t> &vec1,
                const std::vector<uint32_t> &vec2,
                std::vector<uint32_t> &result);

void vector_add(const std::vector<int64_t> &vec1,
                const std::vector<int64_t> &vec2,
                std::vector<int64_t> &result);

void vector_add(const std::vector<uint64_t> &vec1,
                const std::vector<uint64_t> &vec2,
                std::vector<uint64_t> &result);

/*****************************************************************************/
template <typename T>
void vector_sub_i8(const T *data1, const T *data2, T *result_data, size_t size);

template <typename T>
void vector_sub_i16(const T *data1,
                    const T *data2,
                    T *result_data,
                    size_t size);

template <typename T>
void vector_sub_i32(const T *data1,
                    const T *data2,
                    T *result_data,
                    size_t size);

template <typename T>
void vector_sub_64(const T *data1, const T *data2, T *result_data, size_t size);

void vector_sub(const std::vector<int8_t> &vec1,
                const std::vector<int8_t> &vec2,
                std::vector<int8_t> &result);

void vector_sub(const std::vector<uint8_t> &vec1,
                const std::vector<uint8_t> &vec2,
                std::vector<uint8_t> &result);

void vector_sub(const std::vector<int16_t> &vec1,
                const std::vector<int16_t> &vec2,
                std::vector<int16_t> &result);

void vector_sub(const std::vector<uint16_t> &vec1,
                const std::vector<uint16_t> &vec2,
                std::vector<uint16_t> &result);

void vector_sub(const std::vector<int32_t> &vec1,
                const std::vector<int32_t> &vec2,
                std::vector<int32_t> &result);

void vector_sub(const std::vector<uint32_t> &vec1,
                const std::vector<uint32_t> &vec2,
                std::vector<uint32_t> &result);

void vector_sub(const std::vector<int64_t> &vec1,
                const std::vector<int64_t> &vec2,
                std::vector<int64_t> &result);

void vector_sub(const std::vector<uint64_t> &vec1,
                const std::vector<uint64_t> &vec2,
                std::vector<uint64_t> &result);

/*****************************************************************************/
template <typename T>
void scalar_mult_i8(const T *data, int scalar, T *result_data, size_t size);

template <typename T>
void scalar_mult_i16(const T *data, int scalar, T *result_data, size_t size);

template <typename T>
void scalar_mult_i32(const T *data, int scalar, T *result_data, size_t size);

template <typename T>
void scalar_mult_i64(const T *data, int scalar, T *result_data, size_t size);

void scalar_mult(const std::vector<int8_t> &vec1,
                 int scalar,
                 std::vector<int8_t> &result);

void scalar_mult(const std::vector<uint8_t> &vec1,
                 int scalar,
                 std::vector<uint8_t> &result);

void scalar_mult(const std::vector<int16_t> &vec1,
                 int scalar,
                 std::vector<int16_t> &result);

void scalar_mult(const std::vector<uint16_t> &vec1,
                 int scalar,
                 std::vector<uint16_t> &result);

void scalar_mult(const std::vector<int32_t> &vec1,
                 int scalar,
                 std::vector<int32_t> &result);

void scalar_mult(const std::vector<uint32_t> &vec1,
                 int scalar,
                 std::vector<uint32_t> &result);

void scalar_mult(const std::vector<int64_t> &vec1,
                 int scalar,
                 std::vector<int64_t> &result);

void scalar_mult(const std::vector<uint64_t> &vec1,
                 int scalar,
                 std::vector<uint64_t> &result);

template <typename T>
T dot_product_i32(const T *vec1, const T *vec2, size_t size);

int dot_product(const std::vector<int8_t> &vec1,
                const std::vector<int8_t> &vec2);

int dot_product(const std::vector<uint8_t> &vec1,
                const std::vector<uint8_t> &vec2);

int dot_product(const std::vector<int16_t> &vec1,
                const std::vector<int16_t> &vec2);

int dot_product(const std::vector<uint16_t> &vec1,
                const std::vector<uint16_t> &vec2);

int dot_product(const std::vector<int32_t> &vec1,
                const std::vector<int32_t> &vec2);

int dot_product(const std::vector<uint32_t> &vec1,
                const std::vector<uint32_t> &vec2);

int dot_product(const std::vector<int64_t> &vec1,
                const std::vector<int64_t> &vec2);

int dot_product(const std::vector<uint64_t> &vec1,
                const std::vector<uint64_t> &vec2);

/*****************************************************************************/

/**
 * @brief Performs vector addition for double vectors
 *
 * This function adds corresponding elements of two double vectors and stores
 * the result in the provided result vector
 *
 * @param vec1 The first input vector
 * @param vec2 The second input vector
 * @param result The vector where the result of the addition will be stored
 */
void vector_add(const std::vector<double> &vec1,
                const std::vector<double> &vec2,
                std::vector<double> &result);

/**
 * @brief Performs vector subtraction for double vectors
 *
 * This function subtracts corresponding elements of two double vectors and
 * stores the result in the provided result vector
 *
 * @param vec1 The first input vector
 * @param vec2 The second input vector
 * @param result The vector where the result of the subtraction will be stored
 */
void vector_sub(const std::vector<double> &vec1,
                const std::vector<double> &vec2,
                std::vector<double> &result);

/**
 * @brief Performs scalar multiplication for double vectors
 *
 * This function multiplies each element of a double vector by a scalar value
 * and stores the result in the provided result vector
 *
 * @param vec The input vector
 * @param scalar The scalar value to multiply each element by
 * @param result The vector where the result of the multiplication will be
 * stored
 */
void scalar_mult(const std::vector<double> &vec,
                 double scalar,
                 std::vector<double> &result);

/**
 * @brief Computes the dot product of two double vectors
 *
 * This function computes the dot product of two double vectors
 *
 * @param vec1 The first input vector
 * @param vec2 The second input vector
 * @return The dot product of the two input vectors
 */
double dot_product(const std::vector<double> &vec1,
                   const std::vector<double> &vec2);

/**
 * @brief Add two vectors element-wise
 *
 * This function calculates the element-wise addition of two vectors and stores
 * the result in the output vector
 *
 * @param vec1 The first vector
 * @param vec2 The second vector
 * @param result The output vector where the result will be stored
 */
template <typename T>
void std_vector_add(const std::vector<T> &vec1,
                    const std::vector<T> &vec2,
                    std::vector<T> &result) {
    result.resize(vec1.size());
    for (size_t i = 0; i < vec1.size(); ++i) {
        result[i] = vec1[i] + vec2[i];
    }
}

/**
 * @brief Subtract one vector from another element-wise
 *
 * This function calculates the element-wise subtraction of one vector from
 * another and stores the result in the output vector
 *
 * @param vec1 The vector to subtract from
 * @param vec2 The vector to subtract
 * @param result The output vector where the result will be stored
 */
template <typename T>
void std_vector_sub(const std::vector<T> &vec1,
                    const std::vector<T> &vec2,
                    std::vector<T> &result) {
    result.resize(vec1.size());
    for (size_t i = 0; i < vec1.size(); ++i) {
        result[i] = vec1[i] - vec2[i];
    }
}

/**
 * @brief Multiply each element of a vector by a scalar
 *
 * This function multiplies each element of a vector by a scalar value and
 * stores the result in the output vector
 *
 * @param vec The input vector
 * @param scalar The scalar value to multiply with
 * @param result The output vector where the result will be stored
 */
template <typename T>
void std_scalar_mult(const std::vector<T> &vec,
                     int scalar,
                     std::vector<T> &result) {
    result.resize(vec.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        result[i] = vec[i] * scalar;
    }
}

/**
 * @brief Compute the dot product of two vectors
 *
 * This function computes the dot product of two vectors
 *
 * @param vec1 The first vector
 * @param vec2 The second vector
 * @return The dot product of the two input vectors
 */
template <typename T>
T std_dot_product(const std::vector<T> &vec1, const std::vector<T> &vec2) {
    T result = 0;
    for (size_t i = 0; i < vec1.size(); ++i) {
        result += vec1[i] * vec2[i];
    }
    return result;
}

/**
 * @brief Compute the cross product of two 3D vectors
 *
 * This function computes the cross product of two 3D vectors and stores the
 * result in the output vector
 *
 * @param vec1 The first vector
 * @param vec2 The second vector
 * @param result The output vector where the result will be stored
 */
void std_cross_product(const std::vector<double> &vec1,
                       const std::vector<double> &vec2,
                       std::vector<double> &result);

/**
 * @brief Compute the Euclidean norm (magnitude) of a vector
 *
 * This function computes the Euclidean norm (magnitude) of a vector
 *
 * @param vec The input vector
 * @return The Euclidean norm of the input vector
 */
double std_vector_norm(const std::vector<double> &vec);

/**
 * @brief Normalize a vector to have unit length
 *
 * This function normalizes a vector to have unit length
 *
 * @param vec The input vector
 * @param result The output vector where the normalized vector will be stored
 */
void std_vector_normalize(const std::vector<double> &vec,
                          std::vector<double> &result);

/**
 * @brief Compute the projection of one vector onto another
 *
 * This function computes the projection of one vector onto another and stores
 * the result in the output vector
 *
 * @param vec The vector to project
 * @param onto_vec The vector onto which to project
 * @param result The output vector where the projected vector will be stored
 */
void std_vector_projection(const std::vector<double> &vec,
                           const std::vector<double> &onto_vec,
                           std::vector<double> &result);
/**
 * @brief Compute the cross product of two 3D vectors of integers
 *
 * This function computes the cross product of two 3D vectors of integers and
 * stores the result in the output vector
 *
 * @param vec1 The first vector of integers
 * @param vec2 The second vector of integers
 * @param result The output vector where the result will be stored
 */
void std_cross_product(const std::vector<int> &vec1,
                       const std::vector<int> &vec2,
                       std::vector<int> &result);

/**
 * @brief Compute the Euclidean norm (magnitude) of a vector of integers
 *
 * This function computes the Euclidean norm (magnitude) of a vector of
 * integers
 *
 * @param vec The input vector of integers
 * @return The Euclidean norm of the input vector
 */
double std_vector_norm(const std::vector<int> &vec);

/**
 * @brief Normalize a vector of integers to have unit length
 *
 * This function normalizes a vector of integers to have unit length
 *
 * @param vec The input vector of integers
 * @param result The output vector where the normalized vector will be stored
 */
void std_vector_normalize(const std::vector<int> &vec,
                          std::vector<double> &result);

/**
 * @brief Compute the projection of one vector of integers onto another
 *
 * This function computes the projection of one vector of integers onto another
 * and stores the result in the output vector
 *
 * @param vec The vector of integers to project
 * @param onto_vec The vector of integers onto which to project
 * @param result The output vector where the projected vector will be stored
 */
void std_vector_projection(const std::vector<int> &vec,
                           const std::vector<int> &onto_vec,
                           std::vector<double> &result);

} // namespace linalg
} // namespace gpmp

#endif
