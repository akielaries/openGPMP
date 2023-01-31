/*
 * Some core concepts seen in Number Theory primarily prime number
 * based equations, formulas, algorithms.
 */
#include "../../include/nt/primes.hpp"
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
mtpk::Primality prim;

int64_t mtpk::Primality::mod_pow(int64_t base, int64_t exponent,
                                 int64_t mod) {
    int64_t x = 1;
    int64_t y = base;

    while (exponent > 0) {
        if (exponent & 1) {
            x = (x * y) % mod;
        }
        exponent = exponent >> 1;
        y        = (y * y) % mod;
    }

    return x;
}

bool mtpk::Primality::is_prime(int64_t n) {
    if (n <= 1)
        return false;

    // Check from 2 to n-1
    for (int64_t iter = 2; iter < n; iter++)
        if (n % iter == 0)
            return false;

    return true;
}

/*
 * determining if a given number is likely to be prime
 */
bool mtpk::Primality::compute_miller_rabin(int64_t d, int64_t n) {
    // Pick a random number in [2..n-2] Corner cases make sure that n
    // > 4
    int64_t a = 2 + rand() % (n - 4);

    // Compute a^d % n
    int64_t x = mod_pow(a, d, n);

    if (x == 1 || x == n - 1)
        return true;

    // Keep squaring x while one of the following doesn't
    // happen
    // (I)   d does not reach n-1
    // (II)  (x^2) % n is not 1
    // (III) (x^2) % n is not n-1
    while (d != n - 1) {
        x = (x * x) % n;
        d *= 2;

        if (x == 1)
            return false;
        if (x == n - 1)
            return true;
    }

    // Return composite
    return false;
}

bool mtpk::Primality::miller_rabin_prime(int64_t n, int64_t iters) {
    /*
     * this method will return true if n is prime, iters will
     * determine accuracy
     */
    // these are corner cases
    if (n <= 1 || n == 4)
        return false;
    if (n <= 3)
        return true;

    // odd will represent an odd number
    int64_t odd = n - 1;
    while (odd % 2 == 0) {
        odd /= 2;
    }

    // iterate given the iters paramater
    for (int64_t i = 0; i < iters; i++) {
        // compute using the Miller-Rabin method
        if (!compute_miller_rabin(odd, n)) {
            return false;
        }
    }
    return true;
}

void mtpk::Primality::miller_rabin(int64_t iters, int64_t min_val,
                                   int64_t max_val) {
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

/*
 * another algorithm capable of finding primes
 */
int64_t mtpk::Primality::jacobian_number(int64_t a, int64_t n) {
    if (!a)
        return 0; // (0/n) = 0

    int64_t ans = 1;

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
bool mtpk::Primality::solovoy_strassen(int64_t p, int64_t iters) {
    if (p < 2)
        return false;

    if (p != 2 && p % 2 == 0)
        return false;

    for (int64_t i = 0; i < iters; i++) {
        // Generate a random number a
        int64_t a        = rand() % (p - 1) + 1;
        int64_t jacobian = (p + jacobian_number(a, p)) % p;
        int64_t mod      = mod_pow(a, (p - 1) / 2, p);

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
bool mtpk::Primality::carmichael_num(int64_t n) {
    for (int64_t b = 2; b < n; b++) {
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
void mtpk::Primality::sieve_of_eratosthenes(int64_t n) {
    // Create a boolean array "prime[0..n]" and initialize
    // all entries it as true. A value in prime[i] will
    // finally be false if i is Not a prime, else true.
    bool prime[n + 1];
    memset(prime, true, sizeof(prime));

    for (int64_t p = 2; p * p <= n; p++) {
        // If prime[p] is not changed, then it is a prime
        if (prime[p] == true) {
            // Update all multiples of p greater than or
            // equal to the square of it numbers which are
            // multiple of p and are less than p^2 are
            // already been marked.
            for (int64_t i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }

    // Print all prime numbers
    for (int64_t p = 2; p <= n; p++)
        if (prime[p])
            std::cout << p << " " << std::endl;
}

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
int64_t mtpk::Primality::pollard_rho(int64_t n) {
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
int64_t mtpk::Primality::ETF(uint64_t n) {
    uint64_t result = 1;

    for (int64_t index = 2; uint64_t(index) < n; index++) {
        if (ba.op_gcd(index, n) == 1) {
            result++;
        }
    }

    return result;
}
