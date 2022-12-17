/*
 * definitions for basic arithmetic operations 
 */

#ifndef ARITH_H
#define ARITH_H
#include <vector>
#include <iostream>
#include <stdio.h>
#include <algorithm>


class Basics {
    
    public:
        /* greatest power of two given integers */
        int greatest_power(int n, int p);
        /* greatest common divisor */
        int rm_gcd(int x, int y);
};

#endif

