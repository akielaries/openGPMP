/* RM-pkg
 * TESTING DERIVATIVE OPERATIONS
 * Test driver showing how to use different derivative-based operations
 * in RM-pkg
 */
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <cassert>
#include "../include/RM_deriv.hpp"


int main() {
    /*
     * When calling the rm_deriv() and rm_deriv_at() functions, the 
     * polynomial must be passed in as a string with the following format:
     * 
     */
    std::cout << "DERIVATIVE EXAMPLE\n\n";

    // declare calculus class obj
    calculus calc;

    // we can declare our equation as a string for ease of use
    std::string st0 = "4x^3 + 3x^1 + 2x^2 + 5x^1 + 2x";
    //std::string st0 = "4x^3 + 3x^1";
    std::string st1 = "1x^3";

    /*
     * this derivative function finds the first derivative of a given 
     * polynomial
     */
    std::cout << "Finding the first derivative of a given polynomial.\n";
    // std::string deriv_result0 = calc.rm_deriv(st0);
    /*

    printf("f(x) = %s \n", st0.c_str());
    printf("DEBUGGING THIS\n");
    //printf("df/dx of f(x) = %s\n", deriv_result0.c_str());
    printf("\n");
    */
    std::cout << "<------------------------>\n" << std::endl;
    /* 
     * this specific derivative function calculates the derivative of a 
     * polynomial at a given value
     */
    std::cout << "First derivative at a given value.\n";
    int val0 = 2;
    int val1 = 3;
    long long deriv_result2 = calc.rm_deriv_at(st0, val0);
    std::cout << deriv_result2 << std::endl;

    /*
    printf("f(x) = %s \n", st0.c_str());
    printf("df/dx of f(x) at x = %d = %lld\n\n", val0, deriv_result2);

    long long deriv_result3 = calc.rm_deriv_at(st1, val1);

    printf("f(x) = %s \n", st1.c_str());
    printf("df/dx of f(x) at x = %d = %lld\n", val1, deriv_result3);
    */
    return 0;
}

