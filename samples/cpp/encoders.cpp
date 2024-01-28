#include "../../include/ml/encoder.hpp"
#include <iostream>
#include <vector>

int main() {
    srand(time(0));

    // input size, hidden size, output size, learning rate
    gpmp::ml::AutoEncoder autoencoder(3, 2, 3, 0.1);

    // training data (input and output should be the same for an autoencoder)
    std::vector<std::vector<double>> training_data = {{1, 0, 0},
                                                      {0, 1, 0},
                                                      {0, 0, 1}};

    // train for 1000 epochs
    autoencoder.train(training_data, 1000);

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

    return 0;
}
