/**
 * @file
 *  
 * Definitions for basic arithmetic operations 
 */

#ifndef ARITH_HPP
#define ARITH_HPP
#include <vector>
#include <iostream>
#include <stdio.h>
#include <algorithm>


namespace mtpk {
/**
 * @brief Arithmetic Template Class. Each method is variadic taking 'n' params.
 */
class Arith {

    public:
        /**
         * @brief Addition method
         * @param 'n' addends 
         * @return sum
         */
        template<typename T>
        inline T add(T t) {
            return t;
        }
        template<typename T, typename... Ts>
        inline auto add(T t, Ts... ts) {
            return t + add(ts...);
        }

        /**
         * @brief Subtraction method
         * @param minuend
         * @param 'n' subtrahends
         * @return difference
         */
        template<typename X>
        inline X sub(X x) {
            return x;
        }
        template<typename X, typename... Xy>
        inline auto sub(X x, Xy... xy) {
            return x - sub(xy...);
        }

        /**
         * @brief Multiplication method
         * @param 'n' factors
         * @return product
         */
        template<typename W>
        inline W mult(W w) {
            return w;
        }
        template<typename W, typename... Wv>
        inline auto mult(W w, Wv... wv) {
            return w * mult(wv...);
        }

        /**
         * @brief Exponentiation method
         * @param base
         * @param 'n' powers
         * @return product
         */
        template<typename Z>
        inline Z exp(Z z) {
            return z;
        }
        template<typename Z, typename... Zy>
        inline auto exp(Z z, Zy... zy) {
            return z *= exp(zy...);
        }
};

/**
 * @brief Arithmetic-based basics Class.
 */
class Basics {

    public:
        /**
         * @brief Find greatest power
         * @param n: (int)
         * @param p: (int)
         * @return result: (int)
         */
        int greatest_power(int n, int p);
        /**
         * @brief Find Greatest Common Divisor
         * @param x: (int)
         * @param y: (int)
         * @return result: (int)
         */
        int op_gcd(int x, int y);
};
} // namespace

#endif

