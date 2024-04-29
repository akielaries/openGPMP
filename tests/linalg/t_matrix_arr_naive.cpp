#include "t_matrix.hpp"
#include <chrono>
#include <cmath>
#include <cstdint>
#include <gtest/gtest.h>
#include <iostream>
#include <limits.h>
#include <openGPMP/linalg/mtx.hpp>
#include <openGPMP/linalg/mtx_tmpl.hpp>
#include <string>
#include <vector>

using namespace gpmp;
#define TEST_COUT std::cerr << "\033[32m[          ] [ INFO ] \033[0m"
#define INFO_COUT                                                              \
    std::cerr << "\033[32m[          ] [ INFO ] \033[0m\033[1;34m\033[1m"
namespace {
TEST(MatrixArrayTest, BasicTest) {
    INFO_COUT << "MATRIX (as Arrays) NAIVE" << std::endl;

    gpmp::linalg::Mtx mtx;
    const int rowsA = 2;
    const int colsA = 3;
    const int colsB = 2;

    // Define matrices A, B, and expected result C
    int A[rowsA * colsA] = {1, 2, 3, 4, 5, 6};
    int B[colsA * colsB] = {7, 8, 9, 10, 11, 12};

    int expectedC[rowsA * colsB] = {58, 64, 139, 154};

    // Initialize result matrix C
    int C[rowsA * colsB];

    // Perform matrix multiplication
    mtx.std_mtx_mult(A, B, C, rowsA, colsA, colsB);

    // Check if result matrix C matches expectedC
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            EXPECT_EQ(C[i * colsB + j], expectedC[i * colsB + j]);
        }
    }
}

} // namespace
