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
 * @brief Logistic Regression
 */
#ifndef LOGREG_hpp
#define LOGREG_hpp

#include <string>
#include <vector>

namespace gpmp {

namespace ml {

/**
 * @class LogReg
 * @brief Represents a Logistic Regression classifier
 */
class LogReg {
  public:
    /**
     * @brief Constructor for the LogReg class
     * @param l_rate The learning rate for gradient descent optimization
     * (default: 001)
     * @param num_iters The number of iterations for gradient descent (default:
     * 1000)
     * @param lda The regularization parameter lambda (default: 001)
     */
    LogReg(double l_rate = 001, int num_iters = 1000, double lda = 001);

    /**
     * @brief Destructor for the LogReg class
     */
    ~LogReg();

    /**
     * @brief Trains the logistic regression model on the given training data
     * @param X_train The feature matrix of the training data
     * @param y_train The labels of the training data
     */
    void train(const std::vector<std::vector<double>> &X_train,
               const std::vector<int> &y_train);

    /**
     * @brief Predicts the class labels for the given test data
     * @param X_test The feature matrix of the test data
     * @return A vector of predicted class labels
     */
    std::vector<int> classify(const std::vector<std::vector<double>> &X);

    /**
     * @brief Computes the predicted probabilities for the given test data
     * @param X_test The feature matrix of the test data
     * @return A vector of predicted probabilities
     */
    std::vector<double> predict(const std::vector<std::vector<double>> &X_test);
    
    /**
     * @brief Computes the accuracy of the model on the given test data
     * @param X_test The feature matrix of the test data
     * @param y_test The true labels of the test data
     * @return The accuracy of the model
     */
    double accuracy(const std::vector<std::vector<double>> &X_test,
                    const std::vector<int> &y_test);

    /**
     * @brief Computes the accuracy of the model on the given test data
     * @param predictions The predicted labels of the test data
     * @param y_test The true labels of the test data
     * @return The accuracy of the model
     */
    double accuracy(const std::vector<double> &predictions,
                    const std::vector<int> &y_test);

    /*
     * @brief Computes the precision of the model on the given test data
     * @param X_test The feature matrix on the test data
     * @param y_test The true labels of the test data
     * @return The precision of the model
     */
    double precision(const std::vector<std::vector<double>> &X_test,
                     const std::vector<int> &y_test);

    /*
     * @brief Computes the recall of the model on the given test data
     * @param X_test The feature matrix on the test data
     * @param y_test The true labels of the test data
     * @return The recall of the model
     */
    double recall(const std::vector<std::vector<double>> &X_test,
                     const std::vector<int> &y_test);
    /**
     * @brief Performs feature scaling on the input feature matrix
     * @param X The feature matrix to be scaled
     */
    void feature_scaling(std::vector<std::vector<double>> &X);

    double learning_rate; /**< The learning rate for gradient descent
                             optimization */
    int num_iterations;   /**< The number of iterations for gradient descent */
    double lambda;        /**< The regularization parameter lambda */
    std::vector<double>
        weights; /**< The weights learned by the logistic regression model */

    /**
     * @brief Computes the sigmoid function value for the given input
     * @param z The input value
     * @return The sigmoid of z
     */
    double sigmoid(double z);

    /**
     * @brief Computes the cost function value for the given input data and
     * labels
     * @param X The feature matrix of the data
     * @param y The labels of the data
     * @return The value of the cost function
     */
    double cost_function(const std::vector<std::vector<double>> &X,
                         const std::vector<int> &y);
};

} // namespace ml

} // namespace gpmp
#endif
