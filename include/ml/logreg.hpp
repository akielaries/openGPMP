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
 * seen here : https://akielaries.github.io/openMTPK/ along with
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
 * @files
 *
 * @brief Logistic Regression
 */
#ifndef LOGREG_hpp
#define LOGREG_hpp

#include <string>
#include <vector>

namespace mtpk {

class Logreg {
  public:
    Logreg(std::vector<std::vector<double>> inputSet,
           std::vector<double> outputSet, std::string reg = "None",
           double lambda = 0.5, double alpha = 0.5);

    std::vector<double> modelSetTest(std::vector<std::vector<double>> X);
    double modelTest(std::vector<double> x);

    void gradientDescent(double learning_rate, int max_epoch, bool UI = 1);

    void MLE(double learning_rate, int max_epoch, bool UI = 1);

    void SGD(double learning_rate, int max_epoch, bool UI = 1);

    void MBGD(double learning_rate, int max_epoch, int mini_batch_size,
              bool UI = 1);

    double score();
    void save(std::string fileName);

  private:
    double Cost(std::vector<double> y_hat, std::vector<double> y);

    std::vector<double> Evaluate(std::vector<std::vector<double>> X);

    double Evaluate(std::vector<double> x);

    void forwardPass();

    std::vector<std::vector<double>> inputSet;
    std::vector<double> outputSet;
    std::vector<double> y_hat;
    std::vector<double> weights;
    double bias;

    int n;
    int k;
    double learning_rate;
    // Regularization Params
    std::string reg;
    double lambda; /* Regularization Parameter */
    double alpha;  /* This is the controlling param for Elastic Net*/
};

} // namespace mtpk
#endif
