/**
 * @file
 * @author Akiel Aries
 *
 * Definitions for basic arithmetic operations
 */

#ifndef ARITH_BASE_HPP
#define ARITH_BASE_HPP
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <vector>

/**
 * @namespace mtpk
 *
 * @brief The core openMTPK namespace
 *
 * @details This namespace wraps all classes and methods used within
 * the library
 */
namespace mtpk {

/**
 * @class Arith
 *
 * @brief Arithmetic Template Class. Each method is variadic taking
 * 'n' params.
 */
class Arith {
  public:
    /**
     * @brief Addition method
     *
     * @tparam 'n' addends
     *
     * @return sum
     */
    template <typename T> inline T add(T t) {
        return t;
    }

    template <typename T, typename... Ts> inline auto add(T t, Ts... ts) {
        return t + add(ts...);
    }

    /**
     * @brief Subtraction method
     *
     * @tparam minuend
     * @tparam 'n' subtrahends
     *
     * @return difference
     */
    template <typename X> inline X sub(X x) {
        return x;
    }
    template <typename X, typename... Xy> inline auto sub(X x, Xy... xy) {
        return x - sub(xy...);
    }

    /**
     * @brief Multiplication method
     *
     * @tparam 'n' factors
     *
     * @return product
     */
    template <typename W> inline W mult(W w) {
        return w;
    }
    template <typename W, typename... Wv> inline auto mult(W w, Wv... wv) {
        return w * mult(wv...);
    }

    /**
     * @brief Exponentiation method
     *
     * @tparam base
     * @tparam 'n' powers
     *
     * @return product
     */
    template <typename Z> inline Z exp(Z z) {
        return z;
    }
    template <typename Z, typename... Zy> inline auto exp(Z z, Zy... zy) {
        return z *= exp(zy...);
    }
};

} // namespace mtpk

#endif
