/**
 * Unit tests for the Linear Algebra module's Eigen class
 */
#include <openGPMP/linalg/eigen.hpp>
#include <cstdlib>
#include <gtest/gtest.h>
#include <iostream>
#include <stdexcept>
#include <vector>

const double TOLERANCE = 1e-3;

TEST(EigenTest, PowerIteration) {
    std::vector<std::vector<double>> squareMat = {{2.0, -1.0, 0.0},
                                                  {-1.0, 2.0, -1.0},
                                                  {0.0, -1.0, 2.0}};
    gpmp::linalg::Eigen eigenSquare(squareMat);

    double eigenvalueSquare = eigenSquare.power_iter(1000, TOLERANCE);

    EXPECT_NEAR(eigenvalueSquare, 3.414, TOLERANCE);
}

TEST(EigenTest, QRAlgorithm) {
    std::vector<std::vector<double>> squareMat = {{2.0, -1.0, 0.0},
                                                  {-1.0, 2.0, -1.0},
                                                  {0.0, -1.0, 2.0}};
    gpmp::linalg::Eigen eigenSquare(squareMat);

    // execute QR algorithm method
    std::vector<double> eigenvaluesSquare =
        eigenSquare.qr_algorithm(1000, TOLERANCE);

    // sort eigenvalues in ascending order for comparison
    std::sort(eigenvaluesSquare.begin(), eigenvaluesSquare.end());

    EXPECT_NEAR(eigenvaluesSquare[0], 1.069, TOLERANCE);
    EXPECT_NEAR(eigenvaluesSquare[1], 1.673, TOLERANCE);
    EXPECT_NEAR(eigenvaluesSquare[2], 2.236, TOLERANCE);
}

TEST(EigenTest, Determinant) {
    // Test square matrix
    std::vector<std::vector<double>> squareMat = {{2.0, -1.0, 0.0},
                                                  {-1.0, 2.0, -1.0},
                                                  {0.0, -1.0, 2.0}};
    gpmp::linalg::Eigen eigenSquare(squareMat);

    // execute determinant method
    double detSquare = eigenSquare.determinant();

    // determinant of the matrix is the product of its eigenvalues
    double expectedDetSquare = 4;

    EXPECT_NEAR(detSquare, expectedDetSquare, TOLERANCE);
}

TEST(EigenTest, Sensitivity) {
    // Test square matrix
    std::vector<std::vector<double>> squareMat = {{2.0, -1.0, 0.0},
                                                  {-1.0, 2.0, -1.0},
                                                  {0.0, -1.0, 2.0}};
    gpmp::linalg::Eigen eigenSquare(squareMat);

    // Perturbation value
    double perturbation = 1e-5;

    // Execute sensitivity method
    std::vector<double> sensitivity = eigenSquare.sensitivity(perturbation);

    // Expected sensitivity for each eigenvalue (analytically computed)
    std::vector<double> expectedSensitivity = {0.894, 0.717, 0.801};

    // Assert sensitivity
    ASSERT_EQ(sensitivity.size(), expectedSensitivity.size());
    for (size_t i = 0; i < sensitivity.size(); ++i) {
        EXPECT_NEAR(sensitivity[i], expectedSensitivity[i], TOLERANCE);
    }
}
