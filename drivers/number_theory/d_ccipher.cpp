/* RM-pkg
 * testing basic encryption algorithms with stream ciphers specifically 
 * caesar cipher
 */
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "../../include/RM_ccipher.hpp"


int main() {
    /*
     * Provide some details on how to use this algorithm
     */
    std::cout << "<------------------------------------------------------>\n\n";

    // declare CIPHER class obj
    CIPHER cc;

    /*
     * declare some key values and strings to hash
     */
    std::cout << "CAESAR CIPHER EXAMPLE\n\n";

    std::string text0 = "Plaintext";
    int shift_key_0 = 5;
    std::string hashtext_0 = cc.C_cipher(text0, shift_key_0);
    std::cout << "Hashtext0 = " << hashtext_0 << std::endl;
    
    std::string text1 = "ATTACKATONCE";
    int shift_key_1 = 4;
    std::string hashtext_1 = cc.C_cipher(text1, shift_key_1);
    std::cout << "Hashtext1 = " << hashtext_1 << std::endl; 

    /* TESTING MONOALPHABETIC SUBSTITUION KEYWORD CIPHER */
    std::cout << "\nMONOALPHABETIC SUBSTITUION KEYWORD CIPHER EXAMPLE\n\n";

    std::string shift_key_2 = "Computer";
    std::string text2 = "Password";
    // encode the plaintext
    std::string encoded_text = cc.KC_encode(shift_key_2);
    // call the cipher function
    std::string hashtext_2 = cc.KC_cipher(text2 , encoded_text);
    
    std::cout << "Hashtext2 = " << hashtext_2 << std::endl;

    return 0;

}

