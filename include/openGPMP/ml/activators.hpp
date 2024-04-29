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

#ifndef ACTIVATION_HPP
#define ACTIVATION_HPP

#include <cmath>
#include <vector>

namespace gpmp {

namespace ml {

/**
 * @brief Activation Methods
 */
class Activation {
  public:
    /**
     * @brief Computes the sigmoid activation function
     * @param z The input value
     * @return The sigmoid of z
     */
    double sigmoid(double z);

    /**
     * @brief Computes the derivative of the sigmoid activation function
     * @param z The input value
     * @return The derivative of sigmoid at z
     */
    double sigmoid_derivative(double z);

    /**
     * @brief Computes the ReLU (Rectified Linear Unit) activation function
     * @param z The input value
     * @return The ReLU of z
     */
    double relu(double z);

    /**
     * @brief Computes the derivative of the ReLU (Rectified Linear Unit)
     * activation function
     * @param z The input value
     * @return The derivative of ReLU at z
     */
    double relu_derivative(double z);

    /**
     * @brief Computes the softmax activation function
     * @param inputs The input values
     * @return The softmax of inputs
     */
    std::vector<double> softmax(const std::vector<double> &inputs);

    /**
     * @brief Computes the derivative of the softmax activation function
     * @param inputs The input values
     * @return The derivatives of softmax at inputs
     */
    std::vector<std::vector<double>>
    softmax_derivative(const std::vector<double> &inputs);

    /**
     * @brief Computes the binary step activation function
     * @param z The input value
     * @return 1 if z >= 0, otherwise 0
     */
    double binary_step(double z);

    /**
     * @brief Computes the hyperbolic tangent (tanh) activation function
     * @param z The input value
     * @return The tanh of z
     */
    double tanh(double z);

    /**
     * @brief Computes the derivative of the hyperbolic tangent (tanh)
     * activation function
     * @param z The input value
     * @return The derivative of tanh at z
     */
    double tanh_derivative(double z);

    /**
     * @brief Computes the Soboleva modified hyperbolic tangent (smht)
     * activation function
     * @param z The input value
     * @return The smht of z
     */
    double smht(double z);

    /**
     * @brief Computes the derivative of the Soboleva modified hyperbolic
     * tangent (smht) activation function
     * @param z The input value
     * @return The derivative of smht at z
     */
    double smht_derivative(double z);

    /**
     * @brief Computes the Gaussian Error Linear Unit (GELU) activation function
     * @param z The input value
     * @return The GELU of z
     */
    double gelu(double z);

    /**
     * @brief Computes the derivative of the Gaussian Error Linear Unit (GELU)
     * activation function
     * @param z The input value
     * @return The derivative of GELU at z
     */
    double gelu_derivative(double z);

    /**
     * @brief Computes the softplus activation function
     * @param z The input value
     * @return The softplus of z
     */
    double softplus(double z);

    /**
     * @brief Computes the Exponential Linear Unit (ELU) activation function
     * @param z The input value
     * @param alpha The ELU parameter (default: 10)
     * @return The ELU of z
     */
    double elu(double z, double alpha = 10);

    /**
     * @brief Computes the derivative of the Exponential Linear Unit (ELU)
     * activation function
     * @param z The input value
     * @param alpha The ELU parameter (default: 10)
     * @return The derivative of ELU at z
     */
    double elu_derivative(double z, double alpha = 10);

    /**
     * @brief Computes the Scaled Exponential Linear Unit (SELU) activation
     * function
     * @param z The input value
     * @param alpha The SELU parameter (default: 167326)
     * @param scale The SELU parameter (default: 10507)
     * @return The SELU of z
     */
    double selu(double z, double alpha = 167326, double scale = 10507);

    /**
     * @brief Computes the derivative of the Scaled Exponential Linear Unit
     * (SELU) activation function
     * @param z The input value
     * @param alpha The SELU parameter (default: 167326)
     * @param scale The SELU parameter (default: 10507)
     * @return The derivative of SELU at z
     */
    double
    selu_derivative(double z, double alpha = 167326, double scale = 10507);

    /**
     * @brief Computes the Leaky Rectified Linear Unit (Leaky ReLU) activation
     * function
     * @param z The input value
     * @param alpha The Leaky ReLU parameter (default: 001)
     * @return The Leaky ReLU of z
     */
    double leaky_relu(double z, double alpha = 001);

    /**
     * @brief Computes the derivative of the Leaky Rectified Linear Unit (Leaky
     * ReLU) activation function
     * @param z The input value
     * @param alpha The Leaky ReLU parameter (default: 001)
     * @return The derivative of Leaky ReLU at z
     */
    double leaky_relu_derivative(double z, double alpha = 001);

    /**
     * @brief Computes the Parametric Rectified Linear Unit (PReLU) activation
     * function
     * @param z The input value
     * @param alpha The PReLU parameter (slope)
     * @return The PReLU of z
     */
    double prelu(double z, double alpha);

    /**
     * @brief Computes the derivative of the Parametric Rectified Linear Unit
     * (PReLU) activation function
     * @param z The input value
     * @param alpha The PReLU parameter (slope)
     * @return The derivative of PReLU at z
     */
    double prelu_derivative(double z, double alpha);

    /**
     * @brief Computes the Sigmoid Linear Unit (SiLU or Swish) activation
     * function
     * @param z The input value
     * @return The SiLU of z
     */
    double silu(double z);

    /**
     * @brief Computes the derivative of the Sigmoid Linear Unit (SiLU or Swish)
     * activation function
     * @param z The input value
     * @return The derivative of SiLU at z
     */
    double silu_derivative(double z);
};

} // namespace ml

} // namespace gpmp

#endif
