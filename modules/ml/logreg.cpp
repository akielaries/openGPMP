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

#include "../../include/ml/logreg.hpp"
#include <algorithm>
#include <cmath>
#include <numeric>
#include <stdexcept>
#include <vector>

gpmp::ml::LogReg::LogReg(double l_rate, int num_iters, double lda)
    : learning_rate(l_rate), num_iterations(num_iters), lambda(lda) {
}

gpmp::ml::LogReg::~LogReg() {
}

void gpmp::ml::LogReg::train(const std::vector<std::vector<double>> &X_train,
                             const std::vector<int> &y_train) {
    // Initialize weights to zeros
    weights.assign(X_train[0].size() + 1, 0.0);

    for (int iter = 0; iter < num_iterations; ++iter) {
        std::vector<double> gradient(X_train[0].size() + 1, 0.0);

        for (size_t i = 0; i < X_train.size(); ++i) {
            // Add bias term to input
            std::vector<double> input = {1.0};
            input.insert(input.end(), X_train[i].begin(), X_train[i].end());

            // Compute the predicted value
            double predicted = sigmoid(std::inner_product(input.begin(),
                                                          input.end(),
                                                          weights.begin(),
                                                          0.0));

            // Compute gradient for each weight
            for (size_t j = 0; j < gradient.size(); ++j) {
                gradient[j] += (predicted - y_train[i]) * input[j];
            }
        }

        // Update weights using gradient descent
        for (size_t j = 0; j < weights.size(); ++j) {
            weights[j] -= learning_rate *
                          (gradient[j] / X_train.size() + lambda * weights[j]);
        }
    }
}

std::vector<double>
gpmp::ml::LogReg::predict(const std::vector<std::vector<double>> &X_test) {
    std::vector<double> predictions;
    for (size_t i = 0; i < X_test.size(); ++i) {
        // Add bias term to input
        std::vector<double> input = {1.0};
        input.insert(input.end(), X_test[i].begin(), X_test[i].end());

        // Compute the predicted value
        double predicted = sigmoid(std::inner_product(input.begin(),
                                                      input.end(),
                                                      weights.begin(),
                                                      0.0));
        predictions.push_back(predicted);
    }
    return predictions;
}

double
gpmp::ml::LogReg::accuracy(const std::vector<std::vector<double>> &X_test,
                           const std::vector<int> &y_test) {
    std::vector<double> predictions = predict(X_test);
    int correct = 0;
    for (size_t i = 0; i < predictions.size(); ++i) {
        if ((predictions[i] >= 0.5 && y_test[i] == 1) ||
            (predictions[i] < 0.5 && y_test[i] == 0)) {
            correct++;
        }
    }
    return static_cast<double>(correct) / y_test.size();
}

double gpmp::ml::LogReg::sigmoid(double z) {
    return 1.0 / (1.0 + exp(-z));
}

void gpmp::ml::LogReg::feature_scaling(std::vector<std::vector<double>> &X) {
    if (X.empty()) {
        throw std::invalid_argument("Input feature matrix is empty.");
    }

    size_t num_features = X[0].size();
    for (size_t j = 0; j < num_features; ++j) {
        double min_val = X[0][j], max_val = X[0][j];
        for (size_t i = 1; i < X.size(); ++i) {
            if (X[i][j] < min_val) {
                min_val = X[i][j];
            }
            if (X[i][j] > max_val) {
                max_val = X[i][j];
            }
        }

        if (fabs(min_val - max_val) < std::numeric_limits<double>::epsilon()) {
            continue; // Skip if all values are the same
        }

        double range = max_val - min_val;
        for (size_t i = 0; i < X.size(); ++i) {
            X[i][j] = (X[i][j] - min_val) / range;
        }
    }
}

double
gpmp::ml::LogReg::cost_function(const std::vector<std::vector<double>> &X,
                                const std::vector<int> &y) {
    double cost = 0.0;
    for (size_t i = 0; i < X.size(); ++i) {
        // Add bias term to input
        std::vector<double> input = {1.0};
        input.insert(input.end(), X[i].begin(), X[i].end());

        double predicted = sigmoid(std::inner_product(input.begin(),
                                                      input.end(),
                                                      weights.begin(),
                                                      0.0));
        cost += -y[i] * log(predicted) - (1 - y[i]) * log(1 - predicted);
    }
    cost /= X.size();
    return cost;
}

std::vector<int>
gpmp::ml::LogReg::classify(const std::vector<std::vector<double>> &X) {
    std::vector<int> classifications;
    for (size_t i = 0; i < X.size(); ++i) {
        // Add bias term to input
        std::vector<double> input = {1.0};
        input.insert(input.end(), X[i].begin(), X[i].end());

        // Compute the predicted value
        double predicted = sigmoid(std::inner_product(input.begin(),
                                                      input.end(),
                                                      weights.begin(),
                                                      0.0));
        int classification = predicted >= 0.5 ? 1 : 0;
        classifications.push_back(classification);
    }
    return classifications;
}
