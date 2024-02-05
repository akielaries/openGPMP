/*************************************************************************
 *
 *  Project
 *                         _____ _____  __  __ _____
 *                        / ____|  __ \|  \/  |  __ \
 *  ___  _ __   ___ _ __ | |  __| |__) | \  / | |__) |
 * / _ \| '_ \ / _ \ '_ \| | |_ |  ___/| |\/| |  ___/
 *| (_) | |_) |  __/ | | | |__| | |    | |  | | |
 * \___/| .__/ \___|_| |_|\_____|_|    |_|  |_|_|
 *      | |
 *      |_|
 *
 * Copyright (C) Akiel Aries, <akiel@akiel.org>, et al.
 *
 * This software is licensed as described in the file LICENSE, which
 * you should have received as part of this distribution. The terms
 * among other details are referenced in the official documentation
 * seen here : https://akielaries.github.io/openGPMP/ along with
 * important files seen in this project.
 *
 * You may opt to use, copy, modify, merge, publish, distribute
 * and/or sell copies of the Software, and permit persons to whom
 * the Software is furnished to do so, under the terms of the
 * LICENSE file. As this is an Open Source effort, all implementations
 * must be of the same methodology.
 *
 *
 *
 * This software is distributed on an AS IS basis, WITHOUT
 * WARRANTY OF ANY KIND, either express or implied.
 *
 ************************************************************************/

#ifndef EIGEN_HPP
#define EIGEN_HPP
#include <vector>

namespace gpmp {

namespace linalg {

/**
 * @brief Class for computing eigenvalues of a matrix
 */
class Eigen {
  private:
    // matrix for eigenvalue computation
    std::vector<std::vector<double>> matrix;
    // size of square matrix
    int size;

  public:
    /**
     * @brief Constructor for the Eigen class
     * @param mat The square matrix for eigenvalue computation
     */
    Eigen(const std::vector<std::vector<double>> &mat);

    /**
     * @brief Perform the power iteration method to find the dominant eigenvalue
     * @param max_iters Maximum number of iterations for power iteration
     * @param tolerance Tolerance for convergence
     * @return The dominant eigenvalue of the matrix
     */
    double power_iter(int max_iters = 100, double tolerance = 1e-10) const;

    /**
     * @brief Calculate all eigenvalues of the matrix using the QR algorithm
     * @param max_iters Maximum number of iterations for QR algorithm
     * @param tolerance Tolerance for convergence
     * @return A vector containing all eigenvalues of the matrix
     */
    std::vector<double> qr_algorithm(int max_iters = 100,
                                     double tolerance = 1e-10) const;

    /**
     * @brief Calculates the sensitivity of the eigenvalues of a matrix to small
     * perturbations
     *
     * This method calculates the sensitivity of each eigenvalue of a matrix to
     * small perturbations
     * The sensitivity is defined as the change in the eigenvalue divided by the
     * amount of perturbation
     *
     * @param perturbation The amount of perturbation to apply to the matrix
     * @return A vector containing the sensitivity of each eigenvalue
     *
     * The size of the returned vector will be the same as the size of the
     * matrix
     */
    std::vector<double> sensitivity(double perturbation) const;
    double determinant() const;

    /**
     * @brief Computes the Schur decomposition of a matrix
     *
     * This method computes the Schur decomposition of a matrix The Schur
     * decomposition
     * is a block triangular decomposition of a matrix, where the diagonal
     * blocks are square and the off-diagonal blocks are zero or upper
     * triangular
     *
     * @param schurMatrix The output matrix to store the Schur decomposition
     * @param tolerance The tolerance for determining if a subdiagonal element
     * is zero
     *
     * The schurMatrix parameter must be pre-allocated with the same dimensions
     * as the matrix object This method modifies the contents of the schurMatrix
     * parameter
     */
    void schur_decomp(std::vector<std::vector<double>> &schurMatrix,
                      double tolerance = 1e-10) const;

    /**
     * @brief Computes the Jordan normal form of a matrix
     *
     * This method computes the Jordan normal form of a matrix The Jordan normal
     * form is
     * a block diagonal matrix, where each block is either a diagonal matrix or
     * a Jordan block
     * A Jordan block is a square matrix with ones on the superdiagonal and the
     * eigenvalue on the diagonal
     *
     * @param tolerance The tolerance for determining if a subdiagonal element
     * is zero
     * @return The Jordan normal form of the matrix
     *
     * The returned matrix will have the same dimensions as the original matrix
     */
    std::vector<std::vector<double>>
    jordan_normal_form(double tolerance = 1e-10) const;
};

} // namespace linalg
} // namespace gpmp

#endif
