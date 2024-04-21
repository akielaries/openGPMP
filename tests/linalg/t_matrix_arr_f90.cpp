/*************************************************************************
 * Testing Mtx class operations
 ************************************************************************/
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

TEST(FORTRAN90MatrixArrayTestI32, AdditionPerformanceComparison) {
    INFO_COUT << "MATRIX (as FORTRAN Arrays) INT32" << std::endl;

    int mtx_size = 1024;
    TEST_COUT << "Matrix size      : " << mtx_size << std::endl;
    // define input matrices A and B
    int *A = new int[mtx_size * mtx_size];
    int *B = new int[mtx_size * mtx_size];
    int *expected = new int[mtx_size * mtx_size];
    int *result = new int[mtx_size * mtx_size];

    // initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    // populate matrices A and B with random values
    for (int i = 0; i < mtx_size; ++i) {
        for (int j = 0; j < mtx_size; ++j) {
            A[i * mtx_size + j] = distribution(gen);
            B[i * mtx_size + j] = distribution(gen);
        }
    }

    gpmp::linalg::Mtx mtx;
    auto start_std = std::chrono::high_resolution_clock::now();

    // expected result using the naive implementation
    mtx.std_mtx_add(A, B, expected, mtx_size, mtx_size);

    auto end_std = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_std = end_std - start_std;

    auto start_f90 = std::chrono::high_resolution_clock::now();

    // result using the f90sics implementation
    mtx.mtx_add_f90(A, B, result, mtx_size);
    auto end_f90 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_f90 = end_f90 - start_f90;

    TEST_COUT << "FORTRAN90 Matrix Addition Time      : "
              << elapsed_seconds_f90.count() << " seconds" << std::endl;
    TEST_COUT << "STANDARD  Matrix Addition Time      : "
              << elapsed_seconds_std.count() << " seconds" << std::endl;

    // compare the results
    ASSERT_TRUE(mtx_verif(expected, result, mtx_size, mtx_size));
    delete[] A;
    delete[] B;
    delete[] expected;
    delete[] result;
}

TEST(FORTRAN90MatrixArrayTestI32, MultiplicationVerification) {
    int mtx_size = 4;

    TEST_COUT << "Matrix size      : " << mtx_size << std::endl;

    int A[] = {59, 84, 97, 92, 42, 26, 44, 81, 98, 18, 84, 97, 77, 100, 55, 21};

    int B[] = {36, 59, 39, 11, 89, 93, 16, 31, 80, 71, 25, 68, 71, 92, 29, 61};
    int exp[] = {23892,
                 26644,
                 8738,
                 15461,
                 13097,
                 15472,
                 5503,
                 9201,
                 18737,
                 22344,
                 9023,
                 13265,
                 17563,
                 19680,
                 6587,
                 8968};
    int *expected = new int[mtx_size * mtx_size];
    int *result = new int[mtx_size * mtx_size];

    gpmp::linalg::Mtx mtx;
    auto start_std = std::chrono::high_resolution_clock::now();

    // expected result using the naive implementation
    mtx.std_mtx_mult(A, B, expected, mtx_size, mtx_size, mtx_size);

    auto end_std = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_std = end_std - start_std;

    auto start_f90 = std::chrono::high_resolution_clock::now();

    // result using the f90sics implementation
    mtx.mtx_mult_f90(A, B, result, mtx_size, mtx_size, mtx_size);
    auto end_f90 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_f90 = end_f90 - start_f90;

    TEST_COUT << "FORTRAN90 Matrix Multiplication Time      : "
              << elapsed_seconds_f90.count() << " seconds" << std::endl;
    TEST_COUT << "STANDARD  Matrix Multiplication Time      : "
              << elapsed_seconds_std.count() << " seconds" << std::endl;

    // compare the results
    ASSERT_TRUE(mtx_verif(exp, result, mtx_size, mtx_size));
    delete[] expected;
    delete[] result;
}

TEST(FORTRAN90MatrixArrayTestI32, MultiplicationPerformanceComparison) {
    int mtx_size = 1024;

    TEST_COUT << "Matrix size      : " << mtx_size << std::endl;
    // define input matrices A and B
    int *A = new int[mtx_size * mtx_size];
    int *B = new int[mtx_size * mtx_size];

    int *expected = new int[mtx_size * mtx_size];
    int *result = new int[mtx_size * mtx_size];

    // initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    // populate matrices A and B with random values
    for (int i = 0; i < mtx_size; ++i) {
        for (int j = 0; j < mtx_size; ++j) {
            A[i * mtx_size + j] = distribution(gen);
            B[i * mtx_size + j] = distribution(gen);
        }
    }

    gpmp::linalg::Mtx mtx;
    auto start_std = std::chrono::high_resolution_clock::now();

    // expected result using the naive implementation
    mtx.std_mtx_mult(A, B, expected, mtx_size, mtx_size, mtx_size);

    auto end_std = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_std = end_std - start_std;

    auto start_f90 = std::chrono::high_resolution_clock::now();

    // result using the f90sics implementation
    mtx.mtx_mult_f90(A, B, result, mtx_size, mtx_size, mtx_size);
    auto end_f90 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_f90 = end_f90 - start_f90;

    TEST_COUT << "FORTRAN90 Matrix Multiplication Time      : "
              << elapsed_seconds_f90.count() << " seconds" << std::endl;
    TEST_COUT << "STANDARD  Matrix Multiplication Time      : "
              << elapsed_seconds_std.count() << " seconds" << std::endl;

    // compare the results
    ASSERT_TRUE(mtx_verif(expected, result, mtx_size, mtx_size));
    delete[] A;
    delete[] B;
    delete[] expected;
    delete[] result;
}

} // namespace
