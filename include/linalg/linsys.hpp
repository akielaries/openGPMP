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

#ifndef LINSYS_HPP
#define LINSYS_HPP

#include <vector>

namespace gpmp {

namespace linalg {

/**
 * @class LinSys
 * @brief Class for solving linear systems and performing matrix operations
 */
class LinSys {
  public:
    std::vector<std::vector<double>> matrix;
    int numRows;
    int numCols;

    /**
     * @brief Constructor for LinSys class
     * @param mat The augmented matrix [A|B] representing the linear system
     */
    LinSys(const std::vector<std::vector<double>> &mat);

    /**
     * @brief Display the augmented matrix
     */
    void display_mtx() const;

    /**
     * @brief Solve the linear system using Gaussian Elimination
     */
    void solve_gauss();

    /**
     * @brief Calculate the determinant of the matrix
     * @return Determinant of the matrix
     */
    double determinant() const;

    /**
     * @brief Invert the matrix
     */
    void invert_mtx();

    /**
     * @brief Perform LU decomposition of the matrix
     */
    void lu_decomp();

    /**
     * @brief Solve the linear system using LU decomposition
     */
    void solve_lu();

    /**
     * @brief Solve the linear system using Cholesky decomposition
     */
    void solve_cholesky();

    /**
     * @brief Solve the linear system using Jacobi iteration
     * @param maxIterations Maximum number of iterations (default: 100)
     * @param tolerance Convergence tolerance (default: 1e-10)
     */
    void solve_jacobi(int maxIterations = 100, double tolerance = 1e-10);

    /**
     * @brief Check if the matrix is symmetric
     * @return True if the matrix is symmetric, false otherwise
     */
    bool is_symmetric() const;

    /**
     * @brief Calculate the Frobenius norm of the matrix
     * @return The Frobenius norm of the matrix
     */
    double frobenius_norm() const;

    /**
     * @brief Calculate the 1-norm of the matrix
     * @return The 1-norm of the matrix
     */
    double one_norm() const;

    /**
     * @brief Calculate the infinity norm of the matrix
     * @return The infinity norm of the matrix
     */
    double inf_norm() const;

    /**
     * @brief Perform Gram-Schmidt orthogonalization on the matrix
     */
    void gram_schmidt();

    /**
     * @brief Check if the matrix is diagonally dominant
     * @return True if the matrix is diagonally dominant, false otherwise
     */
    bool diagonally_dominant() const;

    /**
     * @brief Check if the linear system is consistent
     * @return True if the system is consistent, false otherwise
     */
    bool is_consistent() const;

    /**
     * @brief Check if the linear system is homogeneous
     * @return True if the system is homogeneous, false otherwise
     */
    bool is_homogeneous() const;
};
} // namespace linalg
} // namespace gpmp

#endif
