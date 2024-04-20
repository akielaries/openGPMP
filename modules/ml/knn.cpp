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

#include "../../include/ml/knn.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <unordered_map>

gpmp::ml::KNN::KNN() {
}

gpmp::ml::KNN::~KNN() {
}

void gpmp::ml::KNN::train(
    const std::vector<std::vector<double>> &_training_data,
    const std::vector<int> &_labels) {
    if (_training_data.size() != _labels.size() || _training_data.empty()) {
        throw std::invalid_argument("Invalid training data or labels.");
    }

    this->training_data = _training_data;
    this->labels = _labels;
}

int gpmp::ml::KNN::predict(const std::vector<double> &input_vector, int k) {
    if (training_data.empty() || labels.empty()) {
        throw std::logic_error(
            "Model not trained. Call train() before predict.");
    }

    if (input_vector.size() != training_data[0].size()) {
        throw std::invalid_argument("Invalid input vector size.");
    }

    // if (k <= 0 || k > training_data.size()) {
    if (k <= 0 || static_cast<size_t>(k) > training_data.size()) {
        throw std::invalid_argument("Invalid value of k.");
    }

    // Calculate distances and store index-label pairs
    std::vector<std::pair<double, int>> distances;
    for (size_t i = 0; i < training_data.size(); ++i) {
        double distance =
            calculateEuclideanDistance(input_vector, training_data[i]);
        distances.emplace_back(distance, labels[i]);
    }

    // Sort distances in ascending order
    std::sort(
        distances.begin(),
        distances.end(),
        [](const std::pair<double, int> &a, const std::pair<double, int> &b) {
            return a.first < b.first;
        });

    // Count votes for each label among the k nearest neighbors
    std::unordered_map<int, int> label_counts;
    for (int i = 0; i < k; ++i) {
        label_counts[distances[i].second]++;
    }

    // Find the label with the maximum votes
    int max_votes = -1;
    int predicted_label = -1;
    for (const auto &entry : label_counts) {
        if (entry.second > max_votes) {
            max_votes = entry.second;
            predicted_label = entry.first;
        }
    }

    return predicted_label;
}

double
gpmp::ml::KNN::calculateEuclideanDistance(const std::vector<double> &vec1,
                                          const std::vector<double> &vec2) {
    double distance = 0.0;
    for (size_t i = 0; i < vec1.size(); ++i) {
        double diff = vec1[i] - vec2[i];
        distance += diff * diff;
    }
    return std::sqrt(distance);
}
