/*************************************************************************
 *
 *  Project
 *                        __  __ _______ _____  _  __
 *                       |  \/  |__   __|  __ \| |/ /
 *  ___  _ __   ___ _ __ | \  / |  | |  | |__) | ' /
 * / _ \| '_ \ / _ \ '_ \| |\/| |  | |  |  ___/|  <
 *| (_) | |_) |  __/ | | | |  | |  | |  | |    | . \
 * \___/| .__/ \___|_| |_|_|  |_|  |_|  |_|    |_|\_\
 *      | |
 *      |_|
 *
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
#include <stdio.h>
#include <vector>

namespace gpmp {

namespace ml {

/**
 * @brief Summary data structure responsible for returning results
 */
typedef struct summary {
    std::vector<std::vector<long double>> mean_stdev;
    long double class_prob;
} summary;

/**
 * @brief Bayes Classifier Class based on assumptions of independence
 */
class BayesClf {
  private:
    std::vector<class_summary> Summary;
    std::vector<long double> unique_label;

  public:
    void fit(std::vector<std::vector<long double>> dataset);
    int64_t predict(const std::vector<long double> &test_data);
};
summary gen_summ(std::vector<std::vector<long double>> dataset,
                 long double class_label);

long double prob_by_summ(const std::vector<long double> &test_data,
                         const class_summary &summary);

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
    BayesBernoulli(std::vector<std::vector<double>> inputSet,
                   std::vector<double> outputSet);
    std::vector<double> modelSetTest(std::vector<std::vector<double>> X);
    double modelTest(std::vector<double> x);
    double score();

  private:
    void computeVocab();
    void computeTheta();
    void Evaluate();

    // Model Params
    double prior_1 = 0;
    double prior_0 = 0;

    std::vector<std::map<double, int>> theta;
    std::vector<double> vocab;
    int class_num;

    // Datasets
    std::vector<std::vector<double>> inputSet;
    std::vector<double> outputSet;
    std::vector<double> y_hat;
};

/**
 * @class BayesGauss
 * @details Classification technique that assumes that each parameter
 * (also called features or predictors) has an independent capacity of
 * predicting the output variable.
 */
class BayesGauss {
  public:
    BayesGauss(std::vector<std::vector<double>> inputSet,
               std::vector<double> outputSet, int class_num);

    std::vector<double> modelSetTest(std::vector<std::vector<double>> X);

    double modelTest(std::vector<double> x);
    double score();

  private:
    void Evaluate();

    int class_num;

    std::vector<double> priors;
    std::vector<double> mu;
    std::vector<double> sigma;

    std::vector<std::vector<double>> inputSet;
    std::vector<double> outputSet;

    std::vector<double> y_hat;
};

/**
 * @class BayesMutliNom
 * @details Specific instance of a Naive Bayes classifier which uses a
 * multinomial distribution for each of the features.
 */

class BayesMutliNom {
  public:
    BayesMutliNom(std::vector<std::vector<double>> inputSet,
                  std::vector<double> outputSet, int class_num);

    std::vector<double> modelSetTest(std::vector<std::vector<double>> X);

    double modelTest(std::vector<double> x);
    double score();

  private:
    void computeTheta();
    void Evaluate();

    // Model Params
    std::vector<double> priors;

    std::vector<std::map<double, int>> theta;
    std::vector<double> vocab;
    int class_num;

    // Datasets
    std::vector<std::vector<double>> inputSet;
    std::vector<double> outputSet;
    std::vector<double> y_hat;
};

} // namespace ml

} // namespace gpmp

#endif
