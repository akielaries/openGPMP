/**
 * Unit tests for the Linear Algebra module's Vector operations
 */
#include "../../include/linalg/vector.hpp"
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

const double TOLERANCE = 1e-3;

#define TEST_COUT std::cerr << "\033[32m[          ] [ INFO ] \033[0m"
#define INFO_COUT                                                              \
    std::cerr << "\033[32m[          ] [ INFO ] \033[0m\033[1;31m\033[1m"
TEST(VectorVectorTestF64, Addition) {
    INFO_COUT << "Vector (as Vectors) FLOAT64" << std::endl;

    // Create input vectors
    std::vector<double> vec1 = {1.0, 2.0, 3.0, 4.0};
    std::vector<double> vec2 = {4.0, 3.0, 2.0, 1.0};
    std::vector<double> result_intrin(vec1.size());

    // Perform vector addition using INTRINSIC
    gpmp::linalg::vector_add(vec1, vec2, result_intrin);

    // Check the result
    EXPECT_EQ(result_intrin.size(), vec1.size());
    for (size_t i = 0; i < result_intrin.size(); ++i) {
        EXPECT_DOUBLE_EQ(result_intrin[i], vec1[i] + vec2[i]);
    }
}

// Unit test to compare results of INTRINSIC vector addition with standard
// vector addition for doubles
TEST(VectorVectorTestF64, AdditionComparison) {
    // Create input vectors
    std::vector<double> vec1 = {1.0, 2.0, 3.0, 4.0};
    std::vector<double> vec2 = {4.0, 3.0, 2.0, 1.0};
    std::vector<double> result_intrin(vec1.size());
    std::vector<double> result_std(vec1.size());

    // Perform vector addition using INTRINSIC and standard methods
    gpmp::linalg::vector_add(vec1, vec2, result_intrin);
    gpmp::linalg::std_vector_add(vec1, vec2, result_std);

    // Check if the results match
    ASSERT_EQ(result_intrin.size(), result_std.size());
    for (size_t i = 0; i < result_intrin.size(); ++i) {
        EXPECT_DOUBLE_EQ(result_intrin[i], result_std[i]);
    }
}

TEST(VectorVectorTestF64, AdditionComparisonRandom) {
    const size_t size = 3333;

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
    std::vector<double> result_intrin(size);
    std::vector<double> result_std(size);
    gpmp::linalg::vector_add(vec1, vec2, result_intrin);
    gpmp::linalg::std_vector_add(vec1, vec2, result_std);

    // Check if the results match
    ASSERT_EQ(result_intrin.size(), result_std.size());
    for (size_t i = 0; i < result_intrin.size(); ++i) {
        EXPECT_EQ(result_intrin[i], result_std[i]);
    }
}

// Unit test to compare execution time of INTRINSIC vector addition with
// standard vector addition for doubles
TEST(VectorVectorTestF64, AdditionPerformanceComparison) {
    const size_t size = 3333 * 3333;
    TEST_COUT << "Vector size      : " << size << std::endl;

    // Create input vectors
    std::vector<double> vec1(size, 1.0);
    std::vector<double> vec2(size, 2.0);
    std::vector<double> result_intrin(size);
    std::vector<double> result_std(size);

    // Measure execution time for INTRINSIC vector addition
    auto start_intrin = std::chrono::high_resolution_clock::now();
    gpmp::linalg::vector_add(vec1, vec2, result_intrin);
    auto end_intrin = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_seconds_intrin =
        end_intrin - start_intrin;

    // Measure execution time for standard vector addition
    auto start_std = std::chrono::high_resolution_clock::now();
    gpmp::linalg::std_vector_add(vec1, vec2, result_std);
    auto end_std = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_seconds_std = end_std - start_std;

    // Print the results
    TEST_COUT << "INTRINSIC Vector Addition Time      : "
              << elapsed_seconds_intrin.count() << " seconds" << std::endl;
    TEST_COUT << "STANDARD  Vector Addition Time      : "
              << elapsed_seconds_std.count() << " seconds" << std::endl;

    ASSERT_EQ(result_intrin.size(), result_std.size());
    for (size_t i = 0; i < result_intrin.size(); ++i) {
        EXPECT_DOUBLE_EQ(result_intrin[i], result_std[i]);
    }
}

TEST(VectorVectorTestF64, Subtraction) {
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

TEST(VectorVectorTestF64, SubtractionComparison) {
    // Create input vectors
    std::vector<double> vec1 = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    std::vector<double> vec2 = {8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
    std::vector<double> result_intrin(vec1.size());
    std::vector<double> result_std(vec1.size());

    // Perform vector subtraction using INTRINSIC and standard methods
    gpmp::linalg::vector_sub(vec1, vec2, result_intrin);
    gpmp::linalg::std_vector_sub(vec1, vec2, result_std);

    // Check if the results match
    ASSERT_EQ(result_intrin.size(), result_std.size());
    for (size_t i = 0; i < result_intrin.size(); ++i) {
        EXPECT_DOUBLE_EQ(result_intrin[i], result_std[i]);
    }
}

TEST(VectorVectorTestF64, SubtractionComparisonRandom) {
    const size_t size = 3333;

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
    std::vector<double> result_intrin(size);
    std::vector<double> result_std(size);
    gpmp::linalg::vector_sub(vec1, vec2, result_intrin);
    gpmp::linalg::std_vector_sub(vec1, vec2, result_std);

    // Check if the results match
    ASSERT_EQ(result_intrin.size(), result_std.size());
    for (size_t i = 0; i < result_intrin.size(); ++i) {
        EXPECT_DOUBLE_EQ(result_intrin[i], result_std[i]);
    }
}

TEST(VectorVectorTestF64, SubtractionPerformanceComparison) {
    const size_t size = 3333 * 3333;
    TEST_COUT << "Vector size      : " << size << std::endl;

    // Create input vectors
    std::vector<double> vec1(size, 1.0);
    std::vector<double> vec2(size, 2.0);
    std::vector<double> result_intrin(size);
    std::vector<double> result_std(size);

    // Measure execution time for INTRINSIC vector addition
    auto start_intrin = std::chrono::high_resolution_clock::now();
    gpmp::linalg::vector_sub(vec1, vec2, result_intrin);
    auto end_intrin = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_seconds_intrin =
        end_intrin - start_intrin;

    // Measure execution time for standard vector addition
    auto start_std = std::chrono::high_resolution_clock::now();
    gpmp::linalg::std_vector_sub(vec1, vec2, result_std);
    auto end_std = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_seconds_std = end_std - start_std;

    // print the results
    TEST_COUT << "INTRINSIC Vector Addition Time      : "
              << elapsed_seconds_intrin.count() << " seconds" << std::endl;
    TEST_COUT << "STANDARD  Vector Addition Time      : "
              << elapsed_seconds_std.count() << " seconds" << std::endl;

    ASSERT_EQ(result_intrin.size(), result_std.size());
    for (size_t i = 0; i < result_intrin.size(); ++i) {
        EXPECT_DOUBLE_EQ(result_intrin[i], result_std[i]);
    }
}

TEST(VectorVectorTestF64, Multiplication) {
    // Create input vector
    std::vector<double> vec = {1.0, 2.0, 3.0, 4.0};
    double scalar = 2.0;
    std::vector<double> result_intrin(vec.size());

    // Perform vector multiplication using INTRINSIC
    gpmp::linalg::scalar_mult(vec, scalar, result_intrin);

    // Check the result
    EXPECT_EQ(result_intrin.size(), vec.size());
    for (size_t i = 0; i < result_intrin.size(); ++i) {
        EXPECT_DOUBLE_EQ(result_intrin[i], vec[i] * scalar);
    }
}

TEST(VectorVectorTestF64, MultComparison) {
    // Create input vector
    std::vector<double> vec = {1.0, 2.0, 3.0, 4.0};
    double scalar = 2.0;
    std::vector<double> result_intrin(vec.size());
    std::vector<double> result_std(vec.size());

    // Perform vector multiplication using INTRINSIC and standard methods
    gpmp::linalg::scalar_mult(vec, scalar, result_intrin);
    gpmp::linalg::std_scalar_mult(vec, scalar, result_std);

    // Check if the results match
    ASSERT_EQ(result_intrin.size(), result_std.size());
    for (size_t i = 0; i < result_intrin.size(); ++i) {
        EXPECT_DOUBLE_EQ(result_intrin[i], result_std[i]);
    }
}

TEST(VectorVectorTestF64, MultComparisonRandom) {
    const size_t size = 3333;

    // Create random number generator
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> dist(-1000, 1000);

    // Generate random vector and scalar
    std::vector<double> vec(size);
    int scalar = dist(rng);
    for (size_t i = 0; i < size; ++i) {
        vec[i] = dist(rng);
    }

    // Perform vector multiplication using INTRINSIC and standard methods
    std::vector<double> result_intrin(size);
    std::vector<double> result_std(size);
    gpmp::linalg::scalar_mult(vec, scalar, result_intrin);
    gpmp::linalg::std_scalar_mult(vec, scalar, result_std);

    // Check if the results match
    for (size_t i = 0; i < result_intrin.size(); ++i) {
        EXPECT_EQ(result_intrin[i], result_std[i]);
    }
}

TEST(VectorVectorTestF64, MultiplicationPerformanceComparison) {
    const size_t size = 3333 * 3333;
    TEST_COUT << "Vector size      : " << size << std::endl;

    // Create input vector
    std::vector<double> vec(size, 1.0);
    double scalar = 2.0;
    std::vector<double> result_intrin(size);
    std::vector<double> result_std(size);

    // Measure execution time for INTRINSIC vector multiplication
    auto start_intrin = std::chrono::high_resolution_clock::now();
    gpmp::linalg::scalar_mult(vec, scalar, result_intrin);
    auto end_intrin = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_seconds_intrin =
        end_intrin - start_intrin;

    // Measure execution time for standard vector multiplication
    auto start_std = std::chrono::high_resolution_clock::now();
    gpmp::linalg::std_scalar_mult(vec, scalar, result_std);
    auto end_std = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_seconds_std = end_std - start_std;

    // Print the results
    TEST_COUT << "INTRINSIC Vector Multiplication Time      : "
              << elapsed_seconds_intrin.count() << " seconds" << std::endl;
    TEST_COUT << "STANDARD  Vector Multiplication Time      : "
              << elapsed_seconds_std.count() << " seconds" << std::endl;
    ASSERT_EQ(result_intrin.size(), result_std.size());
    for (size_t i = 0; i < result_intrin.size(); ++i) {
        EXPECT_DOUBLE_EQ(result_intrin[i], result_std[i]);
    }
}

TEST(VectorVectorTestF64, DotProduct) {
    // Create input vectors
    std::vector<double> vec1 = {1.0, 2.0, 3.0, 4.0};
    std::vector<double> vec2 = {4.0, 3.0, 2.0, 1.0};

    // Calculate dot product using INTRINSIC
    double result_intrin = gpmp::linalg::dot_product(vec1, vec2);

    // Calculate dot product using standard method
    double result_std = gpmp::linalg::std_dot_product(vec1, vec2);

    // Check if the results match
    EXPECT_DOUBLE_EQ(result_intrin, result_std);
}

TEST(VectorVectorTestF64, DotProductRandom) {
    const size_t size = 3333;

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

TEST(VectorVectorTestF64, DotProductPerformanceComparison) {
    const size_t size = 3333 * 3333;
    TEST_COUT << "Vector size      : " << size << std::endl;

    // Create input vectors
    std::vector<double> vec1(size, 1.0);
    std::vector<double> vec2(size, 2.0);

    // Measure execution time for INTRINSIC dot product calculation
    auto start_intrin = std::chrono::high_resolution_clock::now();
    double result_intrin = gpmp::linalg::dot_product(vec1, vec2);
    auto end_intrin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_intrin =
        end_intrin - start_intrin;

    // Measure execution time for standard dot product calculation
    auto start_std = std::chrono::high_resolution_clock::now();
    double result_std = gpmp::linalg::std_dot_product(vec1, vec2);
    auto end_std = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_std = end_std - start_std;

    // Print the results
    TEST_COUT << "INTRINSIC Dot Product Time      : "
              << elapsed_seconds_intrin.count() << " seconds" << std::endl;
    TEST_COUT << "STANDARD  Dot Product Time      : "
              << elapsed_seconds_std.count() << " seconds" << std::endl;

    EXPECT_DOUBLE_EQ(result_intrin, result_std);
}
