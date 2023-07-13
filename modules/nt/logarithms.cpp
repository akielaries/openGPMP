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
 * seen here : https://akielaries.github.io/openGPMP/ along with
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
 * Discrete Logarithms
 */
#include "../../include/nt/logarithms.hpp"
#include "../../include/arithmetic.hpp"
#include "../../include/nt/prime_test.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>

// primes object for this Logarithms file
gpmp::PrimalityTest __LOG_PRIMES__;

// OSX uses srand() opposed to rand()
#ifdef __APPLE__
#define USE_SRAND
#endif

uint64_t gpmp::Logarithms::pollard_rho_log(uint64_t g, uint64_t y, uint64_t p) {
    uint64_t x = rand() % (p - 1) + 1;

#ifdef USE_SRAND
    srand(time(NULL));
    x = rand() % (p - 1) + 1;
#endif

    uint64_t y1 = y;
    uint64_t y2 = y;
    uint64_t d = 1;
    std::unordered_map<uint64_t, uint64_t> values;

    // Compute the iterated values of the sequence x_n = g^x_n-1 mod p
    // until a collision is found
    while (d == 1) {
        x = (x * x + 1) % p;
        y1 = (y1 * g) % p;
        y2 = (y2 * g) % p;
        y2 = (y2 * g) % p;
        d = std::gcd(std::llabs(y2 - y1), p);
        values[x] = y1;
    }

    // Compute the discrete logarithm using the collision point
    if (d == p) {
        return -1;
    } else {
        uint64_t x0 = std::llabs(y2 - y1) / d;
        uint64_t y0 = values[x0];
        uint64_t k = 1;
        while (y0 != y) {
            y0 = (y0 * g) % p;
            k++;
        }
        return k * x0 % (p - 1);
    }
}

/* Baby-Step Giant-Step */
uint64_t gpmp::Logarithms::BSGS(uint64_t a, uint64_t b, uint64_t m) {
    uint64_t n = (uint64_t)sqrt(m) + 1;

    std::unordered_map<uint64_t, uint64_t> value;

    // store all values of a^(n*i) of LHS
    for (uint64_t i = n; i >= 1; --i) {
        value[__LOG_PRIMES__.mod_pow(a, i * n, m)] = i;
    }

    for (uint64_t j = 0; j < n; ++j) {
        // calculate (a ^ j) * b and check
        uint64_t cur = (__LOG_PRIMES__.mod_pow(a, j, m) * b) % m;

        // If collision occurs i.e., LHS = RHS
        if (value[cur]) {
            uint64_t ans = value[cur] * n - j;
            // Check whether ans lies below m or not
            if (ans < m) {
                return ans;
            }
        }
    }
    return -1;
}
