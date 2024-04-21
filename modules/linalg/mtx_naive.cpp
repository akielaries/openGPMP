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
 * Standard/Naive Matrix Operations on Arrays
 *
 ************************************************************************/

/************************************************************************
 *
 * Standard/Naive Matrix Operations on vector<>
 *
 ************************************************************************/
// naive matrix addition algorithm on vector<>
template <typename T>
void gpmp::linalg::Mtx::std_mtx_add(const std::vector<T> &A,
                                    const std::vector<T> &B,
                                    std::vector<T> &C) {
    // MTX A AND B MUST BE SAME SIZE
    int rows = A.size();
    int cols = rows > 0 ? A.size() / rows : 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // perform matrix addition
            C[i * cols + j] = A[i * cols + j] + B[i * cols + j];
        }
    }
}

// instantiations for types accepted by templated std_mtx_add function for
// flat vectors
template void gpmp::linalg::Mtx::std_mtx_add(const std::vector<int> &A,
                                             const std::vector<int> &B,
                                             std::vector<int> &C);

template void gpmp::linalg::Mtx::std_mtx_add(const std::vector<double> &A,
                                             const std::vector<double> &B,
                                             std::vector<double> &C);

template void gpmp::linalg::Mtx::std_mtx_add(const std::vector<float> &A,
                                             const std::vector<float> &B,
                                             std::vector<float> &C);

/************************************************************************
 *
 * Standard/Naive Matrix Operations on vector<vector>
 *
 ************************************************************************/
// naive matrix addition algorithm on vector<vector>
template <typename T>
void gpmp::linalg::Mtx::std_mtx_add(const std::vector<std::vector<T>> &A,
                                    const std::vector<std::vector<T>> &B,
                                    std::vector<std::vector<T>> &C) {
    const int size = A.size();

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            // perform matrix addition
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// instantiations for types accepted by templated std_mtx_add function
template void
gpmp::linalg::Mtx::std_mtx_add(const std::vector<std::vector<int>> &A,
                               const std::vector<std::vector<int>> &B,
                               std::vector<std::vector<int>> &C);

template void
gpmp::linalg::Mtx::std_mtx_add(const std::vector<std::vector<double>> &A,
                               const std::vector<std::vector<double>> &B,
                               std::vector<std::vector<double>> &C);

template void
gpmp::linalg::Mtx::std_mtx_add(const std::vector<std::vector<float>> &A,
                               const std::vector<std::vector<float>> &B,
                               std::vector<std::vector<float>> &C);

// naive matrix subtraction algorithm
template <typename T>
void gpmp::linalg::Mtx::std_mtx_sub(const std::vector<std::vector<T>> &A,
                                    const std::vector<std::vector<T>> &B,
                                    std::vector<std::vector<T>> &C) {
    const int size = A.size();

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            // Perform matrix subtraction
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// instantiations for types accepted by templated std_mtx_sub function
template void
gpmp::linalg::Mtx::std_mtx_sub(const std::vector<std::vector<int>> &A,
                               const std::vector<std::vector<int>> &B,
                               std::vector<std::vector<int>> &C);

template void
gpmp::linalg::Mtx::std_mtx_sub(const std::vector<std::vector<double>> &A,
                               const std::vector<std::vector<double>> &B,
                               std::vector<std::vector<double>> &C);

template void
gpmp::linalg::Mtx::std_mtx_sub(const std::vector<std::vector<float>> &A,
                               const std::vector<std::vector<float>> &B,
                               std::vector<std::vector<float>> &C);

// naive matrix multiplication algorithm
template <typename T>
void gpmp::linalg::Mtx::std_mtx_mult(const std::vector<std::vector<T>> &A,
                                     const std::vector<std::vector<T>> &B,
                                     std::vector<std::vector<T>> &C) {
    assert(A.size() == B.size());
    assert(A[0].size() == B[0].size());

    int64_t nrows = A.size();
    int64_t ncols = A[0].size();

    for (int64_t i = 0; i < nrows; ++i) {
        for (int64_t j = 0; j < ncols; ++j) {
            C[i][j] = 0.0;
            for (int64_t k = 0; k < ncols; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// instantiations for types accepted by templated std_mtx_mult function
template void
gpmp::linalg::Mtx::std_mtx_mult(const std::vector<std::vector<int>> &A,
                                const std::vector<std::vector<int>> &B,
                                std::vector<std::vector<int>> &C);

template void
gpmp::linalg::Mtx::std_mtx_mult(const std::vector<std::vector<double>> &A,
                                const std::vector<std::vector<double>> &B,
                                std::vector<std::vector<double>> &C);

template void
gpmp::linalg::Mtx::std_mtx_mult(const std::vector<std::vector<float>> &A,
                                const std::vector<std::vector<float>> &B,
                                std::vector<std::vector<float>> &C);

/*
// naive implementation of Strassen matrix multiplication algorithm
void gpmp::linalg::Mtx::std_mtx_mult_strass(
    const std::vector<std::vector<int>> &A,
    const std::vector<std::vector<int>> &B, std::vector<std::vector<int>> &C) {
    int n = A.size();

    // base case: If the matrix size is 1x1, perform regular multiplication
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
    }

    // splitting the matrices into quadrants
    int half = n / 2;
    std::vector<std::vector<int>> A11(half, std::vector<int>(half));
    std::vector<std::vector<int>> A12(half, std::vector<int>(half));
    std::vector<std::vector<int>> A21(half, std::vector<int>(half));
    std::vector<std::vector<int>> A22(half, std::vector<int>(half));
    std::vector<std::vector<int>> B11(half, std::vector<int>(half));
    std::vector<std::vector<int>> B12(half, std::vector<int>(half));
    std::vector<std::vector<int>> B21(half, std::vector<int>(half));
    std::vector<std::vector<int>> B22(half, std::vector<int>(half));
    std::vector<std::vector<int>> C11(half, std::vector<int>(half));
    std::vector<std::vector<int>> C12(half, std::vector<int>(half));
    std::vector<std::vector<int>> C21(half, std::vector<int>(half));
    std::vector<std::vector<int>> C22(half, std::vector<int>(half));

    // dividing the input matrices into quadrants
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + half];
            A21[i][j] = A[i + half][j];
            A22[i][j] = A[i + half][j + half];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + half];
            B21[i][j] = B[i + half][j];
            B22[i][j] = B[i + half][j + half];
        }
    }

    // recursive calls for sub-matrix multiplication
    std::vector<std::vector<int>> M1(half, std::vector<int>(half));
    std::vector<std::vector<int>> M2(half, std::vector<int>(half));
    std::vector<std::vector<int>> M3(half, std::vector<int>(half));
    std::vector<std::vector<int>> M4(half, std::vector<int>(half));
    std::vector<std::vector<int>> M5(half, std::vector<int>(half));
    std::vector<std::vector<int>> M6(half, std::vector<int>(half));
    std::vector<std::vector<int>> M7(half, std::vector<int>(half));

    // M1 = (A11 + A22) * (B11 + B22)
    std_mtx_mult_strass(std_mtx_add(A11, A22), std_mtx_add(B11, B22), M1);
    // M2 = (A21 + A22) * B11
    std_mtx_mult_strass(std_mtx_add(A21, A22), B11, M2);
    // M3 = A11 * (B12 - B22)
    std_mtx_mult_strass(A11, std_mtx_sub(B12, B22), M3);
    // M4 = A22 * (B21 - B11)
    std_mtx_mult_strass(A22, std_mtx_sub(B21, B11), M4);
    // M5 = (A11 + A12) * B22
    std_mtx_mult_strass(std_mtx_add(A11, A12), B22, M5);
    // M6 = (A21 - A11) * (B11 + B12)
    std_mtx_mult_strass(std_mtx_sub(A21, A11), std_mtx_add(B11, B12), M6);
    // M7 = (A12 - A22) * (B21 + B22)
    std_mtx_mult_strass(std_mtx_sub(A12, A22), std_mtx_add(B21, B22), M7);

    // Computing the sub-matrices of the result matrix
    std::vector<std::vector<int>> C11_temp =

    std_mtx_add(std_mtx_sub(std_mtx_add(M1, M4), M5), M7);

    std::vector<std::vector<int>> C12_temp = std_mtx_add(M3, M5);
    std::vector<std::vector<int>> C21_temp = std_mtx_add(M2, M4);
    std::vector<std::vector<int>> C22_temp =
        std_mtx_add(std_mtx_sub(std_mtx_add(M1, M3), M2), M6);

    // Combining the sub-matrices to form the resulting matrix
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i][j] = C11_temp[i][j];
            C[i][j + half] = C12_temp[i][j];
            C[i + half][j] = C21_temp[i][j];
            C[i + half][j + half] = C22_temp[i][j];
        }
    }
}*/
