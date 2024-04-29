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
#include <openGPMP/linalg/tensor.hpp>
#include <stdexcept>

// Constructors

gpmp::linalg::Tensor::Tensor() : data_({{{}}}), dimensions_{0, 0, 0} {
}

gpmp::linalg::Tensor::Tensor(const std::vector<size_t> &dimensions) {
    if (dimensions.empty()) {
        throw std::invalid_argument("Error: Tensor dimensions are empty.");
    }

    // Assign values to dimensions_
    for (size_t i = 0; i < 3; ++i) {
        dimensions_[i] = dimensions[i];
    }

    size_t totalSize = 1;
    for (size_t dim : dimensions) {
        totalSize *= dim;
    }
    data_ = std::vector<std::vector<std::vector<double>>>(
        dimensions_[0],
        std::vector<std::vector<double>>(
            dimensions_[1],
            std::vector<double>(dimensions_[2], 0.0)));
}

gpmp::linalg::Tensor::Tensor(
    const std::vector<std::vector<std::vector<double>>> &data)
    : data_(data) {
    if (data.empty() || data[0].empty()) {
        throw std::invalid_argument("Error: Tensor data is empty.");
    }

    dimensions_[0] = data.size();
    dimensions_[1] = data[0].size();
    dimensions_[2] = data[0][0].size();
}

gpmp::linalg::Tensor
gpmp::linalg::Tensor::add(const gpmp::linalg::Tensor &other) const {
    if (dimensions_[0] != other.dimensions_[0] ||
        dimensions_[1] != other.dimensions_[1] ||
        dimensions_[2] != other.dimensions_[2]) {
        throw std::invalid_argument(
            "Error: Tensor dimensions do not match for addition.");
    }

    gpmp::linalg::Tensor result;
    result.data_ = data_;

    for (size_t i = 0; i < dimensions_[0]; ++i) {
        for (size_t j = 0; j < dimensions_[1]; ++j) {
            for (size_t k = 0; k < dimensions_[2]; ++k) {
                result.data_[i][j][k] += other.data_[i][j][k];
            }
        }
    }

    return result;
}

gpmp::linalg::Tensor gpmp::linalg::Tensor::multiply(double scalar) const {
    gpmp::linalg::Tensor result;
    result.data_ = data_;

    for (size_t i = 0; i < dimensions_[0]; ++i) {
        for (size_t j = 0; j < dimensions_[1]; ++j) {
            for (size_t k = 0; k < dimensions_[2]; ++k) {
                result.data_[i][j][k] *= scalar;
            }
        }
    }

    return result;
}

gpmp::linalg::Tensor gpmp::linalg::Tensor::multiply(const Tensor &other) const {
    if (dimensions_[2] != other.dimensions_[1]) {
        throw std::invalid_argument(
            "Error: Tensor dimensions do not match for multiplication.");
    }

    gpmp::linalg::Tensor result;
    result.dimensions_[0] = dimensions_[0];
    result.dimensions_[1] = dimensions_[1];
    result.dimensions_[2] = other.dimensions_[2];

    result.data_ = std::vector<std::vector<std::vector<double>>>(
        dimensions_[0],
        std::vector<std::vector<double>>(
            dimensions_[1],
            std::vector<double>(other.dimensions_[2], 0.0)));

    for (size_t i = 0; i < dimensions_[0]; ++i) {
        for (size_t j = 0; j < dimensions_[1]; ++j) {
            for (size_t k = 0; k < other.dimensions_[2]; ++k) {
                for (size_t l = 0; l < dimensions_[2]; ++l) {
                    result.data_[i][j][k] +=
                        data_[i][j][l] * other.data_[l][j][k];
                }
            }
        }
    }

    return result;
}

double gpmp::linalg::Tensor::get(const std::vector<size_t> &indices) const {
    if (indices.size() != 3) {
        throw std::out_of_range(
            "Error: Invalid number of indices for tensor access.");
    }

    for (size_t i = 0; i < 3; ++i) {
        if (indices[i] >= dimensions_[i]) {
            throw std::out_of_range(
                "Error: Index out of bounds for tensor access.");
        }
    }

    return data_[indices[0]][indices[1]][indices[2]];
}

void gpmp::linalg::Tensor::set(const std::vector<size_t> &indices,
                               double value) {
    if (indices.size() != 3) {
        throw std::out_of_range(
            "Error: Invalid number of indices for tensor access.");
    }

    for (size_t i = 0; i < 3; ++i) {
        if (indices[i] >= dimensions_[i]) {
            throw std::out_of_range(
                "Error: Index out of bounds for tensor access.");
        }
    }

    data_[indices[0]][indices[1]][indices[2]] = value;
}

void gpmp::linalg::Tensor::display() const {
    for (size_t i = 0; i < dimensions_[0]; ++i) {
        for (size_t j = 0; j < dimensions_[1]; ++j) {
            for (size_t k = 0; k < dimensions_[2]; ++k) {
                std::cout << data_[i][j][k] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}
