/**
 * @file
 *
 * @brief openMTPK NUMBER THEORY MODULE
 *
 * @details This file serves as the core header for the Number Theory
 * module. This header includes the following :
 *  - Primes
 *  - Cryptography/Encryption
 *      - Rivest-Cipher 4 (RC4)
 *      - Caesar Cipher
 *      - Keyword Stream Cipher
 */
#ifndef NT_HPP
#define NT_HPP


/**
 * @brief \b Primes
 * @details includes :
 * @note
 *
 * @todo
 */
#define PRIMES
#include "number_theory/primes.hpp"

/**
 * @brief \b Cryptographic \b Algorithms
 * @details includes :
 * @note
 *
 * @todo
 */
#define CRYPTOGRAPHY
#include "number_theory/cipher.hpp"
#include "number_theory/rc4.hpp"

#endif

