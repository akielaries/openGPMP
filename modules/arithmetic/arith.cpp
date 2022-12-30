/*
 * stubbed out implementation file for arithmetic operations
 */
#include "../../include/arithmetic/arith.hpp"
    

int mtpk::Basics::greatest_power(int n, int p) {
    int x = 0;

    // Calculate x = n/p + n/(p^2) + n/(p^3) + ....
    while (n) {
        n /= p;
        x += n;
    }
    return x;
}

int mtpk::Basics::op_gcd(int x, int y) {
    if(x < y)
        return op_gcd(y, x);

    else if(x % y == 0)
        return y;

    else
        return op_gcd(y, x % y);
}

