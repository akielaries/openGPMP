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

#ifndef KFOLD_HPP
#define KFOLD_HPP

#include <functional>
#include <vector>

namespace gpmp {

namespace ml {

/**
 * @class Kfold
 * @brief Represents a k-fold cross-validation utility
 */
class Kfold {
  public:
    /**
     * @brief Constructor for the Kfold class
     * @param k The number of folds for cross-validation
     */
    Kfold(int k);

    /**
     * @brief Destructor for the Kfold class
     */
    ~Kfold();

    /**
     * @brief Splits the indices of instances into k folds for cross-validation
     * @param num_instances The total number of instances
     * @throw std::invalid_argument if k or num_instances is invalid
     */
    void split_indices(int num_instances);

    /**
     * @brief Performs k-fold cross-validation using the provided training and
     * testing function
     * @param train_and_test_func The function that trains and tests the model
     * on given folds The function should take two integers as parameters: the
     * index of the training fold and the index of the testing instance
     * @throw std::logic_error if indices are not split before performing
     * cross-validation
     */
    void
    perform_cross_validation(std::function<void(int, int)> train_and_test_func);

  private:
    /**< The number of folds for cross-validation */
    int k;
    /**< The indices of instances grouped into k folds */
    std::vector<std::vector<int>> fold_indices;
};
}

}

#endif
