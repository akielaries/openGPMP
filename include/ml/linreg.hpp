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

/*
 * Linear regression is a statistical method for modeling
 * relationships between a dependent variable with a given set of
 * independent variables.
 */

#ifndef LINREG_H
#define LINREG_H
#include <cstdint>
#include <stdio.h>
#include <vector>

namespace gpmp {

namespace ml {

class LinearRegression {
    // Dynamic array which is going to contain all (i-th x)
    std::vector<long double> x;
    // Dynamic array which is going to contain all (i-th y)
    std::vector<long double> y;
    // Store the coefficient/slope in the best fitting line
    long double coeff;
    // Store the constant term in the best fitting line
    long double constant;
    // Contains sum of product of all (i-th x) and (i-th y)
    long double sum_xy;
    // Contains sum of all (i-th x)
    long double sum_x;
    // Contains sum of all (i-th y)
    long double sum_y;
    // Contains sum of square of all (i-th x)
    long double sum_x_square;
    // Contains sum of square of all (i-th y)
    long double sum_y_square;

  public:
    LinearRegression();
    /*{
            coeff;
            constant;
            sum_y;
            sum_y_square;
            sum_x_square;
            sum_x;
            sum_xy;
        }*/

    // Function that calculate the coefficient/slope of the best
    // fitting line
    void calculate_coeffecient();
    /*
     * Member function that will calculate the constant term of the
     * best fitting line
     */
    void calculate_constant();
    // Function that return the number of entries (xi, yi) in the data
    // set
    int64_t data_size();
    // Function that return the coefficient/slope of the best fitting
    // line
    long double return_coeffecient();
    // Function that return the constant term of the best fitting line
    long double return_constant();
    // Function that print the best fitting line
    void best_fit();
    // Function to take input from the dataset
    void get_input(int64_t n);
    // Function to show the data set
    void show_data();
    // Function to predict the value corresponding to some input
    long double predict(long double x);
    // Function that returns overall sum of square of errors
    long double error_square();
    /*
     * Functions that return the error i.e the difference between the
     * actual value and value predicted by our model
     */
    long double error_in(long double num);
    // function that calculates the number of rows in a file
    int64_t num_rows(const char *input);
};

} // namespace ml

} // namespace gpmp

#endif
