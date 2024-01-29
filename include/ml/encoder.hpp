/*************************************************************************
 *
 *  Project
 *                         _____ _____  __  __ _____
 *                        / ____|  __ \|  \/  |  __ \
 *  ___  _ __   ___ _ __ | |  __| |__) | \  / | |__) |
 * / _ \| '_ \ / _ \ '_ \| | |_ |  ___/| |\/| |  ___/
 *| (_) | |_) |  __/ | | | |__| | |    | |  | | |
 * \___/| .__/ \___|_| |_|\_____|_|    |_|  |_|_|
 *      | |
 *      |_|
 *
 * Copyright (C) Akiel Aries, <akiel@akiel.org>, et al.
 *
 * This software is licensed as described in the file LICENSE, which
 * you should have received as part of this distribution. The terms
 * among other details are referenced in the official documentation
 * seen here : https://akielaries.github.io/openGPMP/ along with
 * important files seen in this project.
 *
 * You may opt to use, copy, modify, merge, publish, distribute
 * and/or sell copies of the Software, and permit persons to whom
 * the Software is furnished to do so, under the terms of the
 * LICENSE file. As this is an Open Source effort, all implementations
 * must be of the same methodology.
 *
 *
 *
 * This software is distributed on an AS IS basis, WITHOUT
 * WARRANTY OF ANY KIND, either express or implied.
 *
 ************************************************************************/

/**
 * @file
 * @brief Auto Encoder Neural Network effecient for unlabeled data
 */
#ifndef ENCODER_HPP
#define ENCODER_HPP

#include <string>
#include <tuple>
#include <vector>

namespace gpmp {

namespace ml {

/**
 * @brief A simple implementation of a vanilla autoencoder
 *
 * This class represents a basic autoencoder with one hidden layer. It can be
 * used for dimensionality reduction and feature learning
 */

// TODO: this base class could probably use its own gradient descent method to
// use across all inheriting classes OR create a class of trainers to use in
// `trainers.cpp`?
class AutoEncoder {
  public:
    /**
     * @brief Size of the input layer
     *
     * The number of input nodes in the autoencoder
     */
    int input_size;

    /**
     * @brief Size of the hidden layer
     *
     * The number of nodes in the hidden layer, which forms the compressed
     * representation
     */
    int hidden_size;

    /**
     * @brief Size of the output layer
     *
     * The number of output nodes in the autoencoder, which should match the
     * input size
     */
    int output_size;

    /**
     * @brief Learning rate for training the autoencoder
     *
     * The rate at which the weights are updated during the training process
     */
    double learning_rate;

    /**
     * @brief Weights from the input layer to the hidden layer
     *
     * A matrix representing the weights connecting the input layer to the
     * hidden layer
     */
    std::vector<std::vector<double>> weights_input_hidden;

    /**
     * @brief Weights from the hidden layer to the output layer
     *
     * A matrix representing the weights connecting the hidden layer to the
     * output layer
     */
    std::vector<std::vector<double>> weights_hidden_output;

    /**
     * @brief Constructor for the AutoEncoder class
     *
     * @param input_size Size of the input layer
     * @param hidden_size Size of the hidden layer
     * @param output_size Size of the output layer
     * @param learning_rate Learning rate for training the autoencoder
     */
    AutoEncoder(int input_size,
                int hidden_size,
                int output_size,
                double learning_rate);

    /**
     * @brief Sigmoid activation function
     *
     * Applies the sigmoid activation function element-wise to the input vector
     *
     * @param x Input vector
     * @return Result of applying the sigmoid function to each element of the
     * input vector
     */
    std::vector<double> sigmoid(const std::vector<double> &x);

    /**
     * @brief Forward pass through the autoencoder
     *
     * Computes the output of the autoencoder given an input vector
     *
     * @param input Input vector
     * @return Output vector of the autoencoder
     */
    std::vector<double> forward(const std::vector<double> &input);

    /**
     * @brief Train the autoencoder on a dataset
     *
     * Uses gradient descent to train the autoencoder on the provided training
     * data
     *
     * @param training_data Matrix containing training data
     * @param epochs Number of training epochs
     */
    virtual void train(const std::vector<std::vector<double>> &training_data,
                       int epochs);

    /**
     * @brief Set the initial learning rate
     *
     * @param initial_rate The initial learning rate
     */
    void lrate_set(double initial_rate);

    /**
     * @brief Update the learning rate based on a schedule
     *
     * @param epoch The current training epoch
     */
    virtual void lrate_update(int epoch);

    /**
     * @brief Print the weights of the autoencoder
     *
     * Prints the weights from the input layer to the hidden layer and from the
     * hidden layer to the output layer
     */
    void display();

    /**
     * @brief Save the model weights to a file
     *
     * @param filename The name of the file to save the weights to
     */
    virtual void save(const std::string &filename) const;

    /**
     * @brief Load model weights from a file
     *
     * @param filename The name of the file to load the weights from
     */
    virtual void load(const std::string &filename);
};

/**
 * @brief SparseAutoEncoder class, a derived class from AutoEncoder
 */
class SparseAutoEncoder : public AutoEncoder {
  public:
    /**
     * @brief Weight for the sparsity penalty term
     */
    double sparsity_weight;

    /**
     * @brief Target sparsity level
     */
    double sparsity_target;

    /**
     * @brief Constructor for the SparseAutoEncoder class
     *
     * @param input_size The size of the input layer
     * @param hidden_size The size of the hidden layer
     * @param output_size The size of the output layer
     * @param learning_rate The learning rate for training
     * @param sparsity_weight The weight for the sparsity penalty term
     * @param sparsity_target The target sparsity level
     */
    SparseAutoEncoder(int input_size,
                      int hidden_size,
                      int output_size,
                      double learning_rate,
                      double sparsity_weight,
                      double sparsity_target);

    /**
     * @brief Trains the sparse autoencoder on the given training data
     *
     * Overrides the train method in the base class with sparsity considerations
     *
     * @param training_data The training data
     * @param epochs The number of training epochs
     */
    void train(const std::vector<std::vector<double>> &training_data,
               int epochs) override;
};

/**
 * @brief DenoisingAutoEncoder class, a derived class from AutoEncoder
 */
class DenoisingAutoEncoder : public AutoEncoder {
  public:
    /**
     * @brief Probability of setting an input value to zero during training
     * (dropout rate)
     */
    double corruption_level;

    /**
     * @brief Constructor for the DenoisingAutoEncoder class
     *
     * @param input_size The size of the input layer
     * @param hidden_size The size of the hidden layer
     * @param output_size The size of the output layer
     * @param learning_rate The learning rate for training
     * @param corruption_level The probability of setting an input value to zero
     * during training
     */
    DenoisingAutoEncoder(int input_size,
                         int hidden_size,
                         int output_size,
                         double learning_rate,
                         double corruption_level);

    /**
     * @brief Adds noise to the input data and trains the denoising autoencoder
     *
     * Overrides the train method in the base class for denoising
     *
     * @param training_data The training data
     * @param epochs The number of training epochs
     */
    void train(const std::vector<std::vector<double>> &training_data,
               int epochs) override;
};

/**
 * @brief ContractiveAutoEncoder class, a derived class from AutoEncoder
 */
class ContractiveAutoEncoder : public AutoEncoder {
  public:
    /**
     * @brief Weight for the contractive penalty term
     */
    double contractive_weight;

    /**
     * @brief Constructor for the ContractiveAutoEncoder class
     *
     * @param input_size The size of the input layer
     * @param hidden_size The size of the hidden layer
     * @param output_size The size of the output layer
     * @param learning_rate The learning rate for training
     * @param contractive_weight The weight for the contractive penalty term
     */
    ContractiveAutoEncoder(int input_size,
                           int hidden_size,
                           int output_size,
                           double learning_rate,
                           double contractive_weight);

    /**
     * @brief Trains the contractive autoencoder on the given training data
     *
     * Overrides the train method in the base class with contractive penalty
     *
     * @param training_data The training data
     * @param epochs The number of training epochs
     */
    virtual void train(const std::vector<std::vector<double>> &training_data,
                       int epochs) override;
};

/**
 * @brief MDLAutoEncoder Minimal Description Length class, a derived class from
 * AutoEncoder
 */
class MDLAutoEncoder : public AutoEncoder {
  public:
    /**
     * @brief Weight for the MDL penalty term
     */
    double mdl_weight;

    /**
     * @brief Constructor for the MDLAutoEncoder class
     *
     * @param input_size The size of the input layer
     * @param hidden_size The size of the hidden layer
     * @param output_size The size of the output layer
     * @param learning_rate The learning rate for training
     * @param mdl_weight The weight for the MDL penalty term
     */
    MDLAutoEncoder(int input_size,
                   int hidden_size,
                   int output_size,
                   double learning_rate,
                   double mdl_weight);

    /**
     * @brief Trains the MDL autoencoder on the given training data
     *
     * Overrides the train method in the base class with MDL penalty
     *
     * @param training_data The training data
     * @param epochs The number of training epochs
     */
    virtual void train(const std::vector<std::vector<double>> &training_data,
                       int epochs) override;
};

/**
 * @brief ConcreteAutoEncoder class, a derived class from AutoEncoder
 */
class ConcreteAutoEncoder : public AutoEncoder {
  public:
    /**
     * @brief Temperature parameter for the Concrete distribution
     */
    double temperature;

    /**
     * @brief Constructor for the ConcreteAutoEncoder class
     *
     * @param input_size The size of the input layer
     * @param hidden_size The size of the hidden layer
     * @param output_size The size of the output layer
     * @param learning_rate The learning rate for training
     * @param temperature The temperature parameter for the Concrete
     * distribution
     */
    ConcreteAutoEncoder(int input_size,
                        int hidden_size,
                        int output_size,
                        double learning_rate,
                        double temperature);

    /**
     * @brief Trains the Concrete autoencoder on the given training data
     *
     * Overrides the train method in the base class with Concrete autoencoder
     * specifics
     *
     * @param training_data The training data
     * @param epochs The number of training epochs
     */
    virtual void train(const std::vector<std::vector<double>> &training_data,
                       int epochs) override;
};

/**
 * @brief VariationalAutoEncoder class, a derived class from AutoEncoder
 */
class VariationalAutoEncoder : public AutoEncoder {
  public:
    /**
     * @brief keeps track of hidden means
     */
    std::vector<double> hidden_mean;
    /**
     * @brief keeps track of hidden log variance
     */
    std::vector<double> hidden_log_variance;

    /**
     * @brief Samples from a standard normal distribution
     *
     * @return A sample from the standard normal distribution.
     */
    double sample_dist();

    /**
     * @brief Reparameterization trick for variational autoencoders
     *
     * @param mean The mean of the distribution
     * @param log_variance The log variance of the distribution
     * @return A sample from the specified distribution
     */
    double reparameterize(double mean, double log_variance);

    /**
     * @brief Performs the forward pass for the encoder and returns hidden
     * activations.
     *
     * @param input The input data.
     * @return The hidden activations.
     */
    std::vector<double> encoder(const std::vector<double> &input);

    /**
     * @brief Performs the forward pass for the decoder and returns output
     * activations.
     *
     * @param hidden_sampled The sampled hidden values.
     * @return The output activations.
     */
    std::vector<double> decoder(const std::vector<double> &hidden_sampled);

    /**
     * @brief Performs the backward pass (gradient descent) updating weights.
     *
     * @param input The input data.
     * @param output The output activations.
     * @param hidden_sampled The sampled hidden values.
     */
    void gradient_descent(const std::vector<double> &input,
                          const std::vector<double> &output,
                          const std::vector<double> &hidden_sampled);

    /**
     * @brief Constructor for the VariationalAutoEncoder class
     *
     * @param input_size The size of the input layer
     * @param hidden_size The size of the hidden layer
     * @param output_size The size of the output layer
     * @param learning_rate The learning rate for training
     */
    VariationalAutoEncoder(int input_size,
                           int hidden_size,
                           int output_size,
                           double learning_rate);

    /**
     * @brief Trains the Variational autoencoder on the given training data
     *
     * Overrides the train method in the base class with Variational autoencoder
     * specifics
     *
     * @param training_data The training data
     * @param epochs The number of training epochs
     */
    virtual void train(const std::vector<std::vector<double>> &training_data,
                       int epochs) override;
};

} // namespace ml

} // namespace gpmp

#endif
