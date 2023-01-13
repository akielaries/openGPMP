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

} // namespace

#endif

