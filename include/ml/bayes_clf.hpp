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
 * Definitions for a family of Naive Bayes Classifiers
 */
#ifndef BAYES_CLF_HPP
#define BAYES_CLF_HPP
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

namespace gpmp {

namespace ml {

/**
 * @brief Bayes Classifier Class based on assumptions of independence
 */
class BayesClf {
  public:
    /**
     * @brief Additive smoothing parameter
     */
    double alpha;

    /**
     * @brief Whether to learn class prior probabilities or not
     */
    bool fit_prior;
    /**
     * @brief Map of class labels to their probabilities
     */
    std::unordered_map<std::string, double> class_probs;
    /**
     * @brief Map of class labels to their feature probabilities
     */
    std::unordered_map<std::string, std::vector<double>> feature_probs;
    /**
     * @brief Vector of class log priors
     */
    std::vector<double> class_log_prior;

    /**
     * @brief Constructor for BayesClf class
     * @param alpha Additive (Laplace/Lidstone) smoothing parameter
     * @param fit_prior Whether to learn class prior probabilities or not
     * @param class_prior Prior probabilities of the classes
     */
    BayesClf(double alpha_param = 1.0,
             bool fit_prior_param = true,
             const std::vector<double> &class_prior = {});

    /**
     * @brief Destructor for BayesClf class
     */
    ~BayesClf();
    /**
     * @brief Train the classifier with a set of labeled data
     * @param data A vector of vectors representing the training instances
     * @param labels A vector of strings representing the corresponding class
     * labels
     */
    void train(const std::vector<std::vector<double>> &data,
               const std::vector<std::string> &labels);

    /**
     * @brief Predict the class of a new data point
     * @param newData A vector of doubles representing the features of the new
     * data point
     * @return The predicted class label as a string
     */
    std::string predict(const std::vector<double> &newData) const;

    /**
     * @brief Display the learned probabilities
     * @note This method is for debugging purposes
     */
    void display() const;
};

/**
 * @class BayesBernoulli
 * @details Bernoulli Naive Bayes is a part of the Naive Bayes family.
 * It is based on the Bernoulli Distribution and accepts only binary
 * values, i.e., 0 or 1. If the features of the dataset are binary,
 * then we can assume that Bernoulli Naive Bayes is the algorithm to
 * be used.
 */
class BayesBernoulli {
  public:
    std::unordered_map<std::string, double> class_probs;
    std::unordered_map<std::string, std::unordered_map<size_t, double>>
        feat_probs;
    double alpha;

    /**
     * @brief Constructor for BayesBernoulli class
     * @param alpha Additive (Laplace/Lidstone) smoothing parameter
     */
    BayesBernoulli(double alpha_param = 1.0) : alpha(alpha_param) {
    }

    /**
     * @brief Destructor for BayesBernoulli class
     */
    ~BayesBernoulli() {
    }

    /**
     * @brief Train the classifier with a set of labeled data
     * @param data A vector of vectors representing the training instances
     * @param labels A vector of strings representing the corresponding class
     * labels
     */
    void train(const std::vector<std::vector<size_t>> &data,
               const std::vector<std::string> &labels);
    /**
     * @brief Predict the class of a new data point
     * @param newData A vector of size_t representing the features of the new
     * data point
     * @return The predicted class label as a string
     */
    std::string predict(const std::vector<size_t> &newData) const;

    /**
     * @brief Display the learned probabilities
     * @note This method is for debugging purposes
     */
    void display() const;
};

/**
 * @class BayesGauss
 * @details Classification technique that assumes that each parameter
 * (also called features or predictors) has an independent capacity of
 * predicting the output variable.
 */
class BayesGauss {
  public:
    std::unordered_map<std::string, double> class_probs;
    std::unordered_map<std::string, std::vector<double>> mean;
    std::unordered_map<std::string, std::vector<double>> variance;

    /**
     * @brief Constructor for BayesGauss class
     */
    BayesGauss() = default;

    /**
     * @brief Destructor for BayesGauss class
     */
    ~BayesGauss() = default;

    /**
     * @brief Train the classifier with a set of labeled data
     * @param data A vector of vectors representing the training instances
     * @param labels A vector of strings representing the corresponding class
     * labels
     */
    void train(const std::vector<std::vector<double>> &data,
               const std::vector<std::string> &labels);

    /**
     * @brief Predict the class of a new data point
     * @param newData A vector of doubles representing the features of the new
     * data point
     * @return The predicted class label as a string
     */
    std::string predict(const std::vector<double> &newData) const;

    /**
     * @brief Display the learned probabilities
     * @note This method is for debugging purposes
     */
    void display() const;

  private:
    /**
     * @brief Calculate the mean and variance for each class
     * @param data A vector of vectors representing the training instances
     * @param labels A vector of strings representing the corresponding class
     * labels
     */
    void mean_and_var(const std::vector<std::vector<double>> &data,
                      const std::vector<std::string> &labels);
};

/**
 * @class BayesMutliNom
 * @details Specific instance of a Naive Bayes classifier which uses a
 * multinomial distribution for each of the features.
 */
class BayesMultiNom {
  public:
    double alpha;
    bool fit_prior;
    std::unordered_map<std::string, double> class_probs;
    std::unordered_map<std::string, std::vector<double>> feature_probs;
    std::vector<double> class_log_prior;

    BayesMultiNom(double alpha_param = 1.0,
                  bool fit_prior_param = true,
                  const std::vector<double> &class_prior = {});

    ~BayesMultiNom();

    void train(const std::vector<std::vector<size_t>> &data,
               const std::vector<std::string> &labels);

    std::string predict(const std::vector<size_t> &new_data) const;

    void display() const;

  private:
    void calculate_class_log_priors();
};

} // namespace ml

} // namespace gpmp

#endif
