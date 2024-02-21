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

#include "../../include/linalg/vector.hpp"
#include <cmath>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <vector>

/************************************************************************
 *
 * Standard/Naive Vector  Operations on vector<>
 *
 ************************************************************************/

// function to compute the cross product of two 3D vectors
void gpmp::linalg::std_cross_product(const std::vector<double> &vec1,
                                     const std::vector<double> &vec2,
                                     std::vector<double> &result) {
    result[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
    result[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
    result[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
}

double gpmp::linalg::std_vector_norm(const std::vector<double> &vec) {
    double norm = 0.0;
    for (double value : vec) {
        norm += value * value;
    }
    return std::sqrt(norm);
}

// function to normalize a vector to have unit length
void gpmp::linalg::std_vector_normalize(const std::vector<double> &vec,
                                        std::vector<double> &result) {
    double norm = gpmp::linalg::std_vector_norm(vec);
    result.resize(vec.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        result[i] = vec[i] / norm;
    }
}

// function to compute the projection of one vector onto another
void gpmp::linalg::std_vector_projection(const std::vector<double> &vec,
                                         const std::vector<double> &onto_vec,
                                         std::vector<double> &result) {
    double dot = std_dot_product(vec, onto_vec);
    double onto_vec_norm_sq = std_dot_product(onto_vec, onto_vec);

    result.resize(onto_vec.size());
    for (size_t i = 0; i < onto_vec.size(); ++i) {
        result[i] = (dot / onto_vec_norm_sq) * onto_vec[i];
    }
}

// function to compute the cross product of two 3D vectors of integers
void gpmp::linalg::std_cross_product(const std::vector<int> &vec1,
                                     const std::vector<int> &vec2,
                                     std::vector<int> &result) {
    result.resize(3);
    result[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
    result[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
    result[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
}

double gpmp::linalg::std_vector_norm(const std::vector<int> &vec) {
    double norm = 0.0;
    for (int value : vec) {
        norm += value * value;
    }
    return std::sqrt(norm);
}

// function to normalize a vector of integers to have unit length
void gpmp::linalg::std_vector_normalize(const std::vector<int> &vec,
                                        std::vector<double> &result) {
    double norm = std_vector_norm(vec);
    result.resize(vec.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        result[i] = static_cast<double>(vec[i]) / norm;
    }
}

// function to compute the projection of one vector of integers onto another
void gpmp::linalg::std_vector_projection(const std::vector<int> &vec,
                                         const std::vector<int> &onto_vec,
                                         std::vector<double> &result) {
    double dot = std_dot_product(vec, onto_vec);
    double onto_vec_norm_sq = std_dot_product(onto_vec, onto_vec);

    result.resize(onto_vec.size());
    for (size_t i = 0; i < onto_vec.size(); ++i) {
        result[i] = (dot / onto_vec_norm_sq) * onto_vec[i];
    }
}
