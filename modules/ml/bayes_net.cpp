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
#include <openGPMP/ml/bayes_net.hpp>
#include <iostream>

BNN::BNN(int in_size, int h_size, int out_size, double p_variance)
    : input_size(in_size), hidden_size(h_size), output_size(out_size),
      prior_variance(p_variance), rng(std::random_device{}()) {
    // initialize weights and biases with random values
    std::normal_distribution<double> normal_distribution(0.0, 1.0);

    input_to_hidden_weights.resize(hidden_size,
                                   std::vector<double>(input_size));
    for (int i = 0; i < hidden_size; ++i) {
        for (int j = 0; j < input_size; ++j) {
            input_to_hidden_weights[i][j] = normal_distribution(rng);
        }
    }

    hidden_biases.resize(hidden_size);
    for (int i = 0; i < hidden_size; ++i) {
        hidden_biases[i] = normal_distribution(rng);
    }

    hidden_to_output_weights.resize(output_size,
                                    std::vector<double>(hidden_size));
    for (int i = 0; i < output_size; ++i) {
        for (int j = 0; j < hidden_size; ++j) {
            hidden_to_output_weights[i][j] = normal_distribution(rng);
        }
    }

    output_biases.resize(output_size);
    for (int i = 0; i < output_size; ++i) {
        output_biases[i] = normal_distribution(rng);
    }
}

double BNN::activation_function(double x) {
    // Using sigmoid activation function for simplicity
    return 1.0 / (1.0 + std::exp(-x));
}

void BNN::fit(const std::vector<std::vector<double>> &X_train,
              const std::vector<std::vector<double>> &y_train,
              int epochs) {
    const double learning_rate = 0.01;

    for (int epoch = 0; epoch < epochs; ++epoch) {
        update_weights(X_train, y_train, learning_rate);

        // Print loss for monitoring training progress
        if (epoch % 100 == 0) {
            double loss = compute_loss(X_train, y_train);
            std::cout << "Epoch: " << epoch << ", Loss: " << loss << std::endl;
        }
    }
}

std::vector<double> BNN::predict(const std::vector<double> &input_vector) {
    // Forward pass
    std::vector<double> hidden_output(hidden_size);
    for (int i = 0; i < hidden_size; ++i) {
        hidden_output[i] = activation_function(
            std::inner_product(input_vector.begin(),
                               input_vector.end(),
                               input_to_hidden_weights[i].begin(),
                               0.0) +
            hidden_biases[i]);
    }

    std::vector<double> output(output_size);
    for (int i = 0; i < output_size; ++i) {
        output[i] = activation_function(
            std::inner_product(hidden_output.begin(),
                               hidden_output.end(),
                               hidden_to_output_weights[i].begin(),
                               0.0) +
            output_biases[i]);
    }

    return output;
}

double BNN::prior_log_likelihood() {
    // Compute log-likelihood of the prior
    double log_likelihood = 0.0;

    // Prior for input-to-hidden weights
    for (int i = 0; i < hidden_size; ++i) {
        for (int j = 0; j < input_size; ++j) {
            log_likelihood +=
                -0.5 *
                (std::pow(input_to_hidden_weights[i][j], 2) / prior_variance +
                 std::log(2 * M_PI * prior_variance));
        }
    }

    // Prior for hidden biases
    for (int i = 0; i < hidden_size; ++i) {
        log_likelihood +=
            -0.5 * (std::pow(hidden_biases[i], 2) / prior_variance +
                    std::log(2 * M_PI * prior_variance));
    }

    // Prior for hidden-to-output weights
    for (int i = 0; i < output_size; ++i) {
        for (int j = 0; j < hidden_size; ++j) {
            log_likelihood +=
                -0.5 *
                (std::pow(hidden_to_output_weights[i][j], 2) / prior_variance +
                 std::log(2 * M_PI * prior_variance));
        }
    }

    // Prior for output biases
    for (int i = 0; i < output_size; ++i) {
        log_likelihood +=
            -0.5 * (std::pow(output_biases[i], 2) / prior_variance +
                    std::log(2 * M_PI * prior_variance));
    }

    return log_likelihood;
}

double BNN::log_likelihood(const std::vector<std::vector<double>> &X,
                           const std::vector<std::vector<double>> &y) {
    // Compute log-likelihood of the data
    double log_likelihood = 0.0;

    for (size_t i = 0; i < X.size(); ++i) {
        // Forward pass
        std::vector<double> hidden_output(hidden_size);
        for (int j = 0; j < hidden_size; ++j) {
            hidden_output[j] = activation_function(
                std::inner_product(X[i].begin(),
                                   X[i].end(),
                                   input_to_hidden_weights[j].begin(),
                                   0.0) +
                hidden_biases[j]);
        }

        std::vector<double> output(output_size);
        for (int j = 0; j < output_size; ++j) {
            output[j] = activation_function(
                std::inner_product(hidden_output.begin(),
                                   hidden_output.end(),
                                   hidden_to_output_weights[j].begin(),
                                   0.0) +
                output_biases[j]);
        }

        // Log-likelihood for Gaussian noise
        for (int j = 0; j < output_size; ++j) {
            log_likelihood +=
                -0.5 * std::log(2 * M_PI) - 0.5 * std::log(prior_variance) -
                0.5 * std::pow(y[i][j] - output[j], 2) / prior_variance;
        }
    }

    return log_likelihood;
}

double BNN::compute_loss(const std::vector<std::vector<double>> &X,
                         const std::vector<std::vector<double>> &y) {
    // Negative log posterior (loss function)
    return -log_likelihood(X, y) - prior_log_likelihood();
}

void BNN::update_weights(const std::vector<std::vector<double>> &X,
                         const std::vector<std::vector<double>> &y,
                         double learning_rate) {
    // Update weights using stochastic gradient descent
    for (size_t i = 0; i < X.size(); ++i) {
        // Forward pass
        std::vector<double> hidden_output(hidden_size);
        for (int j = 0; j < hidden_size; ++j) {
            hidden_output[j] = activation_function(
                std::inner_product(X[i].begin(),
                                   X[i].end(),
                                   input_to_hidden_weights[j].begin(),
                                   0.0) +
                hidden_biases[j]);
        }

        std::vector<double> output(output_size);
        for (int j = 0; j < output_size; ++j) {
            output[j] = activation_function(
                std::inner_product(hidden_output.begin(),
                                   hidden_output.end(),
                                   hidden_to_output_weights[j].begin(),
                                   0.0) +
                output_biases[j]);
        }

        // Backward pass (stochastic gradient descent)
        for (int j = 0; j < output_size; ++j) {
            // Gradient for output layer
            double output_gradient =
                (y[i][j] - output[j]) * output[j] * (1.0 - output[j]);

            // Update hidden-to-output weights
            for (int k = 0; k < hidden_size; ++k) {
                hidden_to_output_weights[j][k] +=
                    learning_rate * output_gradient * hidden_output[k];
            }

            // Update output biases
            output_biases[j] += learning_rate * output_gradient;
        }

        // Backward pass for hidden layer
        for (int j = 0; j < hidden_size; ++j) {
            // Gradient for hidden layer
            double hidden_gradient = 0.0;
            for (int k = 0; k < output_size; ++k) {
                hidden_gradient += input_to_hidden_weights[k][j] *
                                   (y[i][k] - output[k]) * output[k] *
                                   (1.0 - output[k]);
            }
            hidden_gradient *= hidden_output[j] * (1.0 - hidden_output[j]);

            // Update input-to-hidden weights
            for (int k = 0; k < input_size; ++k) {
                input_to_hidden_weights[j][k] +=
                    learning_rate * hidden_gradient * X[i][k];
            }

            // Update hidden biases
            hidden_biases[j] += learning_rate * hidden_gradient;
        }
    }
}
