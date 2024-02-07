/**
 * Unit tests for the Linear Algebra module's Linear Systems class
 */
#include "../../include/linalg/linsys.hpp"
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <gtest/gtest.h>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

const double TOLERANCE = 1e-3;

TEST(LinSysTest, SolveGauss) {
    std::vector<std::vector<double>> square_mat = {{3.0, 2.0, -4.0, 3.0},
                                                   {2.0, 3.0, 3.0, 15.0},
                                                   {5.0, -3, 1.0, 14.0}};
    gpmp::linalg::LinSys linSysSquare(square_mat);

    // execute solve_gauss method
    std::vector<double> solution = linSysSquare.solve_gauss();

    // expected solution for the test matrix
    std::vector<double> expected_sol = {3, 1, 2};

    // assert solution vector
    ASSERT_EQ(solution.size(), expected_sol.size());

    for (int i = 0; i < solution.size(); i++) {
        ASSERT_NEAR(solution[i], expected_sol[i], TOLERANCE);
    }
}

TEST(LinSysTest, DeterminantTest) {
    /*std::vector<std::vector<double>> square_mat = {
        {3.0, 2.0, -4.0, 3.0},
        {2.0, 3.0, 3.0, 15.0},
        {5.0, -3.0, 1.0, 14.0},
        {1.0, 1.0, 1.0, 6.0}};
    */

    std::vector<std::vector<double>> square_mat = {{2, 1}, {5, 3}};
    gpmp::linalg::LinSys linSysSquare(square_mat);

    double det = linSysSquare.determinant();

    double expectedDet = 1;

    ASSERT_DOUBLE_EQ(expectedDet, det);
}

TEST(LinSysTest, DeterminantTestB) {
    std::vector<std::vector<double>> square_mat = {{4, 4, 3, 1},
                                                   {2, 8, 8, 6},
                                                   {4, 3, 2, 2},
                                                   {4, 1, 5, 6}};

    gpmp::linalg::LinSys linSysSquare(square_mat);

    double det = linSysSquare.determinant();

    double expectedDet = -226;

    ASSERT_DOUBLE_EQ(expectedDet, det);
}

TEST(LinSysTest, LUDecompositionTest) {
    // Define a square matrix
    std::vector<std::vector<double>> square_mat = {{3.0, 2.0, -4.0, 3.0},
                                                   {2.0, 3.0, 3.0, 15.0},
                                                   {5.0, -3.0, 1.0, 14.0},
                                                   {1.0, 1.0, 1.0, 6.0}};

    // expected lower
    std::vector<std::vector<double>> L = {{1, 0, 0, 0},
                                          {0.666667, 1, 0, 0},
                                          {1.66667, -3.8, 1, 0},
                                          {0.333333, 0.2, 0.0410959, 1}};

    // expected upper
    std::vector<std::vector<double>> U = {{3, 2, -4, 3},
                                          {0, 1.66667, 5.66667, 13},
                                          {0, 0, 29.2, 58.4},
                                          {0, 0, 0, 0}};

    // Create a LinSys object
    gpmp::linalg::LinSys linSysSquare(square_mat);

    // execute LU decomposition
    auto LU_mtx = linSysSquare.lu_decomp();

    // Check the dimensions of L and U
    ASSERT_EQ(LU_mtx.first.size(), L.size());
    ASSERT_EQ(LU_mtx.second.size(), U.size());

    // Check each element of L and U against the expected values
    for (uint32_t i = 0; i < LU_mtx.first.size(); i++) {
        for (uint32_t j = 0; j < LU_mtx.first[i].size(); j++) {
            ASSERT_NEAR(LU_mtx.first[i][j], L[i][j], TOLERANCE);
            ASSERT_NEAR(LU_mtx.second[i][j], U[i][j], TOLERANCE);
        }
    }
}

TEST(LinSysTest, IsSymmetric) {
    //  symmetric positive-definite matrix
    std::vector<std::vector<double>> symmetric_mat = {{4.0, 1.0, 2.0},
                                                      {1.0, 5.0, 3.0},
                                                      {2.0, 3.0, 6.0}};
    gpmp::linalg::LinSys linSysSymmetric(symmetric_mat);

    EXPECT_TRUE(linSysSymmetric.is_symmetric());

    //  non-symmetric matrix
    std::vector<std::vector<double>> nonSymmetric_mat = {{1.0, 2.0, 3.0},
                                                         {2.0, 4.0, 5.0},
                                                         {3.0, 5.0, 6.0}};
    gpmp::linalg::LinSys linSysNonSymmetric(nonSymmetric_mat);

    EXPECT_FALSE(linSysNonSymmetric.is_symmetric());
}

TEST(LinSysTest, FrobeniusNorm) {
    std::vector<std::vector<double>> test_mat = {{1.0, 2.0, 3.0},
                                                 {4.0, 5.0, 6.0},
                                                 {7.0, 8.0, 9.0}};
    gpmp::linalg::LinSys linSys(test_mat);

    // expected Frobenius norm for the test matrix
    double expected_norm = std::sqrt(1 * 1 + 2 * 2 + 3 * 3 + 4 * 4 + 5 * 5 +
                                     6 * 6 + 7 * 7 + 8 * 8 + 9 * 9);

    EXPECT_DOUBLE_EQ(linSys.frobenius_norm(), expected_norm);
}

TEST(LinSysTest, OneNorm) {
    std::vector<std::vector<double>> testMat = {{1.0, 2.0, 3.0},
                                                {4.0, 5.0, 6.0},
                                                {7.0, 8.0, 9.0}};
    gpmp::linalg::LinSys linSys(testMat);

    // expected 1-norm for the test matrix
    double expectedNorm = 18;

    EXPECT_DOUBLE_EQ(linSys.one_norm(), expectedNorm);
}

TEST(LinSysTest, InfNorm) {
    std::vector<std::vector<double>> testMat = {{1.0, 2.0, 3.0},
                                                {4.0, 5.0, 6.0},
                                                {7.0, 8.0, 9.0}};
    gpmp::linalg::LinSys linSys(testMat);

    double expectedNorm = 24;

    EXPECT_DOUBLE_EQ(linSys.inf_norm(), expectedNorm);
}

TEST(LinSysTest, DiagonallyDominant) {
    // diagonally dominant matrix
    std::vector<std::vector<double>> diagonallyDominantMat = {{4.0, -1.0, 0.0},
                                                              {-1.0, 4.0, -1.0},
                                                              {0.0, -1.0, 3.0}};
    gpmp::linalg::LinSys LinSysA(diagonallyDominantMat);

    EXPECT_TRUE(LinSysA.diagonally_dominant());

    // non-diagonally dominant matrix
    std::vector<std::vector<double>> nonDiagonallyDominantMat = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}};
    gpmp::linalg::LinSys LinSysB(nonDiagonallyDominantMat);

    EXPECT_FALSE(LinSysB.diagonally_dominant());
}

TEST(LinSysTest, IsConsistent) {
    // create a consistent system
    std::vector<std::vector<double>> consistentMat = {{1.0, 2.0, 3.0},
                                                      {4.0, 5.0, 6.0},
                                                      {7.0, 8.0, 9.0}};
    gpmp::linalg::LinSys linSysConsistent(consistentMat);

    EXPECT_TRUE(linSysConsistent.is_consistent());

    // create an inconsistent system
    std::vector<std::vector<double>> inconsistentMat = {{0.0, 0.0, 0.0, 1.0},
                                                        {0.0, 0.0, 0.0, 2.0},
                                                        {0.0, 0.0, 0.0, 3.0}};
    gpmp::linalg::LinSys linSysInconsistent(inconsistentMat);

    // check if the system is inconsistent
    EXPECT_FALSE(linSysInconsistent.is_consistent());
}

TEST(LinSysTest, IsHomogeneous) {
    // create a homogeneous system
    std::vector<std::vector<double>> homogeneousMat = {{1.0, 2.0, 3.0, 0.0},
                                                       {4.0, 5.0, 6.0, 0.0},
                                                       {7.0, 8.0, 9.0, 0.0}};
    gpmp::linalg::LinSys LinSysA(homogeneousMat);

    EXPECT_TRUE(LinSysA.is_homogeneous());

    // create a non-homogeneous system
    std::vector<std::vector<double>> nonHomogeneousMat = {{1.0, 2.0, 3.0, 1.0},
                                                          {4.0, 5.0, 6.0, 2.0},
                                                          {7.0, 8.0, 9.0, 3.0}};
    gpmp::linalg::LinSys LinSysB(nonHomogeneousMat);

    EXPECT_FALSE(LinSysB.is_homogeneous());
}
