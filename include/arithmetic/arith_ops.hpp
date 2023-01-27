/**
 * @file
 * @author Akiel Aries
 *  
 * Definitions for basic arithmetic operations 
 */

#ifndef ARITH_OPS_HPP
#define ARITH_OPS_HPP
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <vector>

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
    int64_t greatest_power(int64_t n, int64_t p);

    /**
         * @brief Find Greatest Common Divisor of 2 integers
         * 
         * @param[in] x : integer 1
         * @param[in] y : integer 2
         * 
         * @return result : (int)
         */
    int64_t op_gcd(int64_t x, int64_t y);
};

} // namespace mtpk

#endif
