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
#ifndef PDFS_HPP
#define PDFS_HPP

namespace gpmp {
namespace stats {

/**
 * @brief Class representing Probability Distribution Functions (PDFs)
 */
class PDF {
  public:
    /**
     * @brief Calculates the probability of success in a Bernoulli trial
     *
     * @param x The outcome (0 or 1)
     * @param p The probability of success
     * @return The probability of observing the outcome
     */
    static double bernoulli(double x, double p);

    /**
     * @brief Calculates the probability density function (PDF) of the Beta
     * distribution
     *
     * @param x The value at which to evaluate the PDF
     * @param alpha The shape parameter alpha (> 0)
     * @param beta The shape parameter beta (> 0)
     * @return The value of the PDF at x
     */
    static double beta(double x, double alpha, double beta);

    /**
     * @brief Calculates the probability of observing k successes in n
     * independent Bernoulli trials
     *
     * @param k The number of successes
     * @param n The number of trials
     * @param p The probability of success in each trial
     * @return The probability of observing k successes
     */
    static double binomial(int k, int n, double p);

    /**
     * @brief Calculates the probability density function (PDF) of the Cauchy
     * distribution
     *
     * @param x The value at which to evaluate the PDF
     * @param x0 The location parameter
     * @param gamma The scale parameter (> 0)
     * @return The value of the PDF at x
     */
    static double cauchy(double x, double x0, double gamma);

    /**
     * @brief Calculates the probability density function (PDF) of the
     * chi-squared distribution
     *
     * @param x The value at which to evaluate the PDF
     * @param k The degrees of freedom (> 0)
     * @return The value of the PDF at x
     */
    static double chi_squared(double x, int k);

    /**
     * @brief Calculates the probability density function (PDF) of the
     * exponential distribution
     *
     * @param x The value at which to evaluate the PDF
     * @param lambda The rate parameter (> 0)
     * @return The value of the PDF at x
     */
    static double exponential(double x, double lambda);

    /**
     * @brief Calculates the probability density function (PDF) of the F
     * distribution
     *
     * @param x The value at which to evaluate the PDF
     * @param df1 The degrees of freedom of the numerator (> 0)
     * @param df2 The degrees of freedom of the denominator (> 0)
     * @return The value of the PDF at x
     */
    static double f_dist(double x, int df1, int df2);

    /**
     * @brief Calculates the probability density function (PDF) of the gamma
     * distribution
     *
     * @param x The value at which to evaluate the PDF
     * @param alpha The shape parameter (> 0)
     * @param beta The scale parameter (> 0)
     * @return The value of the PDF at x
     */
    static double gamma(double x, double alpha, double beta);

    /**
     * @brief Calculates the probability density function (PDF) of the inverse
     * gamma distribution
     *
     * @param x The value at which to evaluate the PDF
     * @param alpha The shape parameter (> 0)
     * @param beta The scale parameter (> 0)
     * @return The value of the PDF at x
     */
    static double inverse_gamma(double x, double alpha, double beta);

    /**
     * @brief Calculates the probability density function (PDF) of the inverse
     * Gaussian distribution
     *
     * @param x The value at which to evaluate the PDF
     * @param mu The mean parameter (> 0)
     * @param lambda The shape parameter (> 0)
     * @return The value of the PDF at x
     */
    static double inverse_gaussian(double x, double mu, double lambda);

    /**
     * @brief Calculates the probability density function (PDF) of the Laplace
     * distribution
     *
     * @param x The value at which to evaluate the PDF
     * @param mu The location parameter
     * @param b The scale parameter (> 0)
     * @return The value of the PDF at x
     */
    static double laplace(double x, double mu, double b);

    /**
     * @brief Calculates the probability density function (PDF) of the logistic
     * distribution
     *
     * @param x The value at which to evaluate the PDF
     * @param mu The location parameter
     * @param s The scale parameter (> 0)
     * @return The value of the PDF at x
     */
    static double logistic(double x, double mu, double s);

    /**
     * @brief Calculates the probability density function (PDF) of the
     * log-normal distribution
     *
     * @param x The value at which to evaluate the PDF
     * @param mu The mean of the underlying normal distribution
     * @param sigma The standard deviation of the underlying normal distribution
     * (> 0)
     * @return The value of the PDF at x
     */
    static double log_normal(double x, double mu, double sigma);

    /**
     * @brief Calculates the probability density function (PDF) of the Gaussian
     * (normal) distribution
     *
     * @param x The value at which to evaluate the PDF
     * @param mu The mean of the distribution
     * @param sigma The standard deviation of the distribution (> 0)
     * @return The value of the PDF at x
     */
    static double gaussian(double x, double mu, double sigma);

    /**
     * @brief Calculates the probability density function (PDF) of the Poisson
     * distribution
     *
     * @param k The number of events
     * @param lambda The rate parameter (> 0)
     * @return The value of the PDF at k
     */
    static double poisson(int k, double lambda);

    /**
     * @brief Calculates the probability density function (PDF) of the
     * Rademacher distribution
     *
     * @param k The value (1 or -1)
     * @return The value of the PDF at k
     */
    static double rademacher(int k);

    /**
     * @brief Calculates the probability density function (PDF) of Student's t
     * distribution
     *
     * @param x The value at which to evaluate the PDF
     * @param df The degrees of freedom (> 0)
     * @return The value of the PDF at x
     */
    static double student_t(double x, int df);

    /**
     * @brief Calculates the probability density function (PDF) of the uniform
     * distribution
     *
     * @param x The value at which to evaluate the PDF
     * @param a The minimum value of the interval
     * @param b The maximum value of the interval
     * @return The value of the PDF at x
     */
    static double uniform(double x, double a, double b);

    /**
     * @brief Calculates the probability density function (PDF) of the Weibull
     * distribution
     *
     * @param x The value at which to evaluate the PDF
     * @param k The shape parameter (> 0)
     * @param lambda The scale parameter (> 0)
     * @return The value of the PDF at x
     */
    static double weibull(double x, double k, double lambda);

    /**
     * @brief Calculates the binomial coefficient "n choose k"
     *
     * @param n The total number of items
     * @param k The number of items to choose
     * @return The binomial coefficient
     */
    static double binomial_coefficient(int n, int k);

    /**
     * @brief Calculates the beta function
     *
     * @param alpha The first shape parameter (> 0)
     * @param beta The second shape parameter (> 0)
     * @return The value of the beta function
     */
    static double beta_function(double alpha, double beta);

    /**
     * @brief Calculates the factorial of an integer
     *
     * @param n The integer
     * @return The factorial of n
     */
    static double factorial(int n);
};
} // namespace stats
} // namespace gpmp

#endif
