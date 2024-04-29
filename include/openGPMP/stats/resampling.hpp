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
#ifndef RESAMPLING_HPP
#define RESAMPLING_HPP

#include <algorithm>
#include <random>
#include <stdexcept>
#include <vector>

namespace gpmp {

namespace stats {

/**
 * @class Resampling
 * @brief A class providing various resampling methods for statistical analysis
 */
class Resampling {
  public:
    /**
     * @brief Perform bootstrap resampling
     * @param data The original data
     * @param numSamples The number of bootstrap samples
     * @return A vector of bootstrap samples
     */
    static std::vector<int> bootstrap(const std::vector<int> &data,
                                      int numSamples);

    /**
     * @brief Perform subsampling
     * @param data The original data
     * @param numSamples The number of subsamples
     * @return A vector of subsampled data
     */
    static std::vector<int> subsample(const std::vector<int> &data,
                                      int numSamples);

    /**
     * @brief Perform jackknife resampling
     * @param data The original data
     * @return A vector of jackknife resamples
     */
    static std::vector<std::vector<int>>
    jackknife(const std::vector<int> &data);

    /**
     * @brief Perform permutation test
     * @param data The original data
     * @param numPermutations The number of permutations
     * @return A vector of permuted data sets
     */
    static std::vector<std::vector<int>>
    permutation_test(const std::vector<int> &data, int numPermutations);

    /**
     * @brief Perform bootstrap t-statistic resampling
     * @param data The original data
     * @param numSamples The number of bootstrap samples
     * @return A vector of bootstrap t-statistics
     */
    static std::vector<double> bootstrap_t(const std::vector<double> &data,
                                           int numSamples);

    /**
     * @brief Calculate confidence interval using bootstrap
     * @param data The original data
     * @param alpha The significance level
     * @param numSamples The number of bootstrap samples
     * @return A pair representing the lower and upper bounds of the confidence
     * interval
     */
    static std::pair<double, double>
    bootstrap_ci(const std::vector<double> &data, double alpha, int numSamples);

    /**
     * @brief Perform smoothed bootstrap resampling
     * @param data The original data
     * @param numSamples The number of bootstrap samples
     * @return A vector of smoothed bootstrap samples
     */
    static std::vector<double>
    smoothed_bootstrap(const std::vector<double> &data, int numSamples);

    /**
     * @brief Perform circular block bootstrap resampling
     * @param data The original data
     * @param blockSize The size of each block
     * @param numSamples The number of bootstrap samples
     * @return A vector of circular block bootstrap samples
     */
    static std::vector<double>
    circular_block_bootstrap(const std::vector<double> &data,
                             int blockSize,
                             int numSamples);

    /**
     * @brief Perform time series bootstrap resampling
     * @param data The original time series data
     * @param numSamples The number of bootstrap samples
     * @return A vector of time series bootstrap samples
     */
    static std::vector<double>
    time_series_bootstrap(const std::vector<double> &data, int numSamples);

    /**
     * @brief Perform weighted bootstrap resampling
     * @param data The original data
     * @param weights The weights associated with each data point
     * @param size The size of each bootstrap sample
     * @return A vector of weighted bootstrap samples
     */
    static std::vector<double>
    weighted_bootstrap(const std::vector<double> &data,
                       const std::vector<double> &weights,
                       int size);

    /**
     * @brief Calculate the p-value using permutation test
     * @param data1 The first data set
     * @param data2 The second data set
     * @param observedStatistic The observed test statistic
     * @return The permutation p-value
     */
    static double permutation_p_value(const std::vector<double> &data1,
                                      const std::vector<double> &data2,
                                      double observedStatistic);
};
} // namespace stats
} // namespace gpmp

#endif
