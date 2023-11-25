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
 * @brief User API for OpenGPMP MACHINE/DEEP LEARNING MODULE
 *
 * @details This file serves as the core header for the Machine & Deep
 * Learning module. This header includes the following :
 *  - Regression
 *      * Linear
 *      * Logistic
 *      * Gausian
 *      * Polynomial
 *      * Lasso
 *      * Ridge
 *  - Classifiers
 *      * Bayes Classification
 *      * Nearest Neighbor
 *      * Decision Tree
 *      * Random Forest
 *      * Support Vector
 *  - Resampling
 *      * Cross-Validation
 *      * Bootstrap
 *      * Permutation Test
 *  - Neural Networks
 *      * Naive
 *      * Multi-layer Perceptron
 *      * Bayes
 *      * Kohonen (Self-Organizing Map)
 */

// <! Inspired from Machine Learning research, papers,        !>
// <! textbooks Scikit-learn, Tensorflow, ML++ and much more. !>

#ifndef ML_HPP
#define ML_HPP

/**
 * @brief \b ML \b Module \b Utilities
 * Trainers, Testers, Initalizers
 */
#define UTILS
#include "ml/utils.hpp"

/**
 * @brief \b Regression \b Algorithms
 * @details includes :
 *  * Linear Regression
 *
 * @note Some cases of Regression are innately Classification
 * algorithms
 *
 * @todo
 *  * logreg
 *  * gausreg
 *  * polyreg
 *  * lassoreg
 *  * ridgereg
 */
#define REGRESSION
#include "ml/linreg.hpp"
// #include "ml/logreg.hpp"
// #include "ml/gausreg.hpp"
// #include "ml/polyreg.hpp"
// #include "ml/lassoreg.hpp"
// #include "ml/ridgereg.hpp"
/*****************************************************************************/

/**
 * @brief \b Classification \b Algorithms
 * @details includes :
 *  * Bayes Classifier
 *  * Nearest Neighbor
 *
 * @note These algorithms are tightly coupled with Regression
 * algorithms
 *
 * @todo
 *  * Decision Tree
 *  * Random Forest
 *  * Support Vector
 */
#define CLASSIFICATION
// #include "ml/bayes_clf.hpp"
// #include "ml/nearest_neighbor.hpp"
// #include "ml/decision_tree"
// #include "ml/rand_forest"
// #include "ml/support_vector"
/*****************************************************************************/

/**
 * @brief \b Resampling \b Techniques
 * @details includes :
 *  * K-Fold Cross-Validation
 *
 * @todo
 *  * Bootstrap
 *  * Permutation Test
 */
#define RESAMPLING
// #include "ml/k-foldCV.hpp"
// #include "ml/bootstrap.hpp"
// #include "ml/perm_test.hpp"

/*****************************************************************************/

/**
 * @brief \b Neural \b Networks
 * @details includes :
 *  * Naive Network
 *  * Bayes Network
 *  * Kohonen Network
 *  * Multi-Layer Perceptron
 */
#define NEURAL_NETWORKS
// #include "ml/naive_net.hpp"
// #include "ml/bayes_net.hpp"
// #include "ml/kohonen_net.hpp"
#include "ml/mlp_net.hpp"
/*****************************************************************************/
/**
 * @brief \b Statistics
 * @details Machine Learning and Statistics are mostly one in the same
 * includes :
 *
 */
#define STATISTICS
/*****************************************************************************/

#endif
