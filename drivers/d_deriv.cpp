/* RM-pkg
 * TESTING DERIVATIVE OPERATIONS
 * Test driver showing how to use different derivative-based operations
 * in RM-pkg
 */
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cassert>
#include "../include/RM_deriv.hpp"


int main() {
    // declare calculus class obj
    calculus calc;

    // we can declare our equation as a string for ease of use
    std::string st0 = "4x^3 + 3x^1 + 2x^2";
    std::string st1 = "1x^3";

    int val0 = 2;
    int val1 = 3;

    /* 
     * this specific derivative function calculates the derivative of a 
     * polynomial at a given value
     */
    std::cout << calc.rm_deriv(st0, val0) << std::endl;
    std::cout << calc.rm_deriv(st1, val1) << std::endl;

    return 0;
}

