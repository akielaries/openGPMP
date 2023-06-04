#include "../../include/nt/prime_gen.hpp"
#include "../../include/arithmetic.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <random>
#include <stdio.h>
#include <string>

/*
 * since this module deals with a great deal of number theory and
 * various logical arithmetic operations, the greek algorithm sieve of
 * Eratosthenes is able to capture all prime numbers to any given
 * limit
 */
void gpmp::PrimalityGen::sieve_of_eratosthenes(uint64_t n) {
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
}
