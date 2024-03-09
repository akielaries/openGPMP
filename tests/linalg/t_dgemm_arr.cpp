#include "../../include/linalg/_dgemm.hpp"
#include "../../include/linalg/mtx.hpp"
#include "t_matrix.hpp"
#include <chrono>
#include <cmath>
#include <cstdint>
#include <gtest/gtest.h>
#include <iostream>
#include <limits.h>
#include <random>
#include <string>
#include <vector>

const double TOLERANCE = 1e-3;

using namespace gpmp;
#define TEST_COUT std::cerr << "\033[32m[          ] [ INFO ] \033[0m"

namespace {
TEST(GEMMArrayTest, DGEMMPerformanceComparison) {
    int mtx_size = 1024;

    TEST_COUT << "Matrix size      : " << mtx_size << std::endl;
    // define input matrices A and B
    double *A = new double[mtx_size * mtx_size];
    double *B = new double[mtx_size * mtx_size];
    double *expected = new double[mtx_size * mtx_size];
    double *result = new double[mtx_size * mtx_size];

    // initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribution(1.0, 100.0);

    // populate matrices A and B with random values
    for (int i = 0; i < mtx_size; ++i) {
        for (int j = 0; j < mtx_size; ++j) {
            A[i * mtx_size + j] = distribution(gen);
            B[i * mtx_size + j] = distribution(gen);
        }
    }

    gpmp::linalg::Mtx mtx;
    gpmp::linalg::DGEMM dgemm;
    auto start_std = std::chrono::high_resolution_clock::now();

    // expected result using the naive implementation
    mtx.std_mtx_mult(A, B, expected, mtx_size, mtx_size, mtx_size);

    auto end_std = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_std = end_std - start_std;

    auto start_intrin = std::chrono::high_resolution_clock::now();

    // result using the intrinsics implementation
    dgemm.dgemm_nn(mtx_size,
                   mtx_size,
                   mtx_size,
                   1.0,
                   A,
                   mtx_size,
                   1,
                   B,
                   mtx_size,
                   1,
                   0.0,
                   result,
                   mtx_size,
                   1);

    auto end_intrin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_intrin =
        end_intrin - start_intrin;

    TEST_COUT << "ROUTINE   Matrix Multiplication Time      : "
              << elapsed_seconds_intrin.count() << " seconds" << std::endl;
    TEST_COUT << "STANDARD  Matrix Multiplication Time      : "
              << elapsed_seconds_std.count() << " seconds" << std::endl;

    // compare the results
    /*for (int i = 0; i < mtx_size; i++) {
        for (int j = 0; j < mtx_size; j++) {
            EXPECT_NEAR(expected[i * mtx_size + j],
                        result[i * mtx_size + j],
                        TOLERANCE);
        }
    }*/
    
    int count = 0;
    int matches = 0;
    int i;

    for (i = 0; i < mtx_size * mtx_size; ++i) {
        // printf("Comparing element at index %d: %.2f vs %.2f\n", i, expected[i], result[i]);
        if (expected[i] != result[i]) {
            count++;
        } else {
            matches++;
        }
    }
    printf("MISMATCHES  / TOTAL : %d/%d\n", count, i);
    printf("MATCHES     / TOTAL : %d/%d\n", matches, i);
    

    //ASSERT_TRUE(mtx_verif(expected, result, mtx_size, mtx_size));

    delete[] A;
    delete[] B;
    delete[] expected;
    delete[] result;
}

} // namespace
