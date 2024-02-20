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

#ifndef MTX_HPP
#define MTX_HPP

#include <cstdint>
#include <iostream>
#include <vector>

#if defined(__GPMP_PYTHON_API__)
#define __PYTHON_API__

#include <boost/bind/bind.hpp>
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#endif

namespace gpmp {

namespace linalg {

/**
 * @brief Mtx class offers matrix arithmetic operations. Some methods are
 * element-wise while others make use of grouping and unrolling
 */
class Mtx {

  public:
#if defined(__GPMP_PYTHON_API__)

    // boost::python::numpy header
    // #include <boost/python.hpp>
    // #include <boost/bind/bind.hpp>
    // #include <boost/python/numpy.hpp>

    /**
     * @brief boost::python::numpy wrapper for array-based array methods
     */
    void mtx_add(const boost::python::numpy::ndarray &A,
                 const boost::python::numpy::ndarray &B,
                 boost::python::numpy::ndarray &C,
                 int rows,
                 int cols);

// if Python API compilation is NOT occuring include these methods
#elif defined(__GPMP_CPP_API__)

#define __GPMP_CPP__
    /**
     * @brief Perform matrix addition using flattened matrices and the
     * designated Fortran subroutine. Accepts type float
     */
    void mtx_add_f90(float *A, float *B, float *C, std::size_t matrixSize);

    /**
     * @brief Perform matrix addition using flattened matrices and the
     * designated Fortran subroutine. Accepts type int
     */
    void mtx_add_f90(int *A, int *B, int *C, std::size_t matrixSize);

    void mtx_mult_f90(int *A,
                      int *B,
                      int *C,
                      std::size_t rows_a,
                      std::size_t cols_a,
                      std::size_t cols_b);

    /*  void mtx_mult_f90(int *A,
                        int *B,
                        int *C,
                        std::size_t mtx_size);
  */
#endif

#if defined(__x86_64__) || defined(i386) || defined(__i386__) ||               \
    defined(__i386) || defined(__amd64__) || defined(__amd64)
    /**
     * @brief Perform matrix addition using Intel intrinsics, accepts
     * flat arrays of 8 bit ints
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note Matrices must be of at least size 8x8
     * @overload
     */
    void
    mtx_add(const int8_t *A, const int8_t *B, int8_t *C, int rows, int cols);

    /**
     * @brief Perform matrix addition using Intel intrinsics, accepts
     * flat arrays of 16 bit ints
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note Matrices must be of at least size 8x8
     * @overload
     */
    void
    mtx_add(const int16_t *A, const int16_t *B, int16_t *C, int rows, int cols);
    /**
     * @brief Perform matrix addition using Intel intrinsics, accepts
     * flat arrays of type int
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note Matrices must be of at least size 8x8
     * @overload
     */
    void mtx_add(const int *A, const int *B, int *C, int rows, int cols);

    /**
     * @brief Perform matrix addition using Intel intrinsics, accepts
     * flat arrays of type double
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note Matrices must be of at least size 8x8
     * @overload
     */
    void
    mtx_add(const double *A, const double *B, double *C, int rows, int cols);

    /**
     * @brief Perform matrix addition using Intel intrinsics, accepts
     * flat arrays of type float
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note Matrices must be of at least size 8x8
     * @overload
     */
    void mtx_add(const float *A, const float *B, float *C, int rows, int cols);

    /**
     * @brief Perform matrix addition using Intel intrinsics, accepts
     * vectors of type int
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note Matrices must be of at least size 8x8
     * @overload
     */
    void mtx_add(const std::vector<std::vector<int>> &A,
                 const std::vector<std::vector<int>> &B,
                 std::vector<std::vector<int>> &C);

    /**
     * @brief Perform matrix addition using Intel intrinsics, accepts
     * vectors of type double
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note Matrices must be of at least size 4x4
     * @overload
     */
    void mtx_add(const std::vector<std::vector<double>> &A,
                 const std::vector<std::vector<double>> &B,
                 std::vector<std::vector<double>> &C);

    /**
     * @brief Perform matrix addition using Intel intrinsics, accepts
     * vectors of type float
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note Matrices must be of at least size 4x4
     * @overload
     */
    void mtx_add(const std::vector<std::vector<float>> &A,
                 const std::vector<std::vector<float>> &B,
                 std::vector<std::vector<float>> &C);

    /**
     * @brief Perform matrix subtraction using Intel intrinsics, accepts
     * flat arrays of 8 bit ints
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note Matrices must be of at least size 8x8
     * @overload
     */
    void
    mtx_sub(const int8_t *A, const int8_t *B, int8_t *C, int rows, int cols);

    /**
     * @brief Perform matrix subtraction using Intel intrinsics, accepts
     * flat arrays of 16 bit ints
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note Matrices must be of at least size 8x8
     * @overload
     */
    void
    mtx_sub(const int16_t *A, const int16_t *B, int16_t *C, int rows, int cols);
    /**
     * @brief Perform matrix subtraction using Intel intrinsics, accepts
     * flat arrays of type int
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note Matrices must be of at least size 8x8
     * @overload
     */
    void mtx_sub(const int *A, const int *B, int *C, int rows, int cols);

    /**
     * @brief Perform matrix subtraction using Intel intrinsics, accepts
     * flat arrays of type double
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note Matrices must be of at least size 8x8
     * @overload
     */
    void
    mtx_sub(const double *A, const double *B, double *C, int rows, int cols);

    /**
     * @brief Perform matrix subtraction using Intel intrinsics, accepts
     * flat arrays of type float
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note Matrices must be of at least size 8x8
     * @overload
     */
    void mtx_sub(const float *A, const float *B, float *C, int rows, int cols);

    /**
     * @brief Perform matrix multiplication using Intel intrinsics, accepts
     * flat arrays of 8 bit integers
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note Matrices must be of at least size 8x8
     * @overload
     */
    void mtx_mult(const int8_t *A,
                  const int8_t *B,
                  int8_t *C,
                  int rows_a,
                  int cols_a,
                  int cols_b);
    /**
     * @brief Perform matrix multiplication using Intel intrinsics, accepts
     * flat arrays of 16 bit integers
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note Matrices must be of at least size 8x8
     * @overload
     */
    void mtx_mult(const int16_t *A,
                  const int16_t *B,
                  int16_t *C,
                  int rows_a,
                  int cols_a,
                  int cols_b);

    /**
     * @brief Perform matrix multiplication using Intel intrinsics, accepts
     * flat arrays of 32 bit integers
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note Matrices must be of at least size 8x8
     * @overload
     */
    void mtx_mult(const int *A,
                  const int *B,
                  int *C,
                  int rows_a,
                  int cols_a,
                  int cols_b);

    void mtx_mult(const int *A,
                  const int *B,
                  int64_t *C,
                  int rows_a,
                  int cols_a,
                  int cols_b);

    void mtx_tpose(const int *A, int *C, int rows, int cols);

    /**
     * @brief Perform matrix subtraction using Intel intrinsics, accepts
     * vectors of type int
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note Matrices must be of at least size 8x8
     * @overload
     */
    void mtx_sub(const std::vector<std::vector<int>> &A,
                 const std::vector<std::vector<int>> &B,
                 std::vector<std::vector<int>> &C);

    /**
     * @brief Perform matrix subtraction using Intel intrinsics, accepts
     * vectors of type double
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note Matrices must be of at least size 4x4
     * @overload
     */
    void mtx_sub(const std::vector<std::vector<double>> &A,
                 const std::vector<std::vector<double>> &B,
                 std::vector<std::vector<double>> &C);

    /**
     * @brief Perform matrix multiplication using Intel intrinsics, accepts
     * vectors of type int
     * @param A input matrix A
     * @param B input matrix B
     * @param C output matrix C
     * @note matrices must be of at least size 8x8
     * @overload
     */
    void mtx_mult(const std::vector<std::vector<int>> &A,
                  const std::vector<std::vector<int>> &B,
                  std::vector<std::vector<int>> &C);

    /**
     * @brief Perform matrix multiplication using Intel intrinsics, accepts
     * vectors of type double
     * @param A input matrix A
     * @param B input matrix B
     * @param C output matrix C
     * @note matrices must be of at least size 4x4
     * @overload
     */
    void mtx_mult(const std::vector<std::vector<double>> &A,
                  const std::vector<std::vector<double>> &B,
                  std::vector<std::vector<double>> &C);
    /**
     * @brief Transpose matrices using Intel intrinsics
     * @param matrix Input matrix
     * @note Require matrices of at least size 8x8
     * @overload
     */
    void mtx_tpose(std::vector<std::vector<int>> &matrix);

    /**
     * @brief Transpose matrices using Intel intrinsics
     * @param matrix Input matrix
     * @note Require matrices of at least size 8x8
     * @overload
     */
    void mtx_tpose(std::vector<std::vector<double>> &matrix);

/**
 * @brief If system is ARM
 */
#elif defined(__ARM_ARCH_ISA_A64) || defined(__ARM_NEON) ||                    \
    defined(__ARM_ARCH) || defined(__aarch64__)
    /**
     * @brief Perform matrix addition using ARM intrinsics, accepts
     * vectors of type int
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note Matrices must be of at least size 8x8
     * @overload
     */
    void mtx_add(const std::vector<std::vector<int>> &A,
                 const std::vector<std::vector<int>> &B,
                 std::vector<std::vector<int>> &C);

    /**
     * @brief Perform matrix addition using ARM intrinsics, accepts
     * vectors of type double
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note Matrices must be of at least size 4x4
     * @overload
     */
    void mtx_add(const std::vector<std::vector<float>> &A,
                 const std::vector<std::vector<float>> &B,
                 std::vector<std::vector<float>> &C);

    /**
     * @brief Perform matrix subtraction using ARM intrinsics, accepts
     * vectors of type int
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note Matrices must be of at least size 8x8
     * @overload
     */
    void mtx_sub(const std::vector<std::vector<int>> &A,
                 const std::vector<std::vector<int>> &B,
                 std::vector<std::vector<int>> &C);

    /**
     * @brief Perform matrix subtraction using ARM intrinsics, accepts
     * vectors of type int
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note Matrices must be of at least size 4x4
     * @overload
     */
    void mtx_sub(const std::vector<std::vector<float>> &A,
                 const std::vector<std::vector<float>> &B,
                 std::vector<std::vector<float>> &C);

    /**
     * @brief Perform matrix multiplication using ARM intrinsics, accepts
     * vectors of type int
     * @param A input matrix A
     * @param B input matrix B
     * @param C output matrix C
     * @note matrices must be of at least size 8x8
     * @overload
     */
    void mtx_mult(const std::vector<std::vector<int>> &A,
                  const std::vector<std::vector<int>> &B,
                  std::vector<std::vector<int>> &C);

    /**
     * @brief Perform matrix multiplication using ARM intrinsics, accepts
     * vectors of type double
     * @param A input matrix A
     * @param B input matrix B
     * @param C output matrix C
     * @note matrices must be of at least size 4x4
     * @overload
     */
    void mtx_mult(const std::vector<std::vector<double>> &A,
                  const std::vector<std::vector<double>> &B,
                  std::vector<std::vector<double>> &C);

    /*void mtx_mult_strass(const std::vector<std::vector<int>> &A,
                         const std::vector<std::vector<int>> &B,
                         std::vector<std::vector<int>> &C);

    void mtx_mult_strass(const std::vector<std::vector<double>> &A,
                         const std::vector<std::vector<double>> &B,
                         std::vector<std::vector<double>> &C);
    */
    /**
     * @brief Transpose matrices using Intel intrinsics
     * @param matrix Input matrix
     * @note Require matrices of at least size 8x8
     * @overload
     */
    void mtx_tpose(std::vector<std::vector<int>> &matrix);

    /**
     * @brief Transpose matrices using Intel intrinsics
     * @param matrix Input matrix
     * @note Require matrices of at least size 4x4
     * @overload
     */
    void mtx_tpose(std::vector<std::vector<double>> &matrix);

#endif

    /**
     * @brief Perform matrix addition on two matrices as flat arrays
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @param rows Number of rows
     * @param cols Number of columns
     * @overload
     */
    template <typename T>
    void std_mtx_add(const T *A, const T *B, T *C, int rows, int cols) {
        // MTX A AND B MUST BE SAME SIZE
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                // perform matrix addition
                C[i * cols + j] = A[i * cols + j] + B[i * cols + j];
            }
        }
    }
    /**
     * @brief Perform matrix subtraction on two matrices as flat arrays
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @param rows Number of rows
     * @param cols Number of columns
     * @overload
     */
    template <typename T>
    void std_mtx_sub(const T *A, const T *B, T *C, int rows, int cols) {
        // MTX A AND B MUST BE SAME SIZE
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                // perform matrix addition
                C[i * cols + j] = A[i * cols + j] - B[i * cols + j];
            }
        }
    }

    template <typename T, typename U>
    void std_mtx_mult(const T *A,
                      const T *B,
                      U *C,
                      int rows_a,
                      int cols_a,
                      int cols_b) {
        for (int i = 0; i < rows_a; ++i) {
            for (int j = 0; j < cols_b; ++j) {
                U sum = 0; // Use T type for sum
                for (int k = 0; k < cols_a; ++k) {
                    sum += A[i * cols_a + k] * B[k * cols_b + j];
                }
                C[i * cols_b + j] = sum;
            }
        }
    }

    template <typename T>
    void std_mtx_tpose(const T *A, T *At, int rows, int cols) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                At[j * rows + i] = A[i * cols + j];
            }
        }
    }
    /**
     * @brief Perform matrix addition on two matrices as flat vectors
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @overload
     */
    template <typename T>
    void std_mtx_add(const std::vector<T> &A,
                     const std::vector<T> &B,
                     std::vector<T> &C);

    /**
     * @brief Perform matrix addition on two matrices as 2D vectors
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @overload
     */
    template <typename T>
    void std_mtx_add(const std::vector<std::vector<T>> &A,
                     const std::vector<std::vector<T>> &B,
                     std::vector<std::vector<T>> &C);

    /**
     * @brief Perform matrix subtraction on two matrices as 2D vectors
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @overload
     */
    template <typename T>
    void std_mtx_sub(const std::vector<std::vector<T>> &A,
                     const std::vector<std::vector<T>> &B,
                     std::vector<std::vector<T>> &C);

    /**
     * @brief Perform matrix multiplication on two matrices 2D vectors
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @overload
     */
    template <typename T>
    void std_mtx_mult(const std::vector<std::vector<T>> &A,
                      const std::vector<std::vector<T>> &B,
                      std::vector<std::vector<T>> &C);

    /**
     * @brief Performs matrix multiplication using the Strassen algorithm
     * @param A Input matrix A
     * @param B Input matrix B
     * @param C Output matrix C
     * @note The input matrices A and B should be square matrices with
     * dimensions that are powers of 2
     * @overload
     */
    /*void std_mtx_mult_strass(const std::vector<std::vector<int>> &A,
                             const std::vector<std::vector<int>> &B,
                             std::vector<std::vector<int>> &C);
    */
};

} // namespace linalg

} // namespace gpmp

#endif
