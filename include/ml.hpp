/**
 * @file
 *
 * @brief openMTPK MACHINE/DEEP LEARNING MODULE
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
