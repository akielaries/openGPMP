/**
 * Unit tests for the Statistics module's probabilistic distribution methods
 */
#include <cmath>
#include <cstdlib>
#include <gtest/gtest.h>
#include <iostream>
#include <openGPMP/stats/probdist.hpp>
#include <stdexcept>
#include <vector>

// Tolerance for floating-point comparisons
const double TOLERANCE = 1e-2;

// Unit test for quantile_dist method
TEST(ProbDistTest, QuantileDist) {
    gpmp::stats::ProbDist probDist;
    // median probability
    double probability = 0.5;
    // median of standard normal distribution
    double expected_quantile = 0.0;

    double actual_quantile = probDist.quantile_dist(probability);
    EXPECT_NEAR(expected_quantile, actual_quantile, TOLERANCE);
}

TEST(ProbDistTest, QuantileDist_ProbabilityZero) {
    gpmp::stats::ProbDist probDist;

    double probability = 0.0;
    double actual_quantile = probDist.quantile_dist(probability);
    EXPECT_EQ(0.0, actual_quantile);
}

// Unit test for normal_PDF method
TEST(ProbDistTest, NormalPDF) {
    gpmp::stats::ProbDist probDist;
    // value at mean
    double x = 0.0;
    // mean of normal distribution
    double mean = 0.0;
    // standard deviation of normal distribution
    double stddev = 1.0;

    // calculated expected value based on input parameters
    double expected_pdf = 0.398942;

    double actual_pdf = probDist.normal_PDF(x, mean, stddev);
    EXPECT_NEAR(expected_pdf, actual_pdf, TOLERANCE);
}

TEST(ProbDistTest, NormalCDF) {
    gpmp::stats::ProbDist probDist;

    // value at mean
    double x = 0.0;
    // mean of normal distribution
    double mean = 0.0;
    // standard deviation of normal distribution
    double stddev = 1.0;

    // cumulative distribution function (CDF) at mean
    double expected_cdf = 0.5;

    double actual_cdf = probDist.normal_CDF(x, mean, stddev);
    EXPECT_NEAR(expected_cdf, actual_cdf, TOLERANCE);
}

// Unit test for uniform_CDF method
TEST(ProbDistTest, UniformCDF) {
    gpmp::stats::ProbDist probDist;

    // current rank
    size_t k = 2;
    // items
    size_t n = 5;

    double expected_cdf = 0.333;

    double actual_cdf = probDist.uniform_CDF(k, n);

    EXPECT_NEAR(expected_cdf, actual_cdf, TOLERANCE);
}

// Unit test for emp_CDF method
TEST(ProbDistTest, EmpCDF) {
    gpmp::stats::ProbDist probDist;

    // Setup
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    double x = 3.0;

    // Expected empirical cumulative distribution function (CDF) value
    double expected_cdf = 0.6;

    double actual_cdf = probDist.emp_CDF(data, x);

    EXPECT_NEAR(expected_cdf, actual_cdf, TOLERANCE);
}

TEST(ProbDistTest, EmpPMF) {
    gpmp::stats::ProbDist probDist;

    std::vector<double> data = {1.0, 2.0, 2.0, 3.0, 3.0, 3.0, 4.0};
    double x = 3.0;

    // expected probability mass function (PMF) value
    double expected_pmf = 3.0 / data.size();

    double actual_pmf = probDist.emp_PMF(data, x);

    EXPECT_NEAR(expected_pmf, actual_pmf, TOLERANCE);
}

TEST(ProbDistTest, InverseEmpCDF) {
    gpmp::stats::ProbDist probDist;

    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    // probability value
    double p = 0.5;

    // expected inverse empirical cumulative distribution function (CDF) value
    double expected_result = 3.0;

    double actual_result = probDist.inverse_emp_CDF(data, p);

    EXPECT_EQ(expected_result, actual_result);
}

// Unit test for mle method
TEST(ProbDistTest, MLE) {
    gpmp::stats::ProbDist probDist;

    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};

    // expected maximum likelihood estimate (MLE)
    double expected_result = 3.0;

    double actual_result = probDist.mle(data);
    EXPECT_EQ(expected_result, actual_result);
}

// Unit test for mom method
TEST(ProbDistTest, MOM) {
    gpmp::stats::ProbDist probDist;

    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};

    // method of moments xpected result
    double expected_result = 2;

    double actual_result = probDist.mom(data);
    EXPECT_NEAR(expected_result, actual_result, TOLERANCE);
}

// Unit test for mle_est method
TEST(ProbDistTest, MLEEst) {
    gpmp::stats::ProbDist probDist;

    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};

    // maximum likelihood estimation
    double expected_result = 3.0;

    double actual_result = probDist.mle_est(data);

    EXPECT_NEAR(expected_result, actual_result, TOLERANCE);
}

// Unit test for mumv method
TEST(ProbDistTest, MUMV) {
    gpmp::stats::ProbDist probDist;

    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};

    // mean of unordered multiset values (MUMV)
    double expected_result = 3.0;

    double actual_result = probDist.mumv(data);
    EXPECT_NEAR(expected_result, actual_result, TOLERANCE);
}

TEST(ProbDistTest, MedianUnbiased) {
    gpmp::stats::ProbDist probDist;

    // sample data (odd number of elements)
    std::vector<double> data_odd = {1.0, 2.0, 3.0, 4.0, 5.0};

    // sample data (even number of elements)
    std::vector<double> data_even = {1.0, 2.0, 3.0, 4.0};

    double expected_result_odd = 3.0;
    double expected_result_even = 2.5;

    double actual_result_odd = probDist.median_uniased(data_odd);
    double actual_result_even = probDist.median_uniased(data_even);

    // Assertions
    EXPECT_NEAR(expected_result_odd, actual_result_odd, TOLERANCE);
    EXPECT_NEAR(expected_result_even, actual_result_even, TOLERANCE);
}

// Unit test for ConfidenceInterval method
TEST(ProbDistTest, ConfidenceInterval) {
    gpmp::stats::ProbDist probDist;

    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};

    // sig level
    double alpha = 0.05;

    auto interval = probDist.ConfidenceInterval(data, alpha);

    EXPECT_LT(interval.first, interval.second);
}

TEST(ProbDistTest, LikelihoodInterval) {
    gpmp::stats::ProbDist probDist;

    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    // sig level
    double alpha = 0.05;

    auto interval = probDist.LikelihoodInterval(data, alpha);

    EXPECT_LT(interval.first, interval.second);
}

TEST(ProbDistTest, PredictionInterval) {
    gpmp::stats::ProbDist probDist;

    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    double alpha = 0.05;

    auto interval = probDist.PredictionInterval(data, alpha);

    EXPECT_LT(interval.first, interval.second);
}

TEST(ProbDistTest, ToleranceInterval) {
    gpmp::stats::ProbDist probDist;

    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    double alpha = 0.05;

    auto interval = probDist.ToleranceInterval(data, alpha);

    EXPECT_LT(interval.first, interval.second);
}

TEST(ProbDistTest, BootstrapResampling) {
    gpmp::stats::ProbDist probDist;

    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};

    // number of bootstrap samples
    int numSamples = 1000;

    auto interval = probDist.BootstrapResampling(data, numSamples);

    EXPECT_LT(interval.first, interval.second);
}

TEST(ProbDistTest, JackknifeResampling) {
    gpmp::stats::ProbDist probDist;

    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};

    auto interval = probDist.JackknifeResampling(data);

    EXPECT_LT(interval.first, interval.second);
}
