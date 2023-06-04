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
 * @brief K-Nearest Neighbors Clustering
 */
#ifndef KNN_hpp
#define KNN_hpp

#include <vector>

namespace gpmp {

namespace ml {

class kNN {
  public:
    kNN(std::vector<std::vector<double>> inputSet,
        std::vector<double> outputSet, int k);

    std::vector<double> modelSetTest(std::vector<std::vector<double>> X);
    int modelTest(std::vector<double> x);
    double score();

  private:
    // Private Model Functions
    std::vector<double> nearestNeighbors(std::vector<double> x);
    int determineClass(std::vector<double> knn);

    // Model Inputs and Parameters
    std::vector<std::vector<double>> inputSet;
    std::vector<double> outputSet;
    int k;
};

} // namespace ml

} // namespace gpmp

#endif
