/**
 * @file
 * @author Akiel Aries
 *
 * @brief openMTPK ARITHMETIC MODULE
 *
 * @details This file serves as the core Arithmetic module housing the
 * basic operations and operations based on/using arithmetic.
 */
#ifndef ARITHMETIC_HPP
#define ARITHMETIC_HPP
#include <cstdint>

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
 * @brief \b Arithmetic \b Basics
 * @details Basics of Arithmetic
 */

/**
 * @class Arith
 *
 * @brief Arithmetic Template Class. Each method is variadic taking
 * 'n' params.
 */
template <typename T>
class Arith {
    public:

    T arr_add(T arr[], int64_t n) {
        T sum = 0;

        for (int64_t i = 0; i < n; i++) {
            sum += arr[i];
        }
        return sum;
    }

    T arr_sub(T arr[], int64_t n) {
        T diff = arr[0];

        for (int64_t i = 1; i < n; i++) {
            diff -= arr[i];
        }
        return diff;
    }

    T arr_mlt(T arr[], int64_t n) {
        T prod = arr[0];

        for (int64_t i = 0; i < n; i++) {
            prod *= arr[i];
        }
        return prod;
    }
};

/**
 * @brief \b Arithmetic \b Operations
 * @details Encompasses Arithmetic related operations
 * @class Basics
 */
class Basics {
    public:
    /**
     * @brief Find greatest power of 2 itegers
     *
     * @param[in] n : integer 1
     * @param[in] p : integer 2
     *
     * @return result : (int)
     */
    int64_t greatest_power(int64_t n, int64_t p);

    /**
     * @brief Find Greatest Common Divisor of 2 integers
     *
     * @param[in] x : integer 1
     * @param[in] y : integer 2
     *
     * @return result : (int)
     */
    int64_t op_gcd(int64_t x, int64_t y);
};

} // namespace mtpk

//  public:
/**
 * @brief Addition method
 *
 * @tparam 'n' addends
 *
 * @return sum
 */
//    template <typename T> inline T add(T t) {
//        return t;
//    }

//    template <typename T, typename... Ts> inline auto add(T t, Ts... ts)
//    {
//        return t + add(ts...);
//    }

/**
 * @brief Subtraction method
 *
 * @tparam minuend
 * @tparam 'n' subtrahends
 *
 * @return difference
 */
//    template <typename X> inline X sub(X x) {
//        return x;
//    }
//    template <typename X, typename... Xy> inline auto sub(X x, Xy... xy)
//    {
//        return x - sub(xy...);
//    }

/**
 * @brief Multiplication method
 *
 * @tparam 'n' factors
 *
 * @return product
 */
//    template <typename W> inline W mult(W w) {
//        return w;
//    }
//    template <typename W, typename... Wv> inline auto mult(W w, Wv... wv)
//    {
//        return w * mult(wv...);
//    }

/**
 * @brief Exponentiation method
 *
 * @tparam base
 * @tparam 'n' powers
 *
 * @return product
 */
//    template <typename Z> inline Z exp(Z z) {
//        return z;
//    }
//    template <typename Z, typename... Zy> inline auto exp(Z z, Zy... zy)
//    {
//        return z *= exp(zy...);
//    }
//};

#endif
