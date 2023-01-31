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
class Calculus {
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
    std::string deriv(std::string &poly);
};

} // namespace mtpk

#endif
