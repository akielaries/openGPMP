/*************************************************************************
 *
 *  Project
 *                         _____ _____  __  __ _____
 *                        / ____|  __ \|  \/  |  __ \
 *  ___  _ __   ___ _ __ | |  __| |__) | \  / | |__) |
 * / _ \| '_ \ / _ \ '_ \| | |_ |  ___/| |\/| |  ___/
 *| (_) | |_) |  __/ | | | |__| | |    | |  | | |
 * \___/| .__/ \___|_| |_|\_____|_|    |_|  |_|_|
 *      | |
 *      |_|
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
 * Some core concepts seen in Number Theory primarily prime number
 * based equations, formulas, algorithms.
 */
#include "../../include/nt/prime_test.hpp"
#include "../../include/arithmetic.hpp"
#include "../../include/core/threads.hpp"

#include <algorithm>
#include <cmath>
#include <cstdlib>

#ifdef __APPLE__
#include <stdlib.h>
#endif

#include <cstring>
#include <iostream>
#include <random>
#include <stdio.h>
#include <string>

// declare Basics and Primality class objects
gpmp::Basics ba;
gpmp::PrimalityTest prim;

// Calculates (a * b) mod m
uint64_t gpmp::PrimalityTest::mod_mul(uint64_t a, uint64_t b, uint64_t m) {
    uint64_t res = 0;
    while (b > 0) {
        if (b & 1) {
            res = (res + a) % m;
        }
        a = (2 * a) % m;
        b >>= 1;
    }
    return res;
}

// Calculates (a ^ b) mod m
uint64_t gpmp::PrimalityTest::mod_pow(uint64_t a, uint64_t b, uint64_t m) {
    uint64_t res = 1;
    a %= m;
    while (b > 0) {
        if (b & 1) {
            res = mod_mul(res, a, m);
        }
        a = mod_mul(a, a, m);
        b >>= 1;
    }
    return res;
}

/*
uint64_t gpmp::PrimalityTest::mod_pow(uint64_t base, uint64_t exponent,
                                 uint64_t mod) {
    uint64_t x = 1;
    uint64_t y = base;

    while (exponent > 0) {
        if (exponent & 1) {
            x = (x * y) % mod;
        }
        exponent = exponent >> 1;
        y = (y * y) % mod;
    }

    return x;
}*/

bool gpmp::PrimalityTest::is_prime(uint64_t n) {
    if (n <= 1) {
        return false;
    }

    // Check from 2 to n-1
    for (uint64_t iter = 2; iter < n; iter++) {
        if (n % iter == 0) {
            return false;
        }
    }
    return true;
}

/*
 * determining if a given number is likely to be prime
 */
bool gpmp::PrimalityTest::compute_miller_rabin(uint64_t d, uint64_t n) {
    // Pick a random number in [2..n-2] Corner cases make sure that n
    // > 4

#ifdef __APPLE__
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint64_t> dist(2, n - 3);
    uint64_t a = dist(gen);
#else
    uint64_t a = 2 + rand() % (n - 4);
#endif
    /*
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dis(2, n - 4);
    uint64_t a = dis(gen);
    */

    // Compute a^d % n
    uint64_t x = mod_pow(a, d, n);

    if (x == 1 || x == n - 1) {
        return true;
    }

    // Keep squaring x while one of the following doesn't
    // happen
    // (I)   d does not reach n-1
    // (II)  (x^2) % n is not 1
    // (III) (x^2) % n is not n-1
    while (d != n - 1) {
        x = (x * x) % n;
        d *= 2;

        if (x == 1) {
            return false;
        }
        if (x == n - 1) {
            return true;
        }
    }

    // Return composite
    return false;
}

bool gpmp::PrimalityTest::witness(uint64_t n,
                                  uint64_t d,
                                  uint64_t a,
                                  uint64_t s) {
    uint64_t x = mod_pow(a, d, n);
    if (x == 1 || x == n - 1) {
        return false;
    }
    for (uint64_t r = 1; r < s; r++) {
        x = mod_mul(x, x, n);
        if (x == n - 1) {
            return false;
        }
    }
    return true;
}

bool gpmp::PrimalityTest::miller_rabin_prime(uint64_t n, uint64_t iters = 10) {
    if (n < 2) {
        return false;
    }
    if (n == 2 || n == 3) {
        return true;
    }
    if (n % 2 == 0) {
        return false;
    }
    uint64_t d = n - 1, s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }
    for (uint64_t i = 0; i < iters; i++) {
        uint64_t a = rand() % (n - 3) + 2;
        if (witness(n, d, a, s)) {
            return false;
        }
    }
    return true;
}

void gpmp::PrimalityTest::miller_rabin(uint64_t iters,
                                       uint64_t min_val,
                                       uint64_t max_val) {
    std::cout << "Primes between " << min_val << " and " << max_val
              << std::endl;
    // int d = iters - 1;
    // int min_val = minimum;
    // int max_val = maximum;

    // traverse from the min to max
    for (; min_val < max_val; min_val++) {
        // while (min_val < max_val) {
        if (miller_rabin_prime(min_val, iters)) {
            std::cout << min_val << " ";
        }
    }
    std::cout << "\n";
}

bool gpmp::PrimalityTest::AKS(uint64_t n) {
    // Check if n is a perfect power
    for (uint64_t b = 2; b <= std::sqrt(n); b++) {
        uint64_t a = std::round(std::pow(n, 1.0 / b));
        if (std::pow(a, b) == n) {
            return false;
        }
    }

    // Find the smallest r such that ord_r(n) > log2(n)^2
    uint64_t r = 2;
    while (r < n) {
        bool is_coprime = true;
        for (uint64_t i = 2; i <= std::sqrt(r); i++) {
            if (r % i == 0 && n % i == 0) {
                is_coprime = false;
                break;
            }
        }
        if (is_coprime) {
            uint64_t t = 1;
            for (uint64_t i = 0; i < std::floor(2 * std::log2(n)); i++) {
                t = (t * r) % n;
            }
            if (t == 1) {
                r++;
                continue;
            }
            bool is_prime = true;
            for (uint64_t i = 0; i < std::floor(std::log2(n)); i++) {
                t = (t * t) % n;
                if (t == 1) {
                    is_prime = false;
                    break;
                }
            }
            if (is_prime) {
                return true;
            }
        }
        r++;
    }
    return false;
}

/*
 * another algorithm capable of finding primes
 */
uint64_t gpmp::PrimalityTest::jacobian_number(uint64_t a, uint64_t n) {
    if (!a)
        return 0; // (0/n) = 0

    uint64_t ans = 1;

    if (a < 0) {
        a = -a; // (a/n) = (-a/n)*(-1/n)
        if (n % 4 == 3)
            ans = -ans; // (-1/n) = -1 if n = 3 (mod 4)
    }

    if (a == 1)
        return ans; // (1/n) = 1

    while (a) {
        if (a < 0) {
            a = -a; // (a/n) = (-a/n)*(-1/n)
            if (n % 4 == 3)
                ans = -ans; // (-1/n) = -1 if n = 3 (mod 4)
        }

        while (a % 2 == 0) {
            a = a / 2;
            if (n % 8 == 3 || n % 8 == 5)
                ans = -ans;
        }
        std::swap(a, n);

        if (a % 4 == 3 && n % 4 == 3)
            ans = -ans;

        a = a % n;

        if (a > n / 2)
            a = a - n;
    }

    if (n == 1)
        return ans;

    return 0;
}
/*
 * primality test determining if a number is composite or probably
 * prime.
 *
 * a^(p-1)/2 = (a/p) (mod p)
 */
bool gpmp::PrimalityTest::solovoy_strassen(uint64_t p, uint64_t iters) {
    if (p < 2)
        return false;

    if (p != 2 && p % 2 == 0)
        return false;

    for (uint64_t i = 0; i < iters; i++) {
        // Generate a random number a
        uint64_t a = rand() % (p - 1) + 1;
        uint64_t jacobian = (p + jacobian_number(a, p)) % p;
        uint64_t mod = mod_pow(a, (p - 1) / 2, p);

        if (!jacobian || mod != jacobian)
            return false;
    }
    return true;
}

/*
 * Absolute Fermat Pseudoprimes referred to as Carmichael Numbers
 * are composite integers satisfying the congruence forumla below
 * b^n - 1 = b (mod n)
 */
bool gpmp::PrimalityTest::carmichael_num(uint64_t n) {
    for (uint64_t b = 2; b < n; b++) {
        // If "b" is relatively prime to n
        if (ba.op_gcd(b, n) == 1)
            // And pow(b, n-1)%n is not 1, return false.
            if (mod_pow(b, n - 1, n) != 1)
                return false;
    }
    return true;
}

/*
 * since this module deals with a great deal of number theory and
 * various logical arithmetic operations, the greek algorithm sieve of
 * Eratosthenes is able to capture all prime numbers to any given
 * limit
 */
/*
void gpmp::PrimalityTest::sieve_of_eratosthenes(uint64_t n) {
    // Create a boolean array "prime[0..n]" and initialize
    // all entries it as true. A value in prime[i] will
    // finally be false if i is Not a prime, else true.
    bool prime[n + 1];
    memset(prime, true, sizeof(prime));

    for (uint64_t p = 2; p * p <= n; p++) {
        // If prime[p] is not changed, then it is a prime
        if (prime[p] == true) {
            // Update all multiples of p greater than or
            // equal to the square of it numbers which are
            // multiple of p and are less than p^2 are
            // already been marked.
            for (uint64_t i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }

    // Print all prime numbers
    for (uint64_t p = 2; p <= n; p++) {
        if (prime[p]) {
            std::cout << p << " " << std::endl;
        }
    }
}*/

/*
 * Euler's Totient Function counts the positive numbers up until a
 * given integer
 *
 * Definition: For any positive integer n, Φ(n) is the number of all
 * positive integers less than or equal to n that are relatively prime
 * to n.
 *
 * Example: Φ(1) = 1
 *          Φ(2) = 1
 *          Φ(3) = 2
 *          Φ(4) = 2
 *          Φ(5) = 4
 */
uint64_t gpmp::PrimalityTest::ETF(uint64_t n) {
    uint64_t result = 1;

    for (uint64_t index = 2; uint64_t(index) < n; index++) {
        if (ba.op_gcd(index, n) == 1) {
            result++;
        }
    }

    return result;
}
