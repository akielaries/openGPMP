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
 * LICENSE file.
 *
 *
 *
 * This software is distributed on an AS IS basis, WITHOUT
 * WARRANTY OF ANY KIND, either express or implied.
 *
 ************************************************************************/
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <openGPMP/optim/quasi.hpp>
#include <tuple>
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
    // Ensure vectors have the same size
    if (a.size() != b.size()) {
        throw std::invalid_argument(
            "Vectors must have the same size for dot product.");
    }

    double result = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        result += a[i] * b[i];
    }
    return result;
}

std::tuple<std::vector<double>, double>
gpmp::optim::QuasiNewton::lbfgs_optimize(
    const std::function<double(const std::vector<double> &)> &f,
    const std::vector<double> &initial_point,
    double tolerance,
    size_t max_iterations,
    size_t memory_size) {

    const double eps = 1e-8;

    size_t n = initial_point.size();
    std::vector<double> x = initial_point;
    std::vector<double> g(n); // Gradient vector
    std::vector<std::vector<double>> s(memory_size,
                                       std::vector<double>(n)); // s vectors
    std::vector<std::vector<double>> y(memory_size,
                                       std::vector<double>(n)); // y vectors
    std::vector<double> rho(memory_size);                       // rho values

    // Evaluate the objective function and gradient at initial_point
    double fx = f(x);
    // Calculate gradient at initial_point
    // Gradient calculation logic to be implemented
    // Assign gradient to 'g'

    for (size_t iter = 0; iter < max_iterations; ++iter) {
        // Check for convergence
        double norm_grad = 0.0;
        for (size_t i = 0; i < n; ++i) {
            norm_grad += g[i] * g[i];
        }
        norm_grad = sqrt(norm_grad);
        if (norm_grad < tolerance) {
            break;
        }

        // Compute search direction (use initial guess)
        std::vector<double> d = g;

        // L-BFGS two-loop recursion
        size_t start = std::min(iter, memory_size);
        // for (size_t i = start - 1; i >= 0; --i) {
        for (size_t i = start; i > 0; --i) {

            rho[i] = 1.0 /
                     inner_product(s[i].begin(), s[i].end(), y[i].begin(), 0.0);
            double alpha =
                rho[i] *
                inner_product(s[i].begin(), s[i].end(), d.begin(), 0.0);
            for (size_t j = 0; j < n; ++j) {
                d[j] -= alpha * y[i][j];
            }
        }

        // Perform scaling
        for (size_t i = 0; i < n; ++i) {
            d[i] *= rho[i];
        }

        // Compute gradient of the objective function along the search direction
        // Gradient calculation logic to be implemented
        // Assign gradient to 'dg'
        double dg = inner_product(d.begin(), d.end(), g.begin(), 0.0);

        // Limit curvature
        if (dg > 0) {
            break;
        }

        // Line search
        double step_size = 1.0;
        std::vector<double> x_new = x;
        for (size_t i = 0; i < n; ++i) {
            x_new[i] += step_size * d[i];
        }

        double fx_new = f(x_new);
        if (fx_new < fx + eps * step_size * dg) {
            // Update x
            x = x_new;
            fx = fx_new;

            // Evaluate gradient at new point
            // Gradient calculation logic to be implemented
            // Assign gradient to 'g'

            // Update s and y
            for (size_t i = 0; i < n; ++i) {
                s[iter % memory_size][i] = x_new[i] - x[i];
                y[iter % memory_size][i] = g[i] - d[i];
            }
        }
    }

    return std::make_tuple(x, fx);
}
