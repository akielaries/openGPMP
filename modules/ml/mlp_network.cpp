/*
 * Implementation of a Multi-Layered Perceptron Neural Network
 */
#include "../../include/ml/mlp_network.cpp"
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>


/*
 * Initialize randomly generated values for network's method
 */
void MLP::rand_init() {
    srand((unsigned) time(NULL));
}

/* verify the random is an integer */
int MLP::rand_int(int hi, int low) {
    return rand() % (hi - low + 1) + low;
}

/* verify generated random is a real number */
double MLP::rand_real() {
    return ((double) rand() / RAND_MAX) * (hi - low) + low;
}

/* MLP CONTRUCTOR */
MLP::MLP(int nl, int npl):num_layers(0), layer_ptr(0),
    dEta(0.25),
    dAlpha(0.9),
    dGain(1.0),
    dMSE(0.0),
    dMAE(0.0),
    dAvgTestError(0.0)


