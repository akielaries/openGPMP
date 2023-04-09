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

/*
 * header for cross-validation + k-fold cross-validation
 * implementations in C++
 */

#ifndef KFOLDCV_H
#define KFOLDCV_H
#include <random>
#include <vector>

using namespace std;

namespace mtpk {

class NearestNeighbor {
  public:
    bool comparison(Company &lhs, Company &rhs);

    long double euclideanDistance(Company &lhs, Company &test);

    long double manhattanDistance(Company &lhs, Company &test);

    void fillDistances(vector<Company> &data, Company &test,
                       long double (*distanceFunction)(Company &,
                                                       Company &));

    bool KNN(vector<Company> &data, Company &test, int64_t k,
             long double (*distanceFunction)(Company &, Company &));
};

} // namespace mtpk

#endif
