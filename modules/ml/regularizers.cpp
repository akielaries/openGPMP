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

#include "../../include/ml/regularizers.hpp"
#include <algorithm>
#include <cmath>
#include <random>

double
gpmp::ml::Regularize::l1_regularization(const std::vector<double> &weights,
                                        double lambda) {
    double penalty = 0.0;
    for (double weight : weights) {
        penalty += std::abs(weight);
    }
    return lambda * penalty;
}

double
gpmp::ml::Regularize::l2_regularization(const std::vector<double> &weights,
                                        double lambda) {
    double penalty = 0.0;
    for (double weight : weights) {
        penalty += weight * weight;
    }
    return 0.5 * lambda * penalty;
}

double gpmp::ml::Regularize::elastic_net_regularization(
    const std::vector<double> &weights,
    double lambda1,
    double lambda2) {
    double l1_penalty = l1_regularization(weights, lambda1);
    double l2_penalty = l2_regularization(weights, lambda2);
    return l1_penalty + l2_penalty;
}

double gpmp::ml::Regularize::dropout_regularization(double dropout_rate,
                                                    int num_neurons) {
    return 0.5 * dropout_rate * num_neurons;
}

bool gpmp::ml::Regularize::early_stopping(double current_val_loss,
                                          double &best_val_loss,
                                          int patience,
                                          int epoch) {
    if (current_val_loss < best_val_loss) {
        best_val_loss = current_val_loss;
        patience = epoch + patience; // Reset patience
    } else {
        if (epoch >= patience) {
            return true; // Stop training
        }
    }
    return false; // Continue training
}

std::vector<double> gpmp::ml::Regularize::ensemble_predictions(
    const std::vector<std::vector<double>> &predictions) {
    std::vector<double> ensemble;
    if (!predictions.empty()) {
        ensemble.resize(predictions.front().size(), 0.0);
        for (const auto &prediction : predictions) {
            for (size_t i = 0; i < prediction.size(); ++i) {
                ensemble[i] += prediction[i];
            }
        }
        for (auto &val : ensemble) {
            val /= predictions.size();
        }
    }
    return ensemble;
}

void gpmp::ml::Regularize::max_norm_regularization(std::vector<double> &weights,
                                                   double max_norm) {
    double norm = 0.0;
    for (double &weight : weights) {
        norm += weight * weight;
    }
    norm = sqrt(norm);
    if (norm > max_norm) {
        double factor = max_norm / norm;
        for (double &weight : weights) {
            weight *= factor;
        }
    }
}

void gpmp::ml::Regularize::weight_decay_regularization(
    std::vector<double> &weights,
    double lambda) {
    for (double &weight : weights) {
        weight *= (1.0 - lambda);
    }
}

std::vector<std::vector<double>> gpmp::ml::Regularize::batch_normalization(
    const std::vector<std::vector<double>> &input_data,
    double epsilon,
    double scale,
    double shift) {
    std::vector<std::vector<double>> normalized_data;
    for (const auto &instance : input_data) {
        double mean = 0.0;
        for (double val : instance) {
            mean += val;
        }
        mean /= instance.size();

        double variance = 0.0;
        for (double val : instance) {
            variance += (val - mean) * (val - mean);
        }
        variance /= instance.size();

        double std_dev = sqrt(variance + epsilon);

        std::vector<double> normalized_instance;
        for (double val : instance) {
            double normalized_val = scale * ((val - mean) / std_dev) + shift;
            normalized_instance.push_back(normalized_val);
        }
        normalized_data.push_back(normalized_instance);
    }
    return normalized_data;
}

std::vector<std::vector<double>> gpmp::ml::Regularize::data_augmentation(
    const std::vector<std::vector<double>> &input_data,
    int augmentation_factor) {
    std::vector<std::vector<double>> augmented_data;
    std::random_device rd;
    std::mt19937 gen(rd());

    for (const auto &instance : input_data) {
        augmented_data.push_back(instance);
        for (int i = 1; i < augmentation_factor; ++i) {
            std::vector<double> augmented_instance = instance;
            std::shuffle(augmented_instance.begin(),
                         augmented_instance.end(),
                         gen);
            augmented_data.push_back(augmented_instance);
        }
    }
    return augmented_data;
}
