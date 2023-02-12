/*
 * Example on using the Multi-Layer Perceptrons networks
 * supplied from openMTPk
 */
#include "../../include/ml/mlp_net.hpp"
#include "../../include/ml/utils.hpp"
#include <deque>
#include <fstream>
#include <iostream>

// use the openMTPK Machine Learning namespaces
using namespace mtpk::ml;

int main() {
    std::cout << "SAMPLE USING THE MULTI-LAYER PERCEPTRON NETWORK.\n";

    std::srand(42069);
    // initialize the SecondaryMLP model
    int64_t inputs{1}, outputs{1}, hidden_layer_units{8}, hidden_layers{3};

    long double     lr{.5};
    mtpk::ml::Utils util;
    auto            model = util.init_SecondaryMLP(inputs = 1, outputs = 1,
                                        hidden_layer_units = 8,
                                        hidden_layers = 3, lr = .5);

    // declare a data file

    // TODO : create util method to save/read/parse datafile, and
    // columns
    // std::ofstream data_file;
    std::string data_file = "../../data/school_scores.csv";

    uint64_t max_iters{1000}, return_every{500};
    // call the train method for the SecondaryMLP model
    util.train_SecondaryMLP(model, data_file, max_iters, return_every);

    return 0;
}
