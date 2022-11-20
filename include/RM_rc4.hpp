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
        void swap_values();
        /* swaps two values using the XOR operator */
        void XOR_swap();
        /* the RC4 encryption algorithm */
        void RC4();
        void PRGA();
        void KSA();

};

#endif

