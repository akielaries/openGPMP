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

    TEST(prime_test, is_prime) {
        int is_prime_0 = 2;
        bool actual_0 = true;
        bool fetched_0 = p.is_prime(is_prime_0);
        EXPECT_EQ(actual_0, fetched_0);

        int is_prime_1 = 3;
        bool actual_1 = true;
        bool fetched_1 = p.is_prime(is_prime_1);
        EXPECT_EQ(actual_1, fetched_1);

        int is_prime_2 = 9;
        bool actual_2 = false;
        bool fetched_2 = p.is_prime(is_prime_2);
        EXPECT_EQ(actual_2, fetched_2);

        int is_prime_3 = 8191;
        bool actual_3 = true;
        bool fetched_3 = p.is_prime(is_prime_3);
        EXPECT_EQ(actual_3, fetched_3);

        int is_prime_4 = 524287;
        bool actual_4 = true;
        bool fetched_4 = p.is_prime(is_prime_4);
        EXPECT_EQ(actual_4, fetched_4);

        int is_prime_5 = 6;
        bool actual_5 = false;
        bool fetched_5 = p.is_prime(is_prime_5);
        EXPECT_EQ(actual_5, fetched_5);

        int is_prime_6 = 2400530;
        bool actual_6 = false;
        bool fetched_6 = p.is_prime(is_prime_6);
        EXPECT_EQ(actual_6, fetched_6);
    }

    TEST(prime_test, carmichael) {
        int is_cm_0 = 561;
        bool actual_cm_0 = true;
        bool  carm_fetched_0 = p.carmichael_num(is_cm_0); 
        EXPECT_EQ(actual_cm_0, carm_fetched_0);

        int is_cm_1 = 560;
        bool actual_cm_1 = false;
        bool  carm_fetched_1 = p.carmichael_num(is_cm_1); 
        EXPECT_EQ(actual_cm_1, carm_fetched_1);
    }
    
    TEST(prime_test, mod_pow) {
        EXPECT_EQ(1, p.mod_pow(3, 2, 2));
        EXPECT_EQ(4, p.mod_pow(5, 2, 7));
        EXPECT_EQ(2, p.mod_pow(8, 9, 3));
        EXPECT_EQ(4, p.mod_pow(2, 30, 5));
    }

    // TEST(prime_test, miller_rabbin) {}
}

