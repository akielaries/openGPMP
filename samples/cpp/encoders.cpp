#include <openGPMP/ml.hpp>
#include <iostream>
#include <vector>
int main() {
    srand(time(0));

    // Vanilla AutoEncoder
    gpmp::ml::AutoEncoder ae(3, 2, 3, 0.1);

    std::cout << "Vanilla AutoEncoder Training:\n";
    std::vector<std::vector<double>> ae_training_data = {{1, 0, 0},
                                                         {0, 1, 0},
                                                         {0, 0, 1}};
    ae.train(ae_training_data, 1000);
    ae.display();

    std::cout << "\nTesting Vanilla AutoEncoder:\n";
    std::vector<double> test_input = {1, 1, 0};
    std::vector<double> output = ae.forward(test_input);
    std::cout << "Autoencoder Output:\n";
    for (double val : output) {
        std::cout << val << " ";
    }

    // Sparse AutoEncoder
    gpmp::ml::SparseAutoEncoder sparse_ae(3, 2, 3, 0.1, 0.01, 0.2);

    std::cout << "\n\nSparse AutoEncoder Training:\n";
    std::vector<std::vector<double>> ae_training_data_sparse = {{1, 0, 0},
                                                                {0, 1, 0},
                                                                {0, 0, 1}};
    sparse_ae.train(ae_training_data_sparse, 1000);
    sparse_ae.display();

    // Denoising AutoEncoder
    gpmp::ml::DenoisingAutoEncoder denoise_ae(3, 2, 3, 0.1, 0.2);

    std::cout << "\nDenoising AutoEncoder Training:\n";
    denoise_ae.train(ae_training_data, 1000);
    denoise_ae.display();

    // Contractive AutoEncoder
    gpmp::ml::ContractiveAutoEncoder contractive_ae(3, 2, 3, 0.1, 0.01);

    std::cout << "\nContractive AutoEncoder Training:\n";
    contractive_ae.train(ae_training_data, 1000);
    contractive_ae.display();

    // Recurrent AutoEncoder
    gpmp::ml::RecurrentAutoEncoder recurrent_ae(3, 2, 3, 0.1);

    std::cout << "\nRecurrent AutoEncoder Training:\n";
    std::vector<std::vector<double>> recurrent_ae_training_data = {{1, 0, 0},
                                                                   {0, 1, 0},
                                                                   {0, 0, 1}};
    recurrent_ae.train(recurrent_ae_training_data, 1000);
    recurrent_ae.display();

    return 0;
}
