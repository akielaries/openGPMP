/*************************************************************************
 *
 *  Project
 *                        __  __ _______ _____  _  __
 *                       |  \/  |__   __|  __ \| |/ /
 *  ___  _ __   ___ _ __ | \  / |  | |  | |__) | ' /
 * / _ \| '_ \ / _ \ '_ \| |\/| |  | |  |  ___/|  <
 *| (_) | |_) |  __/ | | | |  | |  | |  | |    | . \
 * \___/| .__/ \___|_| |_|_|  |_|  |_|  |_|    |_|\_\
 *      | |
 *      |_|
 *
 *
 * Copyright (C) Akiel Aries, <akiel@akiel.org>, et al.
 *
 * This software is licensed as described in the file LICENSE, which
 * you should have received as part of this distribution. The terms
 * among other details are referenced in the official documentation
 * seen here : https://akielaries.github.io/openMTPK/ along with
 * important files seen in this project.
 *
 * You may opt to use, copy, modify, merge, publish, distribute
 * and/or sell copies of the Software, and permit persons to whom
 * the Software is furnished to do so, under the terms of the
 * LICENSE file. As this is an Open Source effort, all implementations
 * must be of the same methodology.
 *
 *
 *
 * This software is distributed on an AS IS basis, WITHOUT
 * WARRANTY OF ANY KIND, either express or implied.
 *
 ************************************************************************/

/*
 * Implementing various derivative related functions in C++
 */
#include "../../include/calculus/differential.hpp"
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

int64_t mtpk::Differential::derivative_term(std::string p_term, int64_t val) {
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

int64_t mtpk::Differential::deriv_at(std::string &poly, int64_t val) {
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

std::string mtpk::Differential::deriv_str(std::string &poly) {
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
