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

#ifndef BNN_HPP
#define BNN_HPP

#include <cmath>
#include <random>
#include <vector>

/**
 * @class BNN
 * @brief Bayesian Neural Network class
 */
class BNN {
  public:
    /**
     * @brief Constructor for the BNN class
     * @param input_size Number of input features
     * @param hidden_size Number of hidden units in the network
     * @param output_size Number of output units in the network
     * @param prior_variance Variance for the prior distribution (default
     * is 1.0)
     */
    BNN(int input_size,
        int hidden_size,
        int output_size,
        double prior_variance = 1.0);

    /**
     * @brief Train the Bayesian Neural Network
     * @param X_train Input training data
     * @param y_train Target training data
     * @param epochs Number of training epochs (default is 1000)
     */
    void fit(const std::vector<std::vector<double>> &X_train,
             const std::vector<std::vector<double>> &y_train,
             int epochs = 1000);

    /**
     * @brief Predict the output for a given input
     * @param input_vector Input data for prediction
     * @return Predicted output vector
     */
    std::vector<double> predict(const std::vector<double> &input_vector);

    /**
     * @brief Number of input features
     */
    int input_size;

    /**
     * @brief Number of hidden units in the network
     */
    int hidden_size;

    /**
     * @brief Number of output units in the network
     */
    int output_size;

    /**
     * @brief Variance for the prior distribution
     */
    double prior_variance;

    /**
     * @brief Weights from input to hidden layer
     */
    std::vector<std::vector<double>> input_to_hidden_weights;

    /**
     * @brief Biases for the hidden layer
     */
    std::vector<double> hidden_biases;

    /**
     * @brief Weights from hidden to output layer
     */
    std::vector<std::vector<double>> hidden_to_output_weights;

    /**
     * @brief Biases for the output layer
     */
    std::vector<double> output_biases;

    /**
     * @brief Mersenne Twister random number generator
     */
    std::mt19937 rng;

    /**
     * @brief Activation function for the hidden layer
     * @param x Input value
     * @return Activated output
     */
    double activation_function(double x);

    /**
     * @brief Compute the log-likelihood of the prior distribution
     * @return Log-likelihood of the prior
     */
    double prior_log_likelihood();

    /**
     * @brief Compute the log-likelihood of the data
     * @param X Input features
     * @param y True labels
     * @return Log-likelihood of the data
     */
    double log_likelihood(const std::vector<std::vector<double>> &X,
                          const std::vector<std::vector<double>> &y);

    /**
     * @brief Compute the negative log posterior (loss function)
     * @param X Input features
     * @param y True labels
     * @return Negative log posterior
     */
    double compute_loss(const std::vector<std::vector<double>> &X,
                        const std::vector<std::vector<double>> &y);

    /**
     * @brief Update weights using stochastic gradient descent
     * @param X Input features
     * @param y True labels
     * @param learning_rate Learning rate for the update
     */
    void update_weights(const std::vector<std::vector<double>> &X,
                        const std::vector<std::vector<double>> &y,
                        double learning_rate);
};

#endif
