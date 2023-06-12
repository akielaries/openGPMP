/*************************************************************************
 *
 *  Project
 *                        __  __ _______ _____  _  __
 *                       |  \/  |__   __|  __ \| |/ /
 *  ___  _ __   ___ _ __ | \  / |  | |  | |__) | ' /
 * / _ \| '_ \ / _ \ '_ \| |\/| |  | |  |  ___/|  <
 *| (_) | |_) |  __/ | | | |  | |  | |  | |    | . \
 * \___/| .__/ \___|_| |_|_|  |_|  |_|  |_|    |_|\_\
 *      | |
 *      |_|
 *
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
#ifndef ML_TRAINERS_HPP
#define ML_TRAINERS_HPP
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "mlp_net.hpp"

namespace gpmp {

namespace ml {

class Trainers {
  public:
    /**
     * @details PrimaryMLP training method
     */
    int64_t train_PrimaryMLP(const char *fnames);

    /**
     * @details PrimaryMLP testing method
     */
    int64_t test_PrimaryMLP(const char *fname);

    /**
     * These methods acts as a helper to the SecondaryMLP class Model.
     * the create_SecondaryMLP method will return an initialized model
     * given the dimensions of the inputs and outputs as well as specs
     * related to the hidden layers of the network
     */
    auto init_SecondaryMLP(size_t inputs,
                           size_t outputs,
                           size_t hidden_layer_units,
                           int64_t hidden_layers,
                           float lr) {
        std::vector<size_t> layer_units;
        layer_units.push_back(inputs);

        for (int64_t i = 0; i < hidden_layers; ++i) {
            layer_units.push_back(hidden_layer_units);
        }
        layer_units.push_back(outputs);
        SecondaryMLP<long double> model_SecondaryMLP(layer_units, 0.01);

        return model_SecondaryMLP;
    }

    /**
     * @details SecondaryMLP training method
     */
    void train_SecondaryMLP(auto initialized_model,
                            const std::string data_file,
                            uint64_t iterations,
                            uint64_t print_increment) {
        std::fstream input(data_file.c_str());
        std::cout << "FILE: " << data_file << " ITERS: " << iterations
                  << " INCREMENT: " << print_increment;
    }
};

} // namespace ml

} // namespace gpmp

#endif
