/* RM-pkg
 * Testing the RC4 stream cipher encryption algorithm on fields
 * of test
 */
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "../../include/RM_rc4.hpp"


int main() {
    /*
     * Provide some details on how to use this algorithm
     */
    std::cout << "DERIVATIVE EXAMPLE\n\n";

    // declare RC4 class obj
    RC4 rc;

    /*
     * declare some key values and strings to hash
     * these first 3 plaintext strings are verified from the RC4 wiki
     */
    // expected hash = BBF316E8D940AF0AD3
    char* key0    = (char*)"Key";
    char* text0   = (char*)"Plaintext";
    // expected hash = 1021BF0420
    std::string key1    = "Wiki";
    std::string text1   = "pedia";
    // expected hash = 45A01F645FC35B383552544B9BF5
    std::string key2    = "Secret";
    std::string text2   = "Attack at dawn";

    // declare a ciphertext pointer and allocate memory
    unsigned char *ciphertext = (unsigned char *)malloc(sizeof(int) * strlen(text0));
  
    if (ciphertext == NULL) {
        fprintf(stderr, "[-] Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    /*
     * the main arguments are <key> & <plaintext> + allocated memory of
     * ciphertext
     */
    rc.compute(key0, text0, ciphertext);
    
    // printing the computed hashes 
    for (size_t i = 0, len = strlen(text0); i < len; i++) {
        printf("\\x%02hhx ", ciphertext[i]);
    }

    free(ciphertext);
    return EXIT_SUCCESS;


}

