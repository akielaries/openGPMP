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

#ifndef NAIVE_NET_HPP
#define NAIVE_NET_HPP

#include <eigen3/Eigen/Eigen>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

typedef long double Scalar;
typedef Eigen::MatrixXf Matrix;
typedef Eigen::RowVectorXf RowVector;
typedef Eigen::VectorXf ColVector;

namespace gpmp {

class NaiveNet {
  public:
    // contructor
    naive_network(std::vector<uint> topology,
                  Scalar learningRate = Scalar(0.005));

    /* perform forward propagation */
    void forward_prop(RowVector &input);
    /* perform backward propagation*/
    void backward_prop(RowVector &output);
    /* calculate neuron errors */
    void errors(RowVector &output);
    /* update weights of neuron connections */
    void update_weights();
    /* train neural network given vector of data points */
    void train(std::vector<RowVector *> data);

    /* Naive Network storage objects */

    /* store layers of the network*/
    std::vector<RowVector *> neuron_layers;
    /* stored un-evaluated values of the layers */
    std::vector<RowVector *> cache_layers;
    /* stores error contribution of each neuron */
    std::vector<RowVector *> deltas;
    /* the connection weight */
    std::vector<Matrix *> weights;
    /* learning rate  */
    Scalar learning_rate;
};

} // namespace gpmp

#endif
