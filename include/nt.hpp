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

/**
 * @file
 *
 * @brief User API for OpenGPMP NUMBER THEORY MODULE
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

#include "nt/prime_gen.hpp"
#include "nt/prime_test.hpp"
#include "nt/euclidean_div.hpp"
#include "nt/factorization.hpp"
#include "nt/gcds.hpp"
#include "nt/logarithms.hpp"
#include "nt/squares.hpp"
#include "nt/cipher.hpp"
#include "nt/rc4.hpp"
#include "nt/random.hpp"

#endif
