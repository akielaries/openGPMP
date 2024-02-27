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
    std::cerr << "\033[32m[          ] [ INFO ] \033[0m\033[1;34m\033[1m"
TEST(VectorVectorTestDouble, Addition) {
    INFO_COUT << "Vector (as Vectors) NAIVE" << std::endl;

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
TEST(VectorVectorTestDouble, Subtraction) {
    std::vector<double> vec1 = {4.0, 5.0, 6.0};
    std::vector<double> vec2 = {1.0, 2.0, 3.0};
    std::vector<double> result;

    gpmp::linalg::std_vector_sub(vec1, vec2, result);

    ASSERT_EQ(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0], 3.0);
    EXPECT_DOUBLE_EQ(result[1], 3.0);
    EXPECT_DOUBLE_EQ(result[2], 3.0);
}

// Test cases for gpmp::linalg::std_scalar_mult function
TEST(VectorVectorTestDouble, Multiplication) {
    std::vector<double> vec = {1.0, 2.0, 3.0};
    std::vector<double> result;

    gpmp::linalg::std_scalar_mult(vec, 2.0, result);

    ASSERT_EQ(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0], 2.0);
    EXPECT_DOUBLE_EQ(result[1], 4.0);
    EXPECT_DOUBLE_EQ(result[2], 6.0);
}

// Test cases for std_dot_product function
TEST(VectorVectorTestDouble, DotProduct) {
    std::vector<double> vec1 = {1.0, 2.0, 3.0};
    std::vector<double> vec2 = {4.0, 5.0, 6.0};

    double result = gpmp::linalg::std_dot_product(vec1, vec2);

    EXPECT_DOUBLE_EQ(result, 32.0);
}

// Test cases for std_cross_product function
TEST(VectorVectorTestDouble, CrossProduct) {
    std::vector<double> vec1 = {1.0, 2.0, 3.0};
    std::vector<double> vec2 = {3.0, 4.0, 5.0};
    std::vector<double> result(3);

    gpmp::linalg::std_cross_product(vec1, vec2, result);

    ASSERT_EQ(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0], -2);
    EXPECT_DOUBLE_EQ(result[1], 4);
    EXPECT_DOUBLE_EQ(result[2], -2);
}

TEST(VectorVectorTestDouble, Magnitude) {
    std::vector<double> vec = {3.0, 4.0};
    double norm = gpmp::linalg::std_vector_norm(vec);
    EXPECT_DOUBLE_EQ(norm, 5.0);
}

// Unit tests for gpmp::linalg::std_vector_normalize function
TEST(VectorVectorTestDouble, Normalization) {
    std::vector<double> vec = {3.0, 4.0};
    std::vector<double> result;
    gpmp::linalg::std_vector_normalize(vec, result);
    EXPECT_DOUBLE_EQ(result[0], 0.6);
    EXPECT_DOUBLE_EQ(result[1], 0.8);
}

// Unit tests for gpmp::linalg::std_vector_projection function
TEST(VectorVectorTestDouble, Projection) {
    std::vector<double> vec = {3.0, 2.0};
    std::vector<double> onto_vec = {4.0, 0.0};
    std::vector<double> result;
    gpmp::linalg::std_vector_projection(vec, onto_vec, result);
    EXPECT_DOUBLE_EQ(result[0], 3.0);
    EXPECT_DOUBLE_EQ(result[1], 0.0);
}

TEST(VectorVectorTestInt, Addition) {
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
TEST(VectorVectorTestInt, Subtraction) {
    std::vector<int> vec1 = {4, 5, 6};
    std::vector<int> vec2 = {1, 2, 3};
    std::vector<int> result;

    gpmp::linalg::std_vector_sub(vec1, vec2, result);

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 3);
    EXPECT_EQ(result[1], 3);
    EXPECT_EQ(result[2], 3);
}

// Unit tests for std_scalar_mult function
TEST(VectorVectorTestInt, Multiplication) {
    std::vector<int> vec = {1, 2, 3};
    std::vector<int> result;

    gpmp::linalg::std_scalar_mult(vec, 2, result);

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 2);
    EXPECT_EQ(result[1], 4);
    EXPECT_EQ(result[2], 6);
}

// Unit tests for std_dot_product function
TEST(VectorVectorTestInt, DotProduct) {
    std::vector<int> vec1 = {1, 2, 3};
    std::vector<int> vec2 = {4, 5, 6};

    int result = gpmp::linalg::std_dot_product(vec1, vec2);

    EXPECT_EQ(result, 32);
}

// Unit tests for std_cross_product function
TEST(VectorVectorTestInt, CrossProduct) {
    std::vector<int> vec1 = {1, 0, 0};
    std::vector<int> vec2 = {0, 1, 0};
    std::vector<int> result(3);

    gpmp::linalg::std_cross_product(vec1, vec2, result);

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 0);
    EXPECT_EQ(result[2], 1);
}

TEST(VectorVectorTestInt, Magnitude) {
    std::vector<int> vec = {3, 4};
    double norm = gpmp::linalg::std_vector_norm(vec);
    EXPECT_DOUBLE_EQ(norm, 5.0);
}

// Unit tests for std_vector_normalize function
TEST(VectorVectorTestInt, Normalization) {
    std::vector<int> vec = {3, 4};
    std::vector<double> result;
    gpmp::linalg::std_vector_normalize(vec, result);
    EXPECT_DOUBLE_EQ(result[0], 0.6);
    EXPECT_DOUBLE_EQ(result[1], 0.8);
}

// Unit tests for std_vector_projection function
TEST(VectorVectorTestInt, Projection) {
    std::vector<int> vec = {3, 2};
    std::vector<int> onto_vec = {4, 0};
    std::vector<double> result;
    gpmp::linalg::std_vector_projection(vec, onto_vec, result);
    EXPECT_DOUBLE_EQ(result[0], 3.0);
    EXPECT_DOUBLE_EQ(result[1], 0.0);
}
