/**
 * @file
 *
 * Training methods and initializers used for the openMTPK Machine
 * Learning module
 */
#ifndef ML_TRAINERS_HPP
#define ML_TRAINERS_HPP
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "mlp_net.hpp"

namespace mtpk {

namespace ml {

class Utils {
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
    auto init_SecondaryMLP(size_t inputs, size_t outputs,
                           size_t hidden_layer_units,
                           int64_t hidden_layers, float lr) {
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

} // namespace mtpk

#endif
