/*
 * Implementing various derivative related functions in C++
 */
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include "../../include/calculus/deriv.hpp"

/*
long long calculus::derivativeTerm(std::string pTerm, long long val) {
    // Get coefficient
    std::string coeffStr = "";
    int i;
    
    for (i = 0; pTerm[i] != 'x'; i++) {
        coeffStr.push_back(pTerm[i]);
    }
    long long coeff = atol(coeffStr.c_str());
 
    // Get Power (Skip 2 characters for x and ^)
    std::string powStr = "";
    
    for (i = i + 2; i != pTerm.size(); i++) {
        powStr.push_back(pTerm[i]);
    }
    long long expo = atol(powStr.c_str());
 
    // For ax^n, we return anx^(n-1)

    long long result = coeff * expo * pow(val, expo - 1);

    return coeff * expo * pow(val, expo - 1);
}
*/ 

long long calculus::derivativeTerm(std::string pTerm, long long val) {

    printf("DEBUGGING DERIVTERM\n\n"); 
    // Get coefficient
    std::string coeffStr = "";
    int i;
    
    for (i = 0; pTerm[i] != 'x'; i++) {
        coeffStr.push_back(pTerm[i]);
    }
    long long coeff = atol(coeffStr.c_str());
 
    // Get Power (Skip 2 characters for x and ^)
    std::string powStr = "";
    
    for (i = i + 2; i != pTerm.size(); i++) {
        powStr.push_back(pTerm[i]);
        printf("powStr = %s \n", powStr.c_str());
    }
    long long expo = atol(powStr.c_str());
 
    // For ax^n, we return anx^(n-1)
    printf("powStr = %s \n", powStr.c_str());
    printf("pTerm = %s \n", pTerm.c_str());
    printf("coeff = %lld \n", coeff);
    printf("Exponent = %lld \n", expo);

    long long result = coeff * expo * pow(val, expo - 1);

    return coeff * expo * pow(val, expo - 1);
}

long long calculus::rm_deriv_at(std::string& poly, int val) {
    long long ans = 0;
 
    // We use istringstream to get input in tokens
    std::istringstream is(poly);
 
    std::string pTerm;
    while (is >> pTerm) {
 
        // If the token is equal to '+' then continue with the string
        if (pTerm == "+")
            continue;
       
        // Otherwise find the derivative of that particular term
        else
            ans = (ans + derivativeTerm(pTerm, val));
    }
    printf("\nDEBUGGING DERIV AT\n\n");
    printf("ans = %lld\n", ans);
    return ans;
}
 
std::string calculus::rm_deriv(std::string& poly) {
    long long ans = 0;
 
    // We use istringstream to get input in tokens
    std::istringstream is(poly);
 
    std::string pTerm;
    while (is >> pTerm) {
        // std::cout << "poly = " << poly << std::endl;
        // std::cout << "pTerm = " << pTerm << std:: endl;
        
        // If the token is equal to '+' then continue with the string
        if (pTerm == "+")
            continue;
       
        // Otherwise find the derivative of that particular term
        else
            ans = ans;
    }
    return poly;
}

