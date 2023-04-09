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
 * Some core concepts seen in Number Theory specifically
 * Integer Factorization
 */
#include "../../include/nt/factorization.hpp"
#include "../../include/arithmetic.hpp"
#include "../../include/nt/prime_test.hpp"
#include "../../include/threadpool.hpp"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <future>
#include <iostream>
#include <numeric>
#include <random>
#include <stdio.h>
#include <string>
#include <vector>

// declare Basics and Primality class objects
mtpk::Basics __FACT_BASICS__;
mtpk::Factorization __FACTOR__;
mtpk::PrimalityTest __FACT_PRIMES__;

// OSX uses srand() opposed to rand()
#ifdef __APPLE__
#define USE_SRAND
#endif

/*
std::vector<std::future<uint64_t>> mtpk::Factorization::pollard_rho_thread(
    const std::vector<uint64_t> &nums_to_factorize) {
    mtpk::ThreadPool pool(2);
    mtpk::Factorization factors;
    std::vector<std::future<uint64_t>> results;

    for (const auto &num : nums_to_factorize) {
        results.emplace_back(pool.enqueue(
            &mtpk::Factorization::pollard_rho, &factors, num));
    }

    return results;
}*/

uint64_t mtpk::Factorization::pollard_rho(uint64_t n) {
    /* initialize random seed */
    std::mt19937_64 rng(
        std::chrono::steady_clock::now().time_since_epoch().count());

    /* no prime divisor for 1 */
    if (n == 1) {
        return n;
    }

    /* even number means one of the divisors is 2 */
    if (n % 2 == 0) {
        return 2;
    }

    /* we will pick from the range [2, N) */
    std::uniform_int_distribution<uint64_t> unif_dist(2, n - 1);
    uint64_t x = unif_dist(rng);
    uint64_t y = x;

    /* the constant in f(x).
     * Algorithm can be re-run with a different c
     * if it throws failure for a composite. */
    std::uniform_int_distribution<uint64_t> c_dist(1, n - 1);
    uint64_t c = c_dist(rng);

    /* Initialize candidate divisor (or result) */
    uint64_t divisor = 1;

    /* until the prime factor isn't obtained.
       If n is prime, return n */
    while (divisor == 1) {
        /* Tortoise Move: x(i+1) = f(x(i)) */
        x = __FACT_PRIMES__.mod_pow(x, 2, n) + c;
        if (x >= n) {
            x -= n;
        }

        /* Hare Move: y(i+1) = f(f(y(i))) */
        y = __FACT_PRIMES__.mod_pow(y, 2, n) + c;
        if (y >= n) {
            y -= n;
        }
        y = __FACT_PRIMES__.mod_pow(y, 2, n) + c;
        if (y >= n) {
            y -= n;
        }

        /* check gcd of |x-y| and n */
        divisor = std::gcd(abs(x - y), n);

        /* retry if the algorithm fails to find prime factor
         * with chosen x and c */
        if (divisor == n) {
            return pollard_rho(n);
        }
    }

    return divisor;
}
