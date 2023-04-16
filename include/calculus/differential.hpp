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

/**
 * @file
 *
 * Definitions for derivative operations
 */

#ifndef DERIV_HPP
#define DERIV_HPP
#include <string>

namespace mtpk {

/**
 * Calculus Class with methods pertaining to basic operations.
 */
class Differential {
  public:
    /**
     * @brief Find the coeffecients and exponents of a polynomial
     *
     * @param[in] p_term : Coeffecients of the polynomial (string)
     * @param[in] val : 'x' term to find from given polynomial
     * (long long int)
     *
     * @return result : formatted coeffecients + exponents
     */
    int64_t derivative_term(std::string p_term, int64_t val);

    // Finds the first derivative of a function
    // deriv_one()

    // Finds the second derivative of a function
    // deriv_two()

    // Finds the third derivative of a function
    // deriv_thr()

    /**
     * @brief Find the derivative of a function with x = val
     *
     * @param[in] poly : polynomial (string)
     * @param[in] val : value to solve for (int)
     *
     * @return result : result of the solved x
     */
    int64_t deriv_at(std::string &poly, int64_t val);

    /**
     * @brief Calculate the derivative of a function, not solving for
     * x
     *
     * @param[in] poly : polynomial (string)
     *
     * @returns result : derived function (string)
     */
    std::string deriv_str(std::string &poly);
};

} // namespace mtpk

#endif
