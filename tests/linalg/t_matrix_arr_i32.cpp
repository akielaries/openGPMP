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
#define INFO_COUT                                                              \
    std::cerr << "\033[32m[          ] [ INFO ] \033[0m\033[1;31m\033[1m"
namespace {

TEST(MatrixArrayTestI32, AdditionComparisonSmall) {
    INFO_COUT << "MATRIX (as Arrays) INT32" << std::endl;

    int mtx_size = 184;
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
    // expected result using the naive implementation
    mtx.std_mtx_add(A, B, expected, mtx_size, mtx_size);

    // result using the intrinsics implementation
    mtx.mtx_add(A, B, result, mtx_size, mtx_size);

    /*
    std::cout << "Matrix A:" << std::endl;
    print_matrix(A, mtx_size, mtx_size);

    std::cout << "Matrix B:" << std::endl;
    print_matrix(B, mtx_size, mtx_size);

    std::cout << "Matrix EXPECTED after addition:" << std::endl;
    print_matrix(expected, mtx_size, mtx_size);

    std::cout << "Matrix RESULT after addition:" << std::endl;
    print_matrix(result, mtx_size, mtx_size);
  */
    // compare the results
    ASSERT_TRUE(mtx_verif(expected, result, mtx_size, mtx_size));
    delete[] A;
    delete[] B;
    delete[] expected;
    delete[] result;
}

TEST(MatrixArrayTestI32, AdditionComparisonLarge) {
    int mtx_size = 1024;
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
    // expected result using the naive implementation
    mtx.std_mtx_add(A, B, expected, mtx_size, mtx_size);

    // result using the intrinsics implementation
    mtx.mtx_add(A, B, result, mtx_size, mtx_size);

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
    ASSERT_TRUE(mtx_verif(expected, result, mtx_size, mtx_size));
    delete[] A;
    delete[] B;
    delete[] expected;
    delete[] result;
}

TEST(MatrixArrayTestI32, AdditionPerformanceComparison) {
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

TEST(MatrixArrayTestI32, SubtractionPerformanceComparison) {
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
    mtx.std_mtx_sub(A, B, expected, mtx_size, mtx_size);

    auto end_std = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_std = end_std - start_std;

    auto start_intrin = std::chrono::high_resolution_clock::now();

    // result using the intrinsics implementation
    mtx.mtx_sub(A, B, result, mtx_size, mtx_size);
    auto end_intrin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_intrin =
        end_intrin - start_intrin;

    TEST_COUT << "INTRINSIC Matrix Subtraction Time      : "
              << elapsed_seconds_intrin.count() << " seconds" << std::endl;
    TEST_COUT << "STANDARD  Matrix Subtraction Time      : "
              << elapsed_seconds_std.count() << " seconds" << std::endl;

    // compare the results
    ASSERT_TRUE(mtx_verif(expected, result, mtx_size, mtx_size));
    delete[] A;
    delete[] B;
    delete[] expected;
    delete[] result;
}

TEST(MatrixArrayTestI32, MultiplicationPerformanceComparison) {
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

    auto start_intrin = std::chrono::high_resolution_clock::now();

    // result using the intrinsics implementation
    mtx.mtx_mult(A, B, result, mtx_size, mtx_size, mtx_size);
    auto end_intrin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_intrin =
        end_intrin - start_intrin;

    TEST_COUT << "INTRINSIC Matrix Multiplication Time      : "
              << elapsed_seconds_intrin.count() << " seconds" << std::endl;
    TEST_COUT << "STANDARD  Matrix Multiplication Time      : "
              << elapsed_seconds_std.count() << " seconds" << std::endl;

    // compare the results
    ASSERT_TRUE(mtx_verif(expected, result, mtx_size, mtx_size));
    delete[] A;
    delete[] B;
    delete[] expected;
    delete[] result;
}

TEST(MatrixArrayTestI32_I64, MultiplicationPerformanceComparison) {
    int mtx_size = 1024;
    TEST_COUT << "Matrix size      : " << mtx_size << std::endl;
    // define input matrices A and B
    int *A = new int[mtx_size * mtx_size];
    int *B = new int[mtx_size * mtx_size];
    int64_t *expected = new int64_t[mtx_size * mtx_size];
    int64_t *result = new int64_t[mtx_size * mtx_size];

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

    auto start_intrin = std::chrono::high_resolution_clock::now();

    // result using the intrinsics implementation
    mtx.mtx_mult(A, B, result, mtx_size, mtx_size, mtx_size);
    auto end_intrin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_intrin =
        end_intrin - start_intrin;

    TEST_COUT << "INTRINSIC Matrix Multiplication Time      : "
              << elapsed_seconds_intrin.count() << " seconds" << std::endl;
    TEST_COUT << "STANDARD  Matrix Multiplication Time      : "
              << elapsed_seconds_std.count() << " seconds" << std::endl;

    // compare the results
    ASSERT_TRUE(mtx_verif(expected, result, mtx_size, mtx_size));
    delete[] A;
    delete[] B;
    delete[] expected;
    delete[] result;
}

TEST(MatrixArrayTestI32, TransposePerformanceComparison) {
    int mtx_size = 1024;
    TEST_COUT << "Matrix size      : " << mtx_size << std::endl;
    // define input matrices A and B
    int *A = new int[mtx_size * mtx_size];
    int *At_naive = new int[mtx_size * mtx_size];
    int *At_intrin = new int[mtx_size * mtx_size];

    // initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    // populate matrix A with random values
    for (int i = 0; i < mtx_size; ++i) {
        for (int j = 0; j < mtx_size; ++j) {
            A[i * mtx_size + j] = distribution(gen);
        }
    }

    gpmp::linalg::Mtx mtx;

    auto start_std = std::chrono::high_resolution_clock::now();

    // Calculate transpose using the naive implementation
    mtx.std_mtx_tpose(A, At_naive, mtx_size, mtx_size);

    auto end_std = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_std = end_std - start_std;

    auto start_intrin = std::chrono::high_resolution_clock::now();

    // Calculate transpose using the AVX2-accelerated implementation
    mtx.mtx_tpose(A, At_intrin, mtx_size, mtx_size);

    auto end_intrin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_intrin =
        end_intrin - start_intrin;

    TEST_COUT << "INTRINSIC Matrix Transpose Time      : "
              << elapsed_seconds_intrin.count() << " seconds" << std::endl;

    TEST_COUT << "STANDARD  Matrix Transpose Time      : "
              << elapsed_seconds_std.count() << " seconds" << std::endl;

    // Compare the results
    ASSERT_TRUE(mtx_verif(At_naive, At_intrin, mtx_size, mtx_size));

    delete[] A;
    delete[] At_naive;
    delete[] At_intrin;
}

} // namespace
