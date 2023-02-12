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

/*
 * definitions for derivative operations operations
 */

#ifndef CIPHER_H
#define CIPHER_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

namespace mtpk {

// monoalphabetic substitution cipher class
class Cipher {
    public:
    /* compute the caesar cipher of a given string with a shift key */
    std::string caesar(std::string plaintext, int64_t key);
    /* encode and prepare the given string for the cipher */
    std::string keyword_encode(std::string key);
    /* compute the keyword cipher of a given string */
    std::string keyword(std::string plaintext, std::string encoded_text);
};

} // namespace mtpk

#endif
