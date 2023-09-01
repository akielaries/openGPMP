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
    /**
     * @brief Constructor for LinearRegression.
     */
    LinearRegression();

    /**
     * @brief Calculate the coefficient/slope of the best fitting line.
     */
    void calculate_coeffecient();

    /**
     * @brief Calculate the constant term of the best fitting line.
     */
    void calculate_constant();

    /**
     * @brief Get the number of entries (xi, yi) in the data set.
     * @return Number of data entries.
     */
    int64_t data_size();

    /**
     * @brief Get the coefficient/slope of the best fitting line.
     * @return Coefficient/slope.
     */
    long double return_coeffecient();

    /**
     * @brief Get the constant term of the best fitting line.
     * @return Constant term.
     */
    long double return_constant();

    /**
     * @brief Print the equation of the best fitting line.
     */
    void best_fit();

    /**
     * @brief Read input data from a file.
     * @param file Path to the input file.
     */
    void get_input(const char *file);

    /**
     * @brief Display the data set.
     */
    void show_data();

    /**
     * @brief Predict a value based on the input.
     * @param x Input value.
     * @return Predicted value.
     */
    long double predict(long double x);

    /**
     * @brief Calculate the sum of square of errors.
     * @return Sum of square of errors.
     */
    long double error_square();

    /**
     * @brief Calculate the error for a given input.
     * @param num Input value.
     * @return Error for the input.
     */
    long double error_in(long double num);

    /**
     * @brief Calculate the number of rows in a file.
     * @param input Path to the input file.
     * @return Number of rows in the file.
     */
    int64_t num_rows(const char *input);

};

} // namespace ml

} // namespace gpmp

#endif
