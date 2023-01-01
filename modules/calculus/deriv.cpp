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
long long Calculus::derivativeTerm(std::string p_term, long long val) {
    // Get coefficient
    std::string coeffStr = "";
    int i;
    
    for (i = 0; p_term[i] != 'x'; i++) {
        coeffStr.push_back(p_term[i]);
    }
    long long coeff = atol(coeffStr.c_str());
 
    // Get Power (Skip 2 characters for x and ^)
    std::string powStr = "";
    
    for (i = i + 2; i != p_term.size(); i++) {
        powStr.push_back(p_term[i]);
    }
    long long expo = atol(powStr.c_str());
 
    // For ax^n, we return anx^(n-1)

    long long result = coeff * expo * pow(val, expo - 1);

    return coeff * expo * pow(val, expo - 1);
}
*/ 

long long mtpk::Calculus::derivative_term(std::string p_term, long long val) {

    printf("DEBUGGING DERIVTERM\n\n"); 
    // Get coefficient
    std::string coeffStr = "";
    int i;
    
    for (i = 0; p_term[i] != 'x'; i++) {
        coeffStr.push_back(p_term[i]);
    }
    long long coeff = atol(coeffStr.c_str());
 
    // Get Power (Skip 2 characters for x and ^)
    std::string powStr = "";
    
    for (i = i + 2; i != p_term.size(); i++) {
        powStr.push_back(p_term[i]);
        printf("powStr = %s \n", powStr.c_str());
    }
    long long expo = atol(powStr.c_str());
 
    // For ax^n, we return anx^(n-1)
    printf("powStr = %s \n", powStr.c_str());
    printf("p_term = %s \n", p_term.c_str());
    printf("coeff = %lld \n", coeff);
    printf("Exponent = %lld \n", expo);

    long long result = coeff * expo * pow(val, expo - 1);

    return coeff * expo * pow(val, expo - 1);
}

long long mtpk::Calculus::deriv_at(std::string& poly, int val) {
    long long ans = 0;
 
    // We use istringstream to get input in tokens
    std::istringstream is(poly);
 
    std::string p_term;
    while (is >> p_term) {
 
        // If the token is equal to '+' then continue with the string
        if (p_term == "+")
            continue;
       
        // Otherwise find the derivative of that particular term
        else
            ans = (ans + derivative_term(p_term, val));
    }
    printf("\nDEBUGGING DERIV AT\n\n");
    printf("ans = %lld\n", ans);
    return ans;
}
 
std::string mtpk::Calculus::deriv(std::string& poly) {
    long long ans = 0;
 
    // We use istringstream to get input in tokens
    std::istringstream is(poly);
 
    std::string p_term;
    while (is >> p_term) {
        // std::cout << "poly = " << poly << std::endl;
        // std::cout << "p_term = " << p_term << std:: endl;
        
        // If the token is equal to '+' then continue with the string
        if (p_term == "+")
            continue;
       
        // Otherwise find the derivative of that particular term
        else
            ans = ans;
    }
    return poly;
}

