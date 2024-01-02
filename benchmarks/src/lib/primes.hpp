#ifndef PRIMES_HPP
#define PRIMES_HPP
#include <cstdint>

/**
 * @brief Utility modulo multiply function finding (a * b) % m
 *
 * @param a first operand of the multiplication
 * @param b second operand of the multiplication
 * @param m modulus used to limit the result
 *
 * @return result of (a * b) % m
 */
uint32_t mod_mul(uint32_t a, uint32_t b, uint32_t m);

/**
 * @brief Utility modulo power function finding (a ^ b) % m
 *
 * @param a base for exponentiation
 * @param b exponent
 * @param m modulus used to limit the result
 *
 * @return result of (a^b) % m
 */
uint32_t mod_pow(uint32_t a, uint32_t b, uint32_t m);

/**
 * @brief witness utility function for miller_rabin checks if a given witness
 * 'a' indicates that 'n' is composite
 *
 * @param n number being tested for primality
 * @param d value 'd' computed from 'n' during the primality test
 * @param a witness value being tested
 * @param s number of times 'd' can be divided by 2 (s = log2(d))
 *
 * @return true/false (bool)
 */
bool witness(uint32_t n, uint32_t d, uint32_t a, uint32_t s);

/**
 * @brief Modified primes algorithm
 *
 * @param n target number (uint64_t)
 * @param iters iterations determine accuracy (uint64_t)
 *
 * return true/false (bool)
 */
bool miller_rabin(uint32_t n, uint32_t iters);

#endif
