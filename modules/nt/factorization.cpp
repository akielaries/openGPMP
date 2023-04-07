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
#include "../../include/nt/primes.hpp"
#include "../../include/threadpool.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <future>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <random>
#include <chrono>


// declare Basics and Primality class objects
mtpk::Basics __FACT_BASICS__;
mtpk::Factorization __FACTOR__;
mtpk::Primality __FACT_PRIMES__;

// OSX uses srand() opposed to rand()
#ifdef __APPLE__
#define USE_SRAND
#endif

/*
 * algorithm for integer factorization proportial to the runtime of
 * the square root of the size of the smallest prime factor of the
 * composite factor being factorized. Given a positive and composite
 * integer n, find a divisor of it.
 *
 * x_n-1 = x^2_n + a(mod n)
 *
 * n = 1111, set x_0 = 2 & f(x) = x^2 + 1
 *
 * x_1 = 5
 * x_2 = 26         gcd(26 - 5, 1111) = 1
 * x_3 = 677
 * x_4 = 598        gcd(698 - 26, 1111) = 11
 */
int64_t mtpk::Factorization::pollard_rho(int64_t n) {
    /* initialize random seed */
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

    /* no prime divisor for 1 */
    if (n == 1) {
        return n;
    }

    /* even number means one of the divisors is 2 */
    if (n % 2 == 0) {
        return 2;
    }

    /* we will pick from the range [2, N) */
    std::uniform_int_distribution<int64_t> unif_dist(2, n - 1);
    int64_t x = unif_dist(rng);
    int64_t y = x;

    /* the constant in f(x).
     * Algorithm can be re-run with a different c
     * if it throws failure for a composite. */
    std::uniform_int_distribution<int64_t> c_dist(1, n - 1);
    int64_t c = c_dist(rng);

    /* Initialize candidate divisor (or result) */
    int64_t divisor = 1;

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
        divisor = __FACT_BASICS__.op_gcd(abs(x - y), n);

        /* retry if the algorithm fails to find prime factor
         * with chosen x and c */
        if (divisor == n) {
            return pollard_rho(n);
        }
    }

    return divisor;
}

int main() {
    mtpk::ThreadPool pool(1);
    mtpk::Factorization factors;
    std::vector<std::future<int64_t>> results;

    // specify the numbers to factorize
    std::vector<int64_t> nums_to_factorize = {
        9223372036854775803, 9223372036854775807, 9223372036854775303,
        4567890123456789LL,  5678901234567890LL,  6789012345678901LL,
        7890123456789012LL,  8901234567890123LL};

    for (const auto &num : nums_to_factorize) {
        results.emplace_back(pool.enqueue(
            &mtpk::Factorization::pollard_rho, &factors, num));
    }

    for (auto &res : results) {
        std::cout << res.get() << std::endl;
    }

    return 0;
}
