/*
 * Implementation of a Multi-Layered Perceptron Neural Network
 */
#include "../../include/ml/mlp_net.hpp"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

using namespace mtpk::ml;

/*
 * Initialize randomly generated values for network's method
 */
void mtpk::ml::PrimaryMLP::rand_init() {
    srand((uint64_t)time(NULL));
}

/* verify the random is an integer */
int64_t mtpk::ml::PrimaryMLP::rand_int(int64_t hi, int64_t low) {
    return rand() % (hi - low + 1) + low;
}

/* verify generated random is a real number */
long double mtpk::ml::PrimaryMLP::rand_real(long double low,
                                            long double hi) {
    return ((long double)rand() / RAND_MAX) * (hi - low) + low;
}

/* PRIMARY MLP CONSTRUCTOR */
mtpk::ml::PrimaryMLP::PrimaryMLP(int64_t nl, int64_t npl[])
    : num_layers(0),
      layer_ptr(0),
      _Eta(0.25),
      _Alpha(0.9),
      _Gain(1.0),
      _MSE(0.0),
      _MAE(0.0),
      _AvgTestError(0.0) {
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
mtpk::ml::PrimaryMLP::~PrimaryMLP() {
    int64_t _LAYER, _NEURON;

    // TODO : thread the loops dealing with rudimentary computations

    for (_LAYER = 0; _LAYER < num_layers; _LAYER++) {
        if (layer_ptr[_LAYER].neuron_ptr) {
            for (_NEURON = 0;
                 _NEURON < layer_ptr[_LAYER].num_neurons;
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
