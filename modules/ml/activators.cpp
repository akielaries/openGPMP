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
#include <openGPMP/ml/activators.hpp>
#include <vector>

double gpmp::ml::Activation::sigmoid(double z) {
    return 1.0 / (1.0 + exp(-z));
}

double gpmp::ml::Activation::sigmoid_derivative(double z) {
    double sig = sigmoid(z);
    return sig * (1.0 - sig);
}

double gpmp::ml::Activation::relu(double z) {
    return z > 0 ? z : 0;
}

double gpmp::ml::Activation::relu_derivative(double z) {
    return z > 0 ? 1 : 0;
}

std::vector<double>
gpmp::ml::Activation::softmax(const std::vector<double> &inputs) {
    std::vector<double> result;
    double sum_exp = 0.0;
    for (double input : inputs) {
        sum_exp += exp(input);
    }
    for (double input : inputs) {
        result.push_back(exp(input) / sum_exp);
    }
    return result;
}

std::vector<std::vector<double>>
gpmp::ml::Activation::softmax_derivative(const std::vector<double> &inputs) {
    std::vector<std::vector<double>> result(
        inputs.size(),
        std::vector<double>(inputs.size(), 0.0));
    std::vector<double> softmax_values = softmax(inputs);
    for (size_t i = 0; i < inputs.size(); ++i) {
        for (size_t j = 0; j < inputs.size(); ++j) {
            if (i == j) {
                result[i][j] = softmax_values[i] * (1.0 - softmax_values[i]);
            } else {
                result[i][j] = -softmax_values[i] * softmax_values[j];
            }
        }
    }
    return result;
}

double gpmp::ml::Activation::binary_step(double z) {
    return z >= 0 ? 1 : 0;
}

double gpmp::ml::Activation::tanh(double z) {
    return std::tanh(z);
}

double gpmp::ml::Activation::tanh_derivative(double z) {
    double tanh_z = std::tanh(z);
    return 1.0 - tanh_z * tanh_z;
}

double gpmp::ml::Activation::smht(double z) {
    return z / (1.0 + exp(-z));
}

double gpmp::ml::Activation::smht_derivative(double z) {
    double smht_z = smht(z);
    return smht_z * (1.0 - smht_z);
}

double gpmp::ml::Activation::gelu(double z) {
    return 0.5 * z *
           (1.0 + tanh(sqrt(2.0 / M_PI) * (z + 0.044715 * z * z * z)));
}

double gpmp::ml::Activation::gelu_derivative(double z) {
    double cdf =
        0.5 * (1.0 + tanh(sqrt(2.0 / M_PI) * (0.044715 * z * z * z + 3 * z)));
    double pdf = exp(-0.5 * z * z) / sqrt(2.0 * M_PI);
    return 0.5 * (1.0 + cdf +
                  z * pdf * (1.0 / M_PI) *
                      (0.5 * (1.0 + tanh(sqrt(2.0 / M_PI) *
                                         (0.044715 * z * z * z + 3 * z)))) +
                  (1.0 / M_PI) * (1.0 - cdf * cdf));
}

double gpmp::ml::Activation::softplus(double z) {
    return log(1.0 + exp(z));
}

double gpmp::ml::Activation::elu(double z, double alpha) {
    return z >= 0 ? z : alpha * (exp(z) - 1);
}

double gpmp::ml::Activation::elu_derivative(double z, double alpha) {
    return z >= 0 ? 1 : elu(z, alpha) + alpha;
}

double gpmp::ml::Activation::selu(double z, double alpha, double scale) {
    return scale * (z >= 0 ? z : alpha * (exp(z) - 1));
}

double
gpmp::ml::Activation::selu_derivative(double z, double alpha, double scale) {
    return scale * (z >= 0 ? 1 : alpha * exp(z));
}

double gpmp::ml::Activation::leaky_relu(double z, double alpha) {
    return z >= 0 ? z : alpha * z;
}

double gpmp::ml::Activation::leaky_relu_derivative(double z, double alpha) {
    return z >= 0 ? 1 : alpha;
}

double gpmp::ml::Activation::prelu(double z, double alpha) {
    return z >= 0 ? z : alpha * z;
}

double gpmp::ml::Activation::prelu_derivative(double z, double alpha) {
    return z >= 0 ? 1 : alpha;
}

double gpmp::ml::Activation::silu(double z) {
    return z / (1 + exp(-z));
}

double gpmp::ml::Activation::silu_derivative(double z) {
    double sig_z = sigmoid(z);
    return sig_z + (1 - sig_z) * z * sig_z;
}
