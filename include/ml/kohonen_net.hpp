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
 * Definitions for Self-Organizing Map (SOM)
 */

#ifndef KOHONEN_NETWORK_HPP
#define KOHONEN_NETWORK_HPP
#include <vector>

namespace gpmp {

namespace ml {

/**
 * @brief Kohonen Neural Network Cluster Class
 *
 * Referred to as Self-Organizing Map
 */
class KohonenNet {
  public:
    /**
     * @brief Constructor for the KohonenNet class
     * @param inputSize The size of the input vector
     * @param mapSize The size of the map in the Kohonen network
     */
    KohonenNet(int inputSize, int mapSize);

    /**
     * @brief Destructor for the KohonenNet class
     */
    ~KohonenNet();
    /**
     * @brief Trains the Kohonen network using input data
     * @param inputData The input data consisting of vectors
     * @param epochs The number of training epochs (default: 1000)
     */
    void train(const std::vector<std::vector<double>> &inputData,
               int epochs = 1000);

    /**
     * @brief Classifies a given input vector and returns the index of the best
     * matching unit
     * @param inputVector The input vector to be classified
     * @return The index of the best matching unit
     */
    int classify(const std::vector<double> &inputVector);

  private:
    int input_size; /**< The size of the input vector */
    int map_size;   /**< The size of the map in the Kohonen network */
    std::vector<std::vector<double>>
        weights; /**< Weight matrix for the Kohonen network */

    /**
     * @brief Initializes the weights of the Kohonen network
     */
    void initialize_weights();

    /**
     * @brief Finds the index of the best matching unit (BMU) for a given input
     * vector
     * @param input_vector The input vector
     * @return The index of the best matching unit
     */
    int best_matching_unit(const std::vector<double> &input_vector);

    /**
     * @brief Updates the weights of the Kohonen network based on the best
     * matching unit and input vector
     * @param bmu The index of the best matching unit
     * @param input_vector The input vector
     * @param learning_rate The learning rate for weight updates
     */
    void update_weights(int bmu,
                        const std::vector<double> &input_vector,
                        double learning_rate);

    /**
     * @brief Calculates the Euclidean distance between two vectors
     * @param vec1 The first vector
     * @param vec2 The second vector
     * @return The Euclidean distance between the two vectors
     */
    double euclidean_distance(const std::vector<double> &vec1,
                              const std::vector<double> &vec2);
};

} // namespace ml

} // namespace gpmp

#endif
