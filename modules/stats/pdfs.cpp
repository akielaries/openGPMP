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
#include <algorithm>
#include <cmath>
#include <limits>
#include <numeric>
#include <openGPMP/core/utils.hpp>
#include <openGPMP/stats/pdfs.hpp>
#include <random>
#include <stdexcept>
#include <vector>

// Bernoulli distribution
// Bernoulli distribution
double gpmp::stats::PDF::bernoulli(double x, double p) {
    if (std::abs(x - 0) < std::numeric_limits<double>::epsilon())
        return 1 - p;
    else if (std::abs(x - 1) < std::numeric_limits<double>::epsilon())
        return p;
    else
        return 0;
}

// Beta distribution
double gpmp::stats::PDF::beta(double x, double alpha, double beta) {
    if (x < 0 || x > 1)
        return 0;
    else
        return (std::pow(x, alpha - 1) * std::pow(1 - x, beta - 1)) /
               beta_function(alpha, beta);
}

// Binomial distribution
double gpmp::stats::PDF::binomial(int k, int n, double p) {
    if (k < 0 || k > n)
        return 0;
    else
        return binomial_coefficient(n, k) * std::pow(p, k) *
               std::pow(1 - p, n - k);
}

// Cauchy distribution
double gpmp::stats::PDF::cauchy(double x, double x0, double gamma) {
    return (1 / (M_PI * gamma)) *
           (gamma * gamma / ((x - x0) * (x - x0) + gamma * gamma));
}

// Chi-squared distribution
double gpmp::stats::PDF::chi_squared(double x, int k) {
    if (x < 0)
        return 0;
    else
        return (std::pow(x, k / 2.0 - 1) * std::exp(-x / 2.0)) /
               (std::pow(2, k / 2.0) * std::tgamma(k / 2.0));
}

// Exponential distribution
double gpmp::stats::PDF::exponential(double x, double lambda) {
    if (x < 0)
        return 0;
    else
        return lambda * std::exp(-lambda * x);
}

// F distribution
double gpmp::stats::PDF::f_dist(double x, int df1, int df2) {
    if (x < 0)
        return 0;
    else
        return std::pow(df1, df1 / 2.0) * std::pow(df2, df2 / 2.0) *
               std::pow(x, df1 / 2.0 - 1) /
               (std::pow(df2 + df1 * x, (df1 + df2) / 2.0) *
                std::tgamma(df1 / 2.0) * std::tgamma(df2 / 2.0));
}

// Gamma distribution
double gpmp::stats::PDF::gamma(double x, double alpha, double beta) {
    if (x < 0)
        return 0;
    else
        return (std::pow(x, alpha - 1) * std::exp(-x / beta)) /
               (std::pow(beta, alpha) * std::tgamma(alpha));
}

// Inverse-Gamma distribution
double gpmp::stats::PDF::inverse_gamma(double x, double alpha, double beta) {
    if (x <= 0)
        return 0;
    else
        return (std::pow(beta, alpha) * std::pow(x, -alpha - 1) *
                std::exp(-beta / x)) /
               std::tgamma(alpha);
}

// Inverse-Gaussian distribution
double gpmp::stats::PDF::inverse_gaussian(double x, double mu, double lambda) {
    if (x <= 0)
        return 0;
    else
        return std::sqrt(lambda / (2 * M_PI * x * x * x)) *
               std::exp(-lambda * (x - mu) * (x - mu) / (2 * mu * mu * x));
}

// Laplace distribution
double gpmp::stats::PDF::laplace(double x, double mu, double b) {
    return 0.5 * std::exp(-std::abs(x - mu) / b) / b;
}

// Logistic distribution
double gpmp::stats::PDF::logistic(double x, double mu, double s) {
    double z = (x - mu) / s;
    return std::exp(-z) / (s * std::pow(1 + std::exp(-z), 2));
}

// Log-Normal distribution
double gpmp::stats::PDF::log_normal(double x, double mu, double sigma) {
    if (x <= 0)
        return 0;
    else
        return (1 / (x * sigma * std::sqrt(2 * M_PI))) *
               std::exp(-0.5 * std::pow((std::log(x) - mu) / sigma, 2));
}

// Normal (Gaussian) distribution
double gpmp::stats::PDF::gaussian(double x, double mu, double sigma) {
    return (1 / (sigma * std::sqrt(2 * M_PI))) *
           std::exp(-0.5 * std::pow((x - mu) / sigma, 2));
}

// Poisson distribution
double gpmp::stats::PDF::poisson(int k, double lambda) {
    if (k < 0)
        return 0;
    else
        return std::exp(-lambda) * std::pow(lambda, k) /
               gpmp::core::Misc::factorial(k);
}

// Rademacher distribution
double gpmp::stats::PDF::rademacher(int k) {
    if (k == -1)
        return 0.5;
    else if (k == 1)
        return 0.5;
    else
        return 0;
}

// Student's t distribution
double gpmp::stats::PDF::student_t(double x, int df) {
    double numerator = std::tgamma((df + 1) / 2.0);
    double denominator = std::sqrt(df * M_PI) * std::tgamma(df / 2.0);
    return std::pow(1 + x * x / df, -(df + 1) / 2.0) * numerator / denominator;
}

// Uniform distribution
double gpmp::stats::PDF::uniform(double x, double a, double b) {
    if (x >= a && x <= b)
        return 1 / (b - a);
    else
        return 0;
}

// Weibull distribution
double gpmp::stats::PDF::weibull(double x, double k, double lambda) {
    if (x < 0)
        return 0;
    else
        return (k / lambda) * std::pow(x / lambda, k - 1) *
               std::exp(-std::pow(x / lambda, k));
}

// Function to calculate binomial coefficient
double gpmp::stats::PDF::binomial_coefficient(int n, int k) {
    double result = 1.0;
    for (int i = 1; i <= k; ++i) {
        result *= static_cast<double>(n - (k - i)) / i;
    }
    return result;
}

// Function to calculate beta function
double gpmp::stats::PDF::beta_function(double alpha, double beta) {
    return std::tgamma(alpha) * std::tgamma(beta) / std::tgamma(alpha + beta);
}
