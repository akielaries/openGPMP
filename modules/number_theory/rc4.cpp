/*
 * This file shows the implementation of the Rivest Cipher 4 (RC4) 
 * encryption algorithm created by Ron Rivest using either a traditional
 * swap method or with the XOR operator
 */
#include <cstdlib>
#include <stdlib.h>
#include <cmath>
#include <sstream>
#include <string>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <omp.h>
#include "../../include/number_theory/rc4.hpp"


void RC4::byte_swap(uint8_t *a, uint8_t *b) {
	uint8_t swapped = * a;
	swapped = *a;
	*a = *b;
	*b = swapped;
}

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

void RC4::KSA(char *key, 
                unsigned char *S,
                int swap_type) {

    uint32_t len = strlen(key);
    int j = 0;

    for (int i = 0; i < BYTE_LIMIT; i++) {
        S[i] = i;
    }

    for (int i = 0; i < BYTE_LIMIT; i++) {
        j = (j + S[i] + key[i % len]) & BITS;

        // choose swap algorithm based off swap_type
        if (swap_type == 0) {
            XOR_swap(&S[i], &S[j]);
        }
        else if (swap_type == 1) {
            trad_swap(&S[i], &S[j]);
        }
        else if (swap_type == 2) {
            byte_swap(&S[i], &S[j]);
        }
        else {
            std::cout << "[-] Error performing swap in KSA\n";
            exit(EXIT_FAILURE);
        }
    }
}

void RC4::PRGA(unsigned char *S, 
                char *plaintext, 
                unsigned char *ciphertext, 
                int swap_type) {
    
    int i = 0;
    int j = 0;

    for (size_t n = 0, len = strlen(plaintext); n < len; n++) {
        i = (i + 1) & BITS;
        j = (j + S[i]) & BITS;

        // choose swap algorithm based off swap_type
        if (swap_type == 0) {
            XOR_swap(&S[i], &S[j]);
        }
        else if (swap_type == 1) {
            trad_swap(&S[i], &S[j]);
        }
        else if (swap_type == 2) {
            byte_swap(&S[i], &S[j]);
        }
        else {
            std::cout << "[-] Error performing swap in PRGA\n";
            exit(EXIT_FAILURE);
        }

        uint32_t rnd = S[(S[i] + S[j]) & BITS];

        ciphertext[n] = rnd ^ plaintext[n];
    }
}

std::string RC4::store_hash(char *plaintext, 
                unsigned char *hashtext, 
                int swap_type) {

    // length of our plaintext
    int len = strlen((char*)plaintext);
    // for snprintf declare a buffer
    char buffer[len + 1];
    int size = sizeof(buffer);
    int result = 0;
    
    // initialize empty string
    std::string stored_text = "";
    
    // traverse the hashtext appending each block to a string
    for (size_t index = 0, len = strlen(plaintext); 
                            index < len; index++) {
        if (swap_type == 0) {
            snprintf(buffer, size, "|x%02hhx|", hashtext[index]);
        }
        // to format our hash to a string for future manipulation
        else {
            snprintf(buffer, size, "%02hhX", hashtext[index]);
        }
        // append the declared string
        stored_text += std::string(buffer);
    }
    return stored_text;
}

unsigned char* RC4::compute(char *key, 
                char *plaintext, 
                unsigned char *ciphertext, 
                int swap_type) {

    if (ciphertext == NULL) {
        std::cout << "[-] Error Allocating Memory\n";
        exit(EXIT_FAILURE);
    }

    unsigned char S[BYTE_LIMIT];
    KSA(key, S, swap_type);
    PRGA(S, plaintext, ciphertext, swap_type);
    
    return ciphertext;
}

