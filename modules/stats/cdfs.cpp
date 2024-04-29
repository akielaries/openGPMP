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
#include <algorithm>
#include <cmath>
#include <limits>
#include <numeric>
#include <openGPMP/stats/cdfs.hpp>
#include <random>
#include <stdexcept>
#include <vector>

// Bernoulli CDF
double gpmp::stats::CDF::bernoulli(double x, double p) {
    if (x < 0)
        return 0.0;
    else if (x < 1)
        return 1 - (1 - p);
    else
        return 1.0;
}

// Beta CDF using the incomplete beta function
double gpmp::stats::CDF::beta(double x, double alpha, double beta) {
    if (x <= 0)
        return 0.0;
    else if (x >= 1)
        return 1.0;
    else
        return incomplete_beta(alpha, beta, x);
}

// Binomial CDF
double gpmp::stats::CDF::binomial(int k, int n, double p) {
    if (k < 0)
        return 0.0;
    else if (k >= n)
        return 1.0;
    else
        return incomplete_beta(1.0 - p, n - k, k + 1);
}

// Cauchy CDF
double gpmp::stats::CDF::cauchy(double x, double x0, double gamma) {
    return 0.5 + atan((x - x0) / gamma) / M_PI;
}

// Chi-squared CDF
double gpmp::stats::CDF::chi_squared(double x, double k) {
    if (x < 0)
        return 0.0;
    else
        return incomplete_gamma(k / 2.0, x / 2.0);
}

// Exponential CDF
double gpmp::stats::CDF::exponential(double x, double lambda) {
    if (x < 0)
        return 0.0;
    else
        return 1.0 - exp(-lambda * x);
}

// F CDF
double gpmp::stats::CDF::f(double x, double df1, double df2) {
    if (x <= 0)
        return 0.0;
    else
        return incomplete_beta(df1 / 2.0, df2 / 2.0, df1 / (df1 + df2 * x));
}

// Gamma CDF
double gpmp::stats::CDF::gamma(double x, double shape, double scale) {
    if (x < 0)
        return 0.0;
    else
        return incomplete_gamma(shape, x / scale);
}

// Inverse-Gamma CDF
double gpmp::stats::CDF::inverse_gamma(double x, double shape, double scale) {
    if (x <= 0)
        return 0.0;
    else
        return 1.0 - incomplete_gamma(shape, scale / x);
}

// Inverse-Gaussian CDF
double gpmp::stats::CDF::inverse_gaussian(double x, double mu, double lambda) {
    if (x <= 0)
        return 0.0;
    else
        return normal_cdf(sqrt(lambda / x) * (x / mu - 1.0));
}

// Laplace CDF
double gpmp::stats::CDF::laplace(double x, double mu, double b) {
    if (x < mu)
        return 0.5 * exp((x - mu) / b);
    else
        return 1.0 - 0.5 * exp(-(x - mu) / b);
}

// Logistic CDF
double gpmp::stats::CDF::logistic(double x, double mu, double s) {
    return 1.0 / (1.0 + exp(-(x - mu) / s));
}

// Log-Normal CDF
double gpmp::stats::CDF::log_normal(double x, double mu, double sigma) {
    if (x <= 0)
        return 0.0;
    else
        return 0.5 + 0.5 * erf((log(x) - mu) / (sqrt(2.0) * sigma));
}

// Normal (Gaussian) CDF
double gpmp::stats::CDF::gaussian(double x, double mu, double sigma) {
    return 0.5 * (1 + erf((x - mu) / (sigma * sqrt(2))));
}

// Poisson CDF
double gpmp::stats::CDF::poisson(int k, double lambda) {
    if (k < 0)
        return 0.0;
    else
        return incomplete_gamma(k + 1, lambda);
}

// Rademacher CDF
double gpmp::stats::CDF::rademacher(double x) {
    if (x < 0)
        return 0.0;
    else if (x < 0.5)
        return 0.0;
    else
        return 1.0;
}

// Student's t CDF
double gpmp::stats::CDF::student_t(double x, double df) {
    if (df <= 0)
        return NAN;
    return 0.5 + 0.5 * std::tgamma((df + 1) / 2) * std::hypot(1, x / sqrt(df)) /
                     (sqrt(df) * std::tgamma(df / 2));
}

// Uniform CDF
double gpmp::stats::CDF::uniform(double x, double a, double b) {
    if (x < a)
        return 0.0;
    else if (x < b)
        return (x - a) / (b - a);
    else
        return 1.0;
}

// Weibull CDF
double gpmp::stats::CDF::weibull(double x, double shape, double scale) {
    if (x < 0)
        return 0.0;
    else
        return 1.0 - exp(-pow(x / scale, shape));
}

// Normal cumulative distribution function
double gpmp::stats::CDF::normal_cdf(double x) {
    return 0.5 * (1 + erf(x / sqrt(2.0)));
}

// Incomplete beta function for beta and binomial CDF
double gpmp::stats::CDF::incomplete_beta(double a, double b, double x) {
    const int maxIterations = 1000;
    const double epsilon = 1e-12;
    double result = 0.0;
    double term = 1.0;
    for (int k = 0; k < maxIterations; ++k) {
        term *=
            (k == 0 ? 1.0
                    : (a + k - 1) * (b - k) / (a + b + k - 1) * x / (k + 1));
        result += term;
        if (std::abs(term) < epsilon * std::abs(result))
            break;
    }
    return result * std::pow(x, a) * std::pow(1 - x, b) / (a * std::beta(a, b));
}

// Incomplete gamma function for chi-squared and gamma CDFs
double gpmp::stats::CDF::incomplete_gamma(double a, double x) {
    const int maxIterations = 1000;
    const double epsilon = 1e-12;
    double result = 0.0;
    double term = 1.0;
    for (int k = 0; k < maxIterations; ++k) {
        term *= x / (a + k);
        result += term;
        if (std::abs(term) < epsilon * std::abs(result))
            break;
    }
    return exp(-x) * std::pow(x, a) * result / std::tgamma(a);
}
