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
 * openGPMP implementation of Linear Regression
 */
#include "../../include/ml/linreg.hpp"
#include "../../include/core/datatable.hpp"
#include "../../include/core/utils.hpp"
#include <fstream>
#include <iostream>
#include <random>
#include <stdio.h>
#include <string>
#include <vector>

/** Logger class object*/
static gpmp::core::Logger _log_;

/*
 * Constructor to provide the default values to all the terms in the
 * object of class regression
 */
gpmp::ml::LinearRegression::LinearRegression() {
    coeff = 0;
    constant = 0;
    sum_y = 0;
    sum_y_square = 0;
    sum_x_square = 0;
    sum_x = 0;
    sum_xy = 0;
}

// Function that calculate the coefficient/slope of the best fitting
// line
void gpmp::ml::LinearRegression::calculate_coeffecient() {
    // get number of datapoints
    long double N = x.size();
    // calculate numerator and denominator
    long double numerator = (N * sum_xy - sum_x * sum_y);
    long double denominator = (N * sum_x_square - sum_x * sum_x);
    // calculate the coeffecient
    coeff = numerator / denominator;
}

/*
 * Member function that will calculate the constant term of the best
 * fitting line
 */
void gpmp::ml::LinearRegression::calculate_constant() {
    long double N = x.size();
    long double numerator = (sum_y * sum_x_square - sum_x * sum_xy);
    long double denominator = (N * sum_x_square - sum_x * sum_x);
    // calculate constant
    constant = numerator / denominator;
}

// Function that return the number of entries (xi, yi) in the data set
int64_t gpmp::ml::LinearRegression::data_size() {
    return x.size();
}

// Function that return the coefficient/slope of the best fitting line
long double gpmp::ml::LinearRegression::return_coeffecient() {
    if (coeff == 0) {
        calculate_coeffecient();
    }
    return coeff;
}

// Function that return the constant term of the best fitting line
long double gpmp::ml::LinearRegression::return_constant() {
    if (constant == 0) {
        calculate_constant();
    }
    return constant;
}

// Function to calculate and display the best fitting line
void gpmp::ml::LinearRegression::best_fit() {
    if (x_train.empty() || y_train.empty()) {
        // Check if training data is empty
        _log_.log(WARNING, "Training data is empty.");

        if (coeff == 0 && constant == 0) {
            // If coefficients are not calculated, calculate them
            calculate_coeffecient();
            calculate_constant();
        }
        // Display the best fitting line equation
        _log_.log(INFO,
                  "Best fitting line : y = " + std::to_string(coeff) + "x + " +
                      std::to_string(constant));
        return;
    }

    // Calculate the coefficients using the training data
    long double N = x_train.size();
    long double sum_xy_train = 0;
    long double sum_x_train = 0;
    long double sum_y_train = 0;
    long double sum_x_square_train = 0;

    for (size_t i = 0; i < N; i++) {
        // Calculate sums for the training data
        sum_xy_train += x_train[i] * y_train[i];
        sum_x_train += x_train[i];
        sum_y_train += y_train[i];
        sum_x_square_train += x_train[i] * x_train[i];
    }

    long double numerator = (N * sum_xy_train - sum_x_train * sum_y_train);
    long double denominator =
        (N * sum_x_square_train - sum_x_train * sum_x_train);

    // Calculate the coefficients of the best fitting line
    coeff = numerator / denominator;
    constant = (sum_y_train - coeff * sum_x_train) / N;
    // Display the best fitting line equation
    _log_.log(INFO,
              "Best fitting line : y = " + std::to_string(coeff) + "x + " +
                  std::to_string(constant));
}

// Function to accept input data in the form of two vectors
void gpmp::ml::LinearRegression::get_input(
    const std::vector<long double> &x_data,
    const std::vector<long double> &y_data) {
    // Clear existing data from x and y vectors
    x.clear();
    y.clear();
    // Initialize LinearRegression class variables
    sum_xy = 0;       /* Set x*y sum */
    sum_x = 0;        /* Set sum of x */
    sum_y = 0;        /* Set sum of y */
    sum_x_square = 0; /* Set sum of x squares */
    sum_y_square = 0; /* Set sum of y squares */

    if (x_data.size() != y_data.size()) {
        // Check if input vectors have the same size
        _log_.log(ERROR, "Input vectors must have the same size");
        return;
    }

    for (size_t i = 0; i < x_data.size(); i++) {
        // Append x and y values to x and y vectors
        x.push_back(x_data[i]);
        y.push_back(y_data[i]);
        // Update sum of (x * y)
        sum_xy += x_data[i] * y_data[i];
        // Update sum of x and y
        sum_x += x_data[i];
        sum_y += y_data[i];
        // Update sum of x squares and y squares
        sum_x_square += x_data[i] * x_data[i];
        sum_y_square += y_data[i] * y_data[i];
    }
}

// Function to accept input data from a DataTableStr
void gpmp::ml::LinearRegression::get_input(
    const gpmp::core::DataTableStr &data,
    const std::vector<std::string> &columns) {
    // Clear any existing data from x and y vectors
    x.clear();
    y.clear();
    sum_xy = 0;
    sum_x = 0;
    sum_y = 0;
    sum_x_square = 0;
    sum_y_square = 0;

    // Ensure that columns is not empty and has at least 2 elements
    if (columns.size() < 2) {
        _log_.log(ERROR, "Input vectors must have at least 2 column names.");
        return;
    }

    // Find the column indices for the specified column names
    std::vector<size_t> column_indices;
    for (const auto &column_name : columns) {
        bool found = false;
        for (size_t i = 0; i < data.first.size(); ++i) {
            if (data.first[i] == column_name) {
                column_indices.push_back(i);
                found = true;
                break;
            }
        }
        if (!found) {
            _log_.log(ERROR,
                      "Column '" + column_name +
                          "' not found in DataTableStr.");
            return;
        }
    }

    for (const auto &row : data.second) {
        try {
            long double xi = std::stold(row[column_indices[0]]);
            long double yi = std::stold(row[column_indices[1]]);
            // Append x and y values to x and y vectors
            x.push_back(xi);
            y.push_back(yi);
            // Update sum of (x * y)
            sum_xy += xi * yi;
            // Update sum of x and y
            sum_x += xi;
            sum_y += yi;
            // Update sum of x squares and y squares
            sum_x_square += xi * xi;
            sum_y_square += yi * yi;
        } catch (const std::exception &e) {
            // Handle parsing errors here
            _log_.log(ERROR, "Error parsing data: " + std::string(e.what()));
            continue;
        }
    }
}

// Function to accept input data from a file
void gpmp::ml::LinearRegression::get_input(const char *file) {
    int n = num_rows(file);
    for (int64_t i = 0; i < n; i++) {
        /*
         * In a csv file, all the values of xi and yi are separated by
         * commas
         */
        char comma;
        long double xi;
        long double yi;
        std::cin >> xi >> comma >> yi;
        // Update sum of (x * y)
        sum_xy += xi * yi;
        // Update sum of x and y
        sum_x += xi;
        sum_y += yi;
        // Update sum of x squares and y squares
        sum_x_square += xi * xi;
        sum_y_square += yi * yi;
        // Append x and y values to x and y vectors
        x.push_back(xi);
        y.push_back(yi);
    }
}

// Function to split data into training and testing sets
void gpmp::ml::LinearRegression::split_data(double test_size,
                                            unsigned int seed,
                                            bool shuffle) {
    if (x.empty() || y.empty()) {
        _log_.log(ERROR, "Training data is empty.");
        return;
    }

    if (test_size <= 0 || test_size >= 1) {
        _log_.log(ERROR, "Invalid `test_size`. Must be between 0 - 1.");
        return;
    }

    size_t data_size = x.size();
    size_t test_data_size = static_cast<size_t>(test_size * data_size);

    // Shuffle the data randomly if specified
    if (shuffle == true) {
        // Create vector of indices
        std::vector<size_t> indices(data_size);
        // Fill vector sequentially w/ `iota`
        std::iota(indices.begin(), indices.end(), 0);
        // Randomly shuffle vector indices from start to end
        std::shuffle(indices.begin(),
                     indices.end(),
                     std::default_random_engine(seed));

        // Clear training and testing data vectors
        x_train.clear();
        y_train.clear();
        x_test.clear();
        y_test.clear();

        // Split the data into training and testing sets based on shuffled
        // indices
        for (size_t i = 0; i < data_size; ++i) {
            if (i < test_data_size) {
                // Append x test vector with shuffled x value
                x_test.push_back(x[indices[i]]);
                y_test.push_back(y[indices[i]]);
            } else {
                // Append x training vector with suffled x value
                x_train.push_back(x[indices[i]]);
                y_train.push_back(y[indices[i]]);
            }
        }
    } else {
        // Without shuffling, split the data without changing its order by
        // assigning the first training element to the training set
        x_train.assign(x.begin(), x.begin() + data_size - test_data_size);
        y_train.assign(y.begin(), y.begin() + data_size - test_data_size);
        // Assign the 1+ testing elements to the testing test
        x_test.assign(x.begin() + data_size - test_data_size, x.end());
        y_test.assign(y.begin() + data_size - test_data_size, y.end());
    }
}

// Function to display the dataset
void gpmp::ml::LinearRegression::show_data() {
    for (int64_t i = 0; i < 62; i++) {
        printf("_");
    }
    printf("\n\n");
    printf("|%15s%5s %15s%5s%20s\n", "X", "", "Y", "", "|");

    // Display each data point in the dataset
    for (int64_t i = 0; uint64_t(i) < x.size(); i++) {
        printf("|%20Lf %20Lf%20s\n", x[i], y[i], "|");
    }

    for (int64_t i = 0; i < 62; i++) {
        printf("_");
    }
    printf("\n");
}

// Function to predict a value based on input x
long double gpmp::ml::LinearRegression::predict(long double x) const {
    return coeff * x + constant;
}

// Function to predict a value based on input x and a dataset
long double
gpmp::ml::LinearRegression::predict(long double x,
                                    const std::vector<long double> &x_data) {
    // Calculate the coefficient if not already calculated
    long double coeff = return_coeffecient();
    // Calculate the constant if not already calculated
    long double constant = return_constant();
    return coeff * x + constant;
}

// Function to calculate the error for a given value
long double gpmp::ml::LinearRegression::error_in(long double num) {
    for (int64_t i = 0; uint64_t(i) < x.size(); i++) {
        if (num == x[i]) {
            return (y[i] - predict(x[i]));
        }
    }
    return 0;
}

// Function to calculate the error for a given value and a dataset
long double
gpmp::ml::LinearRegression::error_in(long double num,
                                     const std::vector<long double> &x_data,
                                     const std::vector<long double> &y_data) {
    long double prediction = predict(num, x_data);
    // Find the corresponding y value for the input x
    for (size_t i = 0; i < x_data.size(); i++) {
        if (num == x_data[i]) {
            return y_data[i] - prediction;
        }
    }
    return 0;
}

// Function that returns the overall sum of the square of errors
long double gpmp::ml::LinearRegression::error_square() {
    long double ans = 0;

    // Iterate through each data point
    for (int64_t i = 0; uint64_t(i) < x.size(); i++) {
        // Calculate the square of the error (difference between predicted and
        // actual values)
        ans += ((predict(x[i]) - y[i]) * (predict(x[i]) - y[i]));
    }
    return ans; // Return the sum of squared errors
}

// Find the Mean Squared Error (MSE) of the given dataset
long double
gpmp::ml::LinearRegression::mse(const std::vector<long double> &x_data,
                                const std::vector<long double> &y_data) const {
    if (x_data.size() != y_data.size()) {
        // Check if input vectors have the same size
        return -1; // Return an error value
    }

    long double mse = 0.0;
    int64_t n = x_data.size();

    // Iterate through each data point
    for (int64_t i = 0; i < n; i++) {
        // Calculate the predicted value using the linear regression model
        long double predicted = predict(x_data[i]);
        // Calculate the error (difference between predicted and actual values)
        long double error = predicted - y_data[i];
        // Accumulate the squared error
        mse += error * error;
    }

    // Calculate the Mean Squared Error by dividing the accumulated squared
    // error by the number of data points
    return mse / static_cast<long double>(n);
}

// Determine an R^2 score value
long double gpmp::ml::LinearRegression::r_sqrd(
    const std::vector<long double> &x_data,
    const std::vector<long double> &y_data) const {
    if (x_data.size() != y_data.size()) {
        // Check if input vectors have the same size
        _log_.log(ERROR, "Input vectors must have the same size.");
        return -1; // Return an error value
    }

    long double total_sum_of_squares = 0.0;
    long double sum_of_squared_errors = 0.0;
    int64_t n = x_data.size();

    long double y_mean = 0.0;
    for (int64_t i = 0; i < n; i++) {
        // Calculate the mean of the dependent variable (Y)
        y_mean += y_data[i];
    }
    y_mean /= static_cast<long double>(n);

    // Iterate through each data point
    for (int64_t i = 0; i < n; i++) {
        // Calculate the predicted value using the linear regression model
        long double predicted = predict(x_data[i]);
        // Calculate the error (difference between predicted and actual values)
        long double error = predicted - y_data[i];
        // Calculate the total sum of squares and sum of squared errors
        total_sum_of_squares += (y_data[i] - y_mean) * (y_data[i] - y_mean);
        sum_of_squared_errors += error * error;
    }

    // Calculate the R-squared value using the formula 1 - (SSE / SST)
    return 1.0 - (sum_of_squared_errors / total_sum_of_squares);
}

// Determine number of rows in given dataset
int64_t gpmp::ml::LinearRegression::num_rows(const char *input) {
    int64_t num = 0;
    std::string row;

    // create input file stream
    std::ifstream file(input);

    while (getline(file, row)) {
        num++;
    }

    return num;
}
