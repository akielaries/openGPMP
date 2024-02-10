/**
 * Unit tests for the Linear Algebra module's Signal Processing class
 */
#include "../../include/linalg/sigproc.hpp"
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <gtest/gtest.h>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

const double TOLERANCE = 1e-3;

const std::vector<std::pair<int, double>> test_signal_a = {{-1, 1},
                                                           {0, 3},
                                                           {1, 2},
                                                           {2, -1}};

TEST(SigProcTest, ZTransformRealTest) {
    std::vector<std::pair<int, double>> result =
        gpmp::linalg::sigproc::z_tform(test_signal_a);
    std::vector<std::pair<int, double>> expected_signal = {{1, 1},
                                                           {0, 3},
                                                           {-1, 2},
                                                           {-2, -1}};

    ASSERT_EQ(result.size(), expected_signal.size());
    for (size_t i = 0; i < result.size(); ++i) {
        EXPECT_EQ(result[i].first, expected_signal[i].first);
        EXPECT_NEAR(result[i].second, expected_signal[i].second, TOLERANCE);
    }
}

TEST(SigProcTest, GaussianFilterTest) {
    // Define an original signal
    std::vector<std::pair<int, double>> original_signal = {{0, 1.0},
                                                           {1, 2.0},
                                                           {2, 3.0},
                                                           {3, 4.0},
                                                           {4, 5.0}};

    // Define the expected filtered signal
    std::vector<std::pair<int, double>> expected_filtered_signal = {{0, 1.520},
                                                                    {1, 2.128},
                                                                    {2, 3.000},
                                                                    {3, 3.871},
                                                                    {4, 4.479}};

    double sigma = 1.0;
    std::vector<std::pair<int, double>> filtered_signal =
        gpmp::linalg::sigproc::gaussian_filter(original_signal, sigma);

    ASSERT_EQ(filtered_signal.size(), original_signal.size());

    // check each point of the filtered signal against the expected value
    for (size_t i = 0; i < filtered_signal.size(); ++i) {
        // use a TOLERANCE value for comparing double values due to
        // floating-point imprecision
        EXPECT_NEAR(filtered_signal[i].second,
                    expected_filtered_signal[i].second,
                    TOLERANCE);
    }
}

TEST(SigProcTest, ButterworthLPFTest) {
    // Define an original signal
    std::vector<std::pair<int, double>> original_signal = {{0, 1.0},
                                                           {1, 2.0},
                                                           {2, 3.0},
                                                           {3, 4.0},
                                                           {4, 5.0}};

    double cutoff_frequency = 0.2;
    double sampling_frequency = 1.0;
    int order = 2;

    // call the Butterworth low-pass filter function
    std::vector<std::pair<int, double>> filtered_signal =
        gpmp::linalg::sigproc::butterworth_lpf(original_signal,
                                               cutoff_frequency,
                                               sampling_frequency,
                                               order);

    // check that the size of the filtered signal matches the original signal
    ASSERT_EQ(filtered_signal.size(), original_signal.size());

    for (size_t i = 0; i < filtered_signal.size(); ++i) {
        EXPECT_GE(filtered_signal[i].second, 0);
        // TODO add more specific assertions as needed
    }
}

TEST(SigProcTest, ChebyshevLPFTest) {
    // Define an original signal
    std::vector<std::pair<int, double>> original_signal = {{0, 1.0},
                                                           {1, 2.0},
                                                           {2, 3.0},
                                                           {3, 4.0},
                                                           {4, 5.0}};

    double cutoff_frequency = 0.2;
    double sampling_frequency = 1.0;
    int order = 2;
    double ripple = 3.0;

    // call the Chebyshev low-pass filter function
    std::vector<std::pair<int, double>> filtered_signal =
        gpmp::linalg::sigproc::chebyshev_lpf(original_signal,
                                             cutoff_frequency,
                                             sampling_frequency,
                                             order,
                                             ripple);

    // Check that the size of the filtered signal matches the original signal
    ASSERT_EQ(filtered_signal.size(), original_signal.size());

    // Add your specific assertions to validate the filtered signal
    // For example, check that the filtered values are within an acceptable
    // range

    for (size_t i = 0; i < filtered_signal.size(); ++i) {
        EXPECT_GE(filtered_signal[i].second, 0); // Ensure non-negative values
        // Add more specific assertions as needed
    }
}

TEST(SigProcTest, ChebyshevLPFTestB) {
    // Test input signal
    std::vector<std::pair<int, double>> signal = {{0, 1.0},
                                                  {1, 2.0},
                                                  {2, 3.0},
                                                  {3, 4.0},
                                                  {4, 5.0}};

    // Parameters for the filter
    double cutoff_frequency = 1.0;
    double sampling_frequency = 10.0;
    int order = 2;
    double ripple = 0.5;

    // Expected output
    std::vector<std::pair<int, double>> expected_filtered_signal = {{0, 0.400},
                                                                    {1, 0.892},
                                                                    {2, 0.693},
                                                                    {3, 0.925},
                                                                    {4, 1.156}};

    // Call the filter function
    std::vector<std::pair<int, double>> filtered_signal =
        gpmp::linalg::sigproc::chebyshev_lpf(signal,
                                             cutoff_frequency,
                                             sampling_frequency,
                                             order,
                                             ripple);

    // check if the filtered signal matches the expected output
    ASSERT_EQ(filtered_signal.size(), expected_filtered_signal.size());
    for (size_t i = 0; i < filtered_signal.size(); ++i) {
        ASSERT_NEAR(filtered_signal[i].second,
                    expected_filtered_signal[i].second,
                    TOLERANCE);
    }
}

TEST(SigProcTest, BesselLPFTest) {
    // Test input signal
    std::vector<std::pair<int, double>> signal = {{0, 1.0},
                                                  {1, 2.0},
                                                  {2, 3.0},
                                                  {3, 4.0},
                                                  {4, 5.0}};

    // Parameters for the filter
    double cutoff_frequency = 1.0;
    double sampling_frequency = 10.0;
    int order = 2;

    // Expected output
    std::vector<std::pair<int, double>> expected_filtered_signal = {{0, 0.677},
                                                                    {1, 1.355},
                                                                    {2, 2.032},
                                                                    {3, 2.710},
                                                                    {4, 3.388}};

    // Call the filter function
    std::vector<std::pair<int, double>> filtered_signal =
        gpmp::linalg::sigproc::bessel_lpf(signal,
                                          cutoff_frequency,
                                          sampling_frequency,
                                          order);

    // Check if the filtered signal matches the expected output
    ASSERT_EQ(filtered_signal.size(), expected_filtered_signal.size());
    for (size_t i = 0; i < filtered_signal.size(); ++i) {
        ASSERT_NEAR(filtered_signal[i].second,
                    expected_filtered_signal[i].second,
                    0.001);
    }
}
