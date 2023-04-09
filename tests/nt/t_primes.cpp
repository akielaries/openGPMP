/*************************************************************************
 *
 *  Project
 *                        __  __ _______ _____  _  __
 *                       |  \/  |__   __|  __ \| |/ /
 *  ___  _ __   ___ _ __ | \  / |  | |  | |__) | ' /
 * / _ \| '_ \ / _ \ '_ \| |\/| |  | |  |  ___/|  <
 *| (_) | |_) |  __/ | | | |  | |  | |  | |    | . \
 * \___/| .__/ \___|_| |_|_|  |_|  |_|  |_|    |_|\_\
 *      | |
 *      |_|
 *
 *
 * Copyright (C) Akiel Aries, <akiel@akiel.org>, et al.
 *
 * This software is licensed as described in the file LICENSE, which
 * you should have received as part of this distribution. The terms
 * among other details are referenced in the official documentation
 * seen here : https://akielaries.github.io/openMTPK/ along with
 * important files seen in this project.
 *
 * You may opt to use, copy, modify, merge, publish, distribute
 * and/or sell copies of the Software, and permit persons to whom
 * the Software is furnished to do so, under the terms of the
 * LICENSE file. As this is an Open Source effort, all implementations
 * must be of the same methodology.
 *
 *
 *
 * This software is distributed on an AS IS basis, WITHOUT
 * WARRANTY OF ANY KIND, either express or implied.
 *
 ************************************************************************/

/*
 * Driver for showing how to use the core basic and elementary
 * functionalities of the Number Theory module
 *
 */
#include "../../include/nt/primes.hpp"
#include <gtest/gtest.h>
#include <iostream>

namespace {
// declare primality class object
mtpk::Primality __PRIMES_CLASS__;

TEST(prime_test, is_prime) {
    uint64_t is_prime_0 = 2;
    bool actual_0 = true;
    bool fetched_0 = __PRIMES_CLASS__.is_prime(is_prime_0);
    EXPECT_EQ(actual_0, fetched_0);

    uint64_t is_prime_1 = 3;
    bool actual_1 = true;
    bool fetched_1 = __PRIMES_CLASS__.is_prime(is_prime_1);
    EXPECT_EQ(actual_1, fetched_1);

    uint64_t is_prime_2 = 9;
    bool actual_2 = false;
    bool fetched_2 = __PRIMES_CLASS__.is_prime(is_prime_2);
    EXPECT_EQ(actual_2, fetched_2);

    uint64_t is_prime_3 = 8191;
    bool actual_3 = true;
    bool fetched_3 = __PRIMES_CLASS__.is_prime(is_prime_3);
    EXPECT_EQ(actual_3, fetched_3);

    uint64_t is_prime_4 = 524287;
    bool actual_4 = true;
    bool fetched_4 = __PRIMES_CLASS__.is_prime(is_prime_4);
    EXPECT_EQ(actual_4, fetched_4);

    uint64_t is_prime_5 = 6;
    bool actual_5 = false;
    bool fetched_5 = __PRIMES_CLASS__.is_prime(is_prime_5);
    EXPECT_EQ(actual_5, fetched_5);

    uint64_t is_prime_6 = 2400530;
    bool actual_6 = false;
    bool fetched_6 = __PRIMES_CLASS__.is_prime(is_prime_6);
    EXPECT_EQ(actual_6, fetched_6);

    uint64_t is_prime_7 = 1;
    bool actual_7 = false;
    bool fetched_7 = __PRIMES_CLASS__.is_prime(is_prime_7);
    EXPECT_EQ(actual_7, fetched_7);
}

TEST(prime_test, carmichael) {
    uint64_t is_cm_0 = 561;
    bool actual_cm_0 = true;
    bool carm_fetched_0 = __PRIMES_CLASS__.carmichael_num(is_cm_0);
    EXPECT_EQ(actual_cm_0, carm_fetched_0);

    uint64_t is_cm_1 = 560;
    bool actual_cm_1 = false;
    bool carm_fetched_1 = __PRIMES_CLASS__.carmichael_num(is_cm_1);
    EXPECT_EQ(actual_cm_1, carm_fetched_1);
}

TEST(prime_test, mod_pow) {
    EXPECT_EQ(1, __PRIMES_CLASS__.mod_pow(3, 2, 2));
    EXPECT_EQ(4, __PRIMES_CLASS__.mod_pow(5, 2, 7));
    EXPECT_EQ(2, __PRIMES_CLASS__.mod_pow(8, 9, 3));
    EXPECT_EQ(4, __PRIMES_CLASS__.mod_pow(2, 30, 5));
}

/*
 * this test case in itself is not vary useful as it acts
 * as a utility function on the overall algorithm that
 * computes primes using the Miller-Rabin method
 */
TEST(prime_test, compute_miller_rabin) {
    EXPECT_EQ(true, __PRIMES_CLASS__.compute_miller_rabin(7, 5));
    EXPECT_EQ(true, __PRIMES_CLASS__.compute_miller_rabin(7, 1));
    EXPECT_EQ(true, __PRIMES_CLASS__.compute_miller_rabin(1049, 5));
    EXPECT_EQ(true, __PRIMES_CLASS__.compute_miller_rabin(2999, 5));
    EXPECT_EQ(true, __PRIMES_CLASS__.compute_miller_rabin(4, 2));
    EXPECT_EQ(true, __PRIMES_CLASS__.compute_miller_rabin(200392, 5));
    EXPECT_EQ(true, __PRIMES_CLASS__.compute_miller_rabin(90, 5));
}

TEST(prime_test, miller_rabin_prime) {
    EXPECT_EQ(true, __PRIMES_CLASS__.miller_rabin_prime(1049, 4));
    EXPECT_EQ(true, __PRIMES_CLASS__.miller_rabin_prime(5, 4));
    EXPECT_EQ(true, __PRIMES_CLASS__.miller_rabin_prime(2999, 4));
    EXPECT_EQ(true, __PRIMES_CLASS__.miller_rabin_prime(3, 4));
    EXPECT_EQ(false, __PRIMES_CLASS__.miller_rabin_prime(3000, 4));
    EXPECT_EQ(false, __PRIMES_CLASS__.miller_rabin_prime(4, 4));
    EXPECT_EQ(false, __PRIMES_CLASS__.miller_rabin_prime(104032, 4));
}

// TEST(prime_test, miller_rabin) {}

TEST(prime_test, solovoy_strassen) {
    EXPECT_EQ(false, __PRIMES_CLASS__.solovoy_strassen(15, 50));
    EXPECT_EQ(false, __PRIMES_CLASS__.solovoy_strassen(25, 50));
    EXPECT_EQ(false, __PRIMES_CLASS__.solovoy_strassen(104032, 50));
    EXPECT_EQ(true, __PRIMES_CLASS__.solovoy_strassen(3, 50));
    EXPECT_EQ(false, __PRIMES_CLASS__.solovoy_strassen(2999, 50));
    EXPECT_EQ(false, __PRIMES_CLASS__.solovoy_strassen(1049, 50));
}
} // namespace
