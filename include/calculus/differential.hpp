/*************************************************************************
 *
 *  Project
 *                         _____ _____  __  __ _____
 *                        / ____|  __ \|  \/  |  __ \
 *  ___  _ __   ___ _ __ | |  __| |__) | \  / | |__) |
 * / _ \| '_ \ / _ \ '_ \| | |_ |  ___/| |\/| |  ___/
 *| (_) | |_) |  __/ | | | |__| | |    | |  | | |
 * \___/| __/ \___|_| |_|\_____|_|    |_|  |_|_|
 *      | |
 *      |_|
 *
 * Copyright (C) Akiel Aries, <akiel@akielorg>, et al.
 *
 * This software is licensed as described in the file LICENSE, which
 * you should have received as part of this distribution The terms
 * among other details are referenced in the official documentation
 * seen here : https://akielariesgithub.io/openGPMP/ along with
 * important files seen in this project
 *
 * You may opt to use, copy, modify, merge, publish, distribute
 * and/or sell copies of the Software, and permit persons to whom
 * the Software is furnished to do so, under the terms of the
 * LICENSE file As this is an Open Source effort, all implementations
 * must be of the same methodology
 *
 *
 *
 * This software is distributed on an AS IS basis, WITHOUT
 * WARRANTY OF ANY KIND, either express or implied
 *
 ************************************************************************/

/**
 * @file
 *
 * Definitions for derivative operations
 */

#ifndef DIFFERENTIAL_HPP
#define DIFFERENTIAL_HPP
#include <string>
#include <vector>

namespace gpmp {

/**
 * @brief Represents a term in a polynomial
 */
class Term {
  public:
    double coefficient; /**< Coefficient of the term */
    int exponent;       /**< Exponent of the term */

    /**
     * @brief Constructs a Term with given coefficient and exponent
     * @param coef The coefficient of the term
     * @param exp The exponent of the term
     */
    Term(double coef, int exp) : coefficient(coef), exponent(exp) {
    }
};

/**
 * @brief Calculus Class with methods pertaining to basic operations
 */
class Differential {
  public:
    std::vector<Term> terms; /**< Vector of terms representing the polynomial */

    /**
     * @brief Overloaded addition operator for Differential objects
     * @param other The Differential object to add
     * @return The sum of two Differential objects
     */
    Differential operator+(const Differential &other) const;

    /**
     * @brief Overloaded multiplication operator for Differential objects
     * @param other The Differential object to multiply
     * @return The product of two Differential objects
     */
    Differential operator*(const Differential &other) const;

    /**
     * @brief Adds a term to the Differential object
     * @param coefficient The coefficient of the term to add
     * @param exponent The exponent of the term to add
     */
    void add_term(double coefficient, int exponent);

    /**
     * @brief Displays the polynomial in a readable format
     */
    void display() const;

    /**
     * @brief Computes the derivative using the power rule
     * @return The derivative of the current Differential object
     */
    Differential power_rule() const;

    /**
     * @brief Computes the derivative using the product rule
     * @param other The other Differential object in the product
     * @return The derivative of the product of two Differential objects
     */
    Differential product_rule(const Differential &other) const;

    /**
     * @brief Computes the derivative using the quotient rule
     * @param other The other Differential object in the quotient
     * @return The derivative of the quotient of two Differential objects
     */
    Differential quotient_rule(const Differential &other) const;

    /**
     * @brief Computes the derivative using the chain rule
     * @param inner The inner function for the chain rule
     * @return The derivative of the composite function
     */
    Differential chain_rule(const Differential &inner) const;

    /**
     * @brief Computes the nth derivative of the current Differential object
     * @param n The order of the derivative to compute
     * @return The nth derivative of the current Differential object
     */
    Differential nth_derivative(int n) const;

    /**
     * @brief Evaluates the polynomial for a given value of x
     * @param x The value at which to evaluate the polynomial
     * @return The result of evaluating the polynomial at x
     */
    double eval(double x) const;

    /**
     * @brief Calculate the limit of the polynomial at a specific point
     *
     * This method calculates the limit of the polynomial at a specific point by
     * evaluating the polynomial at that point The limit is undefined if the
     * polynomial has a term with a positive exponent at the highest degree
     *
     * @param x The point at which to calculate the limit
     * @return The limit of the polynomial at the specified point
     */
    double limit_at(double x) const;

    /**
     * @brief Calculate the limit of the polynomial as x approaches infinity
     *
     * This method calculates the limit of the polynomial as x approaches
     * infinity by examining the term with the highest exponent The limit is
     * infinity or negative infinity if the highest exponent is greater than
     * zero Otherwise, the limit is the constant term
     *
     * @return The limit of the polynomial as x approaches infinity
     */
    double limit_at_infinity() const;
};

} // namespace gpmp

#endif
