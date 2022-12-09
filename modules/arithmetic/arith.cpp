/*
 * stubbed out implementation file for arithmetic operations
 */

#include "../../include/arithmetic/arith.hpp"
    

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

