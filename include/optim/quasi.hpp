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

#ifndef QUASI_HPP
#define QUASI_HPP

#include <functional>
#include <vector>

namespace gpmp {

namespace optim {

/**
 * @class QuasiNewton
 * @brief Class implementing Quasi-Newton optimization methods
 */
class QuasiNewton {
  public:
    /**
     * @brief Optimize a function using the Berndt–Hall–Hall–Hausman (BHHH)
     * algorithm
     *
     * @param func The objective function to minimize
     * @param initial_point The initial guess for the optimal parameters
     * @param tolerance The tolerance for stopping criterion
     * @param max_iterations The maximum number of iterations
     * @return The vector of optimal parameters
     */
    std::vector<double> bhhh_optimize(
        const std::function<double(const std::vector<double> &)> &func,
        const std::vector<double> &initial_point,
        double tolerance,
        size_t max_iterations);

    /**
     * @brief Calculate the gradient of a function at a given point
     *
     * @param func The objective function
     * @param point The point at which to calculate the gradient
     * @param epsilon The perturbation for finite differences
     * @return The gradient vector
     */
    std::vector<double> calculate_gradient(
        const std::function<double(const std::vector<double> &)> &func,
        const std::vector<double> &point,
        double epsilon);

    /**
     * @brief Calculate the BHHH matrix from the gradient
     *
     * @param gradient The gradient vector
     * @return The BHHH matrix
     */
    std::vector<std::vector<double>>
    calculate_bhhh_matrix(const std::vector<double> &gradient);

    /**
     * @brief Update the current point using the BHHH matrix
     *
     * @param current_point The current point
     * @param gradient The gradient vector
     * @param bhhh_matrix The BHHH matrix
     * @return The updated point
     */
    std::vector<double>
    update_point(const std::vector<double> &current_point,
                 const std::vector<double> &gradient,
                 const std::vector<std::vector<double>> &bhhh_matrix);

    /**
     * @brief Optimize a function using the Broyden–Fletcher–Goldfarb–Shanno
     * (BFGS) algorithm
     *
     * @param func The objective function to minimize
     * @param initial_point The initial guess for the optimal parameters
     * @param tolerance The tolerance for stopping criterion
     * @param max_iterations The maximum number of iterations
     * @return The vector of optimal parameters
     */
    std::vector<double> bfgs_optimize(
        const std::function<double(const std::vector<double> &)> &func,
        const std::vector<double> &initial_point,
        double tolerance,
        size_t max_iterations);

    /**
     * @brief Calculate the search direction using the BFGS method
     *
     * @param gradient The gradient vector
     * @param hessian_inverse The inverse of the Hessian matrix
     * @return The search direction vector
     */
    std::vector<double> calculate_search_direction(
        const std::vector<double> &gradient,
        const std::vector<std::vector<double>> &hessian_inverse);

    /**
     * @brief Perform line search to find an appropriate step size
     *
     * @param func The objective function
     * @param current_point The current point
     * @param search_direction The search direction vector
     * @return The optimal step size
     */
    double
    line_search(const std::function<double(const std::vector<double> &)> &func,
                const std::vector<double> &current_point,
                const std::vector<double> &search_direction);

    /**
     * @brief Update the current point using the line search and step size
     *
     * @param current_point The current point
     * @param search_direction The search direction vector
     * @param step_size The step size from the line search
     * @return The updated point
     */
    std::vector<double>
    update_point(const std::vector<double> &current_point,
                 const std::vector<double> &search_direction,
                 double step_size);

    /**
     * @brief Calculate the gradient difference between two points
     *
     * @param next_point The next point
     * @param current_point The current point
     * @param gradient The gradient vector
     * @return The gradient difference vector
     */
    std::vector<double>
    calculate_gradient_difference(const std::vector<double> &next_point,
                                  const std::vector<double> &current_point,
                                  const std::vector<double> &gradient);

    /**
     * @brief Update the inverse of the Hessian matrix using the BFGS method
     *
     * @param hessian_inverse The current inverse of the Hessian matrix
     * @param gradient_difference The gradient difference vector
     * @param search_direction The search direction vector
     * @return The updated inverse of the Hessian matrix
     */
    std::vector<std::vector<double>> update_hessian_inverse(
        const std::vector<std::vector<double>> &hessian_inverse,
        const std::vector<double> &gradient_difference,
        const std::vector<double> &search_direction);

    /**
     * @brief Calculate the dot product of two vectors
     *
     * @param a The first vector
     * @param b The second vector
     * @return The dot product value
     */
    double dot_product(const std::vector<double> &a,
                       const std::vector<double> &b);

    /**
     * @brief Subtract two vectors element-wise
     *
     * @param a The first vector
     * @param b The second vector
     * @return The result of subtracting each element of vector b from vector a
     */
    std::vector<double> vector_subtraction(const std::vector<double> &a,
                                           const std::vector<double> &b) const;

    /**
     * @brief Optimize a function using the Limited-Memory
     * Broyden-Fletcher-Goldfarb-Shanno (L-BFGS) algorithm
     *
     * @param func The objective function to optimize
     * @param initial_point The initial guess for the optimal point
     * @param tolerance The tolerance for stopping criterion
     * @param max_iterations The maximum number of iterations
     * @param memory_size The size of the limited-memory history (s and y
     * vectors)
     * @return The optimized point that minimizes the given objective function
     */
    std::tuple<std::vector<double>, double> lbfgs_optimize(
        const std::function<double(const std::vector<double> &)> &f,
        const std::vector<double> &initial_point,
        double tolerance = 1e-4,
        size_t max_iterations = 100,
        size_t memory_size = 5);

};

} // namespace optim

} // namespace gpmp
#endif
