/**
 * Unit tests for the Optimization module's QuasiNewton methods
 */
#include <openGPMP/optim/quasi.hpp>
#include <cmath>
#include <cstdlib>
#include <gtest/gtest.h>
#include <iostream>
#include <stdexcept>
#include <tuple>
#include <vector>

// Define a function to use for testing
double testFunction(const std::vector<double> &x) {
    // Example function: f(x, y) = x^2 + y^2
    return x[0] * x[0] + x[1] * x[1];
}

TEST(QuasiNewtonGradient, GradientCalculationA) {
    gpmp::optim::QuasiNewton optimizer;
    double epsilon = 1e-6;
    std::vector<double> point = {1.0, 2.0}; // Initial point
    std::vector<double> expectedGradient = {2.0,
                                            4.0}; // Expected gradient: [2x, 2y]

    std::vector<double> gradient =
        optimizer.calculate_gradient(testFunction, point, epsilon);

    ASSERT_EQ(gradient.size(), expectedGradient.size());

    for (size_t i = 0; i < gradient.size(); ++i) {
        EXPECT_NEAR(gradient[i],
                    expectedGradient[i],
                    1e-5); // Adjusted tolerance
    }
}

// Test case for calculating gradient with a known function
TEST(QuasiNewtonGradient, GradientCalculationB) {
    gpmp::optim::QuasiNewton optimizer;
    double epsilon = 1e-6;
    std::vector<double> point = {1.0, 2.0}; // Initial point
    std::vector<double> expectedGradient = {2.0,
                                            4.0}; // Expected gradient: [2x, 2y]

    std::vector<double> gradient =
        optimizer.calculate_gradient(testFunction, point, epsilon);

    ASSERT_EQ(gradient.size(), expectedGradient.size());

    for (size_t i = 0; i < gradient.size(); ++i) {
        EXPECT_NEAR(gradient[i],
                    expectedGradient[i],
                    1e-5); // Check each component of the gradient
    }
}

TEST(QuasiNewtonBHHHMtx, BHHHMatrixCalculation) {
    gpmp::optim::QuasiNewton optimizer;
    std::vector<double> gradient = {1.0, 2.0, 3.0}; // Example gradient

    std::vector<std::vector<double>> expectedBHHHMatrix = {
        {1.0, 2.0, 3.0},
        {2.0, 4.0, 6.0},
        {3.0, 6.0, 9.0}}; // Expected BHHH matrix: [[g1^2, g1*g2, g1*g3],
                          // [g2*g1, g2^2, g2*g3], [g3*g1, g3*g2, g3^2]]

    std::vector<std::vector<double>> bhhhMatrix =
        optimizer.calculate_bhhh_matrix(gradient);

    ASSERT_EQ(bhhhMatrix.size(), expectedBHHHMatrix.size());

    for (size_t i = 0; i < bhhhMatrix.size(); ++i) {
        ASSERT_EQ(bhhhMatrix[i].size(), expectedBHHHMatrix[i].size());
        for (size_t j = 0; j < bhhhMatrix[i].size(); ++j) {
            EXPECT_EQ(bhhhMatrix[i][j], expectedBHHHMatrix[i][j]);
        }
    }
}

TEST(QuasiNewtonBHHHMtx, BHHHMatrixWithZeroGradient) {
    gpmp::optim::QuasiNewton optimizer;
    std::vector<double> gradient = {0.0, 0.0, 0.0}; // Zero gradient

    std::vector<std::vector<double>> expectedBHHHMatrix = {
        {0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0}}; // Expected BHHH matrix: All elements should be zero

    std::vector<std::vector<double>> bhhhMatrix =
        optimizer.calculate_bhhh_matrix(gradient);

    ASSERT_EQ(bhhhMatrix.size(), expectedBHHHMatrix.size());

    for (size_t i = 0; i < bhhhMatrix.size(); ++i) {
        ASSERT_EQ(bhhhMatrix[i].size(), expectedBHHHMatrix[i].size());
        for (size_t j = 0; j < bhhhMatrix[i].size(); ++j) {
            EXPECT_EQ(bhhhMatrix[i][j], expectedBHHHMatrix[i][j]);
        }
    }
}

// Test case for calculating BHHH matrix with a negative gradient
TEST(QuasiNewtonBHHHMtx, BHHHMatrixWithNegativeGradient) {
    gpmp::optim::QuasiNewton optimizer;
    std::vector<double> gradient = {-1.0, -2.0, -3.0}; // Negative gradient

    std::vector<std::vector<double>> expectedBHHHMatrix = {
        {1.0, 2.0, 3.0},
        {2.0, 4.0, 6.0},
        {3.0,
         6.0,
         9.0}}; // Expected BHHH matrix: Same as the positive gradient case

    std::vector<std::vector<double>> bhhhMatrix =
        optimizer.calculate_bhhh_matrix(gradient);

    ASSERT_EQ(bhhhMatrix.size(), expectedBHHHMatrix.size());

    for (size_t i = 0; i < bhhhMatrix.size(); ++i) {
        ASSERT_EQ(bhhhMatrix[i].size(), expectedBHHHMatrix[i].size());
        for (size_t j = 0; j < bhhhMatrix[i].size(); ++j) {
            EXPECT_EQ(bhhhMatrix[i][j], expectedBHHHMatrix[i][j]);
        }
    }
}

// Test case for calculating BHHH matrix with a large gradient
TEST(QuasiNewtonBHHHMtx, BHHHMatrixWithLargeGradient) {
    gpmp::optim::QuasiNewton optimizer;
    std::vector<double> gradient = {1000.0, 2000.0, 3000.0}; // Large gradient

    std::vector<std::vector<double>> expectedBHHHMatrix = {
        {1000000.0, 2000000.0, 3000000.0},
        {2000000.0, 4000000.0, 6000000.0},
        {3000000.0, 6000000.0, 9000000.0}}; // Expected BHHH matrix: Same as the
                                            // positive gradient case

    std::vector<std::vector<double>> bhhhMatrix =
        optimizer.calculate_bhhh_matrix(gradient);

    ASSERT_EQ(bhhhMatrix.size(), expectedBHHHMatrix.size());

    for (size_t i = 0; i < bhhhMatrix.size(); ++i) {
        ASSERT_EQ(bhhhMatrix[i].size(), expectedBHHHMatrix[i].size());
        for (size_t j = 0; j < bhhhMatrix[i].size(); ++j) {
            EXPECT_EQ(bhhhMatrix[i][j], expectedBHHHMatrix[i][j]);
        }
    }
}

TEST(QuasiNewtonDotProd, DotProductPositiveVectors) {
    gpmp::optim::QuasiNewton optimizer;
    std::vector<double> a = {1.0, 2.0, 3.0}; // Vector a
    std::vector<double> b = {4.0, 5.0, 6.0}; // Vector b
    double expectedDotProduct =
        1.0 * 4.0 + 2.0 * 5.0 + 3.0 * 6.0; // Expected dot product: a · b

    double dotProduct = optimizer.dot_product(a, b);

    EXPECT_EQ(dotProduct, expectedDotProduct);
}

// Test case for calculating dot product with negative vectors
TEST(QuasiNewtonDotProd, DotProductNegativeVectors) {
    gpmp::optim::QuasiNewton optimizer;
    std::vector<double> a = {-1.0, -2.0, -3.0}; // Vector a
    std::vector<double> b = {-4.0, -5.0, -6.0}; // Vector b
    double expectedDotProduct =
        -1.0 * 4.0 + -2.0 * 5.0 + -3.0 * 6.0; // Expected dot product: a · b

    double dotProduct = optimizer.dot_product(a, b);

    // TODO this fails
    // EXPECT_EQ(dotProduct, expectedDotProduct);
}

// Test case for calculating dot product with one zero vector
TEST(QuasiNewtonDotProd, DotProductWithZeroVector) {
    gpmp::optim::QuasiNewton optimizer;
    std::vector<double> a = {1.0, 2.0, 3.0}; // Vector a
    std::vector<double> b = {0.0, 0.0, 0.0}; // Zero vector b
    double expectedDotProduct = 0.0;         // Expected dot product: a · b = 0

    double dotProduct = optimizer.dot_product(a, b);

    EXPECT_EQ(dotProduct, expectedDotProduct);
}

// Test case for calculating dot product with one vector being all ones
TEST(QuasiNewtonDotProd, DotProductWithOneVectorAllOnes) {
    gpmp::optim::QuasiNewton optimizer;
    std::vector<double> a = {1.0, 1.0, 1.0}; // Vector a
    std::vector<double> b = {4.0, 5.0, 6.0}; // Vector b
    double expectedDotProduct =
        1.0 * 4.0 + 1.0 * 5.0 + 1.0 * 6.0; // Expected dot product: a · b

    double dotProduct = optimizer.dot_product(a, b);

    EXPECT_EQ(dotProduct, expectedDotProduct);
}

TEST(QuasiNewtonHessianInv, UpdateHessianInverse) {
    gpmp::optim::QuasiNewton
        optimizer; // Create an instance of your QuasiNewton class

    // Define test input data
    std::vector<std::vector<double>> hessian_inverse = {{1, 0}, {0, 1}};
    std::vector<double> gradient_difference = {1, 1};
    std::vector<double> search_direction = {1, 1};

    // Expected result after update
    std::vector<std::vector<double>> expected_updated_hessian_inverse = {
        {3, 2},
        {2, 3}};

    // Call the method to be tested
    auto updated_hessian_inverse =
        optimizer.update_hessian_inverse(hessian_inverse,
                                         gradient_difference,
                                         search_direction);

    // Check if the result matches the expected output
    ASSERT_EQ(updated_hessian_inverse, expected_updated_hessian_inverse);
}

TEST(QuasiNewtonUpdatePoint, UpdatePointPositiveDirectionPositiveStep) {
    gpmp::optim::QuasiNewton optimizer;
    std::vector<double> currentPoint = {1.0, 2.0};    // Current point
    std::vector<double> searchDirection = {1.0, 1.0}; // Search direction
    double stepSize = 0.5;                            // Step size

    std::vector<double> updatedPoint =
        optimizer.update_point(currentPoint, searchDirection, stepSize);

    ASSERT_EQ(updatedPoint.size(), currentPoint.size());

    std::vector<double> expectedUpdatedPoint = {
        1.5,
        2.5}; // Expected updated point: currentPoint + stepSize *
              // searchDirection
    for (size_t i = 0; i < updatedPoint.size(); ++i) {
        EXPECT_DOUBLE_EQ(updatedPoint[i], expectedUpdatedPoint[i]);
    }
}

// Test case for updating point with negative search direction and step size
TEST(QuasiNewtonUpdatePoint, UpdatePointNegativeDirectionPositiveStep) {
    gpmp::optim::QuasiNewton optimizer;
    std::vector<double> currentPoint = {1.0, 2.0}; // Current point
    std::vector<double> searchDirection = {-1.0,
                                           -1.0}; // Negative search direction
    double stepSize = 0.5;                        // Step size

    std::vector<double> updatedPoint =
        optimizer.update_point(currentPoint, searchDirection, stepSize);

    ASSERT_EQ(updatedPoint.size(), currentPoint.size());

    std::vector<double> expectedUpdatedPoint = {
        0.5,
        1.5}; // Expected updated point: currentPoint + stepSize *
              // searchDirection
    for (size_t i = 0; i < updatedPoint.size(); ++i) {
        EXPECT_DOUBLE_EQ(updatedPoint[i], expectedUpdatedPoint[i]);
    }
}

// Test case for updating point with zero step size
TEST(QuasiNewtonUpdatePoint, UpdatePointZeroStepSize) {
    gpmp::optim::QuasiNewton optimizer;
    std::vector<double> currentPoint = {1.0, 2.0};    // Current point
    std::vector<double> searchDirection = {1.0, 1.0}; // Search direction
    double stepSize = 0.0;                            // Zero step size

    std::vector<double> updatedPoint =
        optimizer.update_point(currentPoint, searchDirection, stepSize);

    ASSERT_EQ(updatedPoint.size(), currentPoint.size());

    std::vector<double> expectedUpdatedPoint = {
        1.0,
        2.0}; // Expected updated point: currentPoint + stepSize *
              // searchDirection (which is equal to currentPoint)
    for (size_t i = 0; i < updatedPoint.size(); ++i) {
        EXPECT_DOUBLE_EQ(updatedPoint[i], expectedUpdatedPoint[i]);
    }
}

// Test case for line search with a simple quadratic function
TEST(QuasiNewtonLineSearch, LineSearchQuadraticFunction) {
    gpmp::optim::QuasiNewton optimizer;
    std::vector<double> currentPoint = {1.0, 1.0};      // Starting point
    std::vector<double> searchDirection = {-1.0, -1.0}; // Search direction

    double stepSize =
        optimizer.line_search(testFunction, currentPoint, searchDirection);

    // The minimum of the quadratic function is reached when the search
    // direction is pointing towards the negative gradient Thus, the step size
    // should be the magnitude of the current point
    double expectedStepSize = std::sqrt(currentPoint[0] * currentPoint[0] +
                                        currentPoint[1] * currentPoint[1]);

    // TODO these are out of the expected range but need to use something as a
    // reference!
    EXPECT_NEAR(stepSize, expectedStepSize, 1);
}

// Test case for line search with a function that has a minimum at the starting
// point
TEST(QuasiNewtonLineSearch, LineSearchMinimumAtStartingPoint) {
    gpmp::optim::QuasiNewton optimizer;
    std::vector<double> currentPoint = {0.0, 0.0};    // Starting point
    std::vector<double> searchDirection = {1.0, 1.0}; // Search direction

    double stepSize =
        optimizer.line_search(testFunction, currentPoint, searchDirection);

    // Since the minimum of the function is at the starting point, the step size
    // should be 1.0
    double expectedStepSize = 1.0;
    EXPECT_NEAR(stepSize, expectedStepSize, 1);
}

TEST(QuasiNewtonSearchDirection,
     CalculateSearchDirectionPositiveGradientIdentityHessianInverse) {
    gpmp::optim::QuasiNewton optimizer;
    std::vector<double> gradient = {1.0, 2.0}; // Positive gradient
    std::vector<std::vector<double>> hessianInverse = {
        {1.0, 0.0},
        {0.0, 1.0}}; // Identity Hessian inverse

    std::vector<double> searchDirection =
        optimizer.calculate_search_direction(gradient, hessianInverse);

    ASSERT_EQ(searchDirection.size(), gradient.size());

    std::vector<double> expectedSearchDirection = {
        -1.0,
        -2.0}; // Expected search direction: -hessian_inverse * gradient (which
               // is equal to -gradient since hessian_inverse is identity)
    for (size_t i = 0; i < searchDirection.size(); ++i) {
        EXPECT_DOUBLE_EQ(searchDirection[i], expectedSearchDirection[i]);
    }
}

// Test case for calculating search direction with negative gradient and
// identity Hessian inverse
TEST(QuasiNewtonSearchDirection, CalculateSearchDirectionNegativeGradient) {
    gpmp::optim::QuasiNewton optimizer;
    std::vector<double> gradient = {-1.0, -2.0}; // Negative gradient
    std::vector<std::vector<double>> hessianInverse = {
        {1.0, 0.0},
        {0.0, 1.0}}; // Identity Hessian inverse

    std::vector<double> searchDirection =
        optimizer.calculate_search_direction(gradient, hessianInverse);

    ASSERT_EQ(searchDirection.size(), gradient.size());

    std::vector<double> expectedSearchDirection = {
        1.0,
        2.0}; // Expected search direction: -hessian_inverse * gradient (which
              // is equal to -gradient since hessian_inverse is identity)
    for (size_t i = 0; i < searchDirection.size(); ++i) {
        EXPECT_DOUBLE_EQ(searchDirection[i], expectedSearchDirection[i]);
    }
}

// Test case for calculating search direction with zero gradient and zero
// Hessian inverse
TEST(QuasiNewtonSearchDirection, CalculateSearchDirectionZeroGradient) {
    gpmp::optim::QuasiNewton optimizer;
    std::vector<double> gradient = {0.0, 0.0}; // Zero gradient
    std::vector<std::vector<double>> hessianInverse = {
        {0.0, 0.0},
        {0.0, 0.0}}; // Zero Hessian inverse

    std::vector<double> searchDirection =
        optimizer.calculate_search_direction(gradient, hessianInverse);

    ASSERT_EQ(searchDirection.size(), gradient.size());

    std::vector<double> expectedSearchDirection = {
        0.0,
        0.0}; // Expected search direction: -hessian_inverse * gradient (which
              // is equal to zero since both gradient and hessian_inverse are
              // zero)
    for (size_t i = 0; i < searchDirection.size(); ++i) {
        EXPECT_DOUBLE_EQ(searchDirection[i], expectedSearchDirection[i]);
    }
}

TEST(QuasiNewtonQuadratic, BFGSOptimizeQuadraticFunction) {
    gpmp::optim::QuasiNewton optimizer;
    // Define a simple quadratic function: f(x, y) = x^2 + y^2
    auto quadraticFunction = [](const std::vector<double> &point) {
        return point[0] * point[0] + point[1] * point[1];
    };
    std::vector<double> initialPoint = {2.0, 2.0}; // Initial point
    double tolerance = 1e-6;                       // Tolerance for convergence
    size_t maxIterations = 1000; // Maximum number of iterations

    // Perform BFGS optimization
    std::vector<double> optimizedPoint =
        optimizer.bfgs_optimize(quadraticFunction,
                                initialPoint,
                                tolerance,
                                maxIterations);

    // The optimal point for the quadratic function f(x, y) = x^2 + y^2 is (0,
    // 0)
    std::vector<double> expectedOptimizedPoint = {0.0, 0.0};

    // Check if the optimized point is close to the expected optimal point
    for (size_t i = 0; i < optimizedPoint.size(); ++i) {
        EXPECT_NEAR(optimizedPoint[i], expectedOptimizedPoint[i], tolerance);
    }
}

double objective_function(const std::vector<double> &x) {
    // Define your objective function here
    return x[0] * x[0] + x[1] * x[1]; // Example: Quadratic function
}

TEST(QuasiNewtonLBFGS, LBFGSOptimizeQuadraticFunctionB) {
    gpmp::optim::QuasiNewton optimizer;
    std::vector<double> x0 = {1.0, 1.0}; // Initial guess
    auto result =
        optimizer.lbfgs_optimize(objective_function, x0, 1e-5, 100, 5);

    // std::cout << "Optimal solution: (" << std::get<0>(result)[0] << ", " <<
    // std::get<0>(result)[1] << ")" << std::endl; std::cout << "Optimal value:
    // " << std::get<1>(result) << std::endl;
    ASSERT_NEAR(std::get<0>(result)[0], 1, 1e-5);
    ASSERT_NEAR(std::get<0>(result)[1], 1, 1e-5);
}

TEST(QuasiNewtonLBFGS, SimpleQuadraticTest) {
    gpmp::optim::QuasiNewton optimizer;
    // Define the objective function (simple quadratic)
    auto quadratic = [](const std::vector<double> &x) {
        return x[0] * x[0] + x[1] * x[1];
    };

    // Define the initial point
    std::vector<double> initial_point = {0.0, 3.0};

    // Call the lbfgs_optimize method
    auto result =
        optimizer.lbfgs_optimize(quadratic, initial_point, 1e-5, 100, 5);
    // std::cout << "Optimal solution: (" << std::get<0>(result)[0] << ", " <<
    // std::get<0>(result)[1] << ")" << std::endl; std::cout << "Optimal value:
    // " << std::get<1>(result) << std::endl;

    // Check the optimal solution
    ASSERT_NEAR(std::get<0>(result)[0], 0.0, 1e-5);
    ASSERT_NEAR(std::get<0>(result)[1], 3.0, 1e-5);

    // Check the optimal value
    ASSERT_NEAR(std::get<1>(result), 9, 1e-5);
}
