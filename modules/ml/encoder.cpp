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

#include "../../include/ml/encoder.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

gpmp::ml::AutoEncoder::AutoEncoder(int in_size,
                                   int h_size,
                                   int out_size,
                                   double l_rate)
    : input_size(in_size), hidden_size(h_size), output_size(out_size),
      learning_rate(l_rate) {

    // initialize weights randomly
    weights_input_hidden.resize(input_size, std::vector<double>(hidden_size));
    weights_hidden_output.resize(hidden_size, std::vector<double>(output_size));

    for (int i = 0; i < input_size; ++i) {
        for (int j = 0; j < hidden_size; ++j) {
            // random values between 0 and 1
            weights_input_hidden[i][j] = (rand() % 1000) / 1000.0;
        }
    }
    for (int i = 0; i < hidden_size; ++i) {
        for (int j = 0; j < output_size; ++j) {
            weights_hidden_output[i][j] = (rand() % 1000) / 1000.0;
        }
    }
}

std::vector<double>
gpmp::ml::AutoEncoder::sigmoid(const std::vector<double> &x) {
    std::vector<double> result;
    for (double val : x) {
        result.push_back(1.0 / (1.0 + exp(-val)));
    }
    return result;
}

std::vector<double>
gpmp::ml::AutoEncoder::forward(const std::vector<double> &input) {
    // forward passes
    std::vector<double> hidden(hidden_size);
    std::vector<double> output(output_size);

    // calculate hidden layer values
    for (int i = 0; i < hidden_size; ++i) {
        hidden[i] = 0;
        for (int j = 0; j < input_size; ++j) {
            hidden[i] += input[j] * weights_input_hidden[j][i];
        }
        hidden[i] = sigmoid({hidden[i]})[0];
    }

    // calculate output layer values
    for (int i = 0; i < output_size; ++i) {
        output[i] = 0;
        for (int j = 0; j < hidden_size; ++j) {
            output[i] += hidden[j] * weights_hidden_output[j][i];
        }
        output[i] = sigmoid({output[i]})[0];
    }

    return output;
}

void gpmp::ml::AutoEncoder::train(
    const std::vector<std::vector<double>> &training_data,
    int epochs) {
    for (int epoch = 0; epoch < epochs; ++epoch) {
        for (const auto &input : training_data) {
            // forward pass
            std::vector<double> hidden(hidden_size);
            std::vector<double> output(output_size);

            // calculate hidden layer values
            for (int i = 0; i < hidden_size; ++i) {
                hidden[i] = 0;
                for (int j = 0; j < input_size; ++j) {
                    hidden[i] += input[j] * weights_input_hidden[j][i];
                }
                hidden[i] = sigmoid({hidden[i]})[0];
            }

            // calculate output layer values
            for (int i = 0; i < output_size; ++i) {
                output[i] = 0;
                for (int j = 0; j < hidden_size; ++j) {
                    output[i] += hidden[j] * weights_hidden_output[j][i];
                }
                output[i] = sigmoid({output[i]})[0];
            }

            // backward pass (gradient descent)
            for (int i = 0; i < output_size; ++i) {
                for (int j = 0; j < hidden_size; ++j) {
                    weights_hidden_output[j][i] -=
                        learning_rate * (output[i] - input[i]) * hidden[j];
                }
            }

            for (int i = 0; i < hidden_size; ++i) {
                for (int j = 0; j < input_size; ++j) {
                    double error = 0;
                    for (int k = 0; k < output_size; ++k) {
                        error += (output[k] - input[k]) *
                                 weights_hidden_output[i][k];
                    }
                    weights_input_hidden[j][i] -= learning_rate * error *
                                                  input[j] * (1 - hidden[i]) *
                                                  hidden[i];
                }
            }
        }
    }
}

void gpmp::ml::AutoEncoder::display() {
    std::cout << "Input to Hidden Weights:\n";
    for (int i = 0; i < input_size; ++i) {
        for (int j = 0; j < hidden_size; ++j) {
            std::cout << weights_input_hidden[i][j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nHidden to Output Weights:\n";
    for (int i = 0; i < hidden_size; ++i) {
        for (int j = 0; j < output_size; ++j) {
            std::cout << weights_hidden_output[i][j] << " ";
        }
        std::cout << "\n";
    }
}

gpmp::ml::SparseAutoEncoder::SparseAutoEncoder(int input_size, int hidden_size, int output_size,
                                     double learning_rate, double sparsity_weight, double sparsity_target)
    : AutoEncoder(input_size, hidden_size, output_size, learning_rate),
      sparsity_weight(sparsity_weight), sparsity_target(sparsity_target) {
    // Initialization code specific to SparseAutoEncoder, if any...
}

