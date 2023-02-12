/* testing basic encryption algorithms with stream ciphers
 * specifically caesar cipher
 */
#include "../../include/number_theory/cipher.hpp"
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

int main() {
    /*
     * Provide some details on how to use this algorithm
     */
    std::cout << "<--------------------------------------------------"
                 "---->\n\n";

    // declare CIPHER class obj
    Cipher cc;

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
    std::string hashtext_2 = cc.KC_cipher(text2, encoded_text);
    std::cout << "Hashtext2 = " << hashtext_2 << std::endl;

    std::string text_4 = "P455W0RD";
    std::string key_shift_4 = "IN1T_d";

    std::string encoded_text_4 = cc.KC_encode(key_shift_4);
    std::string hashtext_4 = cc.KC_cipher(text_4, encoded_text_4);
    std::cout << "Hashtext4 = " << hashtext_4 << std::endl;

    return 0;
}
