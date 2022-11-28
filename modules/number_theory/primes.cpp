/*
 * Some core concepts seen in Number Theory primarily prime number based
 * equations, formulas, algorithms. 
 */
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include "../../include/number_theory/primes.hpp"


int basics::power (int x, unsigned int y, int p) {
    int res = 1;    // Initialize result
    x = x % p;      // Update x if it is more than or
                    // equal to p
    
    while (y > 0) {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res*x) % p;
 
        // y must be even now
        y = y>>1; // y = y/2
        x = (x*x) % p;
    }
    return res;
}

int basics::greatest_power(int n, int p) {
    int x = 0;
 
    // Calculate x = n/p + n/(p^2) + n/(p^3) + ....
    while (n) {
        n /= p;
        x += n;
    }
    return x;
}

int basics::gcd(int x, int y) {
    if(x < y)
        return gcd(y, x);
    
    else if(x % y == 0)
        return y;
    
    else 
        return gcd(y, x % y); 
}

long long primality::modulo(long long base, 
        long long exponent,
        long long mod) {

    long long x = 1;
    long long y = base;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            x = (x * y) % mod;

        y = (y * y) % mod;
        exponent = exponent / 2;
    }

    return x % mod;
}


bool primality::is_prime(int n) {
    if (n <= 1)
        return false;
 
    int iter = 2;
    // Check from 2 to n-1
    for (iter; iter < n; iter++)
        if (n % iter == 0)
            return false;
 
    return true;
}

/*
 * determining if a given number is likely to be prime
 */
bool primality::miller_rabin(int d, int n) {
    // Pick a random number in [2..n-2] Corner cases make sure that n > 4
    int a = 2 + rand() % (n - 4);
 
    // Compute a^d % n
    int x = power(a, d, n);
 
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

/*
 * another algorithm capable of finding primes
 */
int primality::jacobian_number(long long a, long long n) {
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
        swap(a, n);

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
bool primality::solovoy_strassen(long long p, int iters) {
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
bool primality::carmichael_number(int n) {
    for (int b = 2; b < n; b++) {
        // If "b" is relatively prime to n
        if (gcd(b, n) == 1)
 
            // And pow(b, n-1)%n is not 1,
            // return false.
            if (power(b, n - 1, n) != 1)
                return false;
    }
    return true;
}

/*
 * since this module deals with a great deal of number theory and various 
 * logical arithmetic operations, the greek algorithm sieve of Eratosthenes
 * is able to capture all prime numbers to any given limit
 */
void primality::sieve_of_eratosthenes(int n) {
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
void primality::pollard_rho(long long int n) {
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
        x = (modular_pow(x, 2, n) + c + n) % n;
 
        /* Hare Move: y(i+1) = f(f(y(i))) */
        y = (modular_pow(y, 2, n) + c + n) % n;
        y = (modular_pow(y, 2, n) + c + n) % n;
 
        /* check gcd of |x-y| and n */
        divisor = __gcd(abs(x - y), n);
 
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
int primality::ETF(unsigned int n) {
    unsigned int result = 1;

    int index = 2;
    
    for (index; index < n; index++) {
        if (gcd(index, n) == 1) {
            result++;
        }
    }

    return result;
}

