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

#ifndef REGULARIZERS_HPP
#define REGULARIZERS_HPP

#include <vector>

namespace gpmp {

namespace ml {

class Regularize {
  public:
    /**
     * @brief Computes L1 regularization penalty (Lasso regression)
     * @param weights The weights of the model
     * @param lambda The regularization parameter
     * @return The L1 regularization penalty
     */
    static double l1_regularization(const std::vector<double> &weights,
                                    double lambda);

    /**
     * @brief Computes L2 regularization penalty (Ridge regression)
     * @param weights The weights of the model
     * @param lambda The regularization parameter
     * @return The L2 regularization penalty
     */
    static double l2_regularization(const std::vector<double> &weights,
                                    double lambda);

    /**
     * @brief Computes Elastic Net regularization penalty
     * @param weights The weights of the model
     * @param lambda1 The L1 regularization parameter
     * @param lambda2 The L2 regularization parameter
     * @return The Elastic Net regularization penalty
     */
    static double elastic_net_regularization(const std::vector<double> &weights,
                                             double lambda1,
                                             double lambda2);

    /**
     * @brief Computes Dropout regularization penalty
     * @param dropout_rate The dropout rate
     * @param num_neurons The number of neurons in the layer
     * @return The Dropout regularization penalty
     */
    static double dropout_regularization(double dropout_rate, int num_neurons);

    /**
     * @brief Performs early stopping based on validation loss
     * @param current_val_loss The current validation loss
     * @param best_val_loss The best validation loss observed so far
     * @param patience The number of epochs to wait before stopping if
     * validation loss doesn't improve
     * @param epoch The current epoch number
     * @return True if early stopping criterion is met, False otherwise
     */
    static bool early_stopping(double current_val_loss,
                               double &best_val_loss,
                               int patience,
                               int epoch);

    /**
     * @brief Combines predictions from multiple models using ensembling
     * @param predictions Vector of prediction vectors from individual models
     * @return Ensemble prediction vector
     */
    static std::vector<double>
    ensemble_predictions(const std::vector<std::vector<double>> &predictions);

    /**
     * @brief Applies max norm regularization to the weights
     * @param weights The weights of the model
     * @param max_norm The maximum norm value
     */
    static void max_norm_regularization(std::vector<double> &weights,
                                        double max_norm);

    /**
     * @brief Applies weight decay regularization to the weights
     * @param weights The weights of the model
     * @param lambda The regularization parameter
     */
    static void weight_decay_regularization(std::vector<double> &weights,
                                            double lambda);

    /**
     * @brief Applies batch normalization to the input data
     * @param input_data The input data matrix
     * @param epsilon A small value added to variance to avoid division by zero
     * @param scale The scale parameter
     * @param shift The shift parameter
     * @return The normalized input data matrix
     */
    static std::vector<std::vector<double>>
    batch_normalization(const std::vector<std::vector<double>> &input_data,
                        double epsilon = 1e-5,
                        double scale = 1.0,
                        double shift = 0.0);

    /**
     * @brief Applies data augmentation to the input data
     * @param input_data The input data matrix
     * @param augmentation_factor The factor by which to augment the data (eg, 2
     * for doubling the data)
     * @return The augmented input data matrix
     */
    static std::vector<std::vector<double>>
    data_augmentation(const std::vector<std::vector<double>> &input_data,
                      int augmentation_factor);
};

} // namespace ml

} // namespace gpmp

#endif
