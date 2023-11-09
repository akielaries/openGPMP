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
#include "../../include/linalg/mtx.hpp"
#include "../../include/linalg/mtx_tmpl.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <limits.h>
#include <string>
#include <vector>

using ::testing::DoubleLE;
using ::testing::FloatLE;
using ::testing::InitGoogleTest;
using namespace gpmp;
#define TEST_COUT std::cerr << "\033[32m[          ] [ INFO ] \033[0m"

namespace {

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
            if (A[i][j] != B[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// unit tests for Mtx class methods using Intel intrinsics
#if defined(__x86_64__) || defined(i386) || defined(__i386__) ||               \
    defined(__i386) || defined(__amd64__) || defined(__amd64)

// test case to compare the results of the intrinsics implementation with the
// naive implementation for matrix addition
TEST(ADD_MTX_SMALL, assert_intel_intrin) {
    int mtx_size = 32;
    TEST_COUT << "Matrix size = " << mtx_size << std::endl;
    // Define input matrices A and B
    std::vector<std::vector<int>> A(mtx_size, std::vector<int>(mtx_size));
    std::vector<std::vector<int>> B(mtx_size, std::vector<int>(mtx_size));
    std::vector<std::vector<int>> expected(mtx_size, std::vector<int>(mtx_size));
    std::vector<std::vector<int>> result(mtx_size,
                                         std::vector<int>(mtx_size));

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    // Populate matrices A and B with random values
    for (int i = 0; i < mtx_size; ++i) {
        for (int j = 0; j < mtx_size; ++j) {
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
        for (int i = 0; i < mtx_size; ++i) {
            for (int j = 0; j < mtx_size; ++j) {
                std::cout << expected[i][j] << " ";
            }
            std::cout << std::endl;
        }

        std::cout << "Matrix RESULT after addition:" << std::endl;
        for (int i = 0; i < mtx_size; ++i) {
            for (int j = 0; j < mtx_size; ++j) {
                std::cout << result[i][j] << " ";
            }
            std::cout << std::endl;
        }
    */

    // compare the results
    ASSERT_TRUE(mtx_verif(expected, result));
}

TEST(ADD_MTX_LARGE, assert_intel_intrin) {
    int mtx_size = 8192;
    TEST_COUT << "Matrix size = " << mtx_size << std::endl;

    // Define input matrices A and B
    std::vector<std::vector<int>> A(mtx_size, std::vector<int>(mtx_size));
    std::vector<std::vector<int>> B(mtx_size, std::vector<int>(mtx_size));
    std::vector<std::vector<int>> expected(mtx_size,
                                           std::vector<int>(mtx_size));
    std::vector<std::vector<int>> result(mtx_size,
                                         std::vector<int>(mtx_size));

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    // Populate matrices A and B with random values
    for (int i = 0; i < mtx_size; ++i) {
        for (int j = 0; j < mtx_size; ++j) {
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
        for (int i = 0; i < mtx_size; ++i) {
            for (int j = 0; j < mtx_size; ++j) {
                std::cout << expected[i][j] << " ";
            }
            std::cout << std::endl;
        }

        std::cout << "Matrix RESULT after addition:" << std::endl;
        for (int i = 0; i < mtx_size; ++i) {
            for (int j = 0; j < mtx_size; ++j) {
                std::cout << result[i][j] << " ";
            }
            std::cout << std::endl;
        }
    */

    // Compare the results
    ASSERT_TRUE(mtx_verif(expected, result));
}

// TODO: implement tests for large matrices, tests for ints, floats, doubles

// unit tests for Mtx class methods using ARM intrinsics
#elif defined(__ARM_ARCH_ISA_A64) || defined(__ARM_NEON) ||                    \
    defined(__ARM_ARCH) || defined(__aarch64__)

TEST(ADD_MATRICES, assert_arm_intrin) {
    int mtx_size = 32;
    // Define input matrices A and B
    std::vector<std::vector<int>> A(mtx_size, std::vector<int>(mtx_size));
    std::vector<std::vector<int>> B(mtx_size, std::vector<int>(mtx_size));
    std::vector<std::vector<int>> expected(mtx_size,
                                           std::vector<int>(mtx_size));
    std::vector<std::vector<int>> result(mtx_size,
                                         std::vector<int>(mtx_size));

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    // Populate matrices A and B with random values
    for (int i = 0; i < mtx_size; ++i) {
        for (int j = 0; j < mtx_size; ++j) {
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
        for (int i = 0; i < mtx_size; ++i) {
            for (int j = 0; j < mtx_size; ++j) {
                std::cout << expected[i][j] << " ";
            }
            std::cout << std::endl;
        }

        std::cout << "Matrix RESULT after addition:" << std::endl;
        for (int i = 0; i < mtx_size; ++i) {
            for (int j = 0; j < mtx_size; ++j) {
                std::cout << result[i][j] << " ";
            }
            std::cout << std::endl;
        }
    */

    // Compare the results
    ASSERT_TRUE(mtx_verif(expected, result));
}
#endif

/*
TEST(matrix_print, print_mtx) {
    gpmp::linalg::Matrix<int> mat(3, 4);
    mat.print_mtx();

    std::tuple<gpmp::linalg::Matrix<int>, gpmp::linalg::Matrix<int>> matrices =
        std::make_tuple(gpmp::linalg::Matrix<int>(5, 3),
                        gpmp::linalg::Matrix<int>(6, 4));

    std::get<0>(matrices).print_mtx();
    std::get<1>(matrices).print_mtx();
}*/

} // namespace
