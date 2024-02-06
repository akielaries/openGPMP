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

#include "../../include/ml/trainers.hpp"
#include <random>

std::vector<double>
gpmp::ml::Trainers::gradientdesc(const std::vector<std::vector<double>> &X,
                                 const std::vector<double> &y,
                                 double alpha,
                                 int num_iters) {
    int m = X.size();                  // Number of training examples
    int n = X[0].size();               // Number of features
    std::vector<double> theta(n, 0.0); // Initialize parameters

    // Perform gradient descent
    for (int iter = 0; iter < num_iters; iter++) {
        std::vector<double> delta_theta(n,
                                        0.0); // Initialize change in parameters

        // Compute predictions and errors
        for (int i = 0; i < m; i++) {
            double prediction = 0;
            for (int j = 0; j < n; j++) {
                prediction += theta[j] * X[i][j];
            }
            double error = prediction - y[i];

            // Update delta_theta
            for (int j = 0; j < n; j++) {
                delta_theta[j] += error * X[i][j];
            }
        }

        // Update parameters
        for (int j = 0; j < n; j++) {
            theta[j] -= (alpha / m) * delta_theta[j];
        }
    }

    return theta;
}

std::vector<double> gpmp::ml::Trainers::stoch_gradientdesc(
    const std::vector<std::vector<double>> &X,
    const std::vector<double> &y,
    double alpha,
    int num_iters) {
    int m = X.size();                  // Number of training examples
    int n = X[0].size();               // Number of features
    std::vector<double> theta(n, 0.0); // Initialize parameters

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, m - 1);

    for (int iter = 0; iter < num_iters; iter++) {
        int random_index =
            distribution(generator); // Choose a random training example
        double prediction = 0;

        for (int j = 0; j < n; j++) {
            prediction += theta[j] * X[random_index][j];
        }

        double error = prediction - y[random_index];

        for (int j = 0; j < n; j++) {
            theta[j] -= (alpha * error * X[random_index][j]);
        }
    }

    return theta;
}
std::vector<double> gpmp::ml::Trainers::minibatch_gradientdesc(
    const std::vector<std::vector<double>> &X,
    const std::vector<double> &y,
    double alpha,
    int num_iters,
    int batch_size) {
    int m = X.size();                  // Number of training examples
    int n = X[0].size();               // Number of features
    std::vector<double> theta(n, 0.0); // Initialize parameters

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, m - 1);

    for (int iter = 0; iter < num_iters; iter++) {
        // Select random batch indices
        std::vector<int> batch_indices;
        for (int i = 0; i < batch_size; i++) {
            batch_indices.push_back(distribution(generator));
        }

        // Compute gradient for the batch
        std::vector<double> delta_theta(n, 0.0);
        for (int idx : batch_indices) {
            double prediction = 0;
            for (int j = 0; j < n; j++) {
                prediction += theta[j] * X[idx][j];
            }
            double error = prediction - y[idx];

            for (int j = 0; j < n; j++) {
                delta_theta[j] += (error * X[idx][j]);
            }
        }

        // Update parameters using the gradient of the batch
        for (int j = 0; j < n; j++) {
            theta[j] -= (alpha / batch_size) * delta_theta[j];
        }
    }

    return theta;
}
