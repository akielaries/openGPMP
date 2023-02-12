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
 *
 * @brief Miscellaneous utilities methods related to openMTPK
 *
 */
#ifndef UTILS_HPP
#define UTILS_HPP

#include "linalg/matrix.hpp"
#include <string>
#include <tuple>
#include <vector>

using namespace mtpk;

namespace mtpk {

/**
 * @class Data
 */
class Data {
    public:
    /**
     * std::vector<std::vector<double>> is a 2D vector which is a
     * Matrix. We could define it with Matrix class
     */

    std::tuple<std::vector<std::vector<double>>, std::vector<double>>
        load();

    std::tuple<std::vector<std::vector<double>>,
               std::vector<std::vector<double>>>
        load();

    std::tuple<std::vector<std::vector<double>>, std::vector<double>>
        load();

    std::tuple<std::vector<double>, std::vector<double>> load();

    void setData(int k, std::string fileName,
                 std::vector<std::vector<double>> &inputSet,
                 std::vector<double> &outputSet);

    void printData(std::vector<std::string> inputName,
                   std::vector<std::vector<double>> inputSet);

    void printData(std::vector<std::string> inputName,
                   std::string outputName,
                   std::vector<std::vector<double>> inputSet,
                   std::vector<double> outputSet);

    void set_input_names(std::string file_name,
                         std::vector<std::string> &input_names);

    std::vector<std::vector<double>>
        feature_scaling(std::vector<std::vector<double>> X);

    std::vector<std::vector<double>>
        one_rep(std::vector<double> temp_output_set, int n_class);

    std::vector<double>
        one_rep_reverse(std::vector<std::vector<double>> temp_output_set);

    std::vector<char> split(std::string text);
    std::vector<std::string> splitSentences(std::string data);
    std::vector<std::string> removeSpaces(std::vector<std::string> data);
    std::vector<std::string> removeNullByte(std::vector<std::string> data);
    std::vector<std::string> segment(std::string text);
};

// exponentiate

// square root

// cube root

/**
 * @class OutlierFinder
 * @brief Finds outliers in models
 */
class OutlierFinder {
    public:
    // Cnstr
    OutlierFinder(int threshold);

    std::vector<std::vector<double>>
        modelSetTest(std::vector<std::vector<double>> inputSet);
    std::vector<double> modelTest(std::vector<double> inputSet);

    // Variables required
    int threshold;
};

} // namespace mtpk

#endif
