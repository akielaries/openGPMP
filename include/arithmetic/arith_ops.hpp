/**
 * @file
 * @author Akiel Aries
 *  
 * Definitions for basic arithmetic operations 
 */

#ifndef ARITH_OPS_HPP
#define ARITH_OPS_HPP
#include <vector>
#include <iostream>
#include <stdio.h>
#include <algorithm>


namespace mtpk {

/**
 * @brief Arithmetic Basics Class based on Arithmetic operations
 */
class Basics {

    public:
        /**
         * @brief Find greatest power of 2 itegers
         * 
         * @param[in] n : integer 1
         * @param[in] p : integer 2
         * 
         * @return result : (int)
         */
        int greatest_power(int n, int p);

        /**
         * @brief Find Greatest Common Divisor of 2 integers
         * 
         * @param[in] x : integer 1
         * @param[in] y : integer 2
         * 
         * @return result : (int)
         */
        int op_gcd(int x, int y);
};

} // namespace

#endif

