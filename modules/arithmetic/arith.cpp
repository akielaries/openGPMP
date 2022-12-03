/*
 * stubbed out implementation file for arithmetic operations
 */

#include "../../include/arithmetic/arith.hpp"
    

int Basics::power(int x, unsigned int y, int p) {
    int res = 1;    // Initialize result
    x = x % p;      // Update x if it is more than or
                    // equal to p

    while (y > 0) {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res * x) % p;

        // y must be even now
        y = y >> 1; // y = y/2
        x = (x * x) % p;
    }
    return res;
}

int Basics::greatest_power(int n, int p) {
    int x = 0;

    // Calculate x = n/p + n/(p^2) + n/(p^3) + ....
    while (n) {
        n /= p;
        x += n;
    }
    return x;
}

int Basics::gcd(int x, int y) {
    if(x < y)
        return gcd(y, x);

    else if(x % y == 0)
        return y;

    else
        return gcd(y, x % y);
}

