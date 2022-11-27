/*
 * definitions for derivative operations operations 
 */

#ifndef RMDERIV_H
#define RMDERIV_H
#include <string>


class calculus {

    public:
        /* finding coeffs and exponents of the function */
        long long derivativeTerm(std::string pTerm, long long val);
        //long long rm_deriv_term(std::string& poly, long long val);

        /* finding the derivative of a function with x = to a certain value */
        long long rm_deriv_at(std::string& poly, int val);
        
        /* 
         * calculate the derivative of a given polynomial, returning the 
         * derivative as a string
         */
        std::string rm_deriv(std::string& poly);

};

#endif

