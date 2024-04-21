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
#include <algorithm>
#include <functional>
#include <numeric>
#include <openGPMP/ml/kfold.hpp>
#include <stdexcept>

gpmp::ml::Kfold::Kfold(int fold) : k(fold) {
}

gpmp::ml::Kfold::~Kfold() {
}

void gpmp::ml::Kfold::split_indices(int num_instances) {
    if (k <= 1 || num_instances <= 0) {
        throw std::invalid_argument(
            "Invalid value of k or number of instances.");
    }

    // Initialize fold_indices with k empty vectors
    fold_indices.clear();
    fold_indices.resize(k);

    // Assign indices to each fold
    int fold_size = num_instances / k;
    int remainder = num_instances % k;
    int start_index = 0;
    for (int i = 0; i < k; ++i) {
        int fold_length = fold_size + (i < remainder ? 1 : 0);
        std::vector<int> indices(fold_length);
        std::iota(indices.begin(), indices.end(), start_index);
        fold_indices[i] = indices;
        start_index += fold_length;
    }
}

void gpmp::ml::Kfold::perform_cross_validation(
    std::function<void(int, int)> train_and_test_func) {
    if (fold_indices.empty()) {
        throw std::logic_error("Indices not split. Call split_indices before "
                               "performing cross-validation.");
    }

    for (int i = 0; i < k; ++i) {
        // Use fold i as the validation set, train on all other folds
        std::vector<int> validation_indices = fold_indices[i];
        for (int j = 0; j < k; ++j) {
            if (j != i) {
                for (int index : fold_indices[j]) {
                    train_and_test_func(j, index);
                }
            }
        }
    }
}
