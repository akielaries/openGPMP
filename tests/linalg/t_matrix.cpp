/*************************************************************************
 *
 *  Project
 *                        __  __ _______ _____  _  __
 *                       |  \/  |__   __|  __ \| |/ /
 *  ___  _ __   ___ _ __ | \  / |  | |  | |__) | ' /
 * / _ \| '_ \ / _ \ '_ \| |\/| |  | |  |  ___/|  <
 *| (_) | |_) |  __/ | | | |  | |  | |  | |    | . \
 * \___/| .__/ \___|_| |_|_|  |_|  |_|  |_|    |_|\_\
 *      | |
 *      |_|
 *
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

/*
 * Testing Linear Algebra Operations
 */
#include "../../include/linalg/matrix.hpp"
#include "../../include/linalg/mtx.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <limits.h>
#include <string>
#include <vector>

using ::testing::DoubleLE;
using ::testing::FloatLE;
using ::testing::InitGoogleTest;
using namespace gpmp;

namespace {

// Test fixture for the matrix addition tests
class MatrixAdditionTest : public ::testing::Test {
  protected:
    // Helper function to compare two matrices
    template <typename T>
    bool matricesAreEqual(const std::vector<std::vector<T>> &A,
                          const std::vector<std::vector<T>> &B) {
        if (A.size() != B.size() || A[0].size() != B[0].size())
            return false;

        for (size_t i = 0; i < A.size(); ++i) {
            for (size_t j = 0; j < A[i].size(); ++j) {
                if (A[i][j] != B[i][j])
                    return false;
            }
        }

        return true;
    }
};
// unit tests for Mtx class methods using Intel intrinsics
#if defined(__x86_64__) || defined(i386) || defined(__i386__) ||               \
    defined(__i386) || defined(__amd64__) || defined(__amd64)

// test case to compare the results of the intrinsics implementation with the
// naive implementation for matrix addition
TEST_MTX_ADD_INTEL(mtx_add, assert_intel_intrin) {
    int matrixSize = 32;
    // Define input matrices A and B
    std::vector<std::vector<int>> A(matrixSize, std::vector<int>(matrixSize));
    std::vector<std::vector<int>> B(matrixSize, std::vector<int>(matrixSize));
    std::vector<std::vector<int>> expected(matrixSize,
                                           std::vector<int>(matrixSize));
    std::vector<std::vector<int>> result(matrixSize,
                                         std::vector<int>(matrixSize));

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    // Populate matrices A and B with random values
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            A[i][j] = distribution(gen);
            B[i][j] = distribution(gen);
        }
    }

    gpmp::linalg::Mtx mtx;
    // expected result using the naive implementation
    mtx.std_mtx_add(A, B, expected);

    // result using the intrinsics implementation
    mtx.mtx_add(A, B, result);

    /*
        std::cout << "Matrix EXPECTED after addition:" << std::endl;
        for (int i = 0; i < matrixSize; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                std::cout << expected[i][j] << " ";
            }
            std::cout << std::endl;
        }

        std::cout << "Matrix RESULT after addition:" << std::endl;
        for (int i = 0; i < matrixSize; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                std::cout << result[i][j] << " ";
            }
            std::cout << std::endl;
        }
    */

    // Compare the results
    ASSERT_TRUE(matricesAreEqual(expected, result));
}

// unit tests for Mtx class methods using ARM intrinsics
#elif defined(__ARM_ARCH_ISA_A64) || defined(__ARM_NEON) ||                    \
    defined(__ARM_ARCH) || defined(__aarch64__)

TEST_MTX_ADD_ARM(mtx_add, assert_arm_intrin) {
    int matrixSize = 32;
    // Define input matrices A and B
    std::vector<std::vector<int>> A(matrixSize, std::vector<int>(matrixSize));
    std::vector<std::vector<int>> B(matrixSize, std::vector<int>(matrixSize));
    std::vector<std::vector<int>> expected(matrixSize,
                                           std::vector<int>(matrixSize));
    std::vector<std::vector<int>> result(matrixSize,
                                         std::vector<int>(matrixSize));

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    // Populate matrices A and B with random values
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            A[i][j] = distribution(gen);
            B[i][j] = distribution(gen);
        }
    }

    gpmp::linalg::Mtx mtx;
    // expected result using the naive implementation
    mtx.std_mtx_add(A, B, expected);

    // result using the intrinsics implementation
    mtx.mtx_add(A, B, result);

    /*
        std::cout << "Matrix EXPECTED after addition:" << std::endl;
        for (int i = 0; i < matrixSize; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                std::cout << expected[i][j] << " ";
            }
            std::cout << std::endl;
        }

        std::cout << "Matrix RESULT after addition:" << std::endl;
        for (int i = 0; i < matrixSize; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                std::cout << result[i][j] << " ";
            }
            std::cout << std::endl;
        }
    */

    // Compare the results
    ASSERT_TRUE(matricesAreEqual(expected, result));
}
#endif

TEST(matrix_print, print_mtx) {
    gpmp::Matrix<int> mat(3, 4);
    mat.print_mtx();

    std::tuple<Matrix<int>, Matrix<int>> matrices =
        std::make_tuple(Matrix<int>(5, 3), Matrix<int>(6, 4));

    std::get<0>(matrices).print_mtx();
    std::get<1>(matrices).print_mtx();
}

} // namespace
