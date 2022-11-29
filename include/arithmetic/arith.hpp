/*
 * definitions for basic arithmetic operations 
 */

#ifndef RMARITH_H
#define RMARITH_H
#include <vector>
#include <iostream>
#include <stdio.h>


class arith {

    public:
        /*
         * It is easiest to include the implementation of our template
         * methods in our header files
         * Addition
         */
        template<typename T>
        inline T rm_add(T t) {
            return t;
        }

        template<typename T, typename... Ts>
        inline auto rm_add(T t, Ts... ts) {
            return t + rm_add(ts...);
        }
        
        // subtraction
        template<typename X>
        inline X rm_sub(X x) {
            return x;
        }

        template<typename X, typename... Xy>
        inline auto rm_sub(X x, Xy... xy) {
            return x - rm_sub(xy...);
        }

        // multiplication
        template<typename W>
        inline W rm_mult(W w) {
            return w;
        }

        template<typename W, typename... Wv>
        inline auto rm_mult(W w, Wv... wv) {
            return w * rm_mult(wv...);
        }

};

#endif

