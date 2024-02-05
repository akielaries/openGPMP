/*************************************************************************
 *
 *  Project
 *                         _____ _____  __  __ _____
 *                        / ____|  __ \|  \/  |  __ \
 *  ___  _ __   ___ _ __ | |  __| |__) | \  / | |__) |
 * / _ \| '_ \ / _ \ '_ \| | |_ |  ___/| |\/| |  ___/
 *| (_) | |_) |  __/ | | | |__| | |    | |  | | |
 * \___/| .__/ \___|_| |_|\_____|_|    |_|  |_|_|
 *      | |
 *      |_|
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

#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <cmath>
#include <functional>
#include <stdexcept>
#include <vector>

namespace gpmp {

namespace optim {

/**
 * @brief A class containing various utility functions and optimization methods
 */
class Func {
  public:
    /**
     * @brief Generates a random point within specified bounds
     *
     * @param lower_bounds The lower bounds for each dimension
     * @param upper_bounds The upper bounds for each dimension
     * @return A randomly generated point within the specified bounds
     */
    std::vector<double>
    generate_random_point(const std::vector<double> &lower_bounds,
                          const std::vector<double> &upper_bounds) const;

    /**
     * @brief Generates a Fibonacci sequence up to a specified length
     *
     * @param length The length of the Fibonacci sequence
     * @return The Fibonacci sequence
     */
    std::vector<double> generate_fibonacci_sequence(size_t length) const;

    /**
     * @brief Performs vector addition
     *
     * @param a The first vector
     * @param b The second vector
     * @return The result of vector addition
     */
    std::vector<double> vector_addition(const std::vector<double> &a,
                                        const std::vector<double> &b) const;

    /**
     * @brief Performs vector subtraction
     *
     * @param a The first vector
     * @param b The second vector
     * @return The result of vector subtraction
     */
    std::vector<double> vector_subtraction(const std::vector<double> &a,
                                           const std::vector<double> &b) const;

    /**
     * @brief Performs vector scalar multiplication
     *
     * @param scalar The scalar value
     * @param vec The vector
     * @return The result of vector scalar multiplication
     */
    std::vector<double>
    vector_scalar_multiply(double scalar, const std::vector<double> &vec) const;

    /**
     * @brief Calculates the midpoint between two values
     *
     * @param a The first value
     * @param b The second value
     * @param fraction The fraction determining the midpoint
     * @return The midpoint between a and b
     */
    double calculate_midpoint(double a, double b, double fraction) const;

    // Golden-section search methods for univariate functions

    /**
     * @brief Finds the minimum of a univariate function using Golden-section
     * search
     *
     * @param func The univariate function to minimize
     * @param a The lower bound of the search interval
     * @param b The upper bound of the search interval
     * @param tol The tolerance for stopping criterion
     * @return The value of the argument that minimizes the function
     */
    double golden_section_search(const std::function<double(double)> &func,
                                 double a,
                                 double b,
                                 double tol);

    // Interpolation methods for univariate functions

    /**
     * @brief Interpolates a univariate function using linear interpolation
     *
     * @param x The point at which to interpolate
     * @param x0 The left point of the interval
     * @param x1 The right point of the interval
     * @param y0 The function value at x0
     * @param y1 The function value at x1
     * @return The interpolated function value at x
     */
    double
    linear_interpolation(double x, double x0, double x1, double y0, double y1);

    /**
     * @brief Interpolates a univariate function using cubic interpolation
     *
     * @param x The point at which to interpolate
     * @param x0 The left point of the interval
     * @param x1 The right point of the interval
     * @param y0 The function value at x0
     * @param y1 The function value at x1
     * @param y0_prime The derivative value at x0
     * @param y1_prime The derivative value at x1
     * @return The interpolated function value at x
     */
    double cubic_interpolation(double x,
                               double x0,
                               double x1,
                               double y0,
                               double y1,
                               double y0_prime,
                               double y1_prime);

    // Golden-section search methods for multivariate functions

    /**
     * @brief Finds the minimum of a multivariate function using Golden-section
     * search
     *
     * @param func The multivariate function to minimize
     * @param lower_bounds The lower bounds of the search interval
     * @param upper_bounds The upper bounds of the search interval
     * @param tol The tolerance for stopping criterion
     * @return The vector of arguments that minimizes the function
     */
    std::vector<double> golden_section_search_multivariate(
        const std::function<double(const std::vector<double> &)> &func,
        const std::vector<double> &lower_bounds,
        const std::vector<double> &upper_bounds,
        double tol);

    /**
     * @brief Performs random search for function optimization
     *
     * @param func The multivariate function to optimize
     * @param lower_bounds The lower bounds of the search interval
     * @param upper_bounds The upper bounds of the search interval
     * @param max_iterations The maximum number of iterations
     * @return The vector of arguments that minimizes the function
     */
    double random_search(
        const std::function<double(const std::vector<double> &)> &func,
        const std::vector<double> &lower_bounds,
        const std::vector<double> &upper_bounds,
        size_t max_iterations);

    /**
     * @brief Fits a linear function to given data points
     *
     * @param x The x-coordinates of data points
     * @param y The corresponding y-coordinates of data points
     * @return Coefficients of the linear fit
     */
    std::vector<double> fit_linear(const std::vector<double> &x,
                                   const std::vector<double> &y);

    /**
     * @brief Performs Fibonacci search for function optimization
     *
     * @param func The multivariate function to optimize
     * @param lower_bounds The lower bounds of the search interval
     * @param upper_bounds The upper bounds of the search interval
     * @param max_iterations The maximum number of iterations
     * @return The vector of arguments that minimizes the function
     */
    double fibonacci_search(
        const std::function<double(const std::vector<double> &)> &func,
        const std::vector<double> &lower_bounds,
        const std::vector<double> &upper_bounds,
        size_t max_iterations);

    /**
     * @brief Performs ternary search for function optimization
     *
     * @param func The multivariate function to optimize
     * @param lower_bounds The lower bounds of the search interval
     * @param upper_bounds The upper bounds of the search interval
     * @param max_iterations The maximum number of iterations
     * @return The vector of arguments that minimizes the function
     */
    double ternary_search(
        const std::function<double(const std::vector<double> &)> &func,
        const std::vector<double> &lower_bounds,
        const std::vector<double> &upper_bounds,
        size_t max_iterations) const;

    /**
     * @brief Performs the bisection method for function optimization
     *
     * @param func The univariate function to optimize
     * @param lower_bound The lower bound of the search interval
     * @param upper_bound The upper bound of the search interval
     * @param max_iterations The maximum number of iterations
     * @return The vector of arguments that minimizes the function
     */
    std::vector<double> bisection_method(
        const std::function<double(const std::vector<double> &)> &func,
        double lower_bound,
        double upper_bound,
        size_t max_iterations);

    /**
     * @brief Performs Newton's method for function optimization
     *
     * @param func The univariate function to optimize
     * @param derivative The derivative of the function
     * @param initial_guess The initial guess for the minimum
     * @param max_iterations The maximum number of iterations
     * @return The vector of arguments that minimizes the function
     */
    std::vector<double> newton_method(
        const std::function<double(const std::vector<double> &)> &func,
        const std::function<double(const std::vector<double> &)> &derivative,
        double initial_guess,
        size_t max_iterations);

    /**
     * @brief Performs Regula Falsi (False Position) method for function
     * optimization
     *
     * @param func The univariate function to optimize
     * @param lower_bound The lower bound of the search interval
     * @param upper_bound The upper bound of the search interval
     * @param max_iterations The maximum number of iterations
     * @return The vector of arguments that minimizes the function
     */
    std::vector<double>
    regula_falsi(const std::function<double(const std::vector<double> &)> &func,
                 double lower_bound,
                 double upper_bound,
                 size_t max_iterations);

    /**
     * @brief Fits a cubic function to given data points
     *
     * @param x The x-coordinates of data points
     * @param y The corresponding y-coordinates of data points
     * @return Coefficients of the cubic fit
     */
    std::vector<double> cubic_fit(const std::vector<double> &x,
                                  const std::vector<double> &y);

    // Nelder–Mead method

    /**
     * @brief Finds the minimum of a multivariate function using the Nelder–Mead
     * method
     *
     * @param func The multivariate function to minimize
     * @param initial_point The initial guess for the minimum
     * @param tolerance The tolerance for stopping criterion
     * @param max_iterations The maximum number of iterations
     * @return The vector of arguments that minimizes the function
     */
    std::vector<double>
    nelder_mead(const std::function<double(const std::vector<double> &)> &func,
                std::vector<double> initial_point,
                double tolerance,
                size_t max_iterations);

    /**
     * @brief Calculates the centroid of a simplex excluding a specific point
     *
     * @param simplex The simplex
     * @param exclude_index The index of the point to exclude
     * @return The centroid of the simplex
     */
    std::vector<double>
    calculate_centroid(const std::vector<std::vector<double>> &simplex,
                       size_t exclude_index);

    /**
     * @brief Reflects a point with respect to a centroid
     *
     * @param point The point to reflect
     * @param centroid The centroid
     * @param reflection_coefficient The reflection coefficient
     * @return The reflected point
     */
    std::vector<double> reflect(const std::vector<double> &point,
                                const std::vector<double> &centroid,
                                double reflection_coefficient);

    /**
     * @brief Calculates the range of values
     *
     * @param values The vector of values
     * @return The range of values
     */
    double calculate_range(const std::vector<double> &values);

    /**
     * @brief Checks if a given interval is valid (lower bound < upper bound)
     *
     * @param a The lower bound of the interval
     * @param b The upper bound of the interval
     * @return True if the interval is valid, false otherwise
     */
    bool is_valid_interval(double a, double b);

  private:
    // Helper methods for golden section search

    /**
     * @brief Finds the minimum of a univariate function using Golden-section
     * search (Internal helper function)
     *
     * @param func The univariate function to minimize
     * @param a The lower bound of the search interval
     * @param b The upper bound of the search interval
     * @param tol The tolerance for stopping criterion
     * @param x1 Internal helper parameter
     * @param x2 Internal helper parameter
     * @return The value of the argument that minimizes the function
     */
    double
    golden_section_search_minimize(const std::function<double(double)> &func,
                                   double a,
                                   double b,
                                   double tol,
                                   double x1,
                                   double x2);

    // Helper methods for multivariate golden section search

    /**
     * @brief Finds the minimum of a multivariate function using Golden-section
     * search (Internal helper function)
     *
     * @param func The multivariate function to minimize
     * @param lower_bounds The lower bounds of the search interval
     * @param upper_bounds The upper bounds of the search interval
     * @param tol The tolerance for stopping criterion
     * @param x1 Internal helper parameter
     * @param x2 Internal helper parameter
     * @return The vector of arguments that minimizes the function
     */
    std::vector<double> golden_section_search_minimize_multivariate(
        const std::function<double(const std::vector<double> &)> &func,
        const std::vector<double> &lower_bounds,
        const std::vector<double> &upper_bounds,
        double tol,
        const std::vector<double> &x1,
        const std::vector<double> &x2);
};

} // namespace optim

} // namespace gpmp

#endif // FUNCTION_HPP
