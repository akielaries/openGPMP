#include "../../include/ml/encoder.hpp"
#include <iostream>
#include <vector>

int main() {
    srand(time(0));

    // input size, hidden size, output size, learning rate
    gpmp::ml::AutoEncoder autoencoder(3, 2, 3, 0.1);

    // training data (input and output should be the same for an autoencoder)
    std::vector<std::vector<double>> ae_training_data = {{1, 0, 0},
                                                         {0, 1, 0},
                                                         {0, 0, 1}};

    // train for 1000 epochs
    autoencoder.train(ae_training_data, 1000);

    // print the trained weights
    autoencoder.display();

    // test the autoencoder with a new input
    std::vector<double> test_input = {1, 1, 0};
    std::vector<double> output = autoencoder.forward(test_input);

    // print the output
    std::cout << "\nAutoencoder Output:\n";
    for (double val : output) {
        std::cout << val << " ";
    }

    // create an instance of SparseAutoEncoder
    gpmp::ml::SparseAutoEncoder sparseAutoEncoder(3, 2, 3, 0.1, 0.01, 0.2);

    // training data (input and output should be the same for an autoencoder)
    std::vector<std::vector<double>> ae_training_data_sparse = {{1, 0, 0},
                                                                {0, 1, 0},
                                                                {0, 0, 1}};

    // train using the base class pointer
    gpmp::ml::AutoEncoder *basePtr = &sparseAutoEncoder;
    basePtr->train(ae_training_data_sparse, 1000);

    // print the trained weights
    basePtr->display();

    return 0;
}
