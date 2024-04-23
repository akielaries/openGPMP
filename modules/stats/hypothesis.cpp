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
#include <iostream>
#include <limits>
#include <openGPMP/stats/describe.hpp>
#include <openGPMP/stats/hypothesis.hpp>
#include <vector>

// Method for conducting a one-sample t-test
double
gpmp::stats::HypothesisTest::one_sample_ttest(const std::vector<double> &sample,
                                              double populationMean) {
    int n = sample.size();
    double sampleMean = gpmp::stats::Describe::mean_arith(sample);
    double sampleStdDev = gpmp::stats::Describe::stdev(sample, sampleMean);
    double standardError = sampleStdDev / sqrt(n);
    return (sampleMean - populationMean) / standardError;
}

// Method for conducting a two-sample t-test
double gpmp::stats::HypothesisTest::two_sample_ttest(
    const std::vector<double> &sample1,
    const std::vector<double> &sample2) {
    int n1 = sample1.size();
    int n2 = sample2.size();
    double sampleMean1 = gpmp::stats::Describe::mean_arith(sample1);
    double sampleMean2 = gpmp::stats::Describe::mean_arith(sample2);
    double sampleVar1 = gpmp::stats::Describe::variance(sample1, sampleMean1);
    double sampleVar2 = gpmp::stats::Describe::variance(sample2, sampleMean2);
    double pooledVar =
        ((n1 - 1) * sampleVar1 + (n2 - 1) * sampleVar2) / (n1 + n2 - 2);
    double t =
        (sampleMean1 - sampleMean2) / sqrt(pooledVar * (1.0 / n1 + 1.0 / n2));
    return t;
}

// Method for conducting ANOVA (Analysis of Variance)
double gpmp::stats::HypothesisTest::ANOVA(
    const std::vector<std::vector<double>> &samples) {
    int k = samples.size();
    int n = 0;
    double grandMean = 0.0;
    double SSB = 0.0;
    double SSW = 0.0;

    // Calculate total number of observations and grand mean
    for (const auto &sample : samples) {
        n += sample.size();
        double sampleMean = gpmp::stats::Describe::mean_arith(sample);
        grandMean += sampleMean;
    }
    grandMean /= k;

    // Calculate sum of squares between groups (SSB) and within groups (SSW)
    for (int i = 0; i < k; ++i) {
        double sampleMean = gpmp::stats::Describe::mean_arith(samples[i]);
        for (double x : samples[i]) {
            SSB += pow((sampleMean - grandMean), 2);
            SSW += pow((x - sampleMean), 2);
        }
    }

    // Calculate degrees of freedom
    int dfBetweenGroups = k - 1;
    int dfWithinGroups = n - k;

    // Calculate F-statistic
    double MSB = SSB / dfBetweenGroups;
    double MSW = SSW / dfWithinGroups;
    double F = MSB / MSW;

    return F;
}

// Method for conducting chi-square test of independence
double gpmp::stats::HypothesisTest::chi_square_test(
    const std::vector<std::vector<int>> &observed,
    const std::vector<std::vector<double>> &expected) {
    int rows = observed.size();
    int cols = observed[0].size();
    double chiSquare = 0.0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            chiSquare +=
                pow((observed[i][j] - expected[i][j]), 2) / expected[i][j];
        }
    }

    return chiSquare;
}

// Method for conducting z-test for proportions
double gpmp::stats::HypothesisTest::proportion_z_test(double p1,
                                                      double p2,
                                                      double n1,
                                                      double n2) {
    double p = (p1 * n1 + p2 * n2) / (n1 + n2);
    double z = (p1 - p2) / sqrt(p * (1 - p) * (1 / n1 + 1 / n2));
    return z;
}

// Method for conducting Wilcoxon signed-rank test
double gpmp::stats::HypothesisTest::wilcoxon_rank_test(
    const std::vector<double> &sample1,
    const std::vector<double> &sample2) {
    int n = sample1.size();
    if (n != static_cast<int>(sample2.size())) {
        std::cerr << "Sample sizes must be equal for Wilcoxon signed-rank test."
                  << std::endl;
        return std::numeric_limits<double>::quiet_NaN();
    }

    std::vector<double> differences;
    for (int i = 0; i < n; ++i) {
        differences.push_back(sample1[i] - sample2[i]);
    }
    std::sort(differences.begin(), differences.end(), [](double a, double b) {
        return std::abs(a) < std::abs(b);
    });

    double Tplus = 0;
    double Tminus = 0;
    int numPositive = 0;
    int numNegative = 0;
    for (double diff : differences) {
        if (diff > 0) {
            Tplus += diff;
            numPositive++;
        } else if (diff < 0) {
            Tminus -= diff;
            numNegative++;
        }
    }
    int T = std::min(Tplus, Tminus);

    // Calculate the critical value using the normal approximation
    double mean = n * (n + 1) / 4.0;
    double stdDev = sqrt(n * (n + 1) * (2 * n + 1) / 24.0);
    double z = (T - mean) / stdDev;

    return z;
}

// Method for conducting Mann-Whitney U test
double gpmp::stats::HypothesisTest::mann_whitney_test(
    const std::vector<double> &sample1,
    const std::vector<double> &sample2) {
    int n1 = sample1.size();
    int n2 = sample2.size();
    double U1 = gpmp::stats::Describe::u_stat(sample1, sample2);
    double U2 = gpmp::stats::Describe::u_stat(sample2, sample1);
    double U = std::min(U1, U2);

    // Calculate the expected value of U
    double expectedU = n1 * n2 / 2.0;

    // Calculate the standard deviation of U
    double stdDev = sqrt(n1 * n2 * (n1 + n2 + 1) / 12.0);

    // Calculate the z-score
    double z = (U - expectedU) / stdDev;

    return z;
}

// Method for conducting Fisher's Exact Test
double gpmp::stats::HypothesisTest::fisher_test(
    const std::vector<std::vector<int>> &table) {
    int nRows = table.size();
    int nCols = table[0].size();

    if (nRows != 2 || nCols != 2) {
        std::cerr << "Fisher's Exact Test requires a 2x2 contingency table."
                  << std::endl;
        return std::numeric_limits<double>::quiet_NaN();
    }

    int a = table[0][0];
    int b = table[0][1];
    int c = table[1][0];
    int d = table[1][1];

    double p = (factorial(a + b) * factorial(c + d) * factorial(a + c) *
                factorial(b + d)) /
               (factorial(a) * factorial(b) * factorial(c) * factorial(d) *
                factorial(a + b + c + d));

    return p;
}

// Method for conducting Kolmogorov-Smirnov Test
double gpmp::stats::HypothesisTest::kol_smirnov_test(
    const std::vector<double> &sample1,
    const std::vector<double> &sample2) {
    int n1 = sample1.size();
    int n2 = sample2.size();

    std::vector<double> combinedSamples = sample1;
    combinedSamples.insert(combinedSamples.end(),
                           sample2.begin(),
                           sample2.end());
    std::sort(combinedSamples.begin(), combinedSamples.end());

    double maxDPlus = 0.0;
    double maxDMinus = 0.0;

    for (size_t i = 0; i < combinedSamples.size(); ++i) {
        double DPlus = (i + 1) / static_cast<double>(n1) - combinedSamples[i];
        double DMinus = combinedSamples[i] - i / static_cast<double>(n2);

        maxDPlus = std::max(maxDPlus, DPlus);
        maxDMinus = std::max(maxDMinus, DMinus);
    }

    return std::max(maxDPlus, maxDMinus);
}

// Method for conducting Wilcoxon Rank Sum Test (Mann-Whitney U Test)
double gpmp::stats::HypothesisTest::wilcoxon_rank_sum_test(
    const std::vector<double> &sample1,
    const std::vector<double> &sample2) {
    int n1 = sample1.size();
    int n2 = sample2.size();
    std::vector<double> ranks;
    ranks.reserve(n1 + n2);

    for (double x : sample1) {
        ranks.push_back(x);
    }
    for (double x : sample2) {
        ranks.push_back(x);
    }

    std::sort(ranks.begin(), ranks.end());

    double rankSum1 = 0.0;
    for (double x : sample1) {
        rankSum1 +=
            std::distance(ranks.begin(),
                          std::lower_bound(ranks.begin(), ranks.end(), x));
    }

    double U1 = rankSum1 - (n1 * (n1 + 1)) / 2.0;
    double U2 = n1 * n2 - U1;

    return std::min(U1, U2);
}

// Method for conducting Kruskal-Wallis Test
double gpmp::stats::HypothesisTest::kruskal_wallis_test(
    const std::vector<std::vector<double>> &samples) {
    int k = samples.size();
    std::vector<std::pair<double, int>> combinedData;

    for (int i = 0; i < k; ++i) {
        for (double x : samples[i]) {
            combinedData.push_back(std::make_pair(x, i));
        }
    }

    std::sort(combinedData.begin(), combinedData.end());

    std::vector<double> ranks;
    ranks.reserve(combinedData.size());

    int rank = 1;
    ranks.push_back(rank);
    for (size_t i = 1; i < combinedData.size(); ++i) {
        if (std::abs(combinedData[i].first - combinedData[i - 1].first) >
            std::numeric_limits<double>::epsilon()) {
            rank++;
        }
        ranks.push_back(rank);
    }

    double H = 0.0;
    for (int i = 0; i < k; ++i) {
        double rankSum = 0.0;
        for (size_t j = 0; j < samples[i].size(); ++j) {
            rankSum += ranks[i * samples[i].size() + j];
        }
        H += (rankSum * rankSum) / samples[i].size();
    }
    H = (12.0 / (combinedData.size() * (combinedData.size() + 1))) * H -
        3.0 * (combinedData.size() + 1);

    return H;
}

// Method for conducting Runs Test
double
gpmp::stats::HypothesisTest::runs_test(const std::vector<bool> &sequence) {
    int n = sequence.size();
    int numRuns = 1;

    for (int i = 1; i < n; ++i) {
        if (sequence[i] != sequence[i - 1]) {
            numRuns++;
        }
    }

    double expectedRuns = (2.0 * n - 1) / 3.0;
    double varianceRuns = (16.0 * n - 29) / 90.0;
    double z = (numRuns - expectedRuns) / sqrt(varianceRuns);

    return z;
}

// Helper method to calculate factorial
int gpmp::stats::HypothesisTest::factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}
