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
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

void gpmp::ml::AutoEncoder::save(const std::string &filename) const {
    std::ofstream file(filename, std::ios::out | std::ios::binary);

    if (file.is_open()) {
        file.write(reinterpret_cast<const char *>(&weights_input_hidden[0][0]),
                   weights_input_hidden.size() *
                       weights_input_hidden[0].size() * sizeof(double));
        file.write(reinterpret_cast<const char *>(&weights_hidden_output[0][0]),
                   weights_hidden_output.size() *
                       weights_hidden_output[0].size() * sizeof(double));

        file.close();
        std::cout << "Model saved successfully." << std::endl;
    } else {
        std::cerr << "Unable to open the file for saving." << std::endl;
    }
}

void gpmp::ml::AutoEncoder::load(const std::string &filename) {
    std::ifstream file(filename, std::ios::in | std::ios::binary);

    if (file.is_open()) {
        file.read(reinterpret_cast<char *>(&weights_input_hidden[0][0]),
                  weights_input_hidden.size() * weights_input_hidden[0].size() *
                      sizeof(double));
        file.read(reinterpret_cast<char *>(&weights_hidden_output[0][0]),
                  weights_hidden_output.size() *
                      weights_hidden_output[0].size() * sizeof(double));

        file.close();
        std::cout << "Model loaded successfully." << std::endl;
    } else {
        std::cerr << "Unable to open the file for loading." << std::endl;
    }
}

void gpmp::ml::AutoEncoder::lrate_set(double initial_rate) {
    learning_rate = initial_rate;
}

void gpmp::ml::AutoEncoder::lrate_update(int epoch) {
    // reduce the learning rate by half every N epochs
    const int decay_interval = 10;
    if (epoch % decay_interval == 0) {
        learning_rate /= 2.0;
        std::cout << "Learning rate updated to: " << learning_rate
                  << " at epoch " << epoch << std::endl;
    }
    // TODO?
}

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

gpmp::ml::SparseAutoEncoder::SparseAutoEncoder(int in_size,
                                               int h_size,
                                               int out_size,
                                               double l_rate,
                                               double s_weight,
                                               double s_target)
    : AutoEncoder(in_size, h_size, out_size, l_rate), sparsity_weight(s_weight),
      sparsity_target(s_target) {
}

void gpmp::ml::SparseAutoEncoder::train(
    const std::vector<std::vector<double>> &training_data,
    int epochs) {

    const double SPARSITY_TARGET_DECAY = 0.1;

    for (int epoch = 0; epoch < epochs; ++epoch) {
        for (const auto &current_input : training_data) {
            // forward pass
            std::vector<double> hidden = forward(current_input);

            // backward pass (gradient descent)
            for (int i = 0; i < output_size; ++i) {
                for (int j = 0; j < hidden_size; ++j) {
                    weights_hidden_output[j][i] -=
                        learning_rate * (hidden[i] - current_input[i]) *
                        hidden[j];
                }
            }

            for (int i = 0; i < hidden_size; ++i) {
                for (int j = 0; j < input_size; ++j) {
                    double error = 0;
                    for (int k = 0; k < output_size; ++k) {
                        error += (hidden[k] - current_input[k]) *
                                 weights_hidden_output[i][k];
                    }

                    double sparsity_term =
                        sparsity_weight * (sparsity_target - hidden[i]);

                    weights_input_hidden[j][i] -=
                        learning_rate * (error + sparsity_term) *
                        current_input[j] * (1 - hidden[i]) * hidden[i];
                }
            }

            for (int i = 0; i < hidden_size; ++i) {
                double average_activation = 0.0;
                for (const auto &input : training_data) {
                    std::vector<double> current_hidden = forward(input);
                    average_activation += current_hidden[i];
                }
                average_activation /= training_data.size();
                sparsity_target =
                    (1.0 - SPARSITY_TARGET_DECAY) * sparsity_target +
                    SPARSITY_TARGET_DECAY * average_activation;
            }
        }
    }
}

gpmp::ml::DenoisingAutoEncoder::DenoisingAutoEncoder(int in_size,
                                                     int h_size,
                                                     int out_size,
                                                     double l_rate,
                                                     double c_level)
    : AutoEncoder(in_size, h_size, out_size, l_rate),
      corruption_level(c_level) {
}

void gpmp::ml::DenoisingAutoEncoder::train(
    const std::vector<std::vector<double>> &training_data,
    int epochs) {
    std::srand(std::time(0));

    for (int epoch = 0; epoch < epochs; ++epoch) {
        for (const auto &input : training_data) {
            // add noise to the input data
            std::vector<double> noisy_input = input;
            for (double &val : noisy_input) {
                if ((std::rand() / (RAND_MAX + 1.0)) < corruption_level) {
                    // set to zero with probability corruption_level
                    val = 0.0;
                }
            }

            // forward pass
            std::vector<double> hidden = forward(noisy_input);

            // backward pass (gradient descent)
            for (int i = 0; i < output_size; ++i) {
                for (int j = 0; j < hidden_size; ++j) {
                    weights_hidden_output[j][i] -=
                        learning_rate * (hidden[i] - input[i]) * hidden[j];
                }
            }

            for (int i = 0; i < hidden_size; ++i) {
                for (int j = 0; j < input_size; ++j) {
                    double error = 0;
                    for (int k = 0; k < output_size; ++k) {
                        error += (hidden[k] - input[k]) *
                                 weights_hidden_output[i][k];
                    }
                    weights_input_hidden[j][i] -= learning_rate * error *
                                                  noisy_input[j] *
                                                  (1 - hidden[i]) * hidden[i];
                }
            }
        }
    }
}
