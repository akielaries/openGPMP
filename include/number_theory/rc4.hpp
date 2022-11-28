/*
 * definitions for derivative operations operations 
 */

#ifndef RMRC4_H
#define RMRC4_H
#include <string>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// (2^8)-1, bitmask for a byte
#define BITS 255
#define BYTE_LIMIT 256

class RC4 {

    public:
        /* swaps two values using uint8_t type */
        void byte_swap(uint8_t *a, uint8_t *b);
        /* swaps two values in a traditional way using chars */
        void trad_swap(unsigned char *a, unsigned char *b);
        /* swaps two values using the XOR operator */
        void XOR_swap(unsigned char *a, unsigned char *b);
        /* Key Scheduling Algorithm */
        void KSA(char *key, 
                    unsigned char *S, 
                    int swap_type);
        /* Pseudo-Random Generation Algorithm */
        void PRGA(unsigned char *S, 
                    char *plaintext,
                    unsigned char *ciphertext,
                    int swap_type);
        /* function to display our hashed text */
        std::string store_hash(char *plaintext, 
                    unsigned char *hashtext, 
                    int swap_type);
        /* compute our hash using the the RC4 encryption algorithm */
        unsigned char* compute(char *key, 
                    char *plaintext, 
                    unsigned char *ciphertext, 
                    int swap_type);

};

#endif

