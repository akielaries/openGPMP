/*
 * Some core concepts seen in Number Theory primarily prime number based
 * equations, formulas, algorithms. 
 */
#include <cstdlib>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
#include <stdio.h>
#include "../../include/number_theory/primes.hpp"
#include "../../include/arithmetic/arith.hpp"


// declare Basics and Primality class objects
Basics basics;
Primality prim;


long long int Primality::modulo(long long int base, 
        long long int exponent,
        long long int mod) {

    long long x = 1;
    long long y = base;

    while (exponent > 0) {
        if (exponent % 2 == 1) {
            x = (x * y) % mod;
        }
        y = (y * y) % mod;
        exponent = exponent / 2;
    }

    return x % mod;
}

long long int Primality::modulo_pow(long long int base, 
        long long int exponent,
        long long int mod) {

    long long x = 1;
    long long y = base;

    while (exponent > 0) {
        if (exponent & 1) {
            x = (x * y) % mod;
        }
        exponent = exponent >> 1;
        y = (y * y) % mod;
    }

    return x;
}

bool Primality::is_prime(int n) {
    if (n <= 1)
        return false;
 
    // Check from 2 to n-1
    for (int iter = 2; iter < n; iter++)
        if (n % iter == 0)
            return false;
 
    return true;
}


/*
 * determining if a given number is likely to be prime
 */
bool Primality::compute_miller_rabin(int d, int n) {
    // Pick a random number in [2..n-2] Corner cases make sure that n > 4
    int a = 2 + rand() % (n - 4);
 
    // Compute a^d % n
    int x = basics.power(a, d, n);
 
    if (x == 1  || x == n-1)
       return true;
 
    // Keep squaring x while one of the following doesn't
    // happen
    // (i)   d does not reach n-1
    // (ii)  (x^2) % n is not 1
    // (iii) (x^2) % n is not n-1
    while (d != n - 1) {
        x = (x * x) % n;
        d *= 2;
 
        if (x == 1)      
            return false;
        if (x == n-1)    
            return true;
    }
 
    // Return composite
    return false;
}

void Primality::miller_rabin(int iters, int minimum, int maximum) {
    int d = iters - 1;
    int min_val = minimum;
    int max_val = maximum;

    while (d % 2 == 0) {
        d /= 2;
    }
    std::cout << "1 loop min_val: " << min_val << std::endl;

    // traverse from the min to max
    for (min_val; min_val < max_val; min_val++) {
        std::cout << "2 loop min_val: " << min_val << std::endl;
    
        // traverse given number of iterations
        for (int i = 0; i < iters; i++) {
            std::cout << "Traverse iters: " << i << std::endl;
            std::cout << "Iters: " << iters << std::endl;
            std::cout << "3 loop min_val: " << min_val << std::endl;
        
            // determine primes with miller_rabin method
            if (!compute_miller_rabin(d, min_val)) {
            
                //std::cout << "d = " << d << std::endl;
            }

            else {
                std::cout << min_val << ", ";
            }
        }
    }
    std::cout << "\n";
}

/*
 * another algorithm capable of finding primes
 */
int Primality::jacobian_number(long long a, long long n) {
    if (!a)
        return 0;// (0/n) = 0
 
    int ans = 1;

    if (a < 0) {
        a = -a; // (a/n) = (-a/n)*(-1/n)
        if (n % 4 == 3)
            ans = -ans; // (-1/n) = -1 if n = 3 (mod 4)
    }
 
    if (a == 1)
        return ans;// (1/n) = 1
 
    while (a) {
        if (a < 0) {
            a = -a;// (a/n) = (-a/n)*(-1/n)
            if (n % 4 == 3)
                ans = -ans;// (-1/n) = -1 if n = 3 (mod 4)
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
 * primality test determining if a number is composite or probably prime.
 * 
 * a^(p-1)/2 = (a/p) (mod p)
 */
bool Primality::solovoy_strassen(long long p, int iters) {
    if (p < 2)
        return false;
    
    if (p != 2 && p % 2 == 0)
        return false;
 
    for (int i = 0; i < iters; i++) {
        // Generate a random number a
        long long a = rand() % (p - 1) + 1;
        long long jacobian = (p + jacobian_number(a, p)) % p;
        long long mod = modulo(a, (p - 1) / 2, p);
 
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
bool Primality::carmichael_num(int n) {
    for (int b = 2; b < n; b++) {
        // If "b" is relatively prime to n
        if (basics.gcd(b, n) == 1)
            // And pow(b, n-1)%n is not 1, return false.
            if (basics.power(b, n - 1, n) != 1)
                return false;
    }
    return true;
}

/*
 * since this module deals with a great deal of number theory and various 
 * logical arithmetic operations, the greek algorithm sieve of Eratosthenes
 * is able to capture all prime numbers to any given limit
 */
void Primality::sieve_of_eratosthenes(int n) {
    // Create a boolean array "prime[0..n]" and initialize
    // all entries it as true. A value in prime[i] will
    // finally be false if i is Not a prime, else true.
    bool prime[n + 1];
    memset(prime, true, sizeof(prime));
 
    for (int p = 2; p * p <= n; p++) {
        // If prime[p] is not changed, then it is a prime
        if (prime[p] == true) {
            // Update all multiples of p greater than or
            // equal to the square of it numbers which are
            // multiple of p and are less than p^2 are
            // already been marked.
            for (int i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }
 
    // Print all prime numbers
    for (int p = 2; p <= n; p++)
        if (prime[p])
            std::cout << p << " " << std::endl;
}

/*
 * algorithm for integer factorization proportial to the runtime of the 
 * square root of the size of the smallest prime factor of the composite
 * factor being factorized. Given a positive and composite integer n, 
 * find a divisor of it.
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
long long int Primality::pollard_rho(long long int n) {
    /* initialize random seed */
    srand (time(NULL));
 
    /* no prime divisor for 1 */
    if (n == 1) 
        return n;
 
    /* even number means one of the divisors is 2 */
    if (n % 2 == 0) 
        return 2;
 
    /* we will pick from the range [2, N) */
    long long int x = (rand() % (n - 2)) + 2;
    long long int y = x;
 
    /* the constant in f(x).
     * Algorithm can be re-run with a different c
     * if it throws failure for a composite. */
    long long int c = (rand() % (n - 1)) + 1;

    /* Initialize candidate divisor (or result) */
    long long int divisor = 1; 
 
    /* until the prime factor isn't obtained.
       If n is prime, return n */
    while (divisor == 1) {
        /* Tortoise Move: x(i+1) = f(x(i)) */
        // take power 
        // calculate modulus
        x = (modulo_pow(x, 2, n) + c + n) % n;
 
        /* Hare Move: y(i+1) = f(f(y(i))) */
        y = (modulo_pow(y, 2, n) + c + n) % n;
        y = (modulo_pow(y, 2, n) + c + n) % n;
 
        /* check gcd of |x-y| and n */
        divisor = basics.gcd(abs(x - y), n);
        //divisor = std::__gcd(abs(x - y), n);
        /* retry if the algorithm fails to find prime factor
         * with chosen x and c */
        if (divisor == n) 
            return pollard_rho(n);
    }
 
    return divisor;
}

/*
 * Euler's Totient Function counts the positive numbers up until a given 
 * integer
 *
 * Definition: For any positive integer n, Φ(n) is the number of all positive 
 * integers less than or equal to n that are relatively prime to n.
 *
 * Example: Φ(1) = 1
 *          Φ(2) = 1
 *          Φ(3) = 2
 *          Φ(4) = 2
 *          Φ(5) = 4
 */
int Primality::ETF(unsigned int n) {
    unsigned int result = 1;
    
    for (int index = 2; unsigned(index) < n; index++) {
        if (basics.gcd(index, n) == 1) {
            result++;
        }
    }

    return result;
}

