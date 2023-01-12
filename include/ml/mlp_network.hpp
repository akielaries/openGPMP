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
    long double ex;
    // error
    long double err;
    // weight
    long double* wt;
    // last weight
    long double* wt_last;
    // saved weight
    long double* wt_saved;
};

struct layer {
    int64_t num_neurons;
    neuron* neuron_ptr;
};


/**
 * @brief Primary Multi-Layer Perceptron Class
 */
class PrimaryMLP {
    /* initialize random values for the network */
    void rand_init();
    /* check that random is an integer */
    int64_t rand_int(int64_t low, int64_t hi);
    /*check random is a real number */
    long double rand_real(long double low, long double hi);

    /*return the number of layers in the network */
    int64_t num_layers;
    layer* layer_ptr;

    long double dMSE;
    long double dMAE;

    void weights_rank();

    void set_signal_in(long double* input);
    void get_signal_out(long double* output);

    void weights_save();
    void weights_restore();

    /* propogate given the signal */
    void prop_signal();
    /* returns the computed output error */
    void output_err(long double* target);
    /* returns the computed error from backwards propogation */
    void back_prop_err();
    /*adjust weights */
    void weights_adjust();
    /* simulate the Multi-Layer Perceptron Neual Network */
    void simulate(long double* input, long double* output, 
                long double* target, bool training);

    public:
        long double dEta;
        long double dAlpha;
        long double dGain;
        long double dAvgTestError;

        /* CONSTRUCT */
        MLP(int64_t nl, int64_t npl[]);
        /* DECONSTRUCT */
        ~MLP();

        /* method to train the network given data*/
        int64_t train(const char* fnames);
        /* method to test given data*/
        int64_t test (const char* fname);
        int64_t evaluate();

        void run(const char* fname, const int64_t& maxiter);

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
        inline long double sigmoid(long double x) {
            return 1.0f / (1 + exp(-x));
        }

        /**
         * @brief Sigmoid Derivative for backwards propogation
         *
         * @param[in] x : (float)
         */
        inline long double sigmoid_deriv(long double x) {
            return (x * (1 - x));
        }

        std::vector<size_t> layer_units;
        std::vector<Matrix<T>> bias_vectors;
        std::vector<Matrix<T>> wt_matrices;
        std::vector<Matrix<T>> activations;

        long double lr;

        /**
         * @brief Secondary Multi-Layer Perceptron Constructor
         */
        explicit SecondaryMLP(std::vector<size_t> layer_units, 
                                    long double lr = .001f) :
            layer_units(layer_units),
            wt_matrices(),
            bias_vectors(),
            lr(lr) {
            
            }

};

} // namespace mlp

} // namespace mtpk

#endif

