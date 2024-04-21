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
#ifndef PROBDIST_HPP
#define PROBDIST_HPP

#include <cmath>
#include <vector>

namespace gpmp {
namespace stats {

class ProbDist {

  public:
    /**
     * @brief Compute the quantile of the standard normal distribution
     * @param probability The probability value between 0 and 1
     * @return The quantile corresponding to the given probability
     */
    double quantile_dist(double probability);
    /**
     * @brief Compute the probability density function (PDF) for the normal
     * distribution
     * @param x The value at which to evaluate the PDF
     * @param mean The mean of the distribution
     * @param stddev The standard deviation of the distribution
     * @return The PDF value at the given point
     */
    double normal_PDF(double x, double mean, double stddev);
    /**
     * @brief Compute the cumulative distribution function (CDF) for the normal
     * distribution
     * @param x The value at which to evaluate the CDF
     * @param mean The mean of the distribution
     * @param stddev The standard deviation of the distribution
     * @return The CDF value at the given point
     */
    double normal_CDF(double x, double mean, double stddev);
    /**
     * @brief Compute the cumulative distribution function (CDF) for the uniform
     * distribution
     * @param k The value at which to evaluate the CDF
     * @param n The maximum value in the uniform distribution
     * @return The CDF value at the given point
     */
    double uniform_CDF(size_t k, size_t n);
    /**
     * @brief Compute the probability density function (PDF) for the exponential
     * distribution
     * @param x The value at which to evaluate the PDF
     * @param k The shape parameter of the distribution
     * @param lambda The rate parameter of the distribution
     * @return The PDF value at the given point
     */
    double exp_PDF(double x, size_t k, double lambda);
    /**
     * @brief Compute the empirical cumulative distribution function (CDF) for a
     * given value
     * @param data The dataset
     * @param x The value at which to evaluate the empirical CDF
     * @return The empirical CDF value at the given point
     */
    double emp_CDF(const std::vector<double> &data, double x);
    /**
     * @brief Compute the empirical probability mass function (PMF) for a given
     * value
     * @param data The dataset
     * @param x The value at which to evaluate the empirical PMF
     * @return The empirical PMF value at the given point
     */
    double emp_PMF(const std::vector<double> &data, double x);
    /**
     * @brief Compute the inverse of the empirical cumulative distribution
     * function (CDF) for a given probability
     * @param data The dataset
     * @param p The probability value between 0 and 1
     * @return The value at which the empirical CDF is equal to or greater than
     * the given probability
     */
    double inverse_emp_CDF(const std::vector<double> &data, double p);

    /**
     * @brief Compute the Maximum Likelihood Estimate (MLE) for the mean of a
     * dataset
     * @param data The dataset
     * @return The MLE estimate for the mean
     */
    double mle(const std::vector<double> &data);

    /**
     * @brief Compute the method of moments (MOM) estimate for the mean of a
     * dataset
     * @param data The dataset
     * @return The MOM estimate for the mean
     */
    double mom(const std::vector<double> &data);
    /**
     * @brief Placeholder function for M-estimation
     * @param data The dataset
     * @return The M-estimation result
     */
    double mle_est(const std::vector<double> &data);

    /**
     * @brief Compute the Mean-Unbiased Minimum-Variance (MUMV) estimate for the
     * mean of a dataset
     * @param data The dataset
     * @return The MUMV estimate for the mean
     */
    double mumv(const std::vector<double> &data);
    /**
     * @brief Compute the median-unbiased estimate for the median of a dataset
     * @param data The dataset
     * @return The median-unbiased estimate for the median
     */
    double median_uniased(const std::vector<double> &data);

    /**
     * @brief Compute the confidence interval for the mean of a dataset
     * @param data The dataset
     * @param alpha The confidence level
     * @return A pair representing the lower and upper bounds of the confidence
     * interval
     */
    std::pair<double, double>
    ConfidenceInterval(const std::vector<double> &data, double alpha);
    /**
     * @brief Compute the value of a pivot function for interval estimation
     * @param data The dataset
     * @param pivotFunction The pivot function to evaluate
     * @return The value of the pivot function
     */
    double Pivot(const std::vector<double> &data,
                 double pivotFunction(const std::vector<double> &));
    /**
     * @brief Example pivot function for computing a confidence interval
     * @param data The dataset
     * @return The value of the pivot function for a confidence interval
     */
    double PivotFunctionForConfidenceInterval(const std::vector<double> &data);
    /**
     * @brief Compute the likelihood interval for a given dataset and
     * significance level
     * @param data The dataset
     * @param alpha The significance level
     * @return A pair representing the lower and upper bounds of the likelihood
     * interval
     */
    std::pair<double, double>
    LikelihoodInterval(const std::vector<double> &data, double alpha);

    /**
     * @brief Compute the prediction interval for a given dataset and
     * significance level
     * @param data The dataset
     * @param alpha The significance level
     * @return A pair representing the lower and upper bounds of the prediction
     * interval
     */
    std::pair<double, double>
    PredictionInterval(const std::vector<double> &data, double alpha);

    /**
     * @brief Compute the tolerance interval for a given dataset and
     * significance level
     * @param data The dataset
     * @param alpha The significance level
     * @return A pair representing the lower and upper bounds of the tolerance
     * interval
     */
    std::pair<double, double> ToleranceInterval(const std::vector<double> &data,
                                                double alpha);

    /**
     * @brief Compute the bootstrap resampling confidence interval for a given
     * dataset and number of samples
     * @param data The dataset
     * @param numSamples The number of bootstrap samples
     * @return A pair representing the lower and upper bounds of the bootstrap
     * resampling confidence interval
     */
    std::pair<double, double>
    BootstrapResampling(const std::vector<double> &data, int numSamples);
    /**
     * @brief Compute the Jackknife resampling confidence interval for a given
     * dataset
     * @param data The dataset
     * @return A pair representing the lower and upper bounds of the Jackknife
     * resampling confidence interval
     */
    std::pair<double, double>
    JackknifeResampling(const std::vector<double> &data);
};

} // namespace stats
} // namespace gpmp

#endif
