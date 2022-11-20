/*
 * This file shows the implementation of the Rivest Cipher 4 (RC4) 
 * encryption algorithm created by Ron Rivest using either a traditional
 * swap method or with the XOR operator
 */
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include "../../include/RM_rc4.hpp"


void RC4::trad_swap(unsigned char *a, unsigned char *b) {
    int swapped = *a;
    *a = *b;
    *b = swapped;
}

void RC4::XOR_swap(unsigned char *a, unsigned char *b) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

void RC4::KSA(char *key, unsigned char *S) {
    uint32_t len = strlen(key);
    int j = 0;

    for (int i = 0; i < BYTE_LIMIT; i++) {
        S[i] = i;
    }

    for (int i = 0; i < BYTE_LIMIT; i++) {
        j = (j + S[i] + key[i % len]) & BITS;
        XOR_swap(&S[i], &S[j]);
    }
}

void RC4::PRGA(unsigned char *S, char *plaintext, 
                unsigned char *ciphertext) {
    int i = 0;
    int j = 0;

    for (size_t n = 0, len = strlen(plaintext); n < len; n++) {
        i = (i + 1) & BITS;
        j = (j + S[i]) & BITS;

        XOR_swap(&S[i], &S[j]);
        uint32_t rnd = S[(S[i] + S[j]) & BITS];

        ciphertext[n] = rnd ^ plaintext[n];
    }
}

void RC4::compute(char *key, char *plaintext, unsigned char *ciphertext) {

    unsigned char S[BYTE_LIMIT];
    KSA(key, S);
    PRGA(S, plaintext, ciphertext);
}

