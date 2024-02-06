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

#include "../../include/ml/svc.hpp"
#include <cmath>
#include <iostream>
#include <numeric>

gpmp::ml::SVC::SVC(double C_, double l_rate, int max_iters, double tol)
    : C(C_), learning_rate(l_rate), max_iterations(max_iters), tolerance(tol) {
}

void gpmp::ml::SVC::fit(const std::vector<std::vector<double>> &X_train,
                        const std::vector<int> &y_train) {
    // Initialize weights and bias
    weights.resize(X_train[0].size(), 0.0);
    bias = 0.0;

    // Stochastic Gradient Descent
    for (int iter = 0; iter < max_iterations; ++iter) {
        update_weights(X_train, y_train);

        // Check convergence
        double loss = compute_loss(X_train, y_train);
        if (loss < tolerance) {
            break;
        }
    }
}

std::vector<int>
gpmp::ml::SVC::predict(const std::vector<std::vector<double>> &X_test) {
    std::vector<int> predictions;
    for (const auto &instance : X_test) {
        double score = 0.0;
        for (size_t i = 0; i < instance.size(); ++i) {
            score += instance[i] * weights[i];
        }
        score += bias;
        int prediction = (score >= 0) ? 1 : -1;
        predictions.push_back(prediction);
    }
    return predictions;
}

double gpmp::ml::SVC::hinge_loss(double prediction, int label) {
    return fmax(0, 1 - label * prediction);
}

double gpmp::ml::SVC::compute_loss(const std::vector<std::vector<double>> &X,
                                   const std::vector<int> &y) {
    double loss = 0.0;
    for (size_t i = 0; i < X.size(); ++i) {
        double prediction = 0.0;
        for (size_t j = 0; j < X[i].size(); ++j) {
            prediction += X[i][j] * weights[j];
        }
        prediction += bias;
        loss += hinge_loss(prediction, y[i]);
    }
    // Add L2 regularization
    for (double weight : weights) {
        loss += 0.5 * C * weight * weight;
    }
    return loss / X.size();
}

void gpmp::ml::SVC::update_weights(const std::vector<std::vector<double>> &X,
                                   const std::vector<int> &y) {
    for (size_t i = 0; i < X.size(); ++i) {
        double prediction = 0.0;
        for (size_t j = 0; j < X[i].size(); ++j) {
            prediction += X[i][j] * weights[j];
        }
        prediction += bias;
        double loss_grad = -y[i] * (1 - prediction);
        if (loss_grad > 0) {
            // Update weights
            for (size_t j = 0; j < X[i].size(); ++j) {
                weights[j] -= learning_rate * (C * weights[j] - y[i] * X[i][j]);
            }
            // Update bias
            bias -= learning_rate * y[i];
        }
    }
}

std::vector<double>
gpmp::ml::SVC::predict_proba(const std::vector<std::vector<double>> &X_test) {
    std::vector<double> probabilities;
    for (const auto &instance : X_test) {
        double score = 0.0;
        for (size_t i = 0; i < instance.size(); ++i) {
            score += instance[i] * weights[i];
        }
        score += bias;
        double prob = sigmoid(score);
        probabilities.push_back(prob);
    }
    return probabilities;
}

double gpmp::ml::SVC::score(const std::vector<std::vector<double>> &X_test,
                            const std::vector<int> &y_test) {
    std::vector<int> predictions = predict(X_test);
    return accuracy(predictions, y_test);
}

void gpmp::ml::SVC::set_kernel(const std::string &k_type) {
    this->kernel_type = k_type;
}

void gpmp::ml::SVC::set_kernel_parameters(double k_param) {
    this->kernel_param = k_param;
}

void gpmp::ml::SVC::set_random_state(int seed) {
    this->random_state = seed;
}

void gpmp::ml::SVC::set_verbose(bool vbose) {
    this->verbose = vbose;
}

void gpmp::ml::SVC::set_penalty(const std::string &p_type) {
    this->penalty_type = p_type;
}

double gpmp::ml::SVC::cross_val_score(const std::vector<std::vector<double>> &X,
                                      const std::vector<int> &y,
                                      int cv) {
    std::vector<int> fold_sizes = k_fold_indices(X.size(), cv);
    double avg_score = 0.0;
    for (int i = 0; i < cv; ++i) {
        std::vector<std::vector<double>> X_train, X_valid;
        std::vector<int> y_train, y_valid;
        int start = 0;
        for (int j = 0; j < cv; ++j) {
            if (j != i) {
                int end = start + fold_sizes[j];
                for (int k = start; k < end; ++k) {
                    X_train.push_back(X[k]);
                    y_train.push_back(y[k]);
                }
            } else {
                int end = start + fold_sizes[j];
                for (int k = start; k < end; ++k) {
                    X_valid.push_back(X[k]);
                    y_valid.push_back(y[k]);
                }
            }
            start += fold_sizes[j];
        }
        fit(X_train, y_train);
        double score_val = score(X_valid, y_valid);
        if (verbose) {
            std::cout << "Cross-validation fold " << i + 1
                      << " accuracy: " << score_val << std::endl;
        }
        avg_score += score_val;
    }
    return avg_score / cv;
}

std::vector<double>
gpmp::ml::SVC::grid_search(const std::vector<std::vector<double>> &X,
                           const std::vector<int> &y,
                           const std::vector<double> &C_values,
                           const std::vector<double> &kernel_params,
                           int cv) {
    std::vector<double> best_params;
    double best_score = 0.0;
    for (double val : C_values) {
        for (double param : kernel_params) {
            set_kernel_parameters(param);
            set_penalty("l2");  // Default penalty type
            set_verbose(false); // Suppress verbose output
            double score = cross_val_score(X, y, cv);
            if (score > best_score) {
                best_score = score;
                best_params = {val, param};
            }
        }
    }
    return best_params;
}

double gpmp::ml::SVC::kernel(const std::vector<double> &x1,
                             const std::vector<double> &x2) {
    if (kernel_type == "linear") {
        return dot_product(x1, x2);
    } else {
        // Default to linear kernel if unknown kernel type
        return dot_product(x1, x2);
    }
}

double gpmp::ml::SVC::dot_product(const std::vector<double> &x1,
                                  const std::vector<double> &x2) {
    double result = 0.0;
    for (size_t i = 0; i < x1.size(); ++i) {
        result += x1[i] * x2[i];
    }
    return result;
}

double gpmp::ml::SVC::sigmoid(double z) {
    return 1.0 / (1.0 + exp(-z));
}

std::vector<int> gpmp::ml::SVC::k_fold_indices(int num_instances, int k) {
    std::vector<int> fold_sizes(k, num_instances / k);
    int remainder = num_instances % k;
    for (int i = 0; i < remainder; ++i) {
        fold_sizes[i]++;
    }
    return fold_sizes;
}

double gpmp::ml::SVC::accuracy(const std::vector<int> &predictions,
                               const std::vector<int> &labels) {
    int correct = 0;
    for (size_t i = 0; i < predictions.size(); ++i) {
        if (predictions[i] == labels[i]) {
            correct++;
        }
    }
    return static_cast<double>(correct) / predictions.size();
}
