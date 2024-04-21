
/*
 * Driver for showing how to use the core basic and elementary
 * functionalities of the Number Theory module
 *
 */
#include <openGPMP/nt/factorization.hpp>
#include <openGPMP/nt/prime_test.hpp>
#include <gtest/gtest.h>
#include <iostream>

namespace {
// declare primality class object
gpmp::PrimalityTest __TEST_PRIMES__;
gpmp::Factorization __TEST_FACTORS__;

// Test case for the pollard_rho method
TEST(FactorizationTest, PollardRhoTest) {
    gpmp::Factorization factorization;
    // Test with a prime number
    uint64_t prime = 997;
}

} // namespace
