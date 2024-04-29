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
#ifndef HYPOTHESIS_HPP
#define HYPOTHESIS_HPP

#include <algorithm>
#include <cmath>
#include <vector>

namespace gpmp {

namespace stats {

/**
 * @class HypothesisTest
 * @brief A class for conducting various statistical hypothesis tests
 */
class HypothesisTest {
  public:
    /**
     * @brief Constructor
     */
    HypothesisTest() {
    }

    /**
     * @brief Destructor
     */
    ~HypothesisTest() {
    }

    /**
     * @brief One-sample t-test
     * @param sample The sample data
     * @param populationMean The population mean
     * @return The t-statistic
     */
    static double one_sample_ttest(const std::vector<double> &sample,
                                   double populationMean);

    /**
     * @brief Two-sample t-test
     * @param sample1 The first sample data
     * @param sample2 The second sample data
     * @return The t-statistic
     */
    static double two_sample_ttest(const std::vector<double> &sample1,
                                   const std::vector<double> &sample2);

    /**
     * @brief Analysis of Variance (ANOVA)
     * @param samples The vector of sample data
     * @return The F-statistic
     */
    static double ANOVA(const std::vector<std::vector<double>> &samples);

    /**
     * @brief Chi-square test of independence
     * @param observed The observed data
     * @param expected The expected data
     * @return The chi-square statistic
     */
    static double
    chi_square_test(const std::vector<std::vector<int>> &observed,
                    const std::vector<std::vector<double>> &expected);

    /**
     * @brief Z-test for proportions
     * @param p1 The proportion for sample 1
     * @param p2 The proportion for sample 2
     * @param n1 The sample size for sample 1
     * @param n2 The sample size for sample 2
     * @return The z-score
     */
    static double proportion_z_test(double p1, double p2, double n1, double n2);

    /**
     * @brief Wilcoxon signed-rank test
     * @param sample1 The first sample data
     * @param sample2 The second sample data
     * @return The z-score
     */
    static double wilcoxon_rank_test(const std::vector<double> &sample1,
                                     const std::vector<double> &sample2);

    /**
     * @brief Mann-Whitney U test
     * @param sample1 The first sample data
     * @param sample2 The second sample data
     * @return The z-score
     */
    static double mann_whitney_test(const std::vector<double> &sample1,
                                    const std::vector<double> &sample2);

    /**
     * @brief Fisher's Exact Test
     * @param table The contingency table
     * @return The p-value
     */
    static double fisher_test(const std::vector<std::vector<int>> &table);

    /**
     * @brief Kolmogorov-Smirnov Test
     * @param sample1 The first sample data
     * @param sample2 The second sample data
     * @return The test statistic
     */
    static double kol_smirnov_test(const std::vector<double> &sample1,
                                   const std::vector<double> &sample2);

    /**
     * @brief Wilcoxon Rank Sum Test (Mann-Whitney U Test)
     * @param sample1 The first sample data
     * @param sample2 The second sample data
     * @return The U statistic
     */
    static double wilcoxon_rank_sum_test(const std::vector<double> &sample1,
                                         const std::vector<double> &sample2);

    /**
     * @brief Kruskal-Wallis Test
     * @param samples The vector of sample data
     * @return The test statistic
     */
    static double
    kruskal_wallis_test(const std::vector<std::vector<double>> &samples);

    /**
     * @brief Runs Test
     * @param sequence The binary sequence
     * @return The z-score
     */
    static double runs_test(const std::vector<bool> &sequence);

  private:
    /**
     * @brief Helper method to calculate factorial
     * @param n The integer value
     * @return The factorial of n
     */
    static int factorial(int n);
};
} // namespace stats

} // namespace gpmp

#endif
