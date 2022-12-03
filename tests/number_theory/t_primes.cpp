/*
 * Driver for showing how to use the core basic and elementary functionalities
 * of the Number Theory module
 *
 */
#include "../../include/number_theory/primes.hpp"
#include <gtest/gtest.h>
#include <iostream>


namespace {
    // declare primality class object
    Primality p;

    TEST(is_prime_test, verify) {
        int val_0 = 2;

        bool actual_0 = true;
        bool fetched_0 = p.is_prime(val_0);
        
        EXPECT_EQ(actual_0, fetched_0);
    }
}

