/**
 * Unit tests for the Number Theory modules PRNGs
 */
#include <openGPMP/nt/random.hpp>
#include <gtest/gtest.h>
#include <iostream>

TEST(LCGTest, DefaultConstructor) {
    gpmp::core::rndm::LCG generator;

    // Generate a few random numbers and ensure they are within bounds
    for (int i = 0; i < 10; ++i) {
        uint64_t result = generator();
        EXPECT_GE(result, 0);
        EXPECT_LE(result, std::numeric_limits<uint64_t>::max());
    }
}

TEST(LCGTest, CustomConstructor) {
    uint64_t seed = 123;
    uint64_t a = 6364136223846793005ULL;
    uint64_t c = 1442695040888963407ULL;

    gpmp::core::rndm::LCG generator(seed, a, c);

    // Generate a few random numbers and ensure they are within bounds
    for (int i = 0; i < 10; ++i) {
        uint64_t result = generator();
        EXPECT_GE(result, 0);
        EXPECT_LE(result, std::numeric_limits<uint64_t>::max());
    }
}
