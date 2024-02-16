/**
 * helpers for matrix tests
 */

#ifndef T_MATRIX_HPP
#define T_MATRIX_HPP

#include <cmath>
#include <cstdint>
#include <gtest/gtest.h>
#include <iostream>
#include <limits.h>
#include <string>
#include <vector>


// utility test helper function to compare two matrices. used for verifying
// accelerated/non-standard implementations to the simple naive algorithm
// for matrix arithmetic operations
template <typename T>
bool mtx_verif(const std::vector<std::vector<T>> &A,
               const std::vector<std::vector<T>> &B) {
    if (A.size() != B.size() || A[0].size() != B[0].size()) {
        return false;
    }

    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < A[i].size(); ++j) {
            if (std::abs(A[i][j] - B[i][j]) >
                std::numeric_limits<T>::epsilon()) {
                return false;
            }
        }
    }
    return true;
}

template <typename T>
bool mtx_verif(const std::vector<T> &A, const std::vector<T> &B) {
    int rows = A.size();
    int cols = rows > 0 ? A.size() / rows : 0;

    if (A.size() != B.size()) {
        return false;
    }

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (A[i * cols + j] != B[i * cols + j]) {
                return false;
            }
        }
    }
    return true;
}

template <typename T>
bool mtx_verif(const T *A, const T *B, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (std::abs(A[i * cols + j] - B[i * cols + j]) >
                std::numeric_limits<T>::epsilon()) {
                return false;
            }
        }
    }
    return true;
}
template <typename T> void print_matrix(const T *matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << matrix[i * cols + j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


#endif
