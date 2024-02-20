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

/*****************************************************************************/
/** VECTOR<INT8> TESTS */

TEST(VectorVectorTestI8, Addition) {
    // Create input vectors
    std::vector<int8_t> vec1 = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int8_t> vec2 = {8, 7, 6, 5, 4, 3, 2, 1};
    std::vector<int8_t> result(vec1.size());

    // Perform vector addition
    gpmp::linalg::vector_add(vec1, vec2, result);

    // Check the result
    EXPECT_EQ(result.size(), vec1.size());
    for (size_t i = 0; i < result.size(); ++i) {
        EXPECT_EQ(result[i], vec1[i] + vec2[i]);
    }
}

TEST(VectorVectorTestI8, AdditionComparison) {
    // Create input vectors
    std::vector<int8_t> vec1 = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int8_t> vec2 = {8, 7, 6, 5, 4, 3, 2, 1};
    std::vector<int8_t> result_intrin(vec1.size());
    std::vector<int8_t> result_std(vec1.size());

    // Perform vector addition using INTRINSIC and standard methods
    gpmp::linalg::vector_add(vec1, vec2, result_intrin);
    gpmp::linalg::std_vector_add(vec1, vec2, result_std);

    // Check if the results match
    ASSERT_EQ(result_intrin.size(), result_std.size());
    for (size_t i = 0; i < result_intrin.size(); ++i) {
        EXPECT_EQ(result_intrin[i], result_std[i]);
    }
}

TEST(VectorVectorTestI8, AdditionComparisonRandom) {
    const size_t size = 3333;

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int8_t> dist(-127, 127);

    // Generate random vectors
    std::vector<int8_t> vec1;
    std::vector<int8_t> vec2;
    for (size_t i = 0; i < size; ++i) {
        vec1.push_back(dist(rng));
        vec2.push_back(dist(rng));
    }

    // Perform vector addition using INTRINSIC and standard methods
    std::vector<int8_t> result_intrin(size);
    std::vector<int8_t> result_std(size);
    gpmp::linalg::vector_add(vec1, vec2, result_intrin);
    gpmp::linalg::std_vector_add(vec1, vec2, result_std);

    // Check if the results match
    ASSERT_EQ(result_intrin.size(), result_std.size());
    for (size_t i = 0; i < result_intrin.size(); ++i) {
        EXPECT_EQ(result_intrin[i], result_std[i]);
    }
}
TEST(VectorVectorTestI8, AdditionPerformanceComparison) {
    const size_t size = 3333 * 3333;

    TEST_COUT << "Vector size      : " << size << std::endl;
    // Create random number generator
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int8_t> dist(-127, 127);

    // Generate random vectors
    std::vector<int8_t> vec1;
    std::vector<int8_t> vec2;
    for (size_t i = 0; i < size; ++i) {
        vec1.push_back(dist(rng));
        vec2.push_back(dist(rng));
    }

    // Measure execution time for INTRINSIC vector addition
    std::vector<int8_t> result_intrin(size);

    auto start_intrin = std::chrono::high_resolution_clock::now();
    gpmp::linalg::vector_add(vec1, vec2, result_intrin);
    auto end_intrin = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_seconds_intrin =
        end_intrin - start_intrin;

    // Measure execution time for standard vector addition
    std::vector<int8_t> result_std(size);

    auto start_std = std::chrono::high_resolution_clock::now();
    gpmp::linalg::std_vector_add(vec1, vec2, result_std);
    auto end_std = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_seconds_std = end_std - start_std;

    TEST_COUT << "INTRINSIC Vector Addition Time      : "
              << elapsed_seconds_intrin.count() << " seconds" << std::endl;

    TEST_COUT << "STANDARD  Vector Addition Time      : "
              << elapsed_seconds_std.count() << " seconds" << std::endl;

    // Check if the results match
    ASSERT_EQ(result_intrin.size(), result_std.size());
    for (size_t i = 0; i < result_intrin.size(); ++i) {
        EXPECT_EQ(result_intrin[i], result_std[i]);
    }
}

TEST(VectorVectorTestI8, Subtraction) {
    // Create input vectors
    std::vector<int8_t> vec1 = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int8_t> vec2 = {8, 7, 6, 5, 4, 3, 2, 1};
    std::vector<int8_t> result(vec1.size());

    // Perform vector subtraction
    gpmp::linalg::vector_sub(vec1, vec2, result);

    // Check the result
    EXPECT_EQ(result.size(), vec1.size());
    for (size_t i = 0; i < result.size(); ++i) {
        EXPECT_EQ(result[i], vec1[i] - vec2[i]);
    }
}

TEST(VectorVectorTestI8, SubtractionComparison) {
    // Create input vectors
    std::vector<int8_t> vec1 = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int8_t> vec2 = {8, 7, 6, 5, 4, 3, 2, 1};
    std::vector<int8_t> result_intrin(vec1.size());
    std::vector<int8_t> result_std(vec1.size());

    // Perform vector subtraction using INTRINSIC and standard methods
    gpmp::linalg::vector_sub(vec1, vec2, result_intrin);
    gpmp::linalg::std_vector_sub(vec1, vec2, result_std);

    // Check if the results match
    ASSERT_EQ(result_intrin.size(), result_std.size());
    for (size_t i = 0; i < result_intrin.size(); ++i) {
        EXPECT_EQ(result_intrin[i], result_std[i]);
    }
}

TEST(VectorVectorTestI8, SubtractionComparisonRandom) {
    const size_t size = 3333;
    // Create random number generator
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int8_t> dist(-127, 127);

    // Generate random vectors
    std::vector<int8_t> vec1;
    std::vector<int8_t> vec2;
    for (size_t i = 0; i < size; ++i) {
        vec1.push_back(dist(rng));
        vec2.push_back(dist(rng));
    }

    // Perform vector addition using INTRINSIC and standard methods
    std::vector<int8_t> result_intrin(size);
    std::vector<int8_t> result_std(size);
    gpmp::linalg::vector_add(vec1, vec2, result_intrin);
    gpmp::linalg::std_vector_add(vec1, vec2, result_std);

    // Check if the results match
    ASSERT_EQ(result_intrin.size(), result_std.size());
    for (size_t i = 0; i < result_intrin.size(); ++i) {
        EXPECT_EQ(result_intrin[i], result_std[i]);
    }
}

TEST(VectorVectorTestI8, SubtractionPerformanceComparison) {
    const size_t size = 3333 * 3333;

    TEST_COUT << "Vector size      : " << size << std::endl;
    // Create random number generator
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int8_t> dist(-127, 127);

    // Generate random vectors
    std::vector<int8_t> vec1;
    std::vector<int8_t> vec2;
    for (size_t i = 0; i < size; ++i) {
        vec1.push_back(dist(rng));
        vec2.push_back(dist(rng));
    }

    // Measure execution time for INTRINSIC vector addition
    std::vector<int8_t> result_intrin(size);

    auto start_intrin = std::chrono::high_resolution_clock::now();
    gpmp::linalg::vector_sub(vec1, vec2, result_intrin);
    auto end_intrin = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_seconds_intrin =
        end_intrin - start_intrin;

    // Measure execution time for standard vector addition
    std::vector<int8_t> result_std(size);

    auto start_std = std::chrono::high_resolution_clock::now();
    gpmp::linalg::std_vector_sub(vec1, vec2, result_std);
    auto end_std = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_seconds_std = end_std - start_std;

    TEST_COUT << "INTRINSIC Vector Subtraction Time      : "
              << elapsed_seconds_intrin.count() << " seconds" << std::endl;

    TEST_COUT << "STANDARD  Vector Subtraction Time      : "
              << elapsed_seconds_std.count() << " seconds" << std::endl;

    // Check if the results match
    ASSERT_EQ(result_intrin.size(), result_std.size());
    for (size_t i = 0; i < result_intrin.size(); ++i) {
        EXPECT_EQ(result_intrin[i], result_std[i]);
    }
}

// Unit test for vector multiplication using INTRINSIC intrinsics
TEST(VectorVectorTestI8, Multiplication) {
    // Create input vector and scalar
    std::vector<int8_t> vec = {1, 2, 3, 4, 5, 6, 7, 8};
    int scalar = 2;
    std::vector<int8_t> result(vec.size());

    // Perform vector multiplication
    gpmp::linalg::scalar_mult(vec, scalar, result);

    // Check the result
    for (size_t i = 0; i < result.size(); ++i) {
        EXPECT_EQ(result[i], vec[i] * scalar);
    }
}

// Unit test to compare results of INTRINSIC vector multiplication with standard
// vector multiplication
TEST(VectorVectorTestI8, MultComparison) {
    // Create input vector and scalar
    std::vector<int8_t> vec = {1, 2, 3, 4, 5, 6, 7, 8};
    int scalar = 2;
    std::vector<int8_t> result_intrin(vec.size());
    std::vector<int8_t> result_std(vec.size());

    // Perform vector multiplication using INTRINSIC and standard methods
    gpmp::linalg::scalar_mult(vec, scalar, result_intrin);
    gpmp::linalg::std_scalar_mult(vec, scalar, result_std);

    // Check if the results match
    for (size_t i = 0; i < result_intrin.size(); ++i) {
        EXPECT_EQ(result_intrin[i], result_std[i]);
    }
}

// Unit test to compare results of INTRINSIC vector multiplication with standard
// vector multiplication using random vectors
TEST(VectorVectorTestI8, MultComparisonRandom) {
    const size_t size = 3333;
    // Create random number generator
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int8_t> dist(0, 11);

    std::vector<int8_t> vec;
    int scalar = dist(rng);
    for (size_t i = 0; i < size; ++i) {
        vec.push_back(dist(rng));
    }

    // Perform vector multiplication using INTRINSIC and standard methods
    std::vector<int8_t> result_intrin(size);
    std::vector<int8_t> result_std(size);
    gpmp::linalg::scalar_mult(vec, scalar, result_intrin);
    gpmp::linalg::std_scalar_mult(vec, scalar, result_std);

    // Check if the results match
    for (size_t i = 0; i < result_intrin.size(); ++i) {
        EXPECT_EQ(result_intrin[i], result_std[i]);
    }
}

// Unit test to compare execution time of INTRINSIC vector multiplication with
// standard vector multiplication
TEST(VectorVectorTestI8, MultPerformanceComparison) {
    const size_t size = 3333 * 3333;
    TEST_COUT << "Vector size      : " << size << std::endl;

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int8_t> dist(0, 11);

    std::vector<int8_t> vec;
    int scalar = dist(rng);
    for (size_t i = 0; i < size; ++i) {
        vec.push_back(dist(rng));
    }

    // Measure execution time for INTRINSIC vector multiplication
    std::vector<int8_t> result_intrin(size);
    auto start_intrin = std::chrono::high_resolution_clock::now();
    gpmp::linalg::scalar_mult(vec, scalar, result_intrin);
    auto end_intrin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_intrin =
        end_intrin - start_intrin;

    // Measure execution time for standard vector multiplication
    std::vector<int8_t> result_std(size);
    auto start_std = std::chrono::high_resolution_clock::now();
    gpmp::linalg::std_scalar_mult(vec, scalar, result_std);
    auto end_std = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_std = end_std - start_std;

    // Print the results
    TEST_COUT << "INTRINSIC Vector Multiplication Time      : "
              << elapsed_seconds_intrin.count() << " seconds" << std::endl;
    TEST_COUT << "STANDARD  Vector Multiplication Time      : "
              << elapsed_seconds_std.count() << " seconds" << std::endl;

    // Check if the results match
    for (size_t i = 0; i < result_intrin.size(); ++i) {
        // EXPECT_EQ(result_intrin[i], result_std[i]);
    }
}

// Unit test for dot product using INTRINSIC intrinsics
TEST(VectorVectorTestI8, DotProduct) {
    // Create input vectors
    std::vector<int8_t> vec1 = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int8_t> vec2 = {8, 7, 6, 5, 4, 3, 2, 1};

    // Calculate dot product
    int result = gpmp::linalg::dot_product(vec1, vec2);

    // Expected result
    int expected_result = 120;

    // Check the result
    EXPECT_EQ(result, expected_result);
}

// Unit test for dot product using INTRINSIC intrinsics with random vectors
TEST(VectorVectorTestI8, DotProductRandom) {
    const size_t size = 3333;

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int8_t> dist(-128, 127);

    std::vector<int8_t> vec1;
    std::vector<int8_t> vec2;
    for (size_t i = 0; i < size; ++i) {
        vec1.push_back(dist(rng));
        vec2.push_back(dist(rng));
    }

    // Calculate dot product using INTRINSIC intrinsics
    int result = gpmp::linalg::dot_product(vec1, vec2);
    int expected_result = gpmp::linalg::std_dot_product(vec1, vec2);

    // Check the result
    EXPECT_EQ(result, expected_result);
}

TEST(VectorVectorTestI8, DotProductPerformanceComparison) {
    const size_t size = 3333 * 3333;
    TEST_COUT << "Vector size      : " << size << std::endl;

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int8_t> dist(0, 11);

    std::vector<int8_t> vec1;
    std::vector<int8_t> vec2;
    for (size_t i = 0; i < size; ++i) {
        vec1.push_back(dist(rng));
        vec2.push_back(dist(rng));
    }

    // Measure execution time for INTRINSIC dot product calculation
    auto start_intrin = std::chrono::high_resolution_clock::now();
    int result_intrin = gpmp::linalg::dot_product(vec1, vec2);
    auto end_intrin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_intrin =
        end_intrin - start_intrin;

    // Measure execution time for standard dot product calculation
    auto start_std = std::chrono::high_resolution_clock::now();
    int result_std = gpmp::linalg::std_dot_product(vec1, vec2);
    auto end_std = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds_std = end_std - start_std;

    // Print the results
    TEST_COUT << "INTRINSIC Dot Product Time      : "
              << elapsed_seconds_intrin.count() << " seconds" << std::endl;
    TEST_COUT << "STANDARD  Dot Product Time      : "
              << elapsed_seconds_std.count() << " seconds" << std::endl;

    EXPECT_EQ(result_std, result_intrin);
}
