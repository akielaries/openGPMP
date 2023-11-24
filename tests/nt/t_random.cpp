/**
 * Unit tests for the Number Theory modules PRNGs
 */
#include "../../include/nt/random.hpp"
#include <gtest/gtest.h>
#include <iostream>

namespace {

// Test fixture class
class LCGTest : public ::testing::Test {
protected:
    // Helper function to check if the generated value is within the specified range
    static bool in_range(uint32_t value, uint32_t lower, uint32_t upper) {
        return value >= lower && value <= upper;
    }
};

// Test case for the LCG function
TEST_F(LCGTest, range_verify) {
    // Set up the lower, upper, and seed values for the test
    uint32_t lower = 10;
    uint32_t upper = 20;
    uint32_t seed = 42;

    // Call the LCG function
    uint32_t result = gpmp::core::rndm::LCG(lower, upper, seed);

    // Check if the generated result is within the specified range
    ASSERT_TRUE(in_range(result, lower, upper));
}

} // namespace
