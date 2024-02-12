/**
 * Unit tests for the Linear Algebra module's Vector operations
 */
#include "../../include/linalg/vector.hpp"
#include <chrono>
#include <cstdlib>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

const double TOLERANCE = 1e-3;

#define TEST_COUT std::cerr << "\033[32m[          ] [ INFO ] \033[0m"

TEST(VectorArithTestDouble, Addition) {
    std::vector<double> vec1 = {1.0, 2.0, 3.0};
    std::vector<double> vec2 = {4.0, 5.0, 6.0};
    std::vector<double> result;

    gpmp::linalg::std_vector_add(vec1, vec2, result);

    ASSERT_EQ(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0], 5.0);
    EXPECT_DOUBLE_EQ(result[1], 7.0);
    EXPECT_DOUBLE_EQ(result[2], 9.0);
}

// Test cases for gpmp::linalg::std_vector_sub function
TEST(VectorArithTestDouble, Subtraction) {
    std::vector<double> vec1 = {4.0, 5.0, 6.0};
    std::vector<double> vec2 = {1.0, 2.0, 3.0};
    std::vector<double> result;

    gpmp::linalg::std_vector_sub(vec1, vec2, result);

    ASSERT_EQ(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0], 3.0);
    EXPECT_DOUBLE_EQ(result[1], 3.0);
    EXPECT_DOUBLE_EQ(result[2], 3.0);
}

// Test cases for gpmp::linalg::std_vector_mult function
TEST(VectorArithTestDouble, Multiplication) {
    std::vector<double> vec = {1.0, 2.0, 3.0};
    std::vector<double> result;

    gpmp::linalg::std_vector_mult(vec, 2.0, result);

    ASSERT_EQ(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0], 2.0);
    EXPECT_DOUBLE_EQ(result[1], 4.0);
    EXPECT_DOUBLE_EQ(result[2], 6.0);
}

// Test cases for std_dot_product function
TEST(VectorArithTestDouble, DotProduct) {
    std::vector<double> vec1 = {1.0, 2.0, 3.0};
    std::vector<double> vec2 = {4.0, 5.0, 6.0};

    double result = gpmp::linalg::std_dot_product(vec1, vec2);

    EXPECT_DOUBLE_EQ(result, 32.0);
}

// Test cases for std_cross_product function
TEST(VectorArithTestDouble, CrossProduct) {
    std::vector<double> vec1 = {1.0, 2.0, 3.0};
    std::vector<double> vec2 = {3.0, 4.0, 5.0};
    std::vector<double> result(3);

    gpmp::linalg::std_cross_product(vec1, vec2, result);

    ASSERT_EQ(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0], -2);
    EXPECT_DOUBLE_EQ(result[1], 4);
    EXPECT_DOUBLE_EQ(result[2], -2);
}

TEST(VectorArithTestDouble, Magnitude) {
    std::vector<double> vec = {3.0, 4.0};
    double norm = gpmp::linalg::std_vector_norm(vec);
    EXPECT_DOUBLE_EQ(norm, 5.0);
}

// Unit tests for gpmp::linalg::std_vector_normalize function
TEST(VectorArithTestDouble, Normalization) {
    std::vector<double> vec = {3.0, 4.0};
    std::vector<double> result;
    gpmp::linalg::std_vector_normalize(vec, result);
    EXPECT_DOUBLE_EQ(result[0], 0.6);
    EXPECT_DOUBLE_EQ(result[1], 0.8);
}

// Unit tests for gpmp::linalg::std_vector_projection function
TEST(VectorArithTestDouble, Projection) {
    std::vector<double> vec = {3.0, 2.0};
    std::vector<double> onto_vec = {4.0, 0.0};
    std::vector<double> result;
    gpmp::linalg::std_vector_projection(vec, onto_vec, result);
    EXPECT_DOUBLE_EQ(result[0], 3.0);
    EXPECT_DOUBLE_EQ(result[1], 0.0);
}

TEST(VectorArithTestInt, Addition) {
    std::vector<int> vec1 = {1, 2, 3};
    std::vector<int> vec2 = {4, 5, 6};
    std::vector<int> result;

    gpmp::linalg::std_vector_add(vec1, vec2, result);

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 5);
    EXPECT_EQ(result[1], 7);
    EXPECT_EQ(result[2], 9);
}

// Unit tests for std_vector_sub function
TEST(VectorArithTestInt, Subtraction) {
    std::vector<int> vec1 = {4, 5, 6};
    std::vector<int> vec2 = {1, 2, 3};
    std::vector<int> result;

    gpmp::linalg::std_vector_sub(vec1, vec2, result);

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 3);
    EXPECT_EQ(result[1], 3);
    EXPECT_EQ(result[2], 3);
}

// Unit tests for std_vector_mult function
TEST(VectorArithTestInt, Multiplication) {
    std::vector<int> vec = {1, 2, 3};
    std::vector<int> result;

    gpmp::linalg::std_vector_mult(vec, 2, result);

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 2);
    EXPECT_EQ(result[1], 4);
    EXPECT_EQ(result[2], 6);
}

// Unit tests for std_dot_product function
TEST(VectorArithTestInt, DotProduct) {
    std::vector<int> vec1 = {1, 2, 3};
    std::vector<int> vec2 = {4, 5, 6};

    int result = gpmp::linalg::std_dot_product(vec1, vec2);

    EXPECT_EQ(result, 32);
}

// Unit tests for std_cross_product function
TEST(VectorArithTestInt, CrossProduct) {
    std::vector<int> vec1 = {1, 0, 0};
    std::vector<int> vec2 = {0, 1, 0};
    std::vector<int> result(3);

    gpmp::linalg::std_cross_product(vec1, vec2, result);

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 0);
    EXPECT_EQ(result[2], 1);
}

TEST(VectorArithTestInt, Magnitude) {
    std::vector<int> vec = {3, 4};
    double norm = gpmp::linalg::std_vector_norm(vec);
    EXPECT_DOUBLE_EQ(norm, 5.0);
}

// Unit tests for std_vector_normalize function
TEST(VectorArithTestInt, Normalization) {
    std::vector<int> vec = {3, 4};
    std::vector<double> result;
    gpmp::linalg::std_vector_normalize(vec, result);
    EXPECT_DOUBLE_EQ(result[0], 0.6);
    EXPECT_DOUBLE_EQ(result[1], 0.8);
}

// Unit tests for std_vector_projection function
TEST(VectorArithTestInt, Projection) {
    std::vector<int> vec = {3, 2};
    std::vector<int> onto_vec = {4, 0};
    std::vector<double> result;
    gpmp::linalg::std_vector_projection(vec, onto_vec, result);
    EXPECT_DOUBLE_EQ(result[0], 3.0);
    EXPECT_DOUBLE_EQ(result[1], 0.0);
}

#if defined(__AVX2__) || defined(__AVX__)

TEST(VectorArithINTRINSICTestInt, Addition) {
    // Create input vectors
    std::vector<int> vec1 = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> vec2 = {8, 7, 6, 5, 4, 3, 2, 1};
    std::vector<int> result(vec1.size());

    // Perform vector addition
    gpmp::linalg::vector_add(vec1, vec2, result);

    // Check the result
    EXPECT_EQ(result.size(), vec1.size());
    for (size_t i = 0; i < result.size(); ++i) {
        EXPECT_EQ(result[i], vec1[i] + vec2[i]);
    }
}

TEST(VectorArithINTRINSICTestInt, AdditionComparison) {
    // Create input vectors
    std::vector<int> vec1 = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> vec2 = {8, 7, 6, 5, 4, 3, 2, 1};
    std::vector<int> result_avx2(vec1.size());
    std::vector<int> result_std(vec1.size());

    // Perform vector addition using INTRINSIC and standard methods
    gpmp::linalg::vector_add(vec1, vec2, result_avx2);
    gpmp::linalg::std_vector_add(vec1, vec2, result_std);

    // Check if the results match
    ASSERT_EQ(result_avx2.size(), result_std.size());
    for (size_t i = 0; i < result_avx2.size(); ++i) {
        EXPECT_EQ(result_avx2[i], result_std[i]);
    }
}

TEST(VectorArithINTRINSICTestInt, AdditionComparisonRandom) {
    const size_t size = 4097;

    // Create random number generator
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(-1000, 1000);

    // Generate random vectors
    std::vector<int> vec1(size);
    std::vector<int> vec2(size);
    for (size_t i = 0; i < size; ++i) {
        vec1[i] = dist(rng);
        vec2[i] = dist(rng);
    }

    // Perform vector addition using INTRINSIC and standard methods
    std::vector<int> result_avx2(size);
    std::vector<int> result_std(size);
    gpmp::linalg::vector_add(vec1, vec2, result_avx2);
    gpmp::linalg::std_vector_add(vec1, vec2, result_std);

    // Check if the results match
    ASSERT_EQ(result_avx2.size(), result_std.size());
    for (size_t i = 0; i < result_avx2.size(); ++i) {
        EXPECT_EQ(result_avx2[i], result_std[i]);
    }
}

TEST(VectorArithINTRINSICTestInt, AdditionPerformanceComparison) {
    const size_t size = 4097 * 4097;

    TEST_COUT << "Vector size      : " << size << std::endl;
    // Create random number generator
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(-1000, 1000);

    // Generate random vectors
    std::vector<int> vec1(size);
    std::vector<int> vec2(size);
    for (size_t i = 0; i < size; ++i) {
        vec1[i] = dist(rng);
        vec2[i] = dist(rng);
    }

    // Measure execution time for INTRINSIC vector addition
    std::vector<int> result_avx2(size);

    auto start_avx2 = std::chrono::high_resolution_clock::now();
    gpmp::linalg::vector_add(vec1, vec2, result_avx2);
    auto end_avx2 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_seconds_avx2 = end_avx2 - start_avx2;

    // Measure execution time for standard vector addition
    std::vector<int> result_std(size);

    auto start_std = std::chrono::high_resolution_clock::now();
    gpmp::linalg::std_vector_add(vec1, vec2, result_std);
    auto end_std = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_seconds_std = end_std - start_std;

    TEST_COUT << "INTRINSIC Vector Addition Time      : "
              << elapsed_seconds_avx2.count() << " seconds" << std::endl;

    TEST_COUT << "STANDARD  Vector Addition Time      : "
              << elapsed_seconds_std.count() << " seconds" << std::endl;
}

TEST(VectorArithINTRINSICTestInt, Subtraction) {
    // Create input vectors
    std::vector<int> vec1 = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> vec2 = {8, 7, 6, 5, 4, 3, 2, 1};
    std::vector<int> result(vec1.size());

    // Perform vector subtraction
    gpmp::linalg::vector_sub(vec1, vec2, result);

    // Check the result
    EXPECT_EQ(result.size(), vec1.size());
    for (size_t i = 0; i < result.size(); ++i) {
        EXPECT_EQ(result[i], vec1[i] - vec2[i]);
    }
}

TEST(VectorArithINTRINSICTestInt, SubtractionComparison) {
    // Create input vectors
    std::vector<int> vec1 = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> vec2 = {8, 7, 6, 5, 4, 3, 2, 1};
    std::vector<int> result_avx2(vec1.size());
    std::vector<int> result_std(vec1.size());

    // Perform vector subtraction using INTRINSIC and standard methods
    gpmp::linalg::vector_sub(vec1, vec2, result_avx2);
    gpmp::linalg::std_vector_sub(vec1, vec2, result_std);

    // Check if the results match
    ASSERT_EQ(result_avx2.size(), result_std.size());
    for (size_t i = 0; i < result_avx2.size(); ++i) {
        EXPECT_EQ(result_avx2[i], result_std[i]);
    }
}

TEST(VectorArithINTRINSICTestInt, SubtractionComparisonRandom) {
    const size_t size = 4097;

    // Create random number generator
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(-1000, 1000);

    // Generate random vectors
    std::vector<int> vec1(size);
    std::vector<int> vec2(size);
    for (size_t i = 0; i < size; ++i) {
        vec1[i] = dist(rng);
        vec2[i] = dist(rng);
    }

    // Perform vector subtraction using INTRINSIC and standard methods
    std::vector<int> result_avx2(size);
    std::vector<int> result_std(size);
    gpmp::linalg::vector_sub(vec1, vec2, result_avx2);
    gpmp::linalg::std_vector_sub(vec1, vec2, result_std);

    // Check if the results match
    ASSERT_EQ(result_avx2.size(), result_std.size());
    for (size_t i = 0; i < result_avx2.size(); ++i) {
        EXPECT_EQ(result_avx2[i], result_std[i]);
    }
}

TEST(VectorArithINTRINSICTestInt, SubtractionPerformanceComparison) {
    const size_t size = 4097 * 4097;

    TEST_COUT << "Vector size      : " << size << std::endl;
    // Create random number generator
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> dist(-1000, 1000);

    // Generate random vectors
    std::vector<double> vec1(size);
    std::vector<double> vec2(size);
    for (size_t i = 0; i < size; ++i) {
        vec1[i] = dist(rng);
        vec2[i] = dist(rng);
    }

    // Measure execution time for INTRINSIC vector addition
    std::vector<double> result_avx2(size);

    auto start_avx2 = std::chrono::high_resolution_clock::now();
    gpmp::linalg::vector_add(vec1, vec2, result_avx2);
    auto end_avx2 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_seconds_avx2 = end_avx2 - start_avx2;

    // Measure execution time for standard vector addition
    std::vector<double> result_std(size);

    auto start_std = std::chrono::high_resolution_clock::now();
    gpmp::linalg::std_vector_add(vec1, vec2, result_std);
    auto end_std = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_seconds_std = end_std - start_std;

    TEST_COUT << "INTRINSIC Vector Subtraction Time      : "
              << elapsed_seconds_avx2.count() << " seconds" << std::endl;

    TEST_COUT << "STANDARD  Vector Subtraction Time      : "
              << elapsed_seconds_std.count() << " seconds" << std::endl;
}

TEST(VectorArithINTRINSICTestDouble, Subtraction) {
    // Create input vectors
    std::vector<double> vec1 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    std::vector<double> vec2 = {8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
    std::vector<double> result(vec1.size());

    // Perform vector subtraction
    gpmp::linalg::vector_sub(vec1, vec2, result);

    // Check the result
    EXPECT_EQ(result.size(), vec1.size());
    for (size_t i = 0; i < result.size(); ++i) {
        EXPECT_DOUBLE_EQ(result[i], vec1[i] - vec2[i]);
    }
}

TEST(VectorArithINTRINSICTestDouble, SubtractionComparison) {
    // Create input vectors
    std::vector<double> vec1 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    std::vector<double> vec2 = {8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
    std::vector<double> result_avx2(vec1.size());
    std::vector<double> result_std(vec1.size());

    // Perform vector subtraction using INTRINSIC and standard methods
    gpmp::linalg::vector_sub(vec1, vec2, result_avx2);
    gpmp::linalg::std_vector_sub(vec1, vec2, result_std);

    // Check if the results match
    ASSERT_EQ(result_avx2.size(), result_std.size());
    for (size_t i = 0; i < result_avx2.size(); ++i) {
        EXPECT_DOUBLE_EQ(result_avx2[i], result_std[i]);
    }
}

TEST(VectorArithINTRINSICTestDouble, SubtractionComparisonRandom) {
    const size_t size = 4097;

    // Create random number generator
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> dist(-1000.0, 1000.0);

    // Generate random vectors
    std::vector<double> vec1(size);
    std::vector<double> vec2(size);
    for (size_t i = 0; i < size; ++i) {
        vec1[i] = dist(rng);
        vec2[i] = dist(rng);
    }

    // Perform vector subtraction using INTRINSIC and standard methods
    std::vector<double> result_avx2(size);
    std::vector<double> result_std(size);
    gpmp::linalg::vector_sub(vec1, vec2, result_avx2);
    gpmp::linalg::std_vector_sub(vec1, vec2, result_std);

    // Check if the results match
    ASSERT_EQ(result_avx2.size(), result_std.size());
    for (size_t i = 0; i < result_avx2.size(); ++i) {
        EXPECT_DOUBLE_EQ(result_avx2[i], result_std[i]);
    }
}

// Unit test for vector multiplication using INTRINSIC intrinsics
TEST(VectorArithINTRINSICTestInt, Multiplication) {
    // Create input vector and scalar
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8};
    int scalar = 2;
    std::vector<int> result(vec.size());

    // Perform vector multiplication
    gpmp::linalg::vector_mult(vec, scalar, result);

    // Check the result
    for (size_t i = 0; i < result.size(); ++i) {
        EXPECT_EQ(result[i], vec[i] * scalar);
    }
}

// Unit test to compare results of INTRINSIC vector multiplication with standard
// vector multiplication
TEST(VectorArithINTRINSICTestInt, MultComparison) {
    // Create input vector and scalar
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8};
    int scalar = 2;
    std::vector<int> result_avx2(vec.size());
    std::vector<int> result_std(vec.size());

    // Perform vector multiplication using INTRINSIC and standard methods
    gpmp::linalg::vector_mult(vec, scalar, result_avx2);
    gpmp::linalg::std_vector_mult(vec, scalar, result_std);

    // Check if the results match
    for (size_t i = 0; i < result_avx2.size(); ++i) {
        EXPECT_EQ(result_avx2[i], result_std[i]);
    }
}

// Unit test to compare results of INTRINSIC vector multiplication with standard
// vector multiplication using random vectors
TEST(VectorArithINTRINSICTestInt, MultComparisonRandom) {
    const size_t size = 4097;

    // Create random number generator
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(-1000, 1000);

    // Generate random vector and scalar
    std::vector<int> vec(size);
    int scalar = dist(rng);
    for (size_t i = 0; i < size; ++i) {
        vec[i] = dist(rng);
    }

    // Perform vector multiplication using INTRINSIC and standard methods
    std::vector<int> result_avx2(size);
    std::vector<int> result_std(size);
    gpmp::linalg::vector_mult(vec, scalar, result_avx2);
    gpmp::linalg::std_vector_mult(vec, scalar, result_std);

    // Check if the results match
    for (size_t i = 0; i < result_avx2.size(); ++i) {
        EXPECT_EQ(result_avx2[i], result_std[i]);
    }
}

// Unit test to compare execution time of INTRINSIC vector multiplication with
// standard vector multiplication
TEST(VectorArithINTRINSICTestInt, MultPerformanceComparison) {
    const size_t size = 4097 * 4097;
    TEST_COUT << "Vector size      : " << size << std::endl;

    // Create random number generator
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(-1000, 1000);

    // Generate random vector and scalar
    std::vector<int> vec(size);
    int scalar = dist(rng);
    for (size_t i = 0; i < size; ++i) {
        vec[i] = dist(rng);
    }

    // Measure execution time for INTRINSIC vector multiplication
    std::vector<int> result_avx2(size);
    auto start_avx2 = std::chrono::high_resolution_clock::now();
    gpmp::linalg::vector_mult(vec, scalar, result_avx2);
    auto end_avx2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_avx2 = end_avx2 - start_avx2;

    // Measure execution time for standard vector multiplication
    std::vector<int> result_std(size);
    auto start_std = std::chrono::high_resolution_clock::now();
    gpmp::linalg::std_vector_mult(vec, scalar, result_std);
    auto end_std = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_std = end_std - start_std;

    // Print the results
    TEST_COUT << "INTRINSIC Vector Multiplication Time      : "
              << elapsed_seconds_avx2.count() << " seconds" << std::endl;
    TEST_COUT << "STANDARD  Vector Multiplication Time      : "
              << elapsed_seconds_std.count() << " seconds" << std::endl;
}

// Unit test for dot product using INTRINSIC intrinsics
TEST(VectorArithINTRINSICTestInt, DotProduct) {
    // Create input vectors
    std::vector<int> vec1 = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> vec2 = {8, 7, 6, 5, 4, 3, 2, 1};

    // Calculate dot product
    int result = gpmp::linalg::dot_product(vec1, vec2);

    // Expected result
    int expected_result =
        1 * 8 + 2 * 7 + 3 * 6 + 4 * 5 + 5 * 4 + 6 * 3 + 7 * 2 + 8 * 1;

    // Check the result
    EXPECT_EQ(result, expected_result);
}

// Unit test for dot product using INTRINSIC intrinsics with random vectors
TEST(VectorArithINTRINSICTestInt, DotProductRandom) {
    const size_t size = 4097;

    // Create random number generator
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(-1000, 1000);

    // Generate random vectors
    std::vector<int> vec1(size);
    std::vector<int> vec2(size);
    for (size_t i = 0; i < size; ++i) {
        vec1[i] = dist(rng);
        vec2[i] = dist(rng);
    }

    // Calculate dot product using INTRINSIC intrinsics
    int result = gpmp::linalg::dot_product(vec1, vec2);

    // Calculate dot product using standard method
    int expected_result = 0;
    for (size_t i = 0; i < size; ++i) {
        expected_result += vec1[i] * vec2[i];
    }

    // Check the result
    EXPECT_EQ(result, expected_result);
}

TEST(VectorArithINTRINSICTestInt, DotProductPerformanceComparison) {
    const size_t size = 4097 * 4097;
    TEST_COUT << "Vector size      : " << size << std::endl;

    // Create input vectors
    std::vector<int> vec1(size, 1);
    std::vector<int> vec2(size, 2);

    // Measure execution time for INTRINSIC dot product calculation
    auto start_avx2 = std::chrono::high_resolution_clock::now();
    int result_avx2 = gpmp::linalg::dot_product(vec1, vec2);
    auto end_avx2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_avx2 = end_avx2 - start_avx2;

    // Measure execution time for standard dot product calculation
    auto start_std = std::chrono::high_resolution_clock::now();
    int result_std = gpmp::linalg::std_dot_product(vec1, vec2);
    auto end_std = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_std = end_std - start_std;

    // Print the results
    TEST_COUT << "INTRINSIC Dot Product Time      : "
              << elapsed_seconds_avx2.count() << " seconds" << std::endl;
    TEST_COUT << "STANDARD  Dot Product Time      : "
              << elapsed_seconds_std.count() << " seconds" << std::endl;
}

TEST(VectorArithINTRINSICTestDouble, Addition) {
    // Create input vectors
    std::vector<double> vec1 = {1.0, 2.0, 3.0, 4.0};
    std::vector<double> vec2 = {4.0, 3.0, 2.0, 1.0};
    std::vector<double> result_avx2(vec1.size());

    // Perform vector addition using INTRINSIC
    gpmp::linalg::vector_add(vec1, vec2, result_avx2);

    // Check the result
    EXPECT_EQ(result_avx2.size(), vec1.size());
    for (size_t i = 0; i < result_avx2.size(); ++i) {
        EXPECT_DOUBLE_EQ(result_avx2[i], vec1[i] + vec2[i]);
    }
}

// Unit test to compare results of INTRINSIC vector addition with standard
// vector addition for doubles
TEST(VectorArithINTRINSICTestDouble, AdditionComparison) {
    // Create input vectors
    std::vector<double> vec1 = {1.0, 2.0, 3.0, 4.0};
    std::vector<double> vec2 = {4.0, 3.0, 2.0, 1.0};
    std::vector<double> result_avx2(vec1.size());
    std::vector<double> result_std(vec1.size());

    // Perform vector addition using INTRINSIC and standard methods
    gpmp::linalg::vector_add(vec1, vec2, result_avx2);
    gpmp::linalg::std_vector_add(vec1, vec2, result_std);

    // Check if the results match
    ASSERT_EQ(result_avx2.size(), result_std.size());
    for (size_t i = 0; i < result_avx2.size(); ++i) {
        EXPECT_DOUBLE_EQ(result_avx2[i], result_std[i]);
    }
}

TEST(VectorArithINTRINSICTestDouble, AdditionComparisonRandom) {
    const size_t size = 4097;

    // Create random number generator
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(-1000, 1000);

    // Generate random vectors
    std::vector<double> vec1(size);
    std::vector<double> vec2(size);
    for (size_t i = 0; i < size; ++i) {
        vec1[i] = dist(rng);
        vec2[i] = dist(rng);
    }

    // Perform vector addition using INTRINSIC and standard methods
    std::vector<double> result_avx2(size);
    std::vector<double> result_std(size);
    gpmp::linalg::vector_add(vec1, vec2, result_avx2);
    gpmp::linalg::std_vector_add(vec1, vec2, result_std);

    // Check if the results match
    ASSERT_EQ(result_avx2.size(), result_std.size());
    for (size_t i = 0; i < result_avx2.size(); ++i) {
        EXPECT_EQ(result_avx2[i], result_std[i]);
    }
}

// Unit test to compare execution time of INTRINSIC vector addition with
// standard vector addition for doubles
TEST(VectorArithINTRINSICTestDouble, AdditionPerformanceComparison) {
    const size_t size = 4097 * 4097;
    TEST_COUT << "Vector size      : " << size << std::endl;

    // Create input vectors
    std::vector<double> vec1(size, 1.0);
    std::vector<double> vec2(size, 2.0);
    std::vector<double> result_avx2(size);
    std::vector<double> result_std(size);

    // Measure execution time for INTRINSIC vector addition
    auto start_avx2 = std::chrono::high_resolution_clock::now();
    gpmp::linalg::vector_add(vec1, vec2, result_avx2);
    auto end_avx2 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_seconds_avx2 = end_avx2 - start_avx2;

    // Measure execution time for standard vector addition
    auto start_std = std::chrono::high_resolution_clock::now();
    gpmp::linalg::std_vector_add(vec1, vec2, result_std);
    auto end_std = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_seconds_std = end_std - start_std;

    // Print the results
    TEST_COUT << "INTRINSIC Vector Addition Time      : "
              << elapsed_seconds_avx2.count() << " seconds" << std::endl;
    TEST_COUT << "STANDARD  Vector Addition Time      : "
              << elapsed_seconds_std.count() << " seconds" << std::endl;
}

TEST(VectorArithINTRINSICTestDouble, Multiplication) {
    // Create input vector
    std::vector<double> vec = {1.0, 2.0, 3.0, 4.0};
    double scalar = 2.0;
    std::vector<double> result_avx2(vec.size());

    // Perform vector multiplication using INTRINSIC
    gpmp::linalg::vector_mult(vec, scalar, result_avx2);

    // Check the result
    EXPECT_EQ(result_avx2.size(), vec.size());
    for (size_t i = 0; i < result_avx2.size(); ++i) {
        EXPECT_DOUBLE_EQ(result_avx2[i], vec[i] * scalar);
    }
}

TEST(VectorArithINTRINSICTestDouble, MultComparison) {
    // Create input vector
    std::vector<double> vec = {1.0, 2.0, 3.0, 4.0};
    double scalar = 2.0;
    std::vector<double> result_avx2(vec.size());
    std::vector<double> result_std(vec.size());

    // Perform vector multiplication using INTRINSIC and standard methods
    gpmp::linalg::vector_mult(vec, scalar, result_avx2);
    gpmp::linalg::std_vector_mult(vec, scalar, result_std);

    // Check if the results match
    ASSERT_EQ(result_avx2.size(), result_std.size());
    for (size_t i = 0; i < result_avx2.size(); ++i) {
        EXPECT_DOUBLE_EQ(result_avx2[i], result_std[i]);
    }
}

TEST(VectorArithINTRINSICTestDouble, MultComparisonRandom) {
    const size_t size = 4097;

    // Create random number generator
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(-1000, 1000);

    // Generate random vector and scalar
    std::vector<double> vec(size);
    int scalar = dist(rng);
    for (size_t i = 0; i < size; ++i) {
        vec[i] = dist(rng);
    }

    // Perform vector multiplication using INTRINSIC and standard methods
    std::vector<double> result_avx2(size);
    std::vector<double> result_std(size);
    gpmp::linalg::vector_mult(vec, scalar, result_avx2);
    gpmp::linalg::std_vector_mult(vec, scalar, result_std);

    // Check if the results match
    for (size_t i = 0; i < result_avx2.size(); ++i) {
        EXPECT_EQ(result_avx2[i], result_std[i]);
    }
}

TEST(VectorArithINTRINSICTestDouble, MultiplicationPerformanceComparison) {
    const size_t size = 4097 * 4097;
    TEST_COUT << "Vector size      : " << size << std::endl;

    // Create input vector
    std::vector<double> vec(size, 1.0);
    double scalar = 2.0;
    std::vector<double> result_avx2(size);
    std::vector<double> result_std(size);

    // Measure execution time for INTRINSIC vector multiplication
    auto start_avx2 = std::chrono::high_resolution_clock::now();
    gpmp::linalg::vector_mult(vec, scalar, result_avx2);
    auto end_avx2 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_seconds_avx2 = end_avx2 - start_avx2;

    // Measure execution time for standard vector multiplication
    auto start_std = std::chrono::high_resolution_clock::now();
    gpmp::linalg::std_vector_mult(vec, scalar, result_std);
    auto end_std = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_seconds_std = end_std - start_std;

    // Print the results
    TEST_COUT << "INTRINSIC Vector Multiplication Time      : "
              << elapsed_seconds_avx2.count() << " seconds" << std::endl;
    TEST_COUT << "STANDARD  Vector Multiplication Time      : "
              << elapsed_seconds_std.count() << " seconds" << std::endl;
}

TEST(VectorArithINTRINSICTestDouble, DotProduct) {
    // Create input vectors
    std::vector<double> vec1 = {1.0, 2.0, 3.0, 4.0};
    std::vector<double> vec2 = {4.0, 3.0, 2.0, 1.0};

    // Calculate dot product using INTRINSIC
    double result_avx2 = gpmp::linalg::dot_product(vec1, vec2);

    // Calculate dot product using standard method
    double result_std = gpmp::linalg::std_dot_product(vec1, vec2);

    // Check if the results match
    EXPECT_DOUBLE_EQ(result_avx2, result_std);
}

TEST(VectorArithINTRINSICTestDouble, DotProductRandom) {
    const size_t size = 4097;

    // Create random number generator
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(-1000, 1000);

    // Generate random vectors
    std::vector<double> vec1(size);
    std::vector<double> vec2(size);
    for (size_t i = 0; i < size; ++i) {
        vec1[i] = dist(rng);
        vec2[i] = dist(rng);
    }

    // Calculate dot product using INTRINSIC intrinsics
    double result = gpmp::linalg::dot_product(vec1, vec2);

    // Calculate dot product using standard method
    double expected_result = 0;
    for (size_t i = 0; i < size; ++i) {
        expected_result += vec1[i] * vec2[i];
    }

    // Check the result
    EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST(VectorArithINTRINSICTestDouble, DotProductPerformanceComparison) {
    const size_t size = 4097 * 4097;
    TEST_COUT << "Vector size      : " << size << std::endl;

    // Create input vectors
    std::vector<double> vec1(size, 1.0);
    std::vector<double> vec2(size, 2.0);

    // Measure execution time for INTRINSIC dot product calculation
    auto start_avx2 = std::chrono::high_resolution_clock::now();
    double result_avx2 = gpmp::linalg::dot_product(vec1, vec2);
    auto end_avx2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_avx2 = end_avx2 - start_avx2;

    // Measure execution time for standard dot product calculation
    auto start_std = std::chrono::high_resolution_clock::now();
    double result_std = gpmp::linalg::std_dot_product(vec1, vec2);
    auto end_std = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_std = end_std - start_std;

    // Print the results
    TEST_COUT << "INTRINSIC Dot Product Time      : "
              << elapsed_seconds_avx2.count() << " seconds" << std::endl;
    TEST_COUT << "STANDARD  Dot Product Time      : "
              << elapsed_seconds_std.count() << " seconds" << std::endl;
}

#endif
