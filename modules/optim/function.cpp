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

#include "../../include/optim/function.hpp"
std::vector<double> gpmp::optim::Func::generate_random_point(
    const std::vector<double> &lower_bounds,
    const std::vector<double> &upper_bounds) const {
    if (lower_bounds.size() != upper_bounds.size()) {
        throw std::invalid_argument(
            "Lower and upper bounds must have the same dimension.");
    }

    std::vector<double> point;
    for (size_t i = 0; i < lower_bounds.size(); ++i) {
        double random_value =
            lower_bounds[i] + static_cast<double>(rand()) / RAND_MAX *
                                  (upper_bounds[i] - lower_bounds[i]);
        point.push_back(random_value);
    }

    return point;
}

std::vector<double>
gpmp::optim::Func::generate_fibonacci_sequence(size_t length) const {
    std::vector<double> sequence;

    double golden_ratio = (1.0 + std::sqrt(5.0)) / 2.0;
    for (size_t i = 0; i < length; ++i) {
        double fibonacci_number =
            std::round(std::pow(golden_ratio, static_cast<double>(i)));
        sequence.push_back(fibonacci_number);
    }

    return sequence;
}

std::vector<double>
gpmp::optim::Func::vector_addition(const std::vector<double> &a,
                                   const std::vector<double> &b) const {
    if (a.size() != b.size()) {
        throw std::invalid_argument(
            "Vector dimensions do not match for addition.");
    }

    std::vector<double> result;
    for (size_t i = 0; i < a.size(); ++i) {
        result.push_back(a[i] + b[i]);
    }

    return result;
}

std::vector<double>
gpmp::optim::Func::vector_subtraction(const std::vector<double> &a,
                                      const std::vector<double> &b) const {
    if (a.size() != b.size()) {
        throw std::invalid_argument(
            "Vector dimensions do not match for subtraction.");
    }

    std::vector<double> result;
    for (size_t i = 0; i < a.size(); ++i) {
        result.push_back(a[i] - b[i]);
    }

    return result;
}

std::vector<double> gpmp::optim::Func::vector_scalar_multiply(
    double scalar,
    const std::vector<double> &vec) const {
    std::vector<double> result;
    for (double value : vec) {
        result.push_back(scalar * value);
    }

    return result;
}

double gpmp::optim::Func::calculate_midpoint(double a,
                                             double b,
                                             double fraction) const {
    return a + fraction * (b - a);
}

double gpmp::optim::Func::golden_section_search(
    const std::function<double(double)> &func,
    double a,
    double b,
    double tol) {
    if (!is_valid_interval(a, b)) {
        throw std::invalid_argument(
            "Invalid interval: lower bound must be less than upper bound.");
    }

    const double inv_phi = (std::sqrt(5.0) - 1.0) / 2.0;
    double x1 = b - inv_phi * (b - a);
    double x2 = a + inv_phi * (b - a);

    return golden_section_search_minimize(func, a, b, tol, x1, x2);
}

double gpmp::optim::Func::linear_interpolation(double x,
                                               double x0,
                                               double x1,
                                               double y0,
                                               double y1) {
    return y0 + (y1 - y0) / (x1 - x0) * (x - x0);
}

double gpmp::optim::Func::cubic_interpolation(double x,
                                              double x0,
                                              double x1,
                                              double y0,
                                              double y1,
                                              double y0_prime,
                                              double y1_prime) {
    double h = x1 - x0;
    double t = (x - x0) / h;
    double t2 = t * t;
    double t3 = t2 * t;

    double a = 2 * t3 - 3 * t2 + 1;
    double b = t3 - 2 * t2 + t;
    double c = t3 - t2;
    double d = -2 * t3 + 3 * t2;

    return a * y0 + b * (h * y0_prime) + c * (h * y1_prime) + d * y1;
}

double gpmp::optim::Func::golden_section_search_minimize(
    const std::function<double(double)> &func,
    double a,
    double b,
    double tol,
    double x1,
    double x2) {
    double f1 = func(x1);
    double f2 = func(x2);

    while ((b - a) > tol) {
        if (f1 < f2) {
            b = x2;
            x2 = x1;
            x1 = a + b - x2;
            f2 = f1;
            f1 = func(x1);
        } else {
            a = x1;
            x1 = x2;
            x2 = a + b - x1;
            f1 = f2;
            f2 = func(x2);
        }
    }

    return (f1 < f2) ? x1 : x2;
}

// Helper methods for multivariate golden section search
// (Implementation of these methods requires more details about the multivariate
// function)

std::vector<double> gpmp::optim::Func::golden_section_search_multivariate(
    const std::function<double(const std::vector<double> &)> &func,
    const std::vector<double> &lower_bounds,
    const std::vector<double> &upper_bounds,
    double tol) {
    if (lower_bounds.size() != upper_bounds.size()) {
        throw std::invalid_argument(
            "Lower and upper bounds must have the same dimension.");
    }

    // Initialize x1 and x2 based on the golden section ratio for each dimension
    std::vector<double> x1(lower_bounds.size());
    std::vector<double> x2(lower_bounds.size());

    for (size_t i = 0; i < lower_bounds.size(); ++i) {
        if (!is_valid_interval(lower_bounds[i], upper_bounds[i])) {
            throw std::invalid_argument("Invalid interval for dimension " +
                                        std::to_string(i));
        }

        const double inv_phi = (std::sqrt(5.0) - 1.0) / 2.0;
        x1[i] = upper_bounds[i] - inv_phi * (upper_bounds[i] - lower_bounds[i]);
        x2[i] = lower_bounds[i] + inv_phi * (upper_bounds[i] - lower_bounds[i]);
    }

    return golden_section_search_minimize_multivariate(func,
                                                       lower_bounds,
                                                       upper_bounds,
                                                       tol,
                                                       x1,
                                                       x2);
}

double gpmp::optim::Func::random_search(
    const std::function<double(const std::vector<double> &)> &func,
    const std::vector<double> &lower_bounds,
    const std::vector<double> &upper_bounds,
    size_t max_iterations) {
    if (lower_bounds.size() != upper_bounds.size()) {
        throw std::invalid_argument(
            "Lower and upper bounds must have the same dimension.");
    }

    size_t dimension = lower_bounds.size();
    std::vector<double> best_point(dimension);
    double best_value = std::numeric_limits<double>::infinity();

    for (size_t iteration = 0; iteration < max_iterations; ++iteration) {
        std::vector<double> random_point =
            generate_random_point(lower_bounds, upper_bounds);
        double value = func(random_point);

        if (value < best_value) {
            best_value = value;
            best_point = random_point;
        }
    }

    return best_value;
}

// Curve-fitting methods

std::vector<double>
gpmp::optim::Func::fit_linear(const std::vector<double> &x,
                              const std::vector<double> &y) {
    size_t n = x.size();

    if (n != y.size() || n < 2) {
        throw std::invalid_argument(
            "Invalid input dimensions for linear curve fitting.");
    }

    double sum_x = 0.0, sum_y = 0.0, sum_xy = 0.0, sum_x_squared = 0.0;

    for (size_t i = 0; i < n; ++i) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_x_squared += x[i] * x[i];
    }

    double a =
        (n * sum_xy - sum_x * sum_y) / (n * sum_x_squared - sum_x * sum_x);
    double b = (sum_y - a * sum_x) / n;

    return {a, b};
}
double gpmp::optim::Func::fibonacci_search(
    const std::function<double(const std::vector<double> &)> &func,
    const std::vector<double> &lower_bounds,
    const std::vector<double> &upper_bounds,
    size_t max_iterations) {
    if (lower_bounds.size() != upper_bounds.size()) {
        throw std::invalid_argument(
            "Lower and upper bounds must have the same dimension.");
    }

    size_t dimension = lower_bounds.size();
    std::vector<double> fib_sequence =
        generate_fibonacci_sequence(max_iterations);
    std::vector<double> a = lower_bounds;
    std::vector<double> b = upper_bounds;

    for (size_t k = 0; k < max_iterations; ++k) {
        double lambda = (fib_sequence[max_iterations - k - 1] /
                         fib_sequence[max_iterations - k + 1]);
        std::vector<double> x1 = vector_addition(
            a,
            vector_scalar_multiply(lambda, vector_subtraction(b, a)));
        std::vector<double> x2 = vector_addition(
            b,
            vector_scalar_multiply(lambda, vector_subtraction(a, b)));

        if (func(x1) < func(x2)) {
            b = x2;
        } else {
            a = x1;
        }
    }

    return func(a);
}

double gpmp::optim::Func::ternary_search(
    const std::function<double(const std::vector<double> &)> &func,
    const std::vector<double> &lower_bounds,
    const std::vector<double> &upper_bounds,
    size_t max_iterations) const {
    double a = lower_bounds[0];
    double b = upper_bounds[0];

    for (size_t iteration = 0; iteration < max_iterations; ++iteration) {
        double m1 = calculate_midpoint(a, b, 1.0 / 3.0);
        double m2 = calculate_midpoint(a, b, 2.0 / 3.0);

        double f_m1 = func({m1});
        double f_m2 = func({m2});

        if (f_m1 < f_m2) {
            b = m2;
        } else {
            a = m1;
        }
    }

    return calculate_midpoint(a, b, 0.5);
}

// First-order methods

std::vector<double> gpmp::optim::Func::bisection_method(
    const std::function<double(const std::vector<double> &)> &func,
    double lower_bound,
    double upper_bound,
    size_t max_iterations) {
    if (lower_bound >= upper_bound) {
        throw std::invalid_argument("Invalid bounds for bisection method.");
    }

    double a = lower_bound;
    double b = upper_bound;

    for (size_t iteration = 0; iteration < max_iterations; ++iteration) {
        double midpoint = (a + b) / 2.0;

        if (func({midpoint}) == 0.0) {
            return {midpoint};
        } else if (func({midpoint}) * func({a}) < 0) {
            b = midpoint;
        } else {
            a = midpoint;
        }
    }

    return {(a + b) / 2.0};
}

// Curve-fitting methods

std::vector<double> gpmp::optim::Func::newton_method(
    const std::function<double(const std::vector<double> &)> &func,
    const std::function<double(const std::vector<double> &)> &derivative,
    double initial_guess,
    size_t max_iterations) {
    double x = initial_guess;

    for (size_t iteration = 0; iteration < max_iterations; ++iteration) {
        double fx = func({x});
        double dfx = derivative({x});

        if (dfx == 0.0) {
            throw std::runtime_error("Newton's method: Derivative is zero.");
        }

        x = x - fx / dfx;
    }

    return {x};
}

std::vector<double> gpmp::optim::Func::regula_falsi(
    const std::function<double(const std::vector<double> &)> &func,
    double lower_bound,
    double upper_bound,
    size_t max_iterations) {
    if (func({lower_bound}) * func({upper_bound}) >= 0.0) {
        throw std::invalid_argument("Invalid bounds for regula falsi method.");
    }

    double a = lower_bound;
    double b = upper_bound;

    for (size_t iteration = 0; iteration < max_iterations; ++iteration) {
        double fa = func({a});
        double fb = func({b});

        if (fa * fb >= 0.0) {
            throw std::runtime_error("Regula falsi method: Function values at "
                                     "the bounds have the same sign.");
        }

        double c = (a * fb - b * fa) / (fb - fa);

        if (func({c}) == 0.0) {
            return {c};
        } else if (fa * func({c}) < 0.0) {
            b = c;
        } else {
            a = c;
        }
    }

    return {(a + b) / 2.0};
}

std::vector<double> gpmp::optim::Func::cubic_fit(const std::vector<double> &x,
                                                 const std::vector<double> &y) {
    size_t n = x.size();

    if (n != y.size() || n < 4) {
        throw std::invalid_argument(
            "Invalid input dimensions for cubic curve fitting.");
    }

    double sum_x = 0.0, sum_y = 0.0, sum_x_squared = 0.0, sum_x_cubed = 0.0,
           sum_xy = 0.0, sum_x_squared_y = 0.0, sum_squared = 0.0;

    for (size_t i = 0; i < n; ++i) {
        double xi_squared = x[i] * x[i];
        double xi_cubed = xi_squared * x[i];

        sum_x += x[i];
        sum_y += y[i];
        sum_x_squared += xi_squared;
        sum_x_cubed += xi_cubed;
        sum_xy += x[i] * y[i];
        sum_x_squared_y += xi_squared * y[i];
    }

    double determinant = n * sum_x_squared * sum_x_squared * sum_x_squared -
                         sum_x_squared * sum_x_squared * sum_x * sum_x_squared -
                         sum_x * sum_x * sum_x_squared * sum_x_squared +
                         sum_x_squared * sum_x * sum_x * sum_x_squared +
                         sum_x * sum_x * sum_x * sum_x_squared -
                         n * sum_x * sum_x * sum_x * sum_x;

    double a = (n * sum_x_squared * sum_x_squared_y -
                sum_x_squared * sum_x * sum_xy * sum_x_squared -
                sum_x * sum_x_squared_y * sum_x_squared +
                sum_x_squared * sum_x * sum_x * sum_xy +
                sum_x * sum_x * sum_x_squared * sum_x * sum_y -
                n * sum_x * sum_x * sum_x * sum_xy) /
               determinant;

    double b = (n * sum_x_squared * sum_x_squared * sum_xy -
                sum_x_squared_y * sum_x_squared * sum_x_squared +
                sum_x * sum_x * sum_x_squared_y * sum_x_squared -
                sum_x_squared * sum_x * sum_x * sum_x * sum_xy -
                sum_x_squared * sum_x_squared * sum_x * sum_y +
                n * sum_x * sum_x * sum_x * sum_x * sum_xy) /
               determinant;

    double c =
        (n * sum_x_squared * sum_x_squared * sum_x * sum_xy -
         sum_x_squared * sum_x_squared_y * sum_x_squared * sum_x +
         sum_x * sum_x * sum_x_squared_y * sum_x_squared * sum_x_squared -
         sum_x_squared * sum_x * sum_x * sum_x * sum_x_squared -
         sum_x * sum_x_squared * sum_x_squared * sum_x * sum_y +
         n * sum_x * sum_x * sum_x * sum_squared * sum_x * sum_y) /
        determinant;

    double d =
        (n * sum_x_squared * sum_x_squared * sum_x * sum_x * sum_xy -
         sum_x_squared * sum_x_squared_y * sum_x_squared * sum_x_squared *
             sum_x +
         sum_x_squared * sum_x * sum_x_squared_y * sum_x_squared *
             sum_x_squared -
         sum_x_squared * sum_x * sum_x * sum_x * sum_x_squared -
         sum_x * sum_x_squared * sum_x_squared * sum_x * sum_x_squared +
         n * sum_x * sum_x * sum_x * sum_squared * sum_x * sum_x_squared) /
        determinant;

    return {a, b, c, d};
}

std::vector<double> gpmp::optim::Func::nelder_mead(
    const std::function<double(const std::vector<double> &)> &func,
    std::vector<double> initial_point,
    double tolerance,
    size_t max_iterations) {
    size_t n = initial_point.size();
    std::vector<std::vector<double>> simplex(n + 1, initial_point);

    for (size_t i = 0; i < n; ++i) {
        simplex[i][i] += 1.0;
    }

    std::vector<double> values(n + 1);
    for (size_t i = 0; i <= n; ++i) {
        values[i] = func(simplex[i]);
    }

    for (size_t iteration = 0; iteration < max_iterations; ++iteration) {
        size_t highest_index =
            std::distance(values.begin(),
                          std::max_element(values.begin(), values.end()));
        size_t lowest_index =
            std::distance(values.begin(),
                          std::min_element(values.begin(), values.end()));

        std::vector<double> centroid =
            calculate_centroid(simplex, highest_index);

        // Reflect
        std::vector<double> reflected_point =
            reflect(simplex[highest_index], centroid, 1.0);
        double reflected_value = func(reflected_point);

        if (reflected_value < values[lowest_index]) {
            // Expand
            std::vector<double> expanded_point =
                reflect(simplex[highest_index], centroid, 2.0);
            double expanded_value = func(expanded_point);

            if (expanded_value < reflected_value) {
                simplex[highest_index] = expanded_point;
                values[highest_index] = expanded_value;
            } else {
                simplex[highest_index] = reflected_point;
                values[highest_index] = reflected_value;
            }
        } else if (reflected_value >= values[lowest_index] &&
                   reflected_value < values[highest_index]) {
            simplex[highest_index] = reflected_point;
            values[highest_index] = reflected_value;
        } else {
            // Contract
            std::vector<double> contracted_point =
                reflect(simplex[highest_index], centroid, 0.5);
            double contracted_value = func(contracted_point);

            if (contracted_value < values[highest_index]) {
                simplex[highest_index] = contracted_point;
                values[highest_index] = contracted_value;
            } else {
                // Shrink
                for (size_t i = 0; i <= n; ++i) {
                    if (i != lowest_index) {
                        for (size_t j = 0; j < n; ++j) {
                            simplex[i][j] = 0.5 * (simplex[i][j] +
                                                   simplex[lowest_index][j]);
                        }
                        values[i] = func(simplex[i]);
                    }
                }
            }
        }

        // Check convergence
        double range = calculate_range(values);
        if (range < tolerance) {
            return simplex[lowest_index];
        }
    }

    return simplex[std::distance(
        values.begin(),
        std::min_element(values.begin(), values.end()))];
}

// Helper methods for Nelder–Mead

std::vector<double> gpmp::optim::Func::calculate_centroid(
    const std::vector<std::vector<double>> &simplex,
    size_t exclude_index) {
    size_t n = simplex[0].size();
    std::vector<double> centroid(n, 0.0);

    for (size_t i = 0; i < simplex.size(); ++i) {
        if (i != exclude_index) {
            for (size_t j = 0; j < n; ++j) {
                centroid[j] += simplex[i][j];
            }
        }
    }

    for (size_t j = 0; j < n; ++j) {
        centroid[j] /= (simplex.size() - 1);
    }

    return centroid;
}

std::vector<double>
gpmp::optim::Func::reflect(const std::vector<double> &point,
                           const std::vector<double> &centroid,
                           double reflection_coefficient) {
    size_t n = point.size();
    std::vector<double> reflected_point(n);

    for (size_t i = 0; i < n; ++i) {
        reflected_point[i] =
            centroid[i] + reflection_coefficient * (centroid[i] - point[i]);
    }

    return reflected_point;
}

double gpmp::optim::Func::calculate_range(const std::vector<double> &values) {
    double max_value = *std::max_element(values.begin(), values.end());
    double min_value = *std::min_element(values.begin(), values.end());

    return max_value - min_value;
}

std::vector<double>
gpmp::optim::Func::golden_section_search_minimize_multivariate(
    const std::function<double(const std::vector<double> &)> &func,
    const std::vector<double> &lower_bounds,
    const std::vector<double> &upper_bounds,
    double tol,
    const std::vector<double> &x1,
    const std::vector<double> &x2) {

    std::vector<double> best_point;
    double best_value = std::numeric_limits<double>::infinity();

    // Perform golden section search for each dimension
    for (size_t i = 0; i < lower_bounds.size(); ++i) {
        double a = lower_bounds[i];
        double b = upper_bounds[i];
        double x1_i = x1[i];
        double x2_i = x2[i];

        double result = golden_section_search_minimize(
            [&](double t) {
                std::vector<double> point(x1);
                point[i] = calculate_midpoint(x1_i, x2_i, t);
                return func(point);
            },
            a,
            b,
            tol,
            0.382,
            0.618);

        if (result < best_value) {
            best_value = result;
            best_point = x1;
            best_point[i] = calculate_midpoint(x1_i, x2_i, result);
        }
    }

    return best_point;
}
