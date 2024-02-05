#include "../../include/linalg/eigen.hpp"

#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

gpmp::linalg::Eigen::Eigen(const std::vector<std::vector<double>> &mat)
    : matrix(mat), size(mat.size()) {
    // Check if the matrix is square
    if (size != mat[0].size()) {
        throw std::invalid_argument(
            "Error: Eigenvalue computation requires a square matrix.");
    }
}

double gpmp::linalg::Eigen::power_iter(int max_iters, double tolerance) const {
    // initial guess
    std::vector<double> x(size, 1.0);
    std::vector<double> y(size);

    for (int iter = 0; iter < max_iters; ++iter) {
        // perform matrix-vector multiplication: y = A * x
        for (int i = 0; i < size; ++i) {
            y[i] = 0.0;
            for (int j = 0; j < size; ++j) {
                y[i] += matrix[i][j] * x[j];
            }
        }

        // find the maximum element in y
        double max_element = 0.0;
        for (int i = 0; i < size; ++i) {
            max_element = std::max(max_element, std::abs(y[i]));
        }

        // normalize y
        for (int i = 0; i < size; ++i) {
            y[i] /= max_element;
        }

        // check for convergence
        double error = 0.0;
        for (int i = 0; i < size; ++i) {
            error += std::abs(y[i] - x[i]);
        }

        if (error < tolerance) {
            // eigenvalue found
            return max_element;
        }

        x = y;
    }

    std::cerr << "Warning: Power iteration did not converge within the"
                 "specified iterations\n";
    // not converged
    return 0.0;
}

std::vector<double> gpmp::linalg::Eigen::qr_algorithm(int max_iters,
                                                      double tolerance) const {
    // initialize a copy of the matrix to avoid modifying the original
    std::vector<std::vector<double>> hessenberg_mtx = matrix;

    // QR Iteration
    for (int iter = 0; iter < max_iters; ++iter) {
        // QR decomposition of the Hessenberg matrix
        for (int i = 0; i < size - 1; ++i) {
            // perform Givens rotation to introduce zeros below the subdiagonal
            double a = hessenberg_mtx[i][i];
            double b = hessenberg_mtx[i + 1][i];
            double r = std::hypot(a, b);
            double c = a / r;
            double s = b / r;

            // apply Givens rotation to the submatrix
            for (int j = 0; j < size; ++j) {
                double temp1 =
                    c * hessenberg_mtx[i][j] + s * hessenberg_mtx[i + 1][j];
                double temp2 =
                    -s * hessenberg_mtx[i][j] + c * hessenberg_mtx[i + 1][j];
                hessenberg_mtx[i][j] = temp1;
                hessenberg_mtx[i + 1][j] = temp2;
            }
        }

        // check for convergence (off-diagonal elements close to zero)
        double offDiagonalSum = 0.0;
        for (int i = 2; i < size; ++i) {
            offDiagonalSum += std::abs(hessenberg_mtx[i][i - 1]);
        }

        if (offDiagonalSum < tolerance) {
            // extract eigenvalues from the diagonal of the Hessenberg matrix
            std::vector<double> eigenvalues;
            for (int i = 0; i < size; ++i) {
                eigenvalues.push_back(hessenberg_mtx[i][i]);
            }

            return eigenvalues;
        }
    }

    std::cerr << "Warning: QR iteration did not converge within the "
                 "specified iterations\n";
    // empty vector if not converged
    return std::vector<double>();
}

double gpmp::linalg::Eigen::determinant() const {
    // compute the determinant as the product of eigenvalues
    std::vector<double> eigenvalues = qr_algorithm();
    double determinant = std::accumulate(eigenvalues.begin(),
                                         eigenvalues.end(),
                                         1.0,
                                         std::multiplies<double>());
    return determinant;
}

std::vector<double>
gpmp::linalg::Eigen::sensitivity(double perturbation) const {
    std::vector<double> originalEigenvalues = qr_algorithm();

    std::vector<double> perturbedEigenvalues;
    for (int i = 0; i < size; ++i) {
        // perturb the matrix
        std::vector<std::vector<double>> perturbedMatrix = matrix;
        perturbedMatrix[i][i] += perturbation;

        // calculate eigenvalues of perturbed matrix
        std::vector<double> perturbedVals =
            Eigen(perturbedMatrix).qr_algorithm();
        perturbedEigenvalues.push_back(perturbedVals[i]);
    }

    // calculate sensitivity: (perturbed eigenvalue - original eigenvalue) /
    // perturbation
    std::vector<double> sensitivity;
    for (int i = 0; i < size; ++i) {
        double sens =
            (perturbedEigenvalues[i] - originalEigenvalues[i]) / perturbation;
        sensitivity.push_back(sens);
    }

    return sensitivity;
}

void gpmp::linalg::Eigen::schur_decomp(
    std::vector<std::vector<double>> &schurMatrix,
    double tolerance) const {
    // Hessenberg matrix is already calculated in QR iteration
    schurMatrix = matrix;

    for (int i = size - 1; i > 0; --i) {
        // check for small subdiagonal elements to introduce a zero
        if (std::abs(schurMatrix[i][i - 1]) < tolerance) {
            schurMatrix[i][i - 1] = 0.0;
        } else {
            // Apply Givens rotation to introduce a zero below the subdiagonal
            double a = schurMatrix[i - 1][i - 1];
            double b = schurMatrix[i][i - 1];
            double r = std::hypot(a, b);
            double c = a / r;
            double s = b / r;

            for (int j = 0; j < size; ++j) {
                double temp1 =
                    c * schurMatrix[i - 1][j] + s * schurMatrix[i][j];
                double temp2 =
                    -s * schurMatrix[i - 1][j] + c * schurMatrix[i][j];
                schurMatrix[i - 1][j] = temp1;
                schurMatrix[i][j] = temp2;
            }
        }
    }
}

std::vector<std::vector<double>>
gpmp::linalg::Eigen::jordan_normal_form(double tolerance) const {
    std::vector<std::vector<double>> jordanMatrix(
        size,
        std::vector<double>(size, 0.0));
    std::vector<double> eigenvalues = qr_algorithm();

    for (int i = 0; i < size; ++i) {
        jordanMatrix[i][i] = eigenvalues[i];

        // find the size of the Jordan block
        int jordanBlockSize = 1;
        while (i + jordanBlockSize < size &&
               std::abs(matrix[i + jordanBlockSize][i]) < tolerance) {
            ++jordanBlockSize;
        }

        // fill the Jordan block
        for (int j = 1; j < jordanBlockSize; ++j) {
            jordanMatrix[i + j][i + j - 1] = 1.0;
        }
    }

    return jordanMatrix;
}
