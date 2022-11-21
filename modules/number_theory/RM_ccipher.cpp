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
#include "../../include/RM_ccipher.hpp"


std::string CIPHER::C_cipher(std::string plaintext, int key) {
    std::string hashtext = "";

    int i = 0;
    for (i; i < plaintext.length(); i++) {
        // inject transformation
        if (isupper(plaintext[i])) {
            // upper case
            hashtext += char(int(plaintext[i] + key - 65) % 26 + 65);
        }
        else {
            // lower case
            hashtext += char(int(plaintext[i] + key - 97) % 26 + 97);
        }
    }

    return hashtext;
} 

std::string CIPHER::KC_encode(std::string key) {
    std::string encoded = "";
    // This array represents the 26 letters of alphabets
    bool arr[26] = {0};
 
    // This loop inserts the keyword at the start of the encoded string
    for (int i=0; i<key.size(); i++) {
        if(key[i] >= 'A' && key[i] <= 'Z') {
            /*
             * To check whether the character is inserted earlier 
             * in the encoded string or not
             */
            if (arr[key[i]-65] == 0) {
                encoded += key[i];
                arr[key[i]-65] = 1;
            }
        }
        else if (key[i] >= 'a' && key[i] <= 'z') {
            if (arr[key[i]-97] == 0) {
                encoded += key[i] - 32;
                arr[key[i]-97] = 1;
            }
        }
    }
 
    // This loop inserts the remaining characters in the encoded string.
    for (int i=0; i<26; i++) {
        if(arr[i] == 0) {
            arr[i]=1;
            encoded += char(i + 65);
        }
    }
    return encoded;
}

std::string CIPHER::KC_cipher(std::string plaintext, std::string encoded_text) {
    std::string cipher = "";

    /*
     * This loop ciphered the message. Spaces, special characters 
     * and numbers remain same.
     */
    int i = 0;
    for (i; i < plaintext.size(); i++) {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            int pos = plaintext[i] - 97;
            cipher += encoded_text[pos];
        }

        else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            int pos = plaintext[i] - 65;
            cipher += encoded_text[pos];
        }
        
        else {
            cipher += plaintext[i];
        }
    }
    return cipher;
}

