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

/**
 * @file
 *
 * Training methods and initializers used for the openGPMP Machine
 * Learning module
 */
#ifndef TRAINERS_HPP
#define TRAINERS_HPP
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace gpmp {

namespace ml {

/**
 * @brief Training Algorithms
 */
class Trainers {
  public:
    /**
     * @brief Perform gradient descent for linear regression
     *
     * Given features X, target y, learning rate alpha, and number of iterations
     * num_iters, this function optimizes the parameters theta using gradient
     * descent
     *
     * @param X             Features matrix (each row represents a training
     * example)
     * @param y             Target vector
     * @param alpha         Learning rate
     * @param num_iters     Number of iterations
     * @return std::vector<double>     Optimized parameters theta
     */
    std::vector<double> gradientdesc(const std::vector<std::vector<double>> &X,
                                     const std::vector<double> &y,
                                     double alpha,
                                     int num_iters);

    /**
     * @brief Perform stochastic gradient descent for linear regression
     *
     * Given features X, target y, learning rate alpha, and number of iterations
     * num_iters, this function optimizes the parameters theta using stochastic
     * gradient descent
     *
     * @param X             Features matrix (each row represents a training
     * example)
     * @param y             Target vector
     * @param alpha         Learning rate
     * @param num_iters     Number of iterations
     * @return std::vector<double>     Optimized parameters theta
     */
    std::vector<double>
    stoch_gradientdesc(const std::vector<std::vector<double>> &X,
                       const std::vector<double> &y,
                       double alpha,
                       int num_iters);

    /**
     * @brief Perform mini-batch gradient descent for linear regression
     *
     * Given features X, target y, learning rate alpha, number of iterations
     * num_iters, and batch size batch_size, this function optimizes the
     * parameters theta using mini-batch gradient descent
     *
     * @param X             Features matrix (each row represents a training
     * example)
     * @param y             Target vector
     * @param alpha         Learning rate
     * @param num_iters     Number of iterations
     * @param batch_size    Size of mini-batch
     * @return std::vector<double>     Optimized parameters theta
     */
    std::vector<double>
    minibatch_gradientdesc(const std::vector<std::vector<double>> &X,
                           const std::vector<double> &y,
                           double alpha,
                           int num_iters,
                           int batch_size);
};

} // namespace ml

} // namespace gpmp

#endif
