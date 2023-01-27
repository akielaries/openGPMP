#include "../../include/number_theory/rc5.hpp"
#include <math.h>
#include <stdint.h>
#include <string.h>

uint32_t shift_left(uint32_t v, uint32_t n) {
}

uint32_t shift_right(uint32_t v, uint32_t n) {
}

uint32_t rotate_left(uint32_t v, uint32_t n) {
}

uint32_t rotate_right(uint32_t v, uint32_t n) {
}

void encrypt(uint32_t S[26], uint32_t inout[4]) {
}

void decrypt(uint32_t S[26], uint32_t inout[4]) {
}

// expand key into S array using magic numbers derived from e and phi
void expand(uint32_t L[4], uint32_t S[26]) {
}

// decrypt of encrypt should be the same
int test(uint32_t S[26], uint32_t messg[4]) {
}
