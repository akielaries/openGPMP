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
#ifndef CDFS_HPP
#define CDFS_HPP

namespace gpmp {
namespace stats {

/**
 * @class CDF
 * @brief Class providing methods for computing cumulative distribution
 * functions (CDFs)
 */
class CDF {
  public:
    /**
     * @brief Compute the cumulative distribution function (CDF) of the
     * Bernoulli distribution
     * @param x The value at which to evaluate the CDF
     * @param p The probability parameter of the Bernoulli distribution
     * @return The CDF value at the given point
     */
    static double bernoulli(double x, double p);

    /**
     * @brief Compute the cumulative distribution function (CDF) of the beta
     * distribution
     * @param x The value at which to evaluate the CDF
     * @param alpha The alpha parameter of the beta distribution
     * @param beta The beta parameter of the beta distribution
     * @return The CDF value at the given point
     */
    static double beta(double x, double alpha, double beta);

    /**
     * @brief Compute the cumulative distribution function (CDF) of the binomial
     * distribution
     * @param k The number of successes
     * @param n The number of trials
     * @param p The probability of success in each trial
     * @return The CDF value at the given point
     */
    static double binomial(int k, int n, double p);

    /**
     * @brief Compute the cumulative distribution function (CDF) of the Cauchy
     * distribution
     * @param x The value at which to evaluate the CDF
     * @param x0 The location parameter of the Cauchy distribution
     * @param gamma The scale parameter of the Cauchy distribution
     * @return The CDF value at the given point
     */
    static double cauchy(double x, double x0, double gamma);

    /**
     * @brief Compute the cumulative distribution function (CDF) of the
     * chi-squared distribution
     * @param x The value at which to evaluate the CDF
     * @param k The degrees of freedom parameter of the chi-squared distribution
     * @return The CDF value at the given point
     */
    static double chi_squared(double x, double k);

    /**
     * @brief Compute the cumulative distribution function (CDF) of the
     * exponential distribution
     * @param x The value at which to evaluate the CDF
     * @param lambda The rate parameter of the exponential distribution
     * @return The CDF value at the given point
     */
    static double exponential(double x, double lambda);

    /**
     * @brief Compute the cumulative distribution function (CDF) of the F
     * distribution
     * @param x The value at which to evaluate the CDF
     * @param df1 The numerator degrees of freedom parameter of the F
     * distribution
     * @param df2 The denominator degrees of freedom parameter of the F
     * distribution
     * @return The CDF value at the given point
     */
    static double f(double x, double df1, double df2);

    /**
     * @brief Compute the cumulative distribution function (CDF) of the gamma
     * distribution
     * @param x The value at which to evaluate the CDF
     * @param shape The shape parameter of the gamma distribution
     * @param scale The scale parameter of the gamma distribution
     * @return The CDF value at the given point
     */
    static double gamma(double x, double shape, double scale);

    /**
     * @brief Compute the cumulative distribution function (CDF) of the
     * inverse-gamma distribution
     * @param x The value at which to evaluate the CDF
     * @param shape The shape parameter of the inverse-gamma distribution
     * @param scale The scale parameter of the inverse-gamma distribution
     * @return The CDF value at the given point
     */
    static double inverse_gamma(double x, double shape, double scale);

    /**
     * @brief Compute the cumulative distribution function (CDF) of the
     * inverse-Gaussian distribution
     * @param x The value at which to evaluate the CDF
     * @param mu The mean parameter of the inverse-Gaussian distribution
     * @param lambda The shape parameter of the inverse-Gaussian distribution
     * @return The CDF value at the given point
     */
    static double inverse_gaussian(double x, double mu, double lambda);

    /**
     * @brief Compute the cumulative distribution function (CDF) of the Laplace
     * distribution
     * @param x The value at which to evaluate the CDF
     * @param mu The location parameter of the Laplace distribution
     * @param b The scale parameter of the Laplace distribution
     * @return The CDF value at the given point
     */
    static double laplace(double x, double mu, double b);

    /**
     * @brief Compute the cumulative distribution function (CDF) of the logistic
     * distribution
     * @param x The value at which to evaluate the CDF
     * @param mu The location parameter of the logistic distribution
     * @param s The scale parameter of the logistic distribution
     * @return The CDF value at the given point
     */
    static double logistic(double x, double mu, double s);

    /**
     * @brief Compute the cumulative distribution function (CDF) of the
     * log-normal distribution
     * @param x The value at which to evaluate the CDF
     * @param mu The mean parameter of the log-normal distribution
     * @param sigma The standard deviation parameter of the log-normal
     * distribution
     * @return The CDF value at the given point
     */
    static double log_normal(double x, double mu, double sigma);

    /**
     * @brief Compute the cumulative distribution function (CDF) of the normal
     * (Gaussian) distribution
     * @param x The value at which to evaluate the CDF
     * @param mu The mean parameter of the normal distribution
     * @param sigma The standard deviation parameter of the normal distribution
     * @return The CDF value at the given point
     */
    static double gaussian(double x, double mu, double sigma);

    /**
     * @brief Compute the cumulative distribution function (CDF) of the Poisson
     * distribution
     * @param k The number of occurrences
     * @param lambda The rate parameter of the Poisson distribution
     * @return The CDF value at the given point
     */
    static double poisson(int k, double lambda);

    /**
     * @brief Compute the cumulative distribution function (CDF) of the
     * Rademacher distribution
     * @param x The value at which to evaluate the CDF
     * @return The CDF value at the given point
     */
    static double rademacher(double x);

    /**
     * @brief Compute the cumulative distribution function (CDF) of Student's t
     * distribution
     * @param x The value at which to evaluate the CDF
     * @param df The degrees of freedom parameter of Student's t distribution
     * @return The CDF value at the given point
     */
    static double student_t(double x, double df);

    /**
     * @brief Compute the cumulative distribution function (CDF) of the uniform
     * distribution
     * @param x The value at which to evaluate the CDF
     * @param a The minimum value of the uniform distribution
     * @param b The maximum value of the uniform distribution
     * @return The CDF value at the given point
     */
    static double uniform(double x, double a, double b);

    /**
     * @brief Compute the cumulative distribution function (CDF) of the Weibull
     * distribution
     * @param x The value at which to evaluate the CDF
     * @param shape The shape parameter of the Weibull distribution
     * @param scale The scale parameter of the Weibull distribution
     * @return The CDF value at the given point
     */
    static double weibull(double x, double shape, double scale);

    /**
     * @brief Compute the cumulative distribution function (CDF) of the standard
     * normal distribution
     * @param x The value at which to evaluate the CDF
     * @return The CDF value at the given point
     */
    static double normal_cdf(double x);

    /**
     * @brief Compute the incomplete beta function
     * @param a The first parameter of the incomplete beta function
     * @param b The second parameter of the incomplete beta function
     * @param x The value at which to evaluate the incomplete beta function
     * @return The value of the incomplete beta function at the given point
     */
    static double incomplete_beta(double a, double b, double x);

    /**
     * @brief Compute the incomplete gamma function
     * @param a The shape parameter of the incomplete gamma function
     * @param x The value at which to evaluate the incomplete gamma function
     * @return The value of the incomplete gamma function at the given point
     */
    static double incomplete_gamma(double a, double x);
};

} // namespace stats
} // namespace gpmp

#endif
