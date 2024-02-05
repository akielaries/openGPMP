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

#include "../../include/linalg/linsys.hpp"
#include <cmath>
#include <iostream>
#include <vector>

gpmp::linalg::LinSys::LinSys(const std::vector<std::vector<double>> &mat)
    : matrix(mat) {
    numRows = matrix.size();
    numCols = matrix[0].size();
}

// display the augmented matrix
void gpmp::linalg::LinSys::display_mtx() const {
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// solve the linear system using Gaussian Elimination
void gpmp::linalg::LinSys::solve_gauss() {
    for (int i = 0; i < numRows - 1; ++i) {
        // perform partial pivot
        int pivotRow = i;
        for (int k = i + 1; k < numRows; ++k) {
            if (std::abs(matrix[k][i]) > std::abs(matrix[pivotRow][i]))
                pivotRow = k;
        }
        std::swap(matrix[i], matrix[pivotRow]);

        // eliminate entries below pivot
        for (int k = i + 1; k < numRows; ++k) {
            double factor = matrix[k][i] / matrix[i][i];
            for (int j = i; j < numCols; ++j) {
                matrix[k][j] -= factor * matrix[i][j];
            }
        }
    }

    // back-substitution
    for (int i = numRows - 1; i >= 0; --i) {
        for (int j = i + 1; j < numCols - 1; ++j) {
            matrix[i][numCols - 1] -= matrix[i][j] * matrix[j][numCols - 1];
        }
        matrix[i][numCols - 1] /= matrix[i][i];
    }
}

// calculate the determinant of the matrix
double gpmp::linalg::LinSys::determinant() const {
    // assuming square matrix
    if (numRows != numCols) {
        std::cerr << "Error: Determinant is undefined for non-square matrices."
                  << std::endl;
        return 0.0;
    }

    std::vector<std::vector<double>> tempMatrix = matrix;
    double det = 1.0;

    for (int i = 0; i < numRows - 1; ++i) {
        for (int k = i + 1; k < numRows; ++k) {
            double factor = tempMatrix[k][i] / tempMatrix[i][i];
            for (int j = i; j < numCols; ++j) {
                tempMatrix[k][j] -= factor * tempMatrix[i][j];
            }
        }
    }

    for (int i = 0; i < numRows; ++i) {
        det *= tempMatrix[i][i];
    }

    return det;
}

// invert the matrix
void gpmp::linalg::LinSys::invert_mtx() {
    // assuming square matrix
    if (numRows != numCols) {
        std::cerr
            << "Error: Matrix inversion is undefined for non-square matrices."
            << std::endl;
        return;
    }

    std::vector<std::vector<double>> identity(
        numRows,
        std::vector<double>(numCols, 0.0));

    // augment the matrix with the identity matrix
    for (int i = 0; i < numRows; ++i) {
        matrix[i].insert(matrix[i].end(),
                         identity[i].begin(),
                         identity[i].end());
    }

    // perform Gaussian elimination
    solve_gauss();

    // separate the inverse matrix
    for (int i = 0; i < numRows; ++i) {
        matrix[i].erase(matrix[i].begin(), matrix[i].begin() + numRows);
    }
}
void gpmp::linalg::LinSys::lu_decomp() {
    for (int i = 0; i < numRows; ++i) {
        for (int j = i + 1; j < numRows; ++j) {
            if (std::abs(matrix[i][i]) < 1e-10) {
                throw std::runtime_error("Error: LU decomposition failed. "
                                         "Diagonal element too small.");
            }
            double factor = matrix[j][i] / matrix[i][i];
            for (int k = i; k < numCols; ++k) {
                matrix[j][k] -= factor * matrix[i][k];
            }
            matrix[j][i] = factor;
        }
    }
}
// solve the linear system using LU decomposition
void gpmp::linalg::LinSys::solve_lu() {
    lu_decomp();

    // forward substitution
    for (int i = 0; i < numRows - 1; ++i) {
        for (int j = i + 1; j < numRows; ++j) {
            matrix[j][numCols - 1] -= matrix[j][i] * matrix[i][numCols - 1];
        }
    }

    // back-substitution
    for (int i = numRows - 1; i >= 0; --i) {
        for (int j = i + 1; j < numCols - 1; ++j) {
            matrix[i][numCols - 1] -= matrix[i][j] * matrix[j][numCols - 1];
        }
        matrix[i][numCols - 1] /= matrix[i][i];
    }
}

void gpmp::linalg::LinSys::solve_cholesky() {
    // assuming symmetric and positive-definite matrix
    if (!is_symmetric()) {
        std::cerr << "Error: Cholesky decomposition is only applicable to"
                     "symmetric positive-definite matrices\n";
    }

    for (int i = 0; i < numRows; ++i) {
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
    for (int i = 0; i < numRows; ++i) {
        double sum = 0.0;
        for (int j = 0; j < i; ++j) {
            sum += matrix[i][j] * matrix[numCols - 1][j];
        }
        matrix[numCols - 1][i] = (matrix[numCols - 1][i] - sum) / matrix[i][i];
    }

    // back-substitution
    for (int i = numRows - 1; i >= 0; --i) {
        double sum = 0.0;
        for (int j = i + 1; j < numCols - 1; ++j) {
            sum += matrix[j][i] * matrix[i][numCols - 1];
        }
        matrix[i][numCols - 1] = (matrix[i][numCols - 1] - sum) / matrix[i][i];
    }
}

// solve the linear system using Jacobi iteration
void gpmp::linalg::LinSys::solve_jacobi(int maxIterations, double tolerance) {
    std::vector<std::vector<double>> x(numRows, std::vector<double>(1, 0.0));
    std::vector<std::vector<double>> xOld = x;

    for (int iter = 0; iter < maxIterations; ++iter) {
        for (int i = 0; i < numRows; ++i) {
            double sum = 0.0;
            for (int j = 0; j < numCols - 1; ++j) {
                if (j != i) {
                    sum += matrix[i][j] * xOld[j][0];
                }
            }
            x[i][0] = (matrix[i][numCols - 1] - sum) / matrix[i][i];
        }

        // check convergence
        double maxDiff = 0.0;
        for (int i = 0; i < numRows; ++i) {
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
    for (int i = 0; i < numRows; ++i) {
        matrix[i][numCols - 1] = x[i][0];
    }
}

// check if the matrix is symmetric and positive-definite
bool gpmp::linalg::LinSys::is_symmetric() const {
    // assuming square matrix
    if (numRows != numCols) {
        return false;
    }

    // check symmetry
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (matrix[i][j] != matrix[j][i]) {
                return false;
            }
        }
    }

    // check positive definiteness
    for (int i = 0; i < numRows; ++i) {
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
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            sum += std::pow(matrix[i][j], 2);
        }
    }
    return std::sqrt(sum);
}

// calculate the 1-norm of the matrix
double gpmp::linalg::LinSys::one_norm() const {
    double maxColSum = 0.0;
    for (int j = 0; j < numCols; ++j) {
        double colSum = 0.0;
        for (int i = 0; i < numRows; ++i) {
            colSum += std::abs(matrix[i][j]);
        }
        maxColSum = std::max(maxColSum, colSum);
    }
    return maxColSum;
}

// calculate the infinity norm of the matrix
double gpmp::linalg::LinSys::inf_norm() const {
    double maxRowSum = 0.0;
    for (int i = 0; i < numRows; ++i) {
        double rowSum = 0.0;
        for (int j = 0; j < numCols; ++j) {
            rowSum += std::abs(matrix[i][j]);
        }
        maxRowSum = std::max(maxRowSum, rowSum);
    }
    return maxRowSum;
}

// perform Gram-Schmidt orthogonalization
void gpmp::linalg::LinSys::gram_schmidt() {
    std::vector<std::vector<double>> orthoBasis(
        numRows,
        std::vector<double>(numCols, 0.0));

    for (int j = 0; j < numCols; ++j) {
        for (int i = 0; i < numRows; ++i) {
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
    for (int i = 0; i < numRows; ++i) {
        double diagonalValue = std::abs(matrix[i][i]);
        double rowSum = 0.0;
        for (int j = 0; j < numCols; ++j) {
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
    for (int i = 0; i < numRows; ++i) {
        bool allZeros = true;
        for (int j = 0; j < numCols - 1; ++j) {
            if (matrix[i][j] != 0.0) {
                allZeros = false;
                break;
            }
        }
        if (allZeros && matrix[i][numCols - 1] != 0.0) {
            return false;
        }
    }
    return true;
}

// check if the system is homogeneous
bool gpmp::linalg::LinSys::is_homogeneous() const {
    for (int i = 0; i < numRows; ++i) {
        if (matrix[i][numCols - 1] != 0.0) {
            return false;
        }
    }
    return true;
}
