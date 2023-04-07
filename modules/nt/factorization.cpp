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
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <string>

// declare Basics and Primality class objects
mtpk::Basics ba;
mtpk::Factorization fact;

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
    srand(time(NULL));

    /* no prime divisor for 1 */
    if (n == 1)
        return n;

    /* even number means one of the divisors is 2 */
    if (n % 2 == 0)
        return 2;

    /* we will pick from the range [2, N) */
    int64_t x = (rand() % (n - 2)) + 2;
    int64_t y = x;

    /* the constant in f(x).
     * Algorithm can be re-run with a different c
     * if it throws failure for a composite. */
    int64_t c = (rand() % (n - 1)) + 1;

    /* Initialize candidate divisor (or result) */
    int64_t divisor = 1;

    /* until the prime factor isn't obtained.
       If n is prime, return n */
    while (divisor == 1) {
        /* Tortoise Move: x(i+1) = f(x(i)) */
        // take power
        // calculate modulus
        x = (mod_pow(x, 2, n) + c + n) % n;

        /* Hare Move: y(i+1) = f(f(y(i))) */
        y = (mod_pow(y, 2, n) + c + n) % n;
        y = (mod_pow(y, 2, n) + c + n) % n;

        /* check gcd of |x-y| and n */
        divisor = ba.op_gcd(abs(x - y), n);
        // divisor = std::__gcd(abs(x - y), n);
        /* retry if the algorithm fails to find prime factor
         * with chosen x and c */
        if (divisor == n)
            return pollard_rho(n);
    }

    return divisor;
}
