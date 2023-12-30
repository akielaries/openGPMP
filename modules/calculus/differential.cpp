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
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>

gpmp::Differential
gpmp::Differential::operator+(const Differential &other) const {
    gpmp::Differential result = *this;

    for (const auto &term : other.terms) {
        result.add_term(term.coefficient, term.exponent);
    }

    return result;
}

gpmp::Differential
gpmp::Differential::operator*(const Differential &other) const {
    gpmp::Differential result;

    for (const auto &term1 : terms) {
        for (const auto &term2 : other.terms) {
            double newCoefficient = term1.coefficient * term2.coefficient;
            int newExponent = term1.exponent + term2.exponent;
            result.add_term(newCoefficient, newExponent);
        }
    }

    return result;
}

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
gpmp::Differential::product_rule(const Differential &other) const {
    gpmp::Differential result;

    for (const auto &term1 : terms) {
        for (const auto &term2 : other.terms) {
            double newCoefficient = term1.coefficient * term2.coefficient;
            int newExponent = term1.exponent + term2.exponent;
            result.add_term(newCoefficient, newExponent);
        }
    }

    return result;
}

gpmp::Differential
gpmp::Differential::quotient_rule(const Differential &other) const {
    gpmp::Differential result;

    for (const auto &term1 : terms) {
        for (const auto &term2 : other.terms) {
            double newCoefficient = (term1.coefficient * term2.exponent) -
                                    (term1.exponent * term2.coefficient);
            int newExponent = term1.exponent - term2.exponent;

            if (term2.coefficient != 0 && term2.exponent != 0) {
                result.add_term(newCoefficient / std::pow(term2.coefficient, 2),
                                newExponent);
            }
        }
    }

    return result;
}

gpmp::Differential
gpmp::Differential::chain_rule(const Differential &inner) const {
    gpmp::Differential result;

    for (const auto &term : terms) {
        gpmp::Differential inner_derivative = inner.power_rule();

        for (auto &inner_term : inner_derivative.terms) {
            inner_term.coefficient *= term.coefficient;
            inner_term.exponent += term.exponent;
        }

        result = result + inner_derivative;
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
