/*************************************************************************
 *
 *  Project
 *                         _____ _____  __  __ _____
 *                        / ____|  __ \|  \/  |  __ \
 *  ___  _ __   ___ _ __ | |  __| |__) | \  / | |__) |
 * / _ \| '_ \ / _ \ '_ \| | |_ |  ___/| |\/| |  ___/
 *| (_) | |_) |  __/ | | | |__| | |    | |  | | |
 * \___/| .__/ \___|_| |_|\_____|_|    |_|  |_|_|
 *      | |
 *      |_|
 *
 * Copyright (C) Akiel Aries, <akiel@akiel.org>, et al.
 *
 * This software is licensed as described in the file LICENSE, which
 * you should have received as part of this distribution. The terms
 * among other details are referenced in the official documentation
 * seen here : https://akielaries.github.io/openGPMP/ along with
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
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>

void gpmp::Differential::add_term(double coefficient, int exponent) {
    terms.emplace_back(coefficient, exponent);
}

void gpmp::Differential::display() const {
    for (size_t i = 0; i < terms.size(); ++i) {
        const auto &term = terms[i];
        if (term.exponent > 1) {
            std::cout << term.coefficient << "*x^" << term.exponent;
        } else if (term.exponent == 1) {
            std::cout << term.coefficient << "*x";
        } else {
            std::cout << term.coefficient;
        }

        if (i < terms.size() - 1) {
            std::cout << " + ";
        }
    }
    std::cout << std::endl;
}

gpmp::Differential gpmp::Differential::power_rule() const {
    gpmp::Differential result;
    for (const auto &term : terms) {
        if (term.exponent > 0) {
            double newCoefficient = term.coefficient * term.exponent;
            int newExponent = term.exponent - 1;
            result.add_term(newCoefficient, newExponent);
        }
    }
    return result;
}

gpmp::Differential
gpmp::Differential::chain_rule(const gpmp::Differential &inner) const {
    gpmp::Differential result;

    for (const auto &outerTerm : terms) {
        // Apply the chain rule to each term of the outer function
        gpmp::Differential innerDerivative = inner.power_rule();

        // Multiply each term of innerDerivative by the coefficient of the outer
        // term
        for (auto &innerTerm : innerDerivative.terms) {
            innerTerm.coefficient *= outerTerm.coefficient;
        }

        // Multiply the inner derivative by the derivative of the outer term
        for (const auto &innerTerm : innerDerivative.terms) {
            double newCoefficient = innerTerm.coefficient;
            int newExponent = outerTerm.exponent + innerTerm.exponent;
            result.add_term(newCoefficient, newExponent);
        }
    }

    return result;
}

gpmp::Differential gpmp::Differential::nth_derivative(int n) const {
    gpmp::Differential result = *this;
    for (int i = 0; i < n; ++i) {
        result = result.power_rule();
    }
    return result;
}

double gpmp::Differential::eval(double x) const {
    double result = 0.0;
    for (const auto &term : terms) {
        result += term.coefficient * std::pow(x, term.exponent);
    }
    return result;
}

double gpmp::Differential::limit_at(double x) const {
    double result = 0.0;

    for (const auto &term : terms) {
        result += term.coefficient * std::pow(x, term.exponent);
    }

    return result;
}

double gpmp::Differential::limit_at_infinity() const {
    // Calculate the limit as x approaches infinity using the highest exponent
    // term
    if (!terms.empty()) {
        const auto &highest_term =
            *std::max_element(terms.begin(),
                              terms.end(),
                              [](const auto &a, const auto &b) {
                                  return a.exponent < b.exponent;
                              });

        if (highest_term.exponent > 0) {
            // If the highest term has a positive exponent, the limit is
            // infinity or negative infinity
            return (highest_term.coefficient > 0)
                       ? std::numeric_limits<double>::infinity()
                       : -std::numeric_limits<double>::infinity();
        } else {
            // If the highest term has a zero exponent, the limit is the
            // constant term
            return highest_term.coefficient;
        }
    }

    // If the differential is empty, the limit is undefined
    return std::numeric_limits<double>::quiet_NaN();
}
