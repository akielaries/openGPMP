/*
 * Implementation of a Multi-Layered Perceptron Neural Network
 */
#include "../../include/ml/mlp_net.hpp"
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

using namespace mtpk::ml;

/*
 * Initialize randomly generated values for network's method
 */
void mtpk::ml::PrimaryMLP::rand_init() {
    srand((uint64_t) time(NULL));
}

/* verify the random is an integer */
int64_t mtpk::ml::PrimaryMLP::rand_int(int64_t hi, int64_t low) {
    return rand() % (hi - low + 1) + low;
}

/* verify generated random is a real number */
long double mtpk::ml::PrimaryMLP::rand_real(long double low, 
                                            long double hi) {
    return ((long double) rand() / RAND_MAX) * (hi - low) + low;
}

/* MLP CONSTRUCTOR */
mtpk::ml::PrimaryMLP::PrimaryMLP(int64_t nl, int64_t npl[]) : 
    num_layers(0), 
    layer_ptr(0),
    dEta(0.25),
    dAlpha(0.9),
    dGain(1.0),
    dMSE(0.0),
    dMAE(0.0),
    dAvgTestError(0.0) { 
    
    int64_t i, j;

    // create network layers
    num_layers = nl;
    layer_ptr = new layer[nl];


}


