/*
 * definitions for derivative operations operations 
 */

#ifndef RMRC4_H
#define RMRC4_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// (2^8)-1, bitmask for a byte
#define BITS 255
#define BYTE_LIMIT 256

class RC4 {

    public:
        /* swaps two values in a traditional way using chars */
        void trad_swap(unsigned char *a, unsigned char *b);
        /* swaps two values using the XOR operator */
        void XOR_swap(unsigned char *a, unsigned char *b);
        /* Key Scheduling Algorithm */
        void KSA(char *key, 
                    unsigned char *S, 
                    bool swap_type);
        /* Pseudo-Random Generation Algorithm */
        void PRGA(unsigned char *S, 
                    char *plaintext,
                    unsigned char *ciphertext,
                    bool swap_type);
        /* functoin to display our hashed text */
        void display_hash(unsigned char *ciphertext);
        /* compute our hash using the the RC4 encryption algorithm */
        void compute(char *key, 
                    char *plaintext, 
                    unsigned char *ciphertext, 
                    bool swap_type);

};

#endif

