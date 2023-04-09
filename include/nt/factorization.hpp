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

/**
 * @file
 *
 * Definitions for operations related to Integer Factorization
 */

#ifndef FACTORIZATION_HPP
#define FACTORIZATION_HPP
#include "../threadpool.hpp"
#include <condition_variable>
#include <cstdint>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <stdio.h>
#include <thread>
#include <vector>

namespace mtpk {
class Factorization {
  public:
    // std::vector<int64_t> pollard_rho(const std::vector<int64_t>&
    // nums_to_factorize);
    /* integer factorization */

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
     * @brief This function implements the Pollard Rho algorithm for
     * integer factorization.
     * @param n The integer to be factorized.
     * @return int64_t One of the prime factors of n.
     */
    int64_t pollard_rho(int64_t n);

    /*  */
    std::vector<std::future<int64_t>>
    pollard_rho_thread(const std::vector<int64_t> &nums_to_factorize);
    /* Lenstra elliptic-curve factorization */
    // int64_t LECF(int64_t n);

    /*  */
};

} // namespace mtpk

#endif
