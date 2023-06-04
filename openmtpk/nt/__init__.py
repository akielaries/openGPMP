"""
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

openGPMP Number Theory Module
=============================
The Number Theory Module encapsulates methods related to prime numbers as
well as cryptography/encryption algorithms.

FEATURES :
    CLASS : Primality
        - Features methods related to prime numbers
    METHODS :
        is_prime
        miller_rabin
        jacobian_number
        solovoy_strassen
        mod_pow
        carmichael_num
        sieve_of_eratosthenes
        pollard_rho
        ETF

    CLASS : RC4
        - Contains methods related to the Rivest-Cipher encryption algo
    METHODS :
        byte_swap
        trad_swap
        XOR_swap
        KSA
        PRGA
        store_hash
        compute

    CLASS : Cipher
        - Contains methods related to Caesar Cipher and a Keyword Swap Cipher

    USAGE :
        >> import pygpmp
        >> prime_num = pygpmp.nt.primality.is_prime(2999)
        OR
        >> from pygpmp import nt
"""

from pygpmp.nt.nt import (
    PrimalityTest,
    PrimalityGen,
    Factorization,
    Logarithms,
    RC4,
    Cipher,
)

__all__: list[str]
__path__: list[str]
