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
 * @brief Auto Encoder Neural Network effecient for unlabeled data
 */
#ifndef ENCODER_NET_HPP
#define ENDOCER_NET_HPP

#include <string>
#include <tuple>
#include <vector>

namespace gpmp {

namespace ml {

class AutoEncoder {
  public:
    int input_size;

    int hidden_size;

    int output_size;

    double learning_rate;

    std::vector<std::vector<double>> weights_input_hidden;

    std::vector<std::vector<double>> weights_hidden_output;

    AutoEncoder(int input_size,
                int hidden_size,
                int output_size,
                double learning_rate);

    std::vector<double> sigmoid(const std::vector<double> &x);

    std::vector<double> forward(const std::vector<double> &input);

    void train(const std::vector<std::vector<double>> &training_data,
               int epochs);

    void printWeights();
};

} // namespace ml

} // namespace gpmp

#endif
