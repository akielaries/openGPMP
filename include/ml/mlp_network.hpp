/**
 * @file
 *
 * Multi-Layer Perceptron Neural Networks containing a 
 * Primary and Secondary network
 */
#ifndef MLP_NETWORK_HPP
#define MLP_NETWORK_HPP
#include <vector>
#include <random>
#include <utility>
#include <cassert>
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
    long double sortir;
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
        PrimaryMLP(int64_t nl, int64_t npl[]);
        /* DECONSTRUCT */
        ~PrimaryMLP();

        /* method to train the network given data*/
        int64_t train(const char* fnames);
        /* method to test given data*/
        int64_t test (const char* fname);
        int64_t evaluate();

        void run(const char* fname, const int64_t& max_iters);

};

/**
 * @brief Secondary Multi-Layer Perceptron Class making use of 
 * the Linear Algebra module
 */
template<typename T>
class SecondaryMLP {
    public:
        /**
         * @details Logging function for collecting the results
         */
        void log(auto &file, const auto &x, const auto &y, const auto &y_hat){
            // mean squared error
            auto mse = (y.data[0] - y_hat.data[0]);
            mse = mse*mse;
            file << mse << " "
                << x.data[0] << " "
                << y.data[0] << " "
                << y_hat.data[0] << " \n";
        }

        /**
         * @brief Sigmoid activation function
         *
         * @param[in] x : (float)
         */
        inline long double sigmoid_activ(long double x) {
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
        std::vector<Matrix<T>> wt_mtx;
        std::vector<Matrix<T>> activations;

        long double lr;

        /**
         * @details Secondary Multi-Layer Perceptron Constructor
         * Initialize a set of weights + biases for each layer 
         * set to random Gaussian Noise related values
         */
        explicit SecondaryMLP(std::vector<size_t> layer_units, 
                                    long double lr = .001) :
            layer_units(layer_units),
            wt_mtx(),
            bias_vectors(),
            lr(lr) {

                // traverse the elements
                for (size_t i = 0; i < layer_units.size() - 1; ++i) {
                    // size of inputs
                    size_t inputs{layer_units[i]};
                    // size of outputs
                    size_t outputs{layer_units[i + 1]};

                    // set to random Guassian Noise related values
                    // weights
                    auto gauss_wt = mtpk::mtx<T>::randn(outputs, inputs);
                    wt_mtx.push_back(gauss_wt);
                    // biases
                    auto bias_wt = mtpk::mtx<T>::randn(outputs, 1);
                    bias_vectors.push_back(bias_wt);
                    // activation function
                    activations.resize(layer_units.size());
                }
            }
        /**
         * @details Forward passes compute the activations at a specific
         * layer. This method saves the results to the activations Matrix
         * passing it forwards to use as an input paramater on the next layer
         */
        auto prop_forwards(Matrix<T> x) {
            assert(get<0>(x.shape) == layer_units[0] && 
                    get<1>(x.shape));
            // input = to previously declared acitvations method
            activations[0] = x;
            Matrix prev(x);

            // traverse layer units
            for (uint64_t i = 0; i < layer_units.size() - 1; ++i) {
                Matrix y = wt_mtx[i].mult(prev);
                y = y + bias_vectors[i];
                y = y.apply_function(sigmoid_activ);
                activations[i + 1] = y;
                prev = y;
            }
            return prev;
        }
        /**
         * @details Backwards Propagation is utilized to optimize the 
         * net's weights. Enabling learning how to correctly map arbitrary
         * inputs to outputs. The goal being to update each weight of the 
         * network allowing them to increase the chance of the actual 
         * output being closer to the target output.
         * This method takes the target output as an input parameter
         */
        void prop_backwards(Matrix<T> target) {
            assert(get<0>(target.shape) == layer_units.back());
            // calculate the error, target - ouput
            auto y = target;
            auto y_hat = activations.back();
            auto err = target - y_hat;
            // back propagate the error calculated from output to input 
            // and step the weights
            for (int64_t i = wt_mtx.size() - 1; i >= 0; --i) {
                // calculate errors for previous layer
                auto wt = wt_mtx[i].T();
                auto prior_errs = wt.mult(err);

                auto outputs_d = activations[i+1].apply_function(sigmoid_deriv);
                auto gradients = err.mult_elem(outputs_d);
                gradients = gradients.scalar_mult(lr);
                auto trans_a = activations[i].T();
                auto gradients_wt = gradients.mult(trans_a);

                // adjust the networks weights based on propagation technique
                bias_vectors[i] = bias_vectors[i].add(gradients);
                wt_mtx[i] = wt_mtx[i].add(gradients_wt);
                err = prior_errs;
            }
        }
};

/**
 * This methods acts as a helper to the SecondaryMLP class Model.
 * the create_SecondaryMLP method will return an initialized model given
 * the dimensions of the inputs and outputs as well as specs related
 * to the hidden layers of the network
 */
auto init_SecondaryMLP(size_t inputs,
                size_t outputs,
                size_t hidden_layer_units,
                int64_t hidden_layers,
                float lr) {
    std::vector<size_t> layer_units;
    layer_units.push_back(inputs);
    
    for (uint64_t i = 0; i < hidden_layers; ++i) {
        layer_units.push_back(hidden_layer_units);
    }
    layer_units.push_back(outputs);
    SecondaryMLP<long double> model_SecondaryMLP(layer_units, 0.01);
    return model_SecondaryMLP;
}

} // namespace mlp

} // namespace mtpk

#endif

