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

#include "../../include/ml/bayes_clf.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

gpmp::ml::BayesClf::BayesClf(double alpha,
                             bool fit_prior,
                             const std::vector<double> &class_prior)
    : alpha(alpha), fit_prior(fit_prior),
      class_log_prior(class_prior.begin(), class_prior.end()) {
}

gpmp::ml::BayesClf::~BayesClf() {
}

void gpmp::ml::BayesClf::train(const std::vector<std::vector<double>> &data,
                               const std::vector<std::string> &labels) {
    // Count class occurrences
    for (const auto &label : labels) {
        class_probs[label] += 1.0;
    }

    // Count feature occurrences for each class
    for (size_t i = 0; i < data.size(); ++i) {
        const std::string &label = labels[i];
        const std::vector<double> &features = data[i];

        class_probs[label] += 1.0;

        for (size_t j = 0; j < features.size(); ++j) {
            feature_probs[label][j] += features[j];
        }
    }

    // Calculate class probabilities and feature probabilities
    double smoothing_factor = alpha * 2.0;
    for (const auto &entry : class_probs) {
        const std::string &label = entry.first;
        double class_count = entry.second;

        // Calculate class probability
        class_probs[label] =
            (class_count + alpha) / (data.size() + smoothing_factor);

        // Calculate feature probabilities
        for (size_t j = 0; j < feature_probs[label].size(); ++j) {
            feature_probs[label][j] = (feature_probs[label][j] + alpha) /
                                      (class_count + smoothing_factor);
        }
    }

    // Calculate class log priors
    if (fit_prior) {
        double total = std::accumulate(
            class_probs.begin(),
            class_probs.end(),
            0.0,
            [](double sum, const auto &entry) { return sum + entry.second; });

        for (auto &entry : class_probs) {
            entry.second /= total;
        }

        std::transform(
            class_probs.begin(),
            class_probs.end(),
            class_log_prior.begin(),
            [total](const auto &entry) { return log(entry.second); });
    }
}

std::string
gpmp::ml::BayesClf::predict(const std::vector<double> &new_data) const {
    double max_prob = -std::numeric_limits<double>::infinity();
    std::string predicted_class;

    for (const auto &entry : class_probs) {
        const std::string &label = entry.first;
        double probability = log(entry.second);

        for (size_t j = 0; j < new_data.size(); ++j) {
            probability += new_data[j] * log(feature_probs.at(label).at(j));
        }

        if (probability > max_prob) {
            max_prob = probability;
            predicted_class = label;
        }
    }

    return predicted_class;
}

void gpmp::ml::BayesClf::display() const {
    std::cout << "Class Probabilities:\n";
    for (const auto &entry : class_probs) {
        std::cout << entry.first << ": " << entry.second << "\n";
    }

    std::cout << "\nFeature Probabilities:\n";
    for (const auto &class_entry : feature_probs) {
        std::cout << class_entry.first << ":\n";
        for (size_t j = 0; j < class_entry.second.size(); ++j) {
            std::cout << "  Feature " << j << ": " << class_entry.second[j]
                      << "\n";
        }
    }

    std::cout << "\nClass Log Priors:\n";
    for (const auto &logPrior : class_log_prior) {
        std::cout << logPrior << "\n";
    }
}
void gpmp::ml::BayesBernoulli::train(
    const std::vector<std::vector<size_t>> &data,
    const std::vector<std::string> &labels) {
    size_t numInstances = data.size();
    size_t num_feats = data[0].size();

    for (size_t i = 0; i < numInstances; ++i) {
        std::string classLabel = labels[i];

        // update class probabilities
        class_probs[classLabel] += 1.0;

        // update feature probabilities
        for (size_t j = 0; j < num_feats; ++j) {
            feat_probs[classLabel][j] += data[i][j];
        }
    }

    // laplace smoothing
    double smoothing_factor = alpha * 2.0;
    for (auto &entry : class_probs) {
        entry.second =
            (entry.second + alpha) / (numInstances + smoothing_factor);
    }

    for (auto &class_entry : feat_probs) {
        for (auto &feat_entry : class_entry.second) {
            feat_entry.second =
                (feat_entry.second + alpha) /
                (class_probs[class_entry.first] + smoothing_factor);
        }
    }
}

// predict the class of a new data point
std::string
gpmp::ml::BayesBernoulli::predict(const std::vector<size_t> &new_data) const {
    double max_prob = -std::numeric_limits<double>::infinity();
    std::string predicted_class;

    for (const auto &class_entry : class_probs) {
        double probability = log(class_entry.second);

        for (size_t i = 0; i < new_data.size(); ++i) {
            probability +=
                new_data[i] * log(feat_probs.at(class_entry.first).at(i));
        }

        if (probability > max_prob) {
            max_prob = probability;
            predicted_class = class_entry.first;
        }
    }

    return predicted_class;
}

// Print learned probabilities (for debugging)
void gpmp::ml::BayesBernoulli::display() const {
    std::cout << "Class Probabilities:\n";
    for (const auto &entry : class_probs) {
        std::cout << entry.first << ": " << entry.second << "\n";
    }

    std::cout << "\nFeature Probabilities:\n";
    for (const auto &class_entry : feat_probs) {
        std::cout << class_entry.first << ":\n";
        for (const auto &feat_entry : class_entry.second) {
            std::cout << "  Feature " << feat_entry.first << ": "
                      << feat_entry.second << "\n";
        }
    }
}
