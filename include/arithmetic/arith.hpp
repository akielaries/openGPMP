/*
 * definitions for basic arithmetic operations 
 */

#ifndef RMARITH_H
#define RMARITH_H
#include <vector>
#include <iostream>
#include <stdio.h>
#include <algorithm>

class arith {

    public:
        /*
         * It is easiest to include the implementation of our template
         * methods in our header files
         * Addition
         */
        template<typename T>
        inline T add(T t) {
            return t;
        }
        template<typename T, typename... Ts>
        inline auto add(T t, Ts... ts) {
            return t + add(ts...);
        }
        
        // subtraction
        template<typename X>
        inline X sub(X x) {
            return x;
        }
        template<typename X, typename... Xy>
        inline auto sub(X x, Xy... xy) {
            return x - sub(xy...);
        }

        // multiplication
        template<typename W>
        inline W mult(W w) {
            return w;
        }
        template<typename W, typename... Wv>
        inline auto mult(W w, Wv... wv) {
            return w * mult(wv...);
        }

        // exponentiation
        template<typename Z>
        inline Z exp(Z z) {
            return z;
        }
        template<typename Z, typename... Zy>
        inline auto exp(Z z, Zy... zy) {
            return z *= exp(zy...);
        }
};

class Basics {
    
    public:
        /* raise to a power */
        int power (int x, unsigned int y, int p);
        /* greatest power of two given integers */
        int greatest_power(int n, int p);
        /* greatest common factor */
        int gcd(int x, int y);
};

#endif

