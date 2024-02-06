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

#include "../../include/optim/quasi.hpp"
#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

std::vector<double> gpmp::optim::QuasiNewton::vector_subtraction(
    const std::vector<double> &a,
    const std::vector<double> &b) const {
    if (a.size() != b.size()) {
        throw std::invalid_argument(
            "Error: Vector dimensions do not match for subtraction.");
    }

    std::vector<double> result;
    result.reserve(a.size());

    for (size_t i = 0; i < a.size(); ++i) {
        result.push_back(a[i] - b[i]);
    }

    return result;
}

std::vector<double> gpmp::optim::QuasiNewton::bhhh_optimize(
    const std::function<double(const std::vector<double> &)> &func,
    const std::vector<double> &initial_point,
    double tolerance,
    size_t max_iterations) {
    std::vector<double> current_point = initial_point;
    size_t n = initial_point.size();

    for (size_t iteration = 0; iteration < max_iterations; ++iteration) {
        // Calculate the gradient
        std::vector<double> gradient =
            calculate_gradient(func, current_point, 1e-6);

        // Check convergence
        double gradient_norm = 0.0;
        for (size_t i = 0; i < n; ++i) {
            gradient_norm += gradient[i] * gradient[i];
        }
        gradient_norm = std::sqrt(gradient_norm);

        if (gradient_norm < tolerance) {
            std::cout << "Converged after " << iteration << " iterations."
                      << std::endl;
            return current_point;
        }

        // Calculate the BHHH matrix
        std::vector<std::vector<double>> bhhh_matrix =
            calculate_bhhh_matrix(gradient);

        // Update the current point
        current_point = update_point(current_point, gradient, bhhh_matrix);
    }

    std::cout << "Reached maximum iterations without convergence." << std::endl;
    return current_point;
}

std::vector<double> gpmp::optim::QuasiNewton::calculate_gradient(
    const std::function<double(const std::vector<double> &)> &func,
    const std::vector<double> &point,
    double epsilon) {
    size_t n = point.size();
    std::vector<double> gradient(n);

    for (size_t i = 0; i < n; ++i) {
        std::vector<double> perturbed_point = point;
        perturbed_point[i] += epsilon;

        double perturbed_value = func(perturbed_point);
        double original_value = func(point);

        gradient[i] = (perturbed_value - original_value) / epsilon;
    }

    return gradient;
}

std::vector<std::vector<double>>
gpmp::optim::QuasiNewton::calculate_bhhh_matrix(
    const std::vector<double> &gradient) {
    size_t n = gradient.size();
    std::vector<std::vector<double>> bhhh_matrix(n, std::vector<double>(n));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            bhhh_matrix[i][j] = gradient[i] * gradient[j];
        }
    }

    return bhhh_matrix;
}

std::vector<double> gpmp::optim::QuasiNewton::update_point(
    const std::vector<double> &current_point,
    const std::vector<double> &gradient,
    const std::vector<std::vector<double>> &bhhh_matrix) {
    size_t n = current_point.size();
    std::vector<double> updated_point(n);

    for (size_t i = 0; i < n; ++i) {
        updated_point[i] = current_point[i] - gradient[i] / bhhh_matrix[i][i];
    }

    return updated_point;
}

std::vector<double> gpmp::optim::QuasiNewton::bfgs_optimize(
    const std::function<double(const std::vector<double> &)> &func,
    const std::vector<double> &initial_point,
    double tolerance,
    size_t max_iterations) {
    std::vector<double> current_point = initial_point;
    size_t n = initial_point.size();

    // Initialize Hessian approximation as the identity matrix
    std::vector<std::vector<double>> hessian_inverse(
        n,
        std::vector<double>(n, 0.0));
    for (size_t i = 0; i < n; ++i) {
        hessian_inverse[i][i] = 1.0;
    }

    for (size_t iteration = 0; iteration < max_iterations; ++iteration) {
        // Calculate the gradient
        std::vector<double> gradient =
            calculate_gradient(func, current_point, 1e-6);

        // Check convergence
        double gradient_norm = 0.0;
        for (size_t i = 0; i < n; ++i) {
            gradient_norm += gradient[i] * gradient[i];
        }
        gradient_norm = std::sqrt(gradient_norm);

        if (gradient_norm < tolerance) {
            std::cout << "Converged after " << iteration << " iterations."
                      << std::endl;
            return current_point;
        }

        // Calculate search direction
        std::vector<double> search_direction =
            calculate_search_direction(gradient, hessian_inverse);

        // Perform line search to find the step size
        double step_size = line_search(func, current_point, search_direction);

        // Update the current point
        std::vector<double> next_point =
            update_point(current_point, search_direction, step_size);

        // Update the Hessian approximation
        std::vector<double> gradient_difference =
            calculate_gradient_difference(next_point, current_point, gradient);
        hessian_inverse = update_hessian_inverse(hessian_inverse,
                                                 gradient_difference,
                                                 search_direction);

        // Move to the next iteration
        current_point = next_point;
    }

    std::cout << "Reached maximum iterations without convergence." << std::endl;
    return current_point;
}

std::vector<double> gpmp::optim::QuasiNewton::calculate_search_direction(
    const std::vector<double> &gradient,
    const std::vector<std::vector<double>> &hessian_inverse) {
    size_t n = gradient.size();
    std::vector<double> search_direction(n);

    for (size_t i = 0; i < n; ++i) {
        search_direction[i] = 0.0;
        for (size_t j = 0; j < n; ++j) {
            search_direction[i] -= hessian_inverse[i][j] * gradient[j];
        }
    }

    return search_direction;
}

double gpmp::optim::QuasiNewton::line_search(
    const std::function<double(const std::vector<double> &)> &func,
    const std::vector<double> &current_point,
    const std::vector<double> &search_direction) {
    const double alpha = 0.001;      // Step size multiplier
    const double beta = 0.5;         // Factor for reducing the step size
    const int maxIterations = 100;   // Maximum number of iterations
    const double minStepSize = 1e-6; // Minimum step size

    double step_size = 1.0; // Initial step size
    std::vector<double> updated_point = current_point;

    // Evaluate the objective function at the current point
    double f_current = func(current_point);

    // Calculate the directional derivative (gradient dot search_direction)
    double directional_derivative =
        dot_product(calculate_gradient(func, current_point, 1e-6),
                    search_direction);

    int iteration = 0;
    while (step_size > minStepSize && iteration < maxIterations) {
        updated_point =
            update_point(current_point, search_direction, step_size);
        double f_updated = func(updated_point);
        if (f_updated <=
            f_current + alpha * step_size * directional_derivative) {
            break; // Stop if Armijo condition is satisfied
        }
        step_size *= beta; // Reduce the step size
        ++iteration;
    }

    return step_size;
}

std::vector<double> gpmp::optim::QuasiNewton::update_point(
    const std::vector<double> &current_point,
    const std::vector<double> &search_direction,
    double step_size) {
    size_t n = current_point.size();
    std::vector<double> updated_point(n);

    for (size_t i = 0; i < n; ++i) {
        updated_point[i] = current_point[i] + step_size * search_direction[i];
    }

    return updated_point;
}

std::vector<double> gpmp::optim::QuasiNewton::calculate_gradient_difference(
    const std::vector<double> &next_point,
    const std::vector<double> &current_point,
    const std::vector<double> &gradient) {
    size_t n = next_point.size();
    std::vector<double> gradient_difference(n);

    for (size_t i = 0; i < n; ++i) {
        gradient_difference[i] =
            gradient[i] * (next_point[i] - current_point[i]);
    }

    return gradient_difference;
}

std::vector<std::vector<double>>
gpmp::optim::QuasiNewton::update_hessian_inverse(
    const std::vector<std::vector<double>> &hessian_inverse,
    const std::vector<double> &gradient_difference,
    const std::vector<double> &search_direction) {

    size_t n = hessian_inverse.size();
    std::vector<std::vector<double>> updated_hessian_inverse(
        n,
        std::vector<double>(n));

    // Update Hessian using BFGS update formula
    double rho = dot_product(gradient_difference, search_direction);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            updated_hessian_inverse[i][j] =
                hessian_inverse[i][j] +
                rho * gradient_difference[i] * gradient_difference[j];
        }
    }

    return updated_hessian_inverse;
}

double gpmp::optim::QuasiNewton::dot_product(const std::vector<double> &a,
                                             const std::vector<double> &b) {
    size_t n = a.size();
    double result = 0.0;

    for (size_t i = 0; i < n; ++i) {
        result += a[i] * b[i];
    }

    return result;
}

std::vector<double> gpmp::optim::QuasiNewton::lbfgs_optimize(
    const std::function<double(const std::vector<double> &)> &func,
    const std::vector<double> &initial_point,
    double tolerance,
    size_t max_iterations,
    size_t memory_size) {
    // Validate memory_size
    if (memory_size == 0) {
        throw std::invalid_argument(
            "Error: Memory size for L-BFGS must be greater than zero.");
    }

    size_t n = initial_point.size();
    size_t m = std::min(memory_size, n);

    // Initialize vectors and matrices
    std::vector<std::vector<double>> s;
    std::vector<std::vector<double>> y;
    std::vector<double> rho;
    std::vector<double> alpha;
    std::vector<double> q;
    std::vector<double> gradient =
        calculate_gradient(func, initial_point, 1e-8);
    std::vector<double> x = initial_point;

    // Main optimization loop
    for (size_t iteration = 0; iteration < max_iterations; ++iteration) {
        // Check convergence
        if (dot_product(gradient, gradient) < tolerance * tolerance) {
            return x; // Converged
        }

        // Compute search direction using L-BFGS update
        q = gradient;
        for (size_t i = m - 1; i != static_cast<size_t>(-1); --i) {
            rho[i] = 1.0 / dot_product(s[i], y[i]);
            alpha[i] = rho[i] * dot_product(s[i], q);
            for (size_t j = 0; j < n; ++j) {
                q[j] -= alpha[i] * y[i][j];
            }
        }

        // Scale the initial Hessian approximation
        double gamma =
            dot_product(s[m - 1], y[m - 1]) / dot_product(y[m - 1], y[m - 1]);
        for (size_t i = 0; i < n; ++i) {
            q[i] *= gamma;
        }

        // Perform forward recursion
        for (size_t i = 0; i < m; ++i) {
            double beta = rho[i] * dot_product(y[i], q);
            for (size_t j = 0; j < n; ++j) {
                q[j] += (alpha[i] - beta) * s[i][j];
            }
        }

        // Perform L-BFGS update
        std::vector<double> direction = q;
        double step_size = line_search(func, x, direction);

        // Update vectors and matrices
        std::vector<double> new_point = update_point(x, direction, step_size);
        std::vector<double> new_gradient =
            calculate_gradient(func, new_point, 1e-8);

        // Update s and y
        s.push_back(vector_subtraction(new_point, x));
        y.push_back(vector_subtraction(new_gradient, gradient));

        // Ensure s and y do not exceed memory_size
        if (s.size() > m) {
            s.erase(s.begin());
            y.erase(y.begin());
        }

        x = new_point;
        gradient = new_gradient;
    }

    return x; // Return the result after the maximum number of iterations
}
