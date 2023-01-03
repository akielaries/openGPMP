/**
 * @file
 *
 * Multi-Layer Perceptron Neural Networks containing a 
 * Primary and Secondary network
 */
#ifndef MLP_NETWORK_HPP
#define MLP_NETWORK_HPP
#include <vector>
#include <stdio.h>
#include "../linalg.hpp"


namespace mtpk {

/**
 * @brief openMTPK Multi-Layer Perceptron namespace
 */
namespace mlp {

/*
 * TODO 
 * Think of using extended or derived classes
 *
 * Weights : MLP
 *
 */
struct neuron { 
    // exit
    double ex;
    // error
    double err;
    // weight
    double* wt;
    // last weight
    double* wt_last;
    // saved weight
    double* wt_saved;
};

struct layer {
    int num_neurons;
    neuron* neuron_ptr;
};


/**
 * @brief Primary Multi-Layer Perceptron Class
 */
class PrimaryNet {
    /* initialize random values for the network */
    void rand_init();
    /* check that random is an integer */
    int rand_int(int low, int hi);
    /*check random is a real number */
    double rand_real(double low, double hi);

    /*return the number of layers in the network */
    int num_layers;
    layer* layer_ptr;

    double dMSE;
    double dMAE;

    void weights_rank();

    void set_signal_in(double* input);
    void get_signal_out(double* output);

    void weights_save();
    void weights_restore();

    /* propogate given the signal */
    void prop_signal();
    /* returns the computed output error */
    void output_err(double* target);
    /* returns the computed error from backwards propogation */
    void back_prop_err();
    /*adjust weights */
    void weights_adjust();
    /* simulate the Multi-Layer Perceptron Neual Network */
    void simulate(double* input, double* output, 
                double* target, bool training);

    public:
        double dEta;
        double dAlpha;
        double dGain;
        double dAvgTestError;

        /* CONSTRUCT */
        MLP(int nl, int npl[]);
        /* DECONSTRUCT */
        ~MLP();

        /* method to train the network given data*/
        int train(const char* fnames);
        /* method to test given data*/
        int test (const char* fname);
        int evaluate();

        void run(const char* fname, const int& maxiter);

};

/**
 * @brief Secondary Multi-Layer Perceptron Class making use of 
 * the Linear Algebra module
 */
template<typename T>
class SecondaryNet {
    public:
        /**
         * @brief Sigmoid activation function
         *
         * @param[in] x : (float)
         */
        inline float sigmoid(float x) {
            return 1.0f / (1 + exp(-x));
        }

        /**
         * @brief Sigmoid Derivative for backwards propogation
         *
         * @param[in] x : (float)
         */
        inline float sigmoid_deriv(float x) {
            return (x * (1 - x));
        }

        std::vector<size_t> layer_units;
        std::vector<Matrix<T>> bias_vectors;
        std::vector<Matrix<T>> wt_matrices;
        std::vector<Matrix<T>> activations;

        float lr;

        /**
         * @brief Secondary Multi-Layer Perceptron Constructor
         */


};

} // namespace mlp

} // namespace mtpk

#endif

