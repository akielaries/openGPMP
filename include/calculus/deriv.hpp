/*
 * definitions for derivative operations operations 
 */

#ifndef DERIV_HPP
#define DERIV_HPP
#include <string>


class calculus {

    public:
        /* finding coeffs and exponents of the function */
        long long derivative_term(std::string pTerm, long long val);
        //long long rm_deriv_term(std::string& poly, long long val);

        /* finding the derivative of a function with x = to a certain value */
        long long deriv_at(std::string& poly, int val);
        
        /* 
         * calculate the derivative of a given polynomial, returning the 
         * derivative as a string
         */
        std::string deriv(std::string& poly);

};

#endif

