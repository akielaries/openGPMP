/*************************************************************************
 * Testing Mtx class operations
 ************************************************************************/
#include "../../include/linalg/mtx.hpp"
#include "../../include/linalg/mtx_tmpl.hpp"
#include "t_matrix.hpp"
#include <chrono>
#include <cmath>
#include <cstdint>
#include <gtest/gtest.h>
#include <iostream>
#include <limits.h>
#include <string>
#include <vector>

using namespace gpmp;
#define TEST_COUT std::cerr << "\033[32m[          ] [ INFO ] \033[0m"

namespace {

TEST(MatrixArrayTestI16, AdditionComparisonSmall) {
    int mtx_size = 300;
    // define input matrices A and B
    int16_t *A = new int16_t[mtx_size * mtx_size];
    int16_t *B = new int16_t[mtx_size * mtx_size];
    int16_t *expected = new int16_t[mtx_size * mtx_size];
    int16_t *result = new int16_t[mtx_size * mtx_size];

    // initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    // populate matrices A and B with random values
    for (int i = 0; i < mtx_size; ++i) {
        for (int j = 0; j < mtx_size; ++j) {
            A[i * mtx_size + j] = static_cast<int16_t>(distribution(gen));
            B[i * mtx_size + j] = static_cast<int16_t>(distribution(gen));
        }
    }

    gpmp::linalg::Mtx mtx;
    // expected result using the naive implementation
    mtx.std_mtx_add(A, B, expected, mtx_size, mtx_size);

    // result using the intrinsics implementation
    mtx.mtx_add(A, B, result, mtx_size, mtx_size);

    // compare the results
    ASSERT_TRUE(mtx_verif(expected, result, mtx_size, mtx_size));
    delete[] A;
    delete[] B;
    delete[] expected;
    delete[] result;
}

TEST(MatrixArrayTestI16, AdditionComparisonLarge) {
    int mtx_size = 1024;
    // define input matrices A and B
    int16_t *A = new int16_t[mtx_size * mtx_size];
    int16_t *B = new int16_t[mtx_size * mtx_size];
    int16_t *expected = new int16_t[mtx_size * mtx_size];
    int16_t *result = new int16_t[mtx_size * mtx_size];

    // initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    // populate matrices A and B with random values
    for (int i = 0; i < mtx_size; ++i) {
        for (int j = 0; j < mtx_size; ++j) {
            A[i * mtx_size + j] = static_cast<int16_t>(distribution(gen));
            B[i * mtx_size + j] = static_cast<int16_t>(distribution(gen));
        }
    }

    gpmp::linalg::Mtx mtx;
    // expected result using the naive implementation
    mtx.std_mtx_add(A, B, expected, mtx_size, mtx_size);

    // result using the intrinsics implementation
    mtx.mtx_add(A, B, result, mtx_size, mtx_size);

    // compare the results
    ASSERT_TRUE(mtx_verif(expected, result, mtx_size, mtx_size));
    delete[] A;
    delete[] B;
    delete[] expected;
    delete[] result;
}

TEST(MatrixArrayTestI16, AdditionPerformanceComparison) {
    int mtx_size = 1024;
    TEST_COUT << "Matrix size      : " << mtx_size << std::endl;
    // define input matrices A and B
    int16_t *A = new int16_t[mtx_size * mtx_size];
    int16_t *B = new int16_t[mtx_size * mtx_size];
    int16_t *expected = new int16_t[mtx_size * mtx_size];
    int16_t *result = new int16_t[mtx_size * mtx_size];

    // initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    // populate matrices A and B with random values
    for (int i = 0; i < mtx_size; ++i) {
        for (int j = 0; j < mtx_size; ++j) {
            A[i * mtx_size + j] = static_cast<int16_t>(distribution(gen));
            B[i * mtx_size + j] = static_cast<int16_t>(distribution(gen));
        }
    }

    gpmp::linalg::Mtx mtx;

    auto start_std = std::chrono::high_resolution_clock::now();

    // expected result using the naive implementation
    mtx.std_mtx_add(A, B, expected, mtx_size, mtx_size);

    auto end_std = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_std = end_std - start_std;

    auto start_intrin = std::chrono::high_resolution_clock::now();

    // result using the intrinsics implementation
    mtx.mtx_add(A, B, result, mtx_size, mtx_size);
    auto end_intrin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_intrin =
        end_intrin - start_intrin;

    TEST_COUT << "INTRINSIC Matrix Addition Time      : "
              << elapsed_seconds_intrin.count() << " seconds" << std::endl;
    TEST_COUT << "STANDARD  Matrix Addition Time      : "
              << elapsed_seconds_std.count() << " seconds" << std::endl;

    // compare the results
    ASSERT_TRUE(mtx_verif(expected, result, mtx_size, mtx_size));
    delete[] A;
    delete[] B;
    delete[] expected;
    delete[] result;
}

}
