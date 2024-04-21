/**
 * Unit tests for the Statistics module's description methods
 */

#include <cmath>
#include <cstdlib>
#include <gtest/gtest.h>
#include <iostream>
#include <openGPMP/stats/describe.hpp>
#include <stdexcept>
#include <vector>

TEST(DescribeTest, MeanArithEmptyVector) {
    gpmp::stats::Describe describe;
    std::vector<double> data;
    EXPECT_TRUE(std::isnan(describe.mean_arith(data)));
}

TEST(DescribeTest, MeanArithSingleElement) {
    gpmp::stats::Describe describe;
    std::vector<double> data = {5.0};
    EXPECT_DOUBLE_EQ(describe.mean_arith(data), 5.0);
}

TEST(DescribeTest, MeanArithMultipleElements) {
    gpmp::stats::Describe describe;
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    EXPECT_DOUBLE_EQ(describe.mean_arith(data), 3.0);
}

TEST(DescribeTest, MeanGeoSingleElement) {
    gpmp::stats::Describe describe;
    std::vector<double> data = {5.0};
    EXPECT_DOUBLE_EQ(describe.mean_geo(data), 5.0);
}

TEST(DescribeTest, MeanGeoMultipleElements) {
    gpmp::stats::Describe describe;
    std::vector<double> data = {1.0, 2.0, 4.0};
    EXPECT_DOUBLE_EQ(describe.mean_geo(data), 2.0);
}
TEST(DescribeTest, MeanCubicEmptyVector) {
    gpmp::stats::Describe describe;
    std::vector<double> data;
    double p = 3.0; // Arbitrary value for p
    EXPECT_TRUE(std::isnan(describe.mean_cubic(data, p)));
}

TEST(DescribeTest, MeanCubicSingleElement) {
    gpmp::stats::Describe describe;
    std::vector<double> data = {5.0};
    double p = 3.0; // Arbitrary value for p
    EXPECT_DOUBLE_EQ(describe.mean_cubic(data, p), 5.0);
}

TEST(DescribeTest, MeanCubicMultipleElements) {
    gpmp::stats::Describe describe;
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    double p = 3.0; // Arbitrary value for p
    double expected = 3.5568933044900626;
    double tolerance = std::numeric_limits<double>::epsilon();
    EXPECT_NEAR(describe.mean_cubic(data, p), expected, tolerance);
}

TEST(DescribeTest, MeanCubicDifferentP) {
    gpmp::stats::Describe describe;
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    double p = 2.0; // Different value for p
    double expected = 3.3166247903553998;
    double tolerance = std::numeric_limits<double>::epsilon();
    EXPECT_NEAR(describe.mean_cubic(data, p), expected, tolerance);
}

TEST(DescribeTest, MeanGeoPowSingleElement) {
    gpmp::stats::Describe describe;
    std::vector<double> data = {5.0};
    double p = 2.0; // Arbitrary value for p
    EXPECT_DOUBLE_EQ(describe.mean_geo_pow(data, p), 25.0);
}

TEST(DescribeTest, MeanHarmonicSingleElement) {
    gpmp::stats::Describe describe;
    std::vector<double> data = {5.0};
    EXPECT_DOUBLE_EQ(describe.mean_harmonic(data), 5.0);
}

TEST(DescribeTest, MeanHarmonicMultipleElements) {
    gpmp::stats::Describe describe;
    std::vector<double> data = {1.0, 2.0, 4.0};
    EXPECT_NEAR(describe.mean_harmonic(data), 1.714285, 1e-4);
}

TEST(DescribeTest, MeanHeronianSingleElement) {
    gpmp::stats::Describe describe;
    std::vector<double> data = {5.0};
    EXPECT_DOUBLE_EQ(describe.mean_heronian(data), 5.0);
}

TEST(DescribeTest, MeanLehmerSingleElement) {
    gpmp::stats::Describe describe;
    std::vector<double> data = {5.0};
    double p = 2.0; // Arbitrary value for p
    EXPECT_DOUBLE_EQ(describe.mean_lehmer(data, p), 25.0);
}

TEST(DescribeTest, MedianOddSize) {
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    gpmp::stats::Describe describe;
    double expected_median = 3.0;
    double actual_median = describe.Median(data);
    EXPECT_EQ(expected_median, actual_median);
}

TEST(DescribeTest, MedianEvenSize) {
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0};
    gpmp::stats::Describe describe;
    double expected_median = 2.5;
    double actual_median = describe.Median(data);
    EXPECT_EQ(expected_median, actual_median);
}
TEST(DescribeTest, AvgAbsDev) {
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    gpmp::stats::Describe describe;
    double expected_avg_abs_dev = 1.2;
    double actual_avg_abs_dev = describe.avg_abs_dev(data);
    double tolerance = 1e-3;
    EXPECT_NEAR(expected_avg_abs_dev, actual_avg_abs_dev, tolerance);
}

TEST(DescribeTest, AvgAbsDevEmptyVector) {
    std::vector<double> data;
    gpmp::stats::Describe describe;
    double expected_avg_abs_dev = 0.0;
    double actual_avg_abs_dev = describe.avg_abs_dev(data);
    EXPECT_TRUE(std::isnan(actual_avg_abs_dev) ||
                actual_avg_abs_dev == expected_avg_abs_dev);
}

TEST(DescribeTest, VarCoeff) {
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    gpmp::stats::Describe describe;
    double expected_var_coeff = 47.1405;
    double actual_var_coeff = describe.var_coeff(data);
    double tolerance = 1e-4;
    EXPECT_NEAR(expected_var_coeff, actual_var_coeff, tolerance);
}

TEST(DescribeTest, VarCoeffEmptyVector) {
    std::vector<double> data;
    gpmp::stats::Describe describe;
    double expected_var_coeff = std::numeric_limits<double>::quiet_NaN();
    double actual_var_coeff = describe.var_coeff(data);
    EXPECT_TRUE(std::isnan(actual_var_coeff) ||
                actual_var_coeff == expected_var_coeff);
}

TEST(DescribeTest, IqRange) {
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    gpmp::stats::Describe describe;
    double expected_iq_range = 2.0;
    double actual_iq_range = describe.iq_range(data);
    EXPECT_EQ(expected_iq_range, actual_iq_range);
}

TEST(DescribeTest, Percentile) {
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    gpmp::stats::Describe describe;
    double expected_percentile = 3.0;
    double actual_percentile = describe.percentile(data, 0.5);
    EXPECT_EQ(expected_percentile, actual_percentile);
}

TEST(DescribeTest, Range) {
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    gpmp::stats::Describe describe;
    double expected_range = 4.0;
    double actual_range = describe.range(data);
    EXPECT_EQ(expected_range, actual_range);
}

TEST(DescribeTest, Stdev) {
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    gpmp::stats::Describe describe;
    double mean = describe.mean_arith(data);
    double expected_stdev = 1.41421;
    double actual_stdev = describe.stdev(data, mean);
    double tolerance = 1e-3;
    EXPECT_NEAR(expected_stdev, actual_stdev, tolerance);
}

TEST(DescribeTest, StdevEmptyVector) {
    std::vector<double> data;
    gpmp::stats::Describe describe;
    double expected_stdev = std::numeric_limits<double>::quiet_NaN();
    double actual_stdev = describe.stdev(data, 0.0);
    EXPECT_TRUE(std::isnan(actual_stdev) || actual_stdev == expected_stdev);
}

TEST(DescribeTest, VarianceEmptyVector) {
    std::vector<double> data;
    gpmp::stats::Describe describe;
    double expected_variance = std::numeric_limits<double>::quiet_NaN();
    double actual_variance = describe.variance(data, 0.0);
    EXPECT_TRUE(std::isnan(actual_variance) ||
                actual_variance == expected_variance);
}

TEST(DescribeTest, Clt) {
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    int numSamples = 100;
    gpmp::stats::Describe describe;
    double expected_clt = 0.1414;
    double actual_clt = describe.clt(data, numSamples);
    double tolerance = 1e-2;
    EXPECT_NEAR(expected_clt, actual_clt, tolerance);
}

TEST(DescribeTest, Kurtosis) {
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    gpmp::stats::Describe describe;
    double mean = describe.mean_arith(data);
    double expected_kurtosis = -1.3;
    double actual_kurtosis = describe.kurtosis(data, mean);
    double tolerance = 1e-3;
    EXPECT_NEAR(expected_kurtosis, actual_kurtosis, tolerance);
}

TEST(DescribeTest, Lmoment1) {
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    gpmp::stats::Describe describe;
    double mean = describe.mean_arith(data);
    double expected_lmoment1 = 0.0;
    double actual_lmoment1 = describe.lmoment1(data, mean);
    EXPECT_EQ(expected_lmoment1, actual_lmoment1);
}

TEST(DescribeTest, Lmoment2) {
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    gpmp::stats::Describe describe;
    double mean = describe.mean_arith(data);
    double expected_lmoment2 = 6.8;
    double actual_lmoment2 = describe.lmoment2(data, mean);
    EXPECT_EQ(expected_lmoment2, actual_lmoment2);
}

TEST(DescribeTest, Skewness) {
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    gpmp::stats::Describe describe;
    double mean = describe.mean_arith(data);
    double stddev = describe.stdev(data, mean);
    double expected_skewness = 0.0;
    double actual_skewness = describe.skewness(data, mean, stddev);
    double tolerance = 1e-3;
    EXPECT_NEAR(expected_skewness, actual_skewness, tolerance);
}

TEST(DescribeTest, RankData) {
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    gpmp::stats::Describe describe;
    std::vector<size_t> expected_ranks =
        {1, 2, 3, 4, 5}; // Expected ranks based on input data
    std::vector<size_t> actual_ranks = describe.rank_data(data);
    EXPECT_EQ(expected_ranks, actual_ranks);
}

TEST(DescribeTest, Ppmc) {
    std::vector<double> x = {1.0, 2.0, 3.0, 4.0, 5.0};
    std::vector<double> y = {2.0, 3.0, 4.0, 5.0, 6.0};
    gpmp::stats::Describe describe;
    double expected_ppmc = 1.0;
    double actual_ppmc = describe.ppmc(x, y);
    double tolerance = 1e-3;
    EXPECT_NEAR(expected_ppmc, actual_ppmc, tolerance);
}
