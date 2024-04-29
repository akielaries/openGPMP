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
#include <cstdlib>
#include <iostream>
#include <openGPMP/ml/kohonen_net.hpp>

gpmp::ml::KohonenNet::KohonenNet(int in_size, int m_size)
    : input_size(in_size), map_size(m_size) {
    initialize_weights();
}

gpmp::ml::KohonenNet::~KohonenNet() {
}

void gpmp::ml::KohonenNet::initialize_weights() {
    weights.resize(map_size, std::vector<double>(input_size));

    // Initialize weights randomly or using some other strategy
    // For simplicity, we initialize them with random values between 0 and 1
    for (int i = 0; i < map_size; ++i) {
        for (int j = 0; j < input_size; ++j) {
            weights[i][j] = static_cast<double>(rand()) / RAND_MAX;
        }
    }
}

void gpmp::ml::KohonenNet::train(
    const std::vector<std::vector<double>> &inputData,
    int epochs) {
    for (int epoch = 0; epoch < epochs; ++epoch) {
        for (const auto &inputVector : inputData) {
            int bmu = best_matching_unit(inputVector);
            double learningRate = 1.0 - static_cast<double>(epoch) / epochs;
            update_weights(bmu, inputVector, learningRate);
        }
    }
}

int gpmp::ml::KohonenNet::classify(const std::vector<double> &inputVector) {
    return best_matching_unit(inputVector);
}

int gpmp::ml::KohonenNet::best_matching_unit(
    const std::vector<double> &inputVector) {
    int bmu = 0;
    double minDistance = euclidean_distance(inputVector, weights[0]);

    for (int i = 1; i < map_size; ++i) {
        double distance = euclidean_distance(inputVector, weights[i]);
        if (distance < minDistance) {
            minDistance = distance;
            bmu = i;
        }
    }

    return bmu;
}

void gpmp::ml::KohonenNet::update_weights(
    int bmu,
    const std::vector<double> &inputVector,
    double learningRate) {
    for (int i = 0; i < input_size; ++i) {
        double delta = inputVector[i] - weights[bmu][i];
        weights[bmu][i] += learningRate * delta;
    }
}

double
gpmp::ml::KohonenNet::euclidean_distance(const std::vector<double> &vec1,
                                         const std::vector<double> &vec2) {
    double distance = 0.0;
    for (size_t i = 0; i < vec1.size(); ++i) {
        double diff = vec1[i] - vec2[i];
        distance += diff * diff;
    }
    return sqrt(distance);
}
