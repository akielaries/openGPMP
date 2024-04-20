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
 *
 * @brief K-Nearest Neighbors Clustering
 */
#ifndef KNN_hpp
#define KNN_hpp

#include <vector>

namespace gpmp {

namespace ml {

/**
 * @class KNN
 * @brief Represents a K Nearest Neighbors (KNN) classifier
 */
class KNN {
  public:
    /**
     * @brief Constructor for the KNN class
     */
    KNN();

    /**
     * @brief Destructor for the KNN class
     */
    ~KNN();

    /**
     * @brief Trains the KNN model with the given training data and labels
     * @param training_data The training data, a vector of feature vectors
     * @param labels The corresponding labels for the training data
     */
    void train(const std::vector<std::vector<double>> &training_data,
               const std::vector<int> &labels);

    /**
     * @brief Predicts the label of a given input vector using KNN algorithm
     * @param input_vector The input vector for which prediction is to be made
     * @param k The number of nearest neighbors to consider
     * @return The predicted label
     */
    int predict(const std::vector<double> &input_vector, int k);

  private:
    /**< The training data stored as feature vectors */
    std::vector<std::vector<double>> training_data;
    /**< The corresponding labels for the training data */
    std::vector<int> labels;

    /**
     * @brief Calculates the Euclidean distance between two vectors
     * @param vec1 The first vector
     * @param vec2 The second vector
     * @return The Euclidean distance between the two vectors
     */
    double calculateEuclideanDistance(const std::vector<double> &vec1,
                                      const std::vector<double> &vec2);
};

} // namespace ml

} // namespace gpmp

#endif
