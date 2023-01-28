/*
 * Implementing various derivative related functions in C++
 */
#include "../../include/calculus/deriv.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>

/*
int64_t Calculus::derivativeTerm(std::string p_term, long long val) {
    // Get coefficient
    std::string coeffStr = "";
    int i;

    for (i = 0; p_term[i] != 'x'; i++) {
        coeffStr.push_back(p_term[i]);
    }
    int64_t coeff = atol(coeffStr.c_str());

    // Get Power (Skip 2 characters for x and ^)
    std::string powStr = "";

    for (i = i + 2; i != p_term.size(); i++) {
        powStr.push_back(p_term[i]);
    }
    int64_t expo = atol(powStr.c_str());

    // For ax^n, we return anx^(n-1)

    int64_t result = coeff * expo * pow(val, expo - 1);

    return coeff * expo * pow(val, expo - 1);
}
*/

int64_t mtpk::Calculus::derivative_term(std::string p_term, int64_t val) {
    printf("DEBUGGING DERIVTERM\n\n");
    // Get coefficient
    std::string coeffStr = "";
    int64_t i;

    for (i = 0; p_term[i] != 'x'; i++) {
        coeffStr.push_back(p_term[i]);
    }
    int64_t coeff = atol(coeffStr.c_str());

    // Get Power (Skip 2 characters for x and ^)
    std::string powStr = "";

    for (i = i + 2; i != p_term.size(); i++) {
        powStr.push_back(p_term[i]);
        printf("powStr = %s \n", powStr.c_str());
    }
    int64_t expo = atol(powStr.c_str());

    // For ax^n, we return anx^(n-1)
    printf("powStr = %s \n", powStr.c_str());
    printf("p_term = %s \n", p_term.c_str());
    printf("coeff = %ld \n", coeff);
    printf("Exponent = %ld \n", expo);

    int64_t result = coeff * expo * pow(val, expo - 1);

    return coeff * expo * pow(val, expo - 1);
}

int64_t mtpk::Calculus::deriv_at(std::string &poly, int64_t val) {
    int64_t ans = 0;

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
    printf("ans = %ld\n", ans);
    return ans;
}

std::string mtpk::Calculus::deriv(std::string &poly) {
    int64_t ans = 0;

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
