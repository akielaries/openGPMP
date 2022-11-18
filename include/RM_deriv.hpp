/*
 * definitions for derivative operations operations 
 */

#ifndef RMDERIV_H
#define RMDERIV_H
#include <vector>
#include <string>
#include <stdio.h>


class calculus {

    public:
        long long derivativeTerm(std::string pTerm, long long val);
        long long rm_deriv(std::string& poly, int val);

};

#endif

