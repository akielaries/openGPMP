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

#include "../../include/linalg/svd.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>

gpmp::linalg::SVD::SVD(std::vector<std::vector<double>> &matrix) {
    if (matrix.empty() || matrix[0].empty()) {
        throw std::invalid_argument("Error: Matrix for SVD is empty.");
    }

    computeSVD(matrix);
}

std::vector<double> gpmp::linalg::SVD::getSingularValues() const {
    return singularValues_;
}

std::vector<std::vector<double>>
gpmp::linalg::SVD::getLeftSingularVectors() const {
    return leftSingularVectors_;
}

std::vector<std::vector<double>>
gpmp::linalg::SVD::getRightSingularVectors() const {
    return rightSingularVectors_;
}

void gpmp::linalg::SVD::computeSVD(std::vector<std::vector<double>> &matrix) {
    size_t m = matrix.size();
    size_t n = matrix[0].size();

    singularValues_.resize(std::min(m, n));
    leftSingularVectors_ =
        std::vector<std::vector<double>>(m, std::vector<double>(m, 0.0));
    rightSingularVectors_ =
        std::vector<std::vector<double>>(n, std::vector<double>(n, 0.0));

    std::vector<double> superdiagonal(n - 1, 0.0);

    bidiagonalize(const_cast<std::vector<std::vector<double>> &>(matrix),
                  singularValues_,
                  superdiagonal);

    // left/right singular vectors as identity matrices
    for (size_t i = 0; i < m; ++i) {
        leftSingularVectors_[i][i] = 1.0;
    }

    for (size_t i = 0; i < n; ++i) {
        rightSingularVectors_[i][i] = 1.0;
    }
}

void gpmp::linalg::SVD::bidiagonalize(std::vector<std::vector<double>> &matrix,
                                      std::vector<double> &diagonal,
                                      std::vector<double> &superdiagonal) {
    size_t m = matrix.size();
    size_t n = matrix[0].size();

    diagonal.resize(std::min(m, n));
    superdiagonal.resize(std::min(m, n) - 1);

    for (size_t k = 0; k < std::min(m, n); ++k) {
        double alpha = 0.0;
        for (size_t i = k; i < m; ++i) {
            alpha += matrix[i][k] * matrix[i][k];
        }
        alpha = (matrix[k][k] > 0) ? -std::sqrt(alpha) : std::sqrt(alpha);

        double beta = alpha * (alpha - matrix[k][k]);
        diagonal[k] = -alpha;

        // make a copy of the current column of the matrix
        std::vector<double> columnCopy(m - k);
        for (size_t i = k; i < m; ++i) {
            columnCopy[i - k] = matrix[i][k];
        }

        computeHouseholderReflection(columnCopy, superdiagonal, beta);
        applyHouseholder(matrix, superdiagonal, beta, k, k + 1);
    }
}

void gpmp::linalg::SVD::computeHouseholderReflection(
    const std::vector<double> &x,
    std::vector<double> &v,
    double &beta) {
    size_t n = x.size();
    double sigma = 0.0;

    for (size_t i = 1; i < n; ++i) {
        sigma += x[i] * x[i];
    }

    v.resize(n);
    v[0] = 1.0;
    for (size_t i = 1; i < n; ++i) {
        v[i] = x[i] / sigma;
    }

    beta = 2.0 / (sigma + 1.0);
}

void gpmp::linalg::SVD::applyHouseholder(
    std::vector<std::vector<double>> &matrix,
    const std::vector<double> &v,
    double beta,
    size_t fromRow,
    size_t fromCol) {
    size_t m = matrix.size();
    size_t n = matrix[0].size();

    for (size_t i = fromRow; i < m; ++i) {
        double dotProduct = 0.0;
        for (size_t j = fromCol; j < n; ++j) {
            dotProduct += matrix[i][j] * v[j - fromCol];
        }

        dotProduct *= beta;

        for (size_t j = fromCol; j < n; ++j) {
            matrix[i][j] -= dotProduct * v[j - fromCol];
        }
    }
}
