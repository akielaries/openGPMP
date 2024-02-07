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

class SigProcTest : public ::testing::Test {
  protected:
    std::vector<double> testSignal1 = {1.0, 2.0, 3.0, 4.0, 5.0};
    std::vector<double> testSignal2 = {5.0, 4.0, 3.0, 2.0, 1.0};
};

TEST_F(SigProcTest, MeanCalculation) {
    gpmp::linalg::SigProc sigProc(testSignal1);
    EXPECT_NEAR(sigProc.mean(), 3.0, TOLERANCE);
}

TEST_F(SigProcTest, StandardDeviationCalculation) {
    gpmp::linalg::SigProc sigProc(testSignal1);
    EXPECT_NEAR(sigProc.stdev(), 1.41421, TOLERANCE);
}

TEST_F(SigProcTest, LPFFiltering) {
    gpmp::linalg::SigProc sigProc(testSignal1);
    sigProc.lpf(0.5);
    // check first few values after filtering
    EXPECT_NEAR(sigProc.mean(), 2.3875, TOLERANCE);
    EXPECT_NEAR(sigProc.stdev(), 1.1028, TOLERANCE);
}

TEST_F(SigProcTest, LPFInvalidAlphaTest) {
    gpmp::linalg::SigProc sigProc(testSignal1);

    // apply low-pass filter with alpha <= 0
    EXPECT_THROW(sigProc.lpf(0.0), std::invalid_argument);

    // apply low-pass filter with alpha >= 1
    EXPECT_THROW(sigProc.lpf(1.0), std::invalid_argument);
}
