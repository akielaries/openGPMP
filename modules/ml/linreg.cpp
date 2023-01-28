/*
 * taking a look at implementing regression in c++
 */
#include "../../include/ml/linreg.hpp"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

/*
 * Constructor to provide the default values to all the terms in the
 * object of class regression
 */
mtpk::LinearRegression::LinearRegression() {
    coeff        = 0;
    constant     = 0;
    sum_y        = 0;
    sum_y_square = 0;
    sum_x_square = 0;
    sum_x        = 0;
    sum_xy       = 0;
}

// Function that calculate the coefficient/slope of the best fitting
// line
void mtpk::LinearRegression::calculate_coeffecient() {
    long double N           = x.size();
    long double numerator   = (N * sum_xy - sum_x * sum_y);
    long double denominator = (N * sum_x_square - sum_x * sum_x);
    coeff                   = numerator / denominator;
}

/*
 * Member function that will calculate the constant term of the best
 * fitting line
 */
void mtpk::LinearRegression::calculate_constant() {
    long double N           = x.size();
    long double numerator   = (sum_y * sum_x_square - sum_x * sum_xy);
    long double denominator = (N * sum_x_square - sum_x * sum_x);
    constant                = numerator / denominator;
}

// Function that return the number of entries (xi, yi) in the data set
int64_t mtpk::LinearRegression::data_size() {
    return x.size();
}

// Function that return the coefficient/slope of the best fitting line
long double mtpk::LinearRegression::return_coeffecient() {
    if (coeff == 0)
        calculate_coeffecient();
    return coeff;
}

// Function that return the constant term of the best fitting line
long double mtpk::LinearRegression::return_constant() {
    if (constant == 0)
        calculate_constant();
    return constant;
}

// Function that print the best fitting line
void mtpk::LinearRegression::best_fit() {
    if (coeff == 0 && constant == 0) {
        calculate_coeffecient();
        calculate_constant();
    }
    std::cout << "The best fitting line is y = " << coeff << "x + "
              << constant << std::endl;
}

// Function to take input from the dataset
void mtpk::LinearRegression::get_input(int64_t n) {
    for (int64_t i = 0; i < n; i++) {
        /*
         * In a csv file all the values of xi and yi are separated by
         * commas
         */
        char comma;
        long double xi;
        long double yi;
        std::cin >> xi >> comma >> yi;
        sum_xy += xi * yi;
        sum_x += xi;
        sum_y += yi;
        sum_x_square += xi * xi;
        sum_y_square += yi * yi;
        x.push_back(xi);
        y.push_back(yi);
    }
}

// Function to show the data set
void mtpk::LinearRegression::show_data() {
    for (int64_t i = 0; i < 62; i++) {
        printf("_");
    }
    printf("\n\n");
    printf("|%15s%5s %15s%5s%20s\n", "X", "", "Y", "", "|");

    for (int64_t i = 0; uint64_t(i) < x.size(); i++) {
        printf("|%20Lf %20Lf%20s\n", x[i], y[i], "|");
    }

    for (int64_t i = 0; i < 62; i++) {
        printf("_");
    }
    printf("\n");
}

// Function to predict the value corresponding to some input
long double mtpk::LinearRegression::predict(long double x) {
    return coeff * x + constant;
}

// Function that returns overall sum of square of errors
long double mtpk::LinearRegression::error_square() {
    long double ans = 0;
    for (int64_t i = 0; uint64_t(i) < x.size(); i++) {
        ans += ((predict(x[i]) - y[i]) * (predict(x[i]) - y[i]));
    }
    return ans;
}
/*
 * Functions that return the error i.e the difference between the
 * actual value and value predicted by our model
 */
long double mtpk::LinearRegression::error_in(long double num) {
    for (int64_t i = 0; uint64_t(i) < x.size(); i++) {
        if (num == x[i]) {
            return (y[i] - predict(x[i]));
        }
    }
    return 0;
}

int64_t mtpk::LinearRegression::num_rows(const char *input) {
    int64_t num = 0;
    std::string row;

    // create input file stream
    std::ifstream file(input);

    while (getline(file, row)) {
        num++;
    }

    return num;
}
/*
int num_col(const char* input) {
    int num = 0;
    string col;
    std::ifstream file(input);

    return col;

}
*/
