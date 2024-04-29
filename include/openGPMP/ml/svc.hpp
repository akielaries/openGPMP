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

#ifndef SVC_HPP
#define SVC_HPP

#include <algorithm>
#include <random>
#include <vector>

namespace gpmp {

namespace ml {

/**
 * @class SVC
 * @brief Support Vector Classifier (SVC) for binary classification using
 * Stochastic Gradient Descent
 */
class SVC {
  public:
    /**
     * @brief Constructor for SVC class
     * @param C_ Regularization parameter (default: 1.0)
     * @param l_rate Learning rate for stochastic gradient descent (default:
     * 0.01)
     * @param max_iters Maximum number of iterations for training (default:
     * 1000)
     * @param tol Tolerance for convergence (default: 1e-4)
     */
    SVC(double C_ = 1.0,
        double l_rate = 0.01,
        int max_iters = 1000,
        double tol = 1e-4);

    /**
     * @brief Fit the SVC model to the training data
     * @param X_train Input features for training
     * @param y_train Labels for training
     */
    void fit(const std::vector<std::vector<double>> &X_train,
             const std::vector<int> &y_train);

    /**
     * @brief Predict labels for given test data
     * @param X_test Input features for prediction
     * @return Predicted labels
     */
    std::vector<int> predict(const std::vector<std::vector<double>> &X_test);

    /**
     * @brief Predict class probabilities for given test data
     * @param X_test Input features for prediction
     * @return Predicted class probabilities
     */
    std::vector<double>
    predict_proba(const std::vector<std::vector<double>> &X_test);

    /**
     * @brief Calculate the accuracy of the model on given test data
     * @param X_test Input features for evaluation
     * @param y_test True labels for evaluation
     * @return Accuracy of the model
     */
    double score(const std::vector<std::vector<double>> &X_test,
                 const std::vector<int> &y_test);

    /**
     * @brief Set the kernel type for the SVC
     * @param k_type Kernel type (eg, "linear")
     */
    void set_kernel(const std::string &k_type);

    /**
     * @brief Set the kernel parameters for the SVC
     * @param k_param Kernel parameter value
     */
    void set_kernel_parameters(double k_param);

    /**
     * @brief Set the random seed for reproducibility
     * @param seed Random seed
     */
    void set_random_state(int seed);

    /**
     * @brief Enable or disable verbose output during training
     * @param vbose Verbose flag
     */
    void set_verbose(bool vbose);

    /**
     * @brief Set the penalty type for regularization
     * @param p_type Penalty type (eg, "l2")
     */
    void set_penalty(const std::string &p_type);

    /**
     * @brief Perform k-fold cross-validation on the model
     * @param X Input features for cross-validation
     * @param y True labels for cross-validation
     * @param cv Number of folds (default: 5)
     * @return Average accuracy over the folds
     */
    double cross_val_score(const std::vector<std::vector<double>> &X,
                           const std::vector<int> &y,
                           int cv = 5);

    /**
     * @brief Perform grid search for hyperparameter tuning
     * @param X Input features for grid search
     * @param y True labels for grid search
     * @param C_values Candidate values for the regularization parameter
     * @param kernel_params Candidate values for the kernel parameter
     * @param cv Number of folds for cross-validation (default: 5)
     * @return Best hyperparameters found
     */
    std::vector<double> grid_search(const std::vector<std::vector<double>> &X,
                                    const std::vector<int> &y,
                                    const std::vector<double> &C_values,
                                    const std::vector<double> &kernel_params,
                                    int cv = 5);

    /**< Regularization parameter */
    double C;
    /**< Learning rate for stochastic gradient descent */
    double learning_rate;
    /**< Maximum number of iterations for training */
    int max_iterations;
    /**< Tolerance for convergence */
    double tolerance;
    /**< Kernel type for SVC */
    std::string kernel_type;
    /**< Kernel parameter for the selected kernel */
    double kernel_param;
    /**< Random seed for reproducibility */
    int random_state;
    /**< Verbose flag for training output */
    bool verbose;
    /**< Penalty type for regularization */
    std::string penalty_type;
    /**< Model weights */
    std::vector<double> weights;
    /**< Model bias */
    double bias;

    /**
     * @brief Compute the hinge loss for a given prediction and true label
     * @param prediction Predicted value
     * @param label True label
     * @return Hinge loss
     */
    double hinge_loss(double prediction, int label);

    /**
     * @brief Compute the total loss (including regularization) for the model
     * @param X Input features
     * @param y True labels
     * @return Total loss
     */
    double compute_loss(const std::vector<std::vector<double>> &X,
                        const std::vector<int> &y);

    /**
     * @brief Update weights and bias using stochastic gradient descent
     * @param X Input features
     * @param y True labels
     */
    void update_weights(const std::vector<std::vector<double>> &X,
                        const std::vector<int> &y);

    /**
     * @brief Compute the kernel function between two vectors
     * @param x1 First vector
     * @param x2 Second vector
     * @return Kernel value
     */
    double kernel(const std::vector<double> &x1, const std::vector<double> &x2);

    /**
     * @brief Compute the dot product between two vectors
     * @param x1 First vector
     * @param x2 Second vector
     * @return Dot product
     */
    double dot_product(const std::vector<double> &x1,
                       const std::vector<double> &x2);

    /**
     * @brief Sigmoid activation function
     * @param z Input value
     * @return Sigmoid value
     */
    double sigmoid(double z);

    /**
     * @brief Generate k-fold indices for cross-validation
     * @param num_instances Total number of instances
     * @param k Number of folds
     * @return Vector of fold sizes
     */
    std::vector<int> k_fold_indices(int num_instances, int k);

    /**
     * @brief Compute the accuracy of predictions
     * @param predictions Predicted labels
     * @param labels True labels
     * @return Accuracy
     */
    double accuracy(const std::vector<int> &predictions,
                    const std::vector<int> &labels);
};

} // namespace ml
} // namespace gpmp

#endif
