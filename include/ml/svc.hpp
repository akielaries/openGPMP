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
 * @file
 * @brief Support Vector Classifier
 */
#define SVC_HPP

#include <string>
#include <vector>

namespace mtpk {

namespace ml {

class SVC {
  public:
    SVC(std::vector<std::vector<double>> inputSet,
        std::vector<double> outputSet, double C);
    std::vector<double> modelSetTest(std::vector<std::vector<double>> X);
    double modelTest(std::vector<double> x);
    void gradientDescent(double learning_rate, int max_epoch, bool UI = 1);
    void SGD(double learning_rate, int max_epoch, bool UI = 1);
    void MBGD(double learning_rate, int max_epoch, int mini_batch_size,
              bool UI = 1);
    double score();
    void save(std::string fileName);

  private:
    double Cost(std::vector<double> y_hat, std::vector<double> y,
                std::vector<double> weights, double C);

    std::vector<double> Evaluate(std::vector<std::vector<double>> X);
    std::vector<double> propagate(std::vector<std::vector<double>> X);
    double Evaluate(std::vector<double> x);
    double propagate(std::vector<double> x);
    void forwardPass();

    std::vector<std::vector<double>> inputSet;
    std::vector<double> outputSet;
    std::vector<double> z;
    std::vector<double> y_hat;
    std::vector<double> weights;
    double bias;

    double C;
    int n;
    int k;

    // UI Portion
    void UI(int epoch, double cost_prev);
};

} // namespace ml

} // namespace mtpk

#endif
