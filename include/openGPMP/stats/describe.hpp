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
#ifndef DESCRIBE_HPP
#define DESCRIBE_HPP

#include <vector>

namespace gpmp {
namespace stats {

/**
 * @brief A class providing methods for descriptive statistics
 */
class Describe {
  public:
    /**
     * @brief Calculates U statistic given two samples
     *
     * @param sample1
     * @param sample2
     * @return U statistic
     */
    static double u_stat(const std::vector<double> &sample1,
                         const std::vector<double> &sample2);

    /**
     * @brief Calculates the arithmetic mean of a given dataset
     *
     * @param data The input dataset
     * @return The arithmetic mean
     */
    static double mean_arith(const std::vector<double> &data);

    /**
     * @brief Calculates the geometric mean of a given dataset
     *
     * @param data The input dataset
     * @return The geometric mean
     */
    double mean_geo(const std::vector<double> &data);

    /**
     * @brief Calculates the cubic generalized mean of a given dataset with a
     * specified power
     *
     * @param data The input dataset
     * @param p The power parameter
     * @return The cubic generalized mean
     */
    double mean_cubic(const std::vector<double> &data, double p);

    /**
     * @brief Calculates the power geometric mean of a given dataset with a
     * specified power
     *
     * @param data The input dataset
     * @param p The power parameter
     * @return The power geometric mean
     */
    double mean_geo_pow(const std::vector<double> &data, double p);

    /**
     * @brief Calculates the harmonic mean of a given dataset
     *
     * @param data The input dataset
     * @return The harmonic mean
     */
    double mean_harmonic(const std::vector<double> &data);

    /**
     * @brief Calculates the Heronian mean of a given dataset
     *
     * @param data The input dataset
     * @return The Heronian mean
     */
    double mean_heronian(const std::vector<double> &data);

    /**
     * @brief Calculates the Heinz mean of a given dataset
     *
     * @param data The input dataset
     * @return The Heinz mean
     */
    double mean_heinz(const std::vector<double> &data);

    /**
     * @brief Calculates the Lehmer mean of a given dataset with a specified
     * power
     *
     * @param data The input dataset
     * @param p The power parameter
     * @return The Lehmer mean
     */
    double mean_lehmer(const std::vector<double> &data, double p);

    /**
     * @brief Calculates the median of a given dataset
     *
     * @param data The input dataset
     * @return The median
     */
    double Median(std::vector<double> data);
    /**
     * @brief Calculates the average absolute deviation of a given dataset
     *
     * @param data The input dataset
     * @return The average absolute deviation
     */
    double avg_abs_dev(const std::vector<double> &data);

    /**
     * @brief Calculates the coefficient of variation of a given dataset
     *
     * @param data The input dataset
     * @return The coefficient of variation (in percentage)
     */
    double var_coeff(const std::vector<double> &data);

    /**
     * @brief Calculates the interquartile range of a given dataset
     *
     * @param data The input dataset
     * @return The interquartile range
     */
    double iq_range(const std::vector<double> &data);
    /**
     * @brief Calculates the specified percentile of a given dataset
     *
     * @param data The input dataset
     * @param percentile The desired percentile (00 to 10)
     * @return The value at the specified percentile
     */
    double percentile(const std::vector<double> &data, double percentile);
    /**
     * @brief Calculates the range of a given dataset
     *
     * @param data The input dataset
     * @return The range
     */
    double range(const std::vector<double> &data);

    /**
     * @brief Calculates the standard deviation of a given dataset, given the
     * mean
     *
     * @param data The input dataset
     * @param mean The mean of the dataset
     * @return The standard deviation
     */
    static double stdev(const std::vector<double> &data, double mean);
    /**
     * @brief Calculates the variance of a given dataset, given the mean
     *
     * @param data The input dataset
     * @param mean The mean of the dataset
     * @return The variance
     */
    static double variance(const std::vector<double> &data, double mean);

    /**
     * @brief Calculates the standard error of the mean using the Central Limit
     * Theorem
     *
     * This method estimates the standard error of the mean based on the Central
     * Limit Theorem
     *
     * @param data The input dataset
     * @param numSamples The number of samples for the Central Limit Theorem
     * @return The estimated standard error of the mean
     */
    double clt(const std::vector<double> &data, int numSamples);

    /**
     * @brief Calculates the kurtosis of a given dataset
     *
     * This method measures the "tailedness" or sharpness of the dataset's peak
     *
     * @param data The input dataset
     * @param mean The mean of the dataset
     * @return The kurtosis value
     */
    double kurtosis(const std::vector<double> &data, double mean);
    /**
     * @brief Calculates the first L-moment of a given dataset
     *
     * L-moments are used to estimate the parameters of a probability
     * distribution
     *
     * @param data The input dataset
     * @param mean The mean of the dataset
     * @return The first L-moment
     */
    double lmoment1(const std::vector<double> &data, double mean);

    /**
     * @brief Calculates the second L-moment of a given dataset
     *
     * L-moments are used to estimate the parameters of a probability
     * distribution
     *
     * @param data The input dataset
     * @param mean The mean of the dataset
     * @return The second L-moment
     */
    double lmoment2(const std::vector<double> &data, double mean);
    /**
     * @brief Calculates the skewness of a given dataset
     *
     * This method measures the asymmetry of the dataset's distribution
     *
     * @param data The input dataset
     * @param mean The mean of the dataset
     * @param stddev The standard deviation of the dataset
     * @return The skewness value
     */
    double
    skewness(const std::vector<double> &data, double mean, double stddev);

    /**
     * @brief Ranks the data in ascending order
     *
     * This method assigns ranks to the data, where the smallest value gets rank
     * 1, the second smallest gets rank 2, and so on
     *
     * @param data The input dataset
     * @return A vector containing the ranks of the input data
     */
    std::vector<size_t> rank_data(const std::vector<double> &data);

    /**
     * @brief Calculates the partial correlation coefficient between two
     * variables, controlling for a third variable
     *
     * This method computes the partial correlation between variables X and Y,
     * controlling for variable Z
     *
     * @param x The values of variable X
     * @param y The values of variable Y
     * @param z The values of control variable Z
     * @return The partial correlation coefficient
     */
    double partial_corr(const std::vector<double> &x,
                        const std::vector<double> &y,
                        const std::vector<double> &z);
    /**
     * @brief Calculates the Pearson Product-Moment Correlation between two
     * variables
     *
     * This method measures the linear relationship between variables X and Y
     *
     * @param x The values of variable X
     * @param y The values of variable Y
     * @return The Pearson Product-Moment Correlation coefficient
     */
    double ppmc(const std::vector<double> &x, const std::vector<double> &y);

    /**
     * @brief Calculates Kendall's Tau Rank Correlation between two variables
     *
     * This method measures the strength and direction of monotonic
     * relationships between variables X and Y
     *
     * @param x The values of variable X
     * @param y The values of variable Y
     * @return Kendall's Tau Rank Correlation coefficient
     */
    double kendalls_tau(const std::vector<double> &x,
                        const std::vector<double> &y);
    /**
     * @brief Calculates Spearman's Rank Correlation between two variables
     *
     * This method measures the strength and direction of monotonic
     * relationships between variables X and Y
     *
     * @param x The values of variable X
     * @param y The values of variable Y
     * @return Spearman's Rank Correlation coefficient
     */
    double spearmans_rho(const std::vector<double> &x,
                         const std::vector<double> &y);
};

} // namespace stats
} // namespace gpmp

#endif
