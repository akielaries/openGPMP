/*
 * definitions for derivative operations operations 
 */

#ifndef RC5_H
#define RC5_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// (2^8)-1, bitmask for a byte
#define BITS 255
#define BYTE_LIMIT 256

class RC5 {

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
        /* functoin to display our hashed text */
        void display_hash(unsigned char *ciphertext);
        /* compute our hash using the the RC4 encryption algorithm */
        void compute(char *key, 
                    char *plaintext, 
                    unsigned char *ciphertext, 
                    int swap_type);

        uint32_t shift_left(uint32_t v, uint32_t n);
        uint32_t shift_right(uint32_t v, uint32_t n);
        uint32_t rotate_left(uint32_t v, uint32_t n);
        uint32_t rotate_right(uint32_t v, uint32_t n);
        void encrypt(uint32_t S[26], uint32_t inout[4]);
        void decrypt(uint32_t S[26], uint32_t inout[4]);
        void expand(uint32_t L[4], uint32_t S[26]);
        int test(uint32_t S[26], uint32_t messg[4]);
};

#endif

