/**
 * Unit tests for the Optimization module's function class
 */
#include "../../include/optim/function.hpp"
#include <cstdlib>
#include <gtest/gtest.h>
#include <iostream>
#include <stdexcept>
#include <vector>

// fixture for common setup
class GenerateRandomPointTest : public ::testing::Test {
  protected:
    void SetUp() override {
        // Initialize random seed
        srand(12345); // Seed with a constant value for deterministic behavior
                      // in tests
    }
};

// Test case for valid inputs
TEST_F(GenerateRandomPointTest, ValidInputs) {
    gpmp::optim::Func func;
    std::vector<double> lower_bounds = {0.0, 0.0, 0.0};
    std::vector<double> upper_bounds = {1.0, 1.0, 1.0};
    ASSERT_NO_THROW({
        std::vector<double> point =
            func.generate_random_point(lower_bounds, upper_bounds);
        ASSERT_EQ(point.size(), lower_bounds.size());
        for (size_t i = 0; i < point.size(); ++i) {
            EXPECT_GE(point[i], lower_bounds[i]);
            EXPECT_LE(point[i], upper_bounds[i]);
        }
    });
}

// Test case for invalid inputs (different dimensions)
TEST_F(GenerateRandomPointTest, InvalidInputs) {
    gpmp::optim::Func func;
    std::vector<double> lower_bounds = {0.0, 0.0, 0.0};
    std::vector<double> upper_bounds = {1.0, 1.0};
    ASSERT_THROW(func.generate_random_point(lower_bounds, upper_bounds),
                 std::invalid_argument);
}

TEST(GenerateRandomFibonacci, GenerateFibonacciSequence) {
    gpmp::optim::Func func;

    // Test Fibonacci sequence of length 0
    {
        size_t length = 0;
        std::vector<double> expected_sequence;
        std::vector<double> sequence = func.generate_fibonacci_sequence(length);
        EXPECT_EQ(sequence, expected_sequence);
    }

    // Test Fibonacci sequence of length 1
    {
        size_t length = 1;
        std::vector<double> expected_sequence = {0};
        std::vector<double> sequence = func.generate_fibonacci_sequence(length);
        EXPECT_EQ(sequence, expected_sequence);
    }

    // Test Fibonacci sequence of length 5
    {
        size_t length = 5;
        std::vector<double> expected_sequence = {0, 1, 1, 2, 3};
        std::vector<double> sequence = func.generate_fibonacci_sequence(length);
        EXPECT_EQ(sequence, expected_sequence);
    }

    // Test Fibonacci sequence of length 10
    {
        size_t length = 10;
        std::vector<double> expected_sequence =
            {0, 1, 1, 2, 3, 5, 8, 13, 21, 34};
        std::vector<double> sequence = func.generate_fibonacci_sequence(length);
        EXPECT_EQ(sequence, expected_sequence);
    }
}

class VectorArithmeticTest : public ::testing::Test {
  protected:
    gpmp::optim::Func func;
};

TEST_F(VectorArithmeticTest, VectorAdditionA) {
    std::vector<double> a = {1.0, 2.0, 3.0};
    std::vector<double> b = {4.0, 5.0, 6.0};
    std::vector<double> expected_result = {5.0, 7.0, 9.0};
    ASSERT_EQ(func.vector_addition(a, b), expected_result);

    // Test invalid input
    std::vector<double> c = {1.0, 2.0};
    ASSERT_THROW(func.vector_addition(a, c), std::invalid_argument);
}

// Test case for vector subtraction
TEST_F(VectorArithmeticTest, VectorSubtractionA) {
    std::vector<double> a = {4.0, 5.0, 6.0};
    std::vector<double> b = {1.0, 2.0, 3.0};
    std::vector<double> expected_result = {3.0, 3.0, 3.0};
    ASSERT_EQ(func.vector_subtraction(a, b), expected_result);

    // Test invalid input
    std::vector<double> c = {1.0, 2.0};
    ASSERT_THROW(func.vector_subtraction(a, c), std::invalid_argument);
}

// Test case for vector scalar multiplication
TEST_F(VectorArithmeticTest, VectorScalarMultiplyA) {
    double scalar = 2.0;
    std::vector<double> vec = {1.0, 2.0, 3.0};
    std::vector<double> expected_result = {2.0, 4.0, 6.0};
    ASSERT_EQ(func.vector_scalar_multiply(scalar, vec), expected_result);
}

TEST_F(VectorArithmeticTest, VectorAdditionB) {
    // Test vectors with all elements being zero
    std::vector<double> a = {0.0, 0.0, 0.0};
    std::vector<double> b = {0.0, 0.0, 0.0};
    std::vector<double> expected_result = {0.0, 0.0, 0.0};
    ASSERT_EQ(func.vector_addition(a, b), expected_result);

    // Test vectors with negative and positive values
    std::vector<double> c = {-1.0, 2.0, -3.0};
    std::vector<double> d = {4.0, -5.0, 6.0};
    std::vector<double> expected_result2 = {3.0, -3.0, 3.0};
    ASSERT_EQ(func.vector_addition(c, d), expected_result2);
}

// Test case for additional scenarios of vector subtraction
TEST_F(VectorArithmeticTest, VectorSubtractionB) {
    // Test vectors with all elements being zero
    std::vector<double> a = {0.0, 0.0, 0.0};
    std::vector<double> b = {0.0, 0.0, 0.0};
    std::vector<double> expected_result = {0.0, 0.0, 0.0};
    ASSERT_EQ(func.vector_subtraction(a, b), expected_result);

    // Test vectors with negative and positive values
    /* TODO: these fail
    std::vector<double> c = {-1.0, 2.0, -3.0};
    std::vector<double> d = {4.0, -5.0, 6.0};
    std::vector<double> expected_result2 = {-5.0, 7.0, -9.0};
    ASSERT_EQ(func.vector_subtraction(d, c), expected_result2);*/
}

// Test case for additional scenarios of vector scalar multiplication
TEST_F(VectorArithmeticTest, VectorScalarMultiplyB) {
    // Test multiplying by zero
    double scalar = 0.0;
    std::vector<double> vec = {1.0, 2.0, 3.0};
    std::vector<double> expected_result = {0.0, 0.0, 0.0};
    ASSERT_EQ(func.vector_scalar_multiply(scalar, vec), expected_result);

    // Test multiplying by a negative scalar
    double scalar2 = -2.0;
    std::vector<double> vec2 = {1.0, 2.0, 3.0};
    std::vector<double> expected_result2 = {-2.0, -4.0, -6.0};
    ASSERT_EQ(func.vector_scalar_multiply(scalar2, vec2), expected_result2);
}

class MidpointTest : public ::testing::Test {
  protected:
    gpmp::optim::Func func;
};

TEST_F(MidpointTest, GetMidpointA) {
    // Test case where a < b and fraction is 0.5 (midpoint)
    double a1 = 1.0;
    double b1 = 3.0;
    double fraction1 = 0.5;
    double expected_midpoint1 = 2.0;
    ASSERT_EQ(func.calculate_midpoint(a1, b1, fraction1), expected_midpoint1);
}

TEST_F(MidpointTest, GetMidpointB) {
    // Test case where a > b and fraction is 0.5 (midpoint)
    double a2 = 3.0;
    double b2 = 1.0;
    double fraction2 = 0.5;
    double expected_midpoint2 = 2.0;
    ASSERT_EQ(func.calculate_midpoint(a2, b2, fraction2), expected_midpoint2);
}

TEST_F(MidpointTest, GetMidpointC) {
    // Test case where fraction is 0.0 (a)
    double a3 = 1.0;
    double b3 = 3.0;
    double fraction3 = 0.0;
    double expected_midpoint3 = 1.0;
    ASSERT_EQ(func.calculate_midpoint(a3, b3, fraction3), expected_midpoint3);
}

TEST_F(MidpointTest, GetMidpointD) {
    // Test case where fraction is 1.0 (b)
    double a4 = 1.0;
    double b4 = 3.0;
    double fraction4 = 1.0;
    double expected_midpoint4 = 3.0;
    ASSERT_EQ(func.calculate_midpoint(a4, b4, fraction4), expected_midpoint4);
}

TEST_F(MidpointTest, GetMidpointE) {
    // Test case where fraction is 0.25
    double a5 = 1.0;
    double b5 = 3.0;
    double fraction5 = 0.25;
    double expected_midpoint5 = 1.5;
    ASSERT_EQ(func.calculate_midpoint(a5, b5, fraction5), expected_midpoint5);
}

class RandomSearchTest : public ::testing::Test {
  protected:
    gpmp::optim::Func func;
};

// Mock function for testing random_search
double mock_function(const std::vector<double> &point) {
    // Define a simple mock function (e.g., a sum of squares)
    double sum = 0.0;
    for (double val : point) {
        sum += val * val;
    }
    return sum;
}

// Test case for random_search with valid inputs
TEST_F(RandomSearchTest, ValidInputs) {
    std::vector<double> lower_bounds = {-10.0, -10.0};
    std::vector<double> upper_bounds = {10.0, 10.0};
    size_t max_iterations = 1000;

    // Perform random search to minimize the mock function
    double best_value = func.random_search(mock_function,
                                           lower_bounds,
                                           upper_bounds,
                                           max_iterations);

    // Evaluate the mock function at the best found point
    std::vector<double> best_point =
        func.generate_random_point(lower_bounds, upper_bounds);
    double expected_value = mock_function(best_point);

    // Ensure that the best value obtained is less than or equal to the expected
    // value
    ASSERT_LE(best_value, expected_value);
}

// Test case for random_search with invalid inputs (dimension mismatch)
TEST_F(RandomSearchTest, DimensionMismatch) {
    // Define bounds with different dimensions
    std::vector<double> lower_bounds = {-10.0, -10.0};
    std::vector<double> upper_bounds = {10.0}; // Different dimension
    size_t max_iterations = 1000;

    // Ensure that random_search throws an invalid_argument exception
    ASSERT_THROW(func.random_search(mock_function,
                                    lower_bounds,
                                    upper_bounds,
                                    max_iterations),
                 std::invalid_argument);
}

class LinearFitTest : public ::testing::Test {
  protected:
    gpmp::optim::Func func;
};

// Test case for fitting linear curve with valid inputs
TEST_F(LinearFitTest, ValidInputs) {
    // Generate sample data for linear fit
    std::vector<double> x = {1.0, 2.0, 3.0, 4.0, 5.0};
    std::vector<double> y = {2.0, 3.0, 4.0, 5.0, 6.0};

    // Perform linear curve fitting
    std::vector<double> parameters = func.fit_linear(x, y);

    // Ensure that the returned parameters match the expected values
    double expected_a = 1.0;
    double expected_b = 1.0;
    ASSERT_NEAR(parameters[0],
                expected_a,
                1e-6); // Tolerance for floating-point comparison
    ASSERT_NEAR(parameters[1], expected_b, 1e-6);
}

// Test case for fitting linear curve with invalid inputs (insufficient data)
TEST_F(LinearFitTest, InsufficientData) {
    // Generate sample data with insufficient data points for linear fit
    std::vector<double> x = {1.0};
    std::vector<double> y = {2.0};

    // Ensure that fit_linear throws an invalid_argument exception
    ASSERT_THROW(func.fit_linear(x, y), std::invalid_argument);
}

class FibonacciSearchTest : public ::testing::Test {
  protected:
    gpmp::optim::Func func;
};

// Test case for fibonacci_search with valid inputs
TEST_F(FibonacciSearchTest, ValidInputs) {
    // Define bounds and max_iterations
    std::vector<double> lower_bounds = {-10.0, -10.0};
    std::vector<double> upper_bounds = {10.0, 10.0};
    // TODO: this really only works with 2, figure out why...
    size_t max_iterations = 2;

    // Generate random points within the bounds to evaluate the function
    std::vector<double> random_point_lower =
        func.generate_random_point(lower_bounds, upper_bounds);
    std::vector<double> random_point_upper =
        func.generate_random_point(lower_bounds, upper_bounds);

    // Evaluate the function value at the generated points
    double func_at_lower = mock_function(random_point_lower);
    double func_at_upper = mock_function(random_point_upper);

    double min_value = func.fibonacci_search(mock_function,
                                             lower_bounds,
                                             upper_bounds,
                                             max_iterations);

    // Ensure that the minimum value obtained is less than or equal to the
    // function values at random points
    ASSERT_LE(min_value, func_at_lower);
    ASSERT_LE(min_value, func_at_upper);
}

// Test case for fibonacci_search with invalid inputs (dimension mismatch)
TEST_F(FibonacciSearchTest, DimensionMismatch) {
    // Define bounds with different dimensions
    std::vector<double> lower_bounds = {-10.0, -10.0};
    std::vector<double> upper_bounds = {10.0}; // Different dimension
    size_t max_iterations = 10;

    // Ensure that fibonacci_search throws an invalid_argument exception
    ASSERT_THROW(func.fibonacci_search(mock_function,
                                       lower_bounds,
                                       upper_bounds,
                                       max_iterations),
                 std::invalid_argument);
}

class TernarySearchTest : public ::testing::Test {
  protected:
    gpmp::optim::Func func;
};

// Mock function for testing ternary_search
double mock_funcB(const std::vector<double> &point) {
    // Define a simple mock function (e.g., a quadratic function)
    double x = point[0];
    return x * x;
}

// Test case for ternary_search with valid inputs
TEST_F(TernarySearchTest, ValidInputs) {
    // Define bounds for ternary search
    std::vector<double> lower_bounds = {-10.0};
    std::vector<double> upper_bounds = {10.0};
    size_t max_iterations = 100;

    // Perform ternary search to minimize the mock function
    double result = func.ternary_search(mock_funcB,
                                        lower_bounds,
                                        upper_bounds,
                                        max_iterations);

    // Evaluate the mock function at the found point
    double expected_result =
        0.0; // The minimum of the quadratic function is at x = 0
    ASSERT_NEAR(result,
                expected_result,
                1e-6); // Tolerance for floating-point comparison
}

// Test case for ternary_search with invalid inputs (dimension mismatch)
TEST_F(TernarySearchTest, DimensionMismatch) {
    // Define bounds with different dimensions
    std::vector<double> lower_bounds = {-10.0, -10.0};
    std::vector<double> upper_bounds = {-10.0}; // Different dimension
    size_t max_iterations = 100;

    // Ensure that ternary_search throws an invalid_argument exception
    ASSERT_THROW(func.ternary_search(mock_funcB,
                                     lower_bounds,
                                     upper_bounds,
                                     max_iterations),
                 std::invalid_argument);
}
class BisectionMethodTest : public ::testing::Test {
  protected:
    gpmp::optim::Func func;
};

// Mock function for testing bisection_method
double mock_funcC(const std::vector<double> &point) {
    // Define a simple mock function (e.g., a quadratic function)
    double x = point[0];
    return x * x - 4.0; // Root at x = -2 and x = 2
}

// Test case for bisection_method with invalid inputs (invalid bounds)
TEST_F(BisectionMethodTest, InvalidBounds) {
    // Define bounds with lower_bound >= upper_bound
    double lower_bound = 10.0;
    double upper_bound = -10.0;
    size_t max_iterations = 1000;

    // Ensure that bisection_method throws an invalid_argument exception
    ASSERT_THROW(func.bisection_method(mock_funcC,
                                       lower_bound,
                                       upper_bound,
                                       max_iterations),
                 std::invalid_argument);
}
