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
 * relationships between a dependent variable with a given
 * independent variable. Multiple linear regression  follows
 * the same idea with multiple or a set of independent
 * variables.
 */

#ifndef LINREG_HPP
#define LINREG_HPP
#include "../core/datatable.hpp"
#include "../core/utils.hpp"
#include <cstdint>
#include <vector>

namespace gpmp {

namespace ml {

class LinearRegression {
  public:
    /** Dynamic array which is going to contain all (i-th x) */
    std::vector<long double> x;
    /** Dynamic array which is going to contain all (i-th y) */
    std::vector<long double> y;
    /** Store the coefficient/slope in the best fitting line */
    long double coeff;
    /** Store the constant term in the best fitting line */
    long double constant;
    /** Contains sum of product of all (i-th x) and (i-th y) */
    long double sum_xy;
    /** Contains sum of all (i-th x) */
    long double sum_x;
    /** Contains sum of all (i-th y) */
    long double sum_y;
    /** Contains sum of square of all (i-th x) */
    long double sum_x_square;
    /** Contains sum of square of all (i-th y) */
    long double sum_y_square;
    /** Vector holding x training data */
    std::vector<long double> x_train;
    /** Vector holding y training data */
    std::vector<long double> y_train;
    /** Vector holding x testing data */
    std::vector<long double> x_test;
    /** Vector holding y testing data */
    std::vector<long double> y_test;

    /**
     * @brief Constructor for LinearRegression.
     */
    LinearRegression();

    /**
     * @brief Calculates the coefficient/slope of the best fitting line.
     *
     * This function calculates the coefficient of the linear regression model
     * by analyzing the dataset.
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
     * @brief Calculates and displays the best fitting line based on training
     * data.
     *
     * This function calculates the best fitting line using the training data
     * and displays the result. If training data is empty, it will also handle
     * the case when the coefficients and constants are not calculated.
     */
    void best_fit();

    /**
     * @brief Sets the input data for the LinearRegression class from two
     * vectors.
     *
     * This function accepts vectors of independent and dependent variable
     * values and initializes the class variables.
     *
     * @param x_data The vector of independent variable values.
     * @param y_data The vector of dependent variable values.
     */
    void get_input(const std::vector<long double> &x_data,
                   const std::vector<long double> &y_data);

    /**
     * @brief Takes input data in the form of a DataTable and prepares it for
     * regression analysis.
     * @param data The DataTable containing the data.
     * @param columns The column names for the independent and dependent
     * variables.
     */
    void get_input(const gpmp::core::DataTableStr &data,
                   const std::vector<std::string> &columns);

    /**
     * @brief Takes input data from a file and prepares it for regression
     * analysis.
     * @param file The name of the file containing the data.
     */
    void get_input(const char *file);

    /**
     * @brief Splits the data into training and testing sets.
     *
     * This function splits the dataset into training and testing sets based on
     * the specified test size and random seed.
     *
     * @param test_size The proportion of data to be used for testing (between 0
     * and 1).
     * @param seed The random seed for shuffling the data.
     */
    void split_data(double test_size, unsigned int seed, bool shuffle);

    /**
     * @brief Display the data set.
     */
    void show_data();

    /**
     * @brief Predict a value based on the input.
     * @param x Input value.
     * @return Predicted value.
     */
    long double predict(long double x) const;

    /**
     * @brief Predict a value based on the input.
     * @param x Input value.
     * @param x_data X value data.
     * @return Predicted value.
     */
    long double predict(long double x, const std::vector<long double> &x_data);

    /**
     * @brief Calculates the error (residual) for a given independent variable
     * value.
     *
     * This function computes the difference between the actual dependent
     * variable value (y) and the predicted value based on the linear regression
     * model for a specified independent variable (x).
     *
     * @param num The independent variable value for which the error is
     * calculated.
     * @return The error (residual) between the actual and predicted values.
     */
    long double error_in(long double num);

    /**
     * @brief Calculates the error (residual) for a given independent variable
     * value using a dataset.
     *
     * This function computes the difference between the actual dependent
     * variable value (y) and the predicted value based on the linear regression
     * model for a specified independent variable (x).
     *
     * @param num The independent variable value for which the error is
     * calculated.
     * @param x_data The vector of independent variable values.
     * @param y_data The vector of actual dependent variable values.
     * @return The error (residual) between the actual and predicted values.
     */
    long double error_in(long double num,
                         const std::vector<long double> &x_data,
                         const std::vector<long double> &y_data);

    /**
     * @brief Calculates the sum of squared errors for the entire dataset.
     *
     * This function computes the sum of squared differences between the actual
     * dependent variable values (y) and the predicted values based on the
     * linear regression model for all data points.
     *
     * @return The sum of squared errors for the dataset.
     */
    long double error_square();

    /**
     * @brief Calculates the Mean Squared Error (MSE) for a dataset.
     *
     * The Mean Squared Error is a measure of the average squared differences
     * between the actual dependent variable values and the predicted values
     * based on the linear regression model.
     *
     * @param x_data The vector of independent variable values.
     * @param y_data The vector of actual dependent variable values.
     * @return The Mean Squared Error for the dataset. Returns -1 if input
     * vectors have different sizes.
     */
    long double mse(const std::vector<long double> &x_data,
                    const std::vector<long double> &y_data) const;

    /**
     * @brief Calculate the coefficient of determination (R-squared).
     *
     * The coefficient of determination, often referred to as R-squared, is a
     * statistical measure that represents the proportion of the variance in the
     * dependent variable (Y) that is predictable from the independent variable
     * (X). It quantifies the goodness of fit of the linear regression model to
     * the data.
     *
     * This function calculates the R-squared value for a linear regression
     * model using the provided dataset of independent variable values (x_data)
     * and dependent variable values (y_data).
     *
     * @param x_data A vector of independent variable values.
     * @param y_data A vector of corresponding dependent variable values.
     *
     * @return The R-squared value, which is a number between 0 and 1. A higher
     * R-squared value indicates a better fit of the model to the data.
     *
     * @note The input vectors (x_data and y_data) must have the same size.
     * @note An R-squared value of -1 is returned as an error indicator when the
     * input vectors have different sizes.
     * @note The function uses the linear regression model's predict() method to
     * make predictions for the independent variable values.
     */
    long double r_sqrd(const std::vector<long double> &x_data,
                       const std::vector<long double> &y_data) const;

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
