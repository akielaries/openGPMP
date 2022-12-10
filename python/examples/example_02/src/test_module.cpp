#include <cmath>
#include <math.h>
#include <stdio.h>
#include <iostream>

#include "../include/test_module.hpp"

double var_foo = 3.4;

// factorial
long long int fact(long long int n) {
    if (n <= 1) {
        return 1;
    }
    else {
        n = n * fact(n - 1);
        return n;
    }
}

int my_mod(int n, int m) {
    int x = n % m;

    printf("Pre-swap  : n = %d, m = %d\n", n, m);
    std::swap(n , m);
    printf("Post-swap : n = %d, m = %d\n", n, m);


    return x;
}

