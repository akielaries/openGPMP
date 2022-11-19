/*
 * definitions for derivative operations operations 
 */

#ifndef RMDERIV_H
#define RMDERIV_H
#include <string>


class calculus {

    public:
        long long derivativeTerm(std::string pTerm, long long val);
        long long rm_deriv_at(std::string& poly, int val);
        std::string rm_deriv(std::string& poly);

};

#endif

