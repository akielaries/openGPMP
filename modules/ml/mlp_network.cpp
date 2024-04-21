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

/*
 * Implementation of a Multi-Layered Perceptron Neural Network
 */
#include <math.h>
#include <openGPMP/ml/mlp_net.hpp>
#include <stdio.h>
#include <string.h>
#include <time.h>

using namespace gpmp::ml;

/*
 * Initialize randomly generated values for network's method
 */
void gpmp::ml::PrimaryMLP::rand_init() {
    srand(4711);
    // srand((uint64_t)time(NULL));
}

/* verify the random is an integer */
int64_t gpmp::ml::PrimaryMLP::rand_int(int64_t hi, int64_t low) {
    return rand() % (hi - low + 1) + low;
}

/* verify generated random is a real number */
long double gpmp::ml::PrimaryMLP::rand_real(long double low, long double hi) {
    return ((long double)rand() / RAND_MAX) * (hi - low) + low;
}

/* PRIMARY MLP CONSTRUCTOR */
gpmp::ml::PrimaryMLP::PrimaryMLP(int64_t nl, int64_t npl[])
    : num_layers(0), layer_ptr(0), _MSE(0.0), _MAE(0.0), _Eta(0.25),
      _Alpha(0.9), _Gain(1.0), _AvgTestError(0.0) {
    int64_t _LAYER, _NEURON;

    // create network layers
    num_layers = nl;
    layer_ptr = new layer[nl];

    // intialize the data of the created network layers
    for (_LAYER = 0; _LAYER < nl; _LAYER++) {
        // intialize values to neuron struct information
        layer_ptr[_LAYER].num_neurons = npl[_LAYER];
        layer_ptr[_LAYER].neuron_ptr = new neuron[npl[_LAYER]];

        // intialize date of the neurons of the created network layers
        for (_NEURON = 0; _NEURON < npl[_LAYER]; _NEURON++) {
            // initialize exit value
            layer_ptr[_LAYER].neuron_ptr[_NEURON].sortir = 1.0;
            // save the error
            layer_ptr[_LAYER].neuron_ptr[_NEURON].err = 0.0;

            // check if there is at least 1 layer
            if (_LAYER > 0) {
                /* initialize weight, last weight, and saved weight
                 * values to _LAYER - 1
                 */
                layer_ptr[_LAYER].neuron_ptr[_NEURON].wt =
                    new long double[npl[_LAYER - 1]];

                layer_ptr[_LAYER].neuron_ptr[_NEURON].wt_last =
                    new long double[npl[_LAYER - 1]];

                layer_ptr[_LAYER].neuron_ptr[_NEURON].wt_saved =
                    new long double[npl[_LAYER - 1]];
            }
            // otherwise
            else {
                /*
                 * initialize weight, last weight, and saved weight
                 * to NULL
                 */
                layer_ptr[_LAYER].neuron_ptr[_NEURON].wt = NULL;
                layer_ptr[_LAYER].neuron_ptr[_NEURON].wt_last = NULL;
                layer_ptr[_LAYER].neuron_ptr[_NEURON].wt_saved = NULL;
            }
        }
    }
}

/* PRIMARY MLP DECONSTRUCTOR */
gpmp::ml::PrimaryMLP::~PrimaryMLP() {
    int64_t _LAYER, _NEURON;

    // TODO : thread the loops dealing with rudimentary computations

    for (_LAYER = 0; _LAYER < num_layers; _LAYER++) {
        if (layer_ptr[_LAYER].neuron_ptr) {
            for (_NEURON = 0; _NEURON < layer_ptr[_LAYER].num_neurons;
                 _NEURON++) {
                if (layer_ptr[_LAYER].neuron_ptr[_NEURON].wt) {
                    delete[] layer_ptr[_LAYER].neuron_ptr[_NEURON].wt;
                }

                if (layer_ptr[_LAYER].neuron_ptr[_NEURON].wt_last) {
                    delete[] layer_ptr[_LAYER].neuron_ptr[_NEURON].wt_last;
                }

                if (layer_ptr[_LAYER].neuron_ptr[_NEURON].wt_saved) {
                    delete[] layer_ptr[_LAYER].neuron_ptr[_NEURON].wt_saved;
                }
            }
        }
        delete[] layer_ptr[_LAYER].neuron_ptr;
    }
    delete[] layer_ptr;
}
