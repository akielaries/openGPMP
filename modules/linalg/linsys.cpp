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
#include <cmath>
#include <cstdint>
#include <iostream>
#include <openGPMP/linalg/linsys.hpp>
#include <utility>
#include <vector>

gpmp::linalg::LinSys::LinSys(const std::vector<std::vector<double>> &mat)
    : matrix(mat) {
    num_rows = matrix.size();
    num_cols = matrix[0].size();
}

// display the augmented matrix
void gpmp::linalg::LinSys::display_mtx() const {
    for (int i = 0; i < num_rows; ++i) {
        for (int j = 0; j < num_cols; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void gpmp::linalg::LinSys::display(
    const std::vector<std::vector<double>> &mat) const {
    uint32_t rows = mat.size();
    uint32_t cols = mat[0].size();

    for (uint32_t i = 0; i < rows; ++i) {
        for (uint32_t j = 0; j < cols; ++j) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// solve the linear system using Gaussian Elimination
std::vector<double> gpmp::linalg::LinSys::solve_gauss() {
    // temp matrix because our result is a vector of solutions
    std::vector<std::vector<double>> temp_mtx = matrix;

    for (int i = 0; i < num_rows - 1; ++i) {
        // perform partial pivot
        int pivotRow = i;
        for (int k = i + 1; k < num_rows; ++k) {
            if (std::abs(temp_mtx[k][i]) > std::abs(temp_mtx[pivotRow][i]))
                pivotRow = k;
        }
        std::swap(temp_mtx[i], temp_mtx[pivotRow]);

        // eliminate entries below pivot
        for (int k = i + 1; k < num_rows; ++k) {
            double factor = temp_mtx[k][i] / temp_mtx[i][i];
            for (int j = i; j < num_cols; ++j) {
                temp_mtx[k][j] -= factor * temp_mtx[i][j];
            }
        }
    }

    // back-substitution
    std::vector<double> solutions(num_rows, 0);

    for (int i = num_rows - 1; i >= 0; --i) {
        double sum = 0.0;
        for (int j = i + 1; j < num_cols - 1; ++j) {
            sum += temp_mtx[i][j] * solutions[j];
        }
        solutions[i] = (temp_mtx[i][num_cols - 1] - sum) / temp_mtx[i][i];
    }

    return solutions;
}

// calculate the determinant of the matrix
double gpmp::linalg::LinSys::determinant() const {
    // assuming square matrix
    if (num_rows != num_cols) {
        std::cerr << "Error: Determinant is undefined for non-square matrices."
                  << std::endl;
        return 0.0;
    }

    std::vector<std::vector<double>> temp_mtx = matrix;
    double det = 1.0;

    for (int i = 0; i < num_rows - 1; ++i) {
        for (int k = i + 1; k < num_rows; ++k) {
            double factor = temp_mtx[k][i] / temp_mtx[i][i];
            for (int j = i; j < num_cols; ++j) {
                temp_mtx[k][j] -= factor * temp_mtx[i][j];
            }
        }
    }

    for (int i = 0; i < num_rows; ++i) {
        det *= temp_mtx[i][i];
    }

    return det;
}

// invert the matrix
void gpmp::linalg::LinSys::invert_mtx() {
    // assuming square matrix
    if (num_rows != num_cols) {
        std::cerr
            << "Error: Matrix inversion is undefined for non-square matrices."
            << std::endl;
        return;
    }

    std::vector<std::vector<double>> identity(
        num_rows,
        std::vector<double>(num_cols, 0.0));

    // augment the matrix with the identity matrix
    for (int i = 0; i < num_rows; ++i) {
        matrix[i].insert(matrix[i].end(),
                         identity[i].begin(),
                         identity[i].end());
    }

    // perform Gaussian elimination
    solve_gauss();

    // separate the inverse matrix
    for (int i = 0; i < num_rows; ++i) {
        matrix[i].erase(matrix[i].begin(), matrix[i].begin() + num_rows);
    }
}

std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>>
gpmp::linalg::LinSys::lu_decomp() {
    std::vector<std::vector<double>> L(num_rows,
                                       std::vector<double>(num_cols, 0.0));
    std::vector<std::vector<double>> U(num_rows,
                                       std::vector<double>(num_cols, 0.0));

    for (int i = 0; i < num_rows; ++i) {
        // Set diagonal elements of L to 1
        L[i][i] = 1.0;

        for (int j = i; j < num_cols; ++j) {
            U[i][j] = matrix[i][j];
            for (int k = 0; k < i; ++k) {
                U[i][j] -= L[i][k] * U[k][j];
            }
        }

        for (int j = i + 1; j < num_rows; ++j) {
            L[j][i] = matrix[j][i];
            for (int k = 0; k < i; ++k) {
                L[j][i] -= L[j][k] * U[k][i];
            }
            L[j][i] /= U[i][i];
        }
    }

    return {L, U};
}

// solve the linear system using LU decomposition
void gpmp::linalg::LinSys::solve_lu() {
    lu_decomp();

    // forward substitution
    for (int i = 0; i < num_rows - 1; ++i) {
        for (int j = i + 1; j < num_rows; ++j) {
            matrix[j][num_cols - 1] -= matrix[j][i] * matrix[i][num_cols - 1];
        }
    }

    // back-substitution
    for (int i = num_rows - 1; i >= 0; --i) {
        for (int j = i + 1; j < num_cols - 1; ++j) {
            matrix[i][num_cols - 1] -= matrix[i][j] * matrix[j][num_cols - 1];
        }
        matrix[i][num_cols - 1] /= matrix[i][i];
    }
}

void gpmp::linalg::LinSys::solve_cholesky() {
    // assuming symmetric and positive-definite matrix
    if (!is_symmetric()) {
        std::cerr << "Error: Cholesky decomposition is only applicable to"
                     "symmetric positive-definite matrices\n";
    }

    for (int i = 0; i < num_rows; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (i == j) {
                double sum = 0.0;
                for (int k = 0; k < j; ++k) {
                    sum += std::pow(matrix[j][k], 2);
                }
                matrix[j][j] = std::sqrt(matrix[j][j] - sum);
            }

            else {
                double sum = 0.0;
                for (int k = 0; k < j; ++k) {
                    sum += matrix[i][k] * matrix[j][k];
                }
                matrix[i][j] = (matrix[i][j] - sum) / matrix[j][j];
            }
        }
    }

    // forward substitution
    for (int i = 0; i < num_rows; ++i) {
        double sum = 0.0;
        for (int j = 0; j < i; ++j) {
            sum += matrix[i][j] * matrix[num_cols - 1][j];
        }
        matrix[num_cols - 1][i] =
            (matrix[num_cols - 1][i] - sum) / matrix[i][i];
    }

    // back-substitution
    for (int i = num_rows - 1; i >= 0; --i) {
        double sum = 0.0;
        for (int j = i + 1; j < num_cols - 1; ++j) {
            sum += matrix[j][i] * matrix[i][num_cols - 1];
        }
        matrix[i][num_cols - 1] =
            (matrix[i][num_cols - 1] - sum) / matrix[i][i];
    }
}

// solve the linear system using Jacobi iteration
void gpmp::linalg::LinSys::solve_jacobi(int maxIterations, double tolerance) {
    std::vector<std::vector<double>> x(num_rows, std::vector<double>(1, 0.0));
    std::vector<std::vector<double>> xOld = x;

    for (int iter = 0; iter < maxIterations; ++iter) {
        for (int i = 0; i < num_rows; ++i) {
            double sum = 0.0;
            for (int j = 0; j < num_cols - 1; ++j) {
                if (j != i) {
                    sum += matrix[i][j] * xOld[j][0];
                }
            }
            x[i][0] = (matrix[i][num_cols - 1] - sum) / matrix[i][i];
        }

        // check convergence
        double maxDiff = 0.0;
        for (int i = 0; i < num_rows; ++i) {
            double diff = std::abs(x[i][0] - xOld[i][0]);
            if (diff > maxDiff) {
                maxDiff = diff;
            }
        }

        // converged
        if (maxDiff < tolerance) {
            break;
        }

        xOld = x;
    }

    // copy the solution back to the augmented matrix
    for (int i = 0; i < num_rows; ++i) {
        matrix[i][num_cols - 1] = x[i][0];
    }
}

// check if the matrix is symmetric and positive-definite
bool gpmp::linalg::LinSys::is_symmetric() const {
    // assuming square matrix
    if (num_rows != num_cols) {
        return false;
    }

    // check symmetry
    for (int i = 0; i < num_rows; ++i) {
        for (int j = 0; j < num_cols; ++j) {
            // if (matrix[i][j] != matrix[j][i]) {
            if (fabs(matrix[i][j] - matrix[j][i]) >
                std::numeric_limits<double>::epsilon()) {
                return false;
            }
        }
    }

    // check positive definiteness
    for (int i = 0; i < num_rows; ++i) {
        std::vector<std::vector<double>> submatrix(i + 1,
                                                   std::vector<double>(i + 1));
        for (int j = 0; j <= i; ++j) {
            for (int k = 0; k <= i; ++k) {
                submatrix[j][k] = matrix[j][k];
            }
        }

        double det = LinSys(submatrix).determinant();
        if (det <= 0.0) {
            return false;
        }
    }

    return true;
}

double gpmp::linalg::LinSys::frobenius_norm() const {
    double sum = 0.0;
    for (int i = 0; i < num_rows; ++i) {
        for (int j = 0; j < num_cols; ++j) {
            sum += std::pow(matrix[i][j], 2);
        }
    }
    return std::sqrt(sum);
}

// calculate the 1-norm of the matrix
double gpmp::linalg::LinSys::one_norm() const {
    double maxColSum = 0.0;
    for (int j = 0; j < num_cols; ++j) {
        double colSum = 0.0;
        for (int i = 0; i < num_rows; ++i) {
            colSum += std::abs(matrix[i][j]);
        }
        maxColSum = std::max(maxColSum, colSum);
    }
    return maxColSum;
}

// calculate the infinity norm of the matrix
double gpmp::linalg::LinSys::inf_norm() const {
    double maxRowSum = 0.0;
    for (int i = 0; i < num_rows; ++i) {
        double rowSum = 0.0;
        for (int j = 0; j < num_cols; ++j) {
            rowSum += std::abs(matrix[i][j]);
        }
        maxRowSum = std::max(maxRowSum, rowSum);
    }
    return maxRowSum;
}

// perform Gram-Schmidt orthogonalization
void gpmp::linalg::LinSys::gram_schmidt() {
    std::vector<std::vector<double>> orthoBasis(
        num_rows,
        std::vector<double>(num_cols, 0.0));

    for (int j = 0; j < num_cols; ++j) {
        for (int i = 0; i < num_rows; ++i) {
            double projection = 0.0;
            for (int k = 0; k < i; ++k) {
                projection += (matrix[i][j] * orthoBasis[k][j]) /
                              (orthoBasis[k][j] * orthoBasis[k][j]);
            }
            orthoBasis[i][j] = matrix[i][j] - projection;
        }
    }

    // Replace the matrix with the orthogonalized basis
    matrix = orthoBasis;
}

// check if the matrix is diagonally dominant
bool gpmp::linalg::LinSys::diagonally_dominant() const {
    for (int i = 0; i < num_rows; ++i) {
        double diagonalValue = std::abs(matrix[i][i]);
        double rowSum = 0.0;
        for (int j = 0; j < num_cols; ++j) {
            if (j != i) {
                rowSum += std::abs(matrix[i][j]);
            }
        }
        if (diagonalValue <= rowSum) {
            return false;
        }
    }
    return true;
}

// check if the system is consistent
bool gpmp::linalg::LinSys::is_consistent() const {
    for (int i = 0; i < num_rows; ++i) {
        bool allZeros = true;
        for (int j = 0; j < num_cols - 1; ++j) {
            if (fabs(matrix[i][j]) > std::numeric_limits<double>::epsilon()) {

                allZeros = false;
                break;
            }
        }
        if (allZeros && fabs(matrix[i][num_cols - 1]) >
                            std::numeric_limits<double>::epsilon()) {
            return false;
        }
    }
    return true;
}

// check if the system is homogeneous
bool gpmp::linalg::LinSys::is_homogeneous() const {
    for (int i = 0; i < num_rows; ++i) {
        if (fabs(matrix[i][num_cols - 1]) >
            std::numeric_limits<double>::epsilon()) {
            return false;
        }
    }
    return true;
}
