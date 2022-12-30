Usage
=====
This is a list highlighting all methods that can be used within openMTPK based off the 
modules of the package. </br>

## Arithmetic
**Class:** Arith </br>
**Methods:** </br>
* `inline auto add(T t, Ts... ts)`
* `inline auto sub(X x, Xy... xy)`
* `inline auto mult(W w, Wv... wv)`
> **Note:** 
> These are variadic template methods taking any numeric datatype as paramaters

## Calculus
**Class:**  </br>
**Methods:** </br>

## Linear Algebra
### Vectors
**Class:**  </br>
**Methods:** </br>

### Matrix
**Class:**  </br>
**Methods:** </br>

## Machine Learning
### Regression
**Class:**  </br>
**Methods:** </br>

### Cross Validation
**Class:**  </br>
**Methods:** </br>

### Neural Networks
#### Naive Network
**Class:**  </br>
**Methods:** </br>

#### Bayes Network
**Class:**  </br>
**Methods:** </br>

#### Kohonen Network (Self-Organizing Map)
**Class:**  </br>
**Methods:** </br>

#### Multi-Layer Perceptron
**Class:** MLP </br>
**Methods:** </br>


## Number Theory
### Primes
**Class:**  </br>
**Methods:** </br>

### Cryptography/Encryption
#### Stream Ciphers
**Class:** Cipher </br>
**Methods:**
* `std::string C_cipher(std::string plaintext, int key)`
* `std::string KC_encode(std::string key);`
* `std::string KC_cipher(std::string plaintext, std::string encoded_text);`

#### Rivest Ciphers
**Class:** RC2 </br>
**Methods:** </br>

**Class:** RC4 </br>
**Methods:** </br>
* `void byte_swap(uint8_t *a, uint8_t *b)`
* `void trad_swap(unsigned char *a, unsigned char *b)`
* `void XOR_swap(unsigned char *a, unsigned char *b)`
* `void KSA(char *key, unsigned char *S, int swap_type)`
* `void PRGA(unsigned char *S, char *plaintext, unsigned char *ciphertext, int swap_type)`
* `std::string store_hash(char *plaintext, unsigned char *hashtext, int swap_type)`
* `unsigned char* compute(char *key, char *plaintext, unsigned char *hashtext, int swap_type)`

**Class:** RC5 </br>
**Methods:** </br>

**Class:** RC6 </br>
**Methods:** </br>


## Topology


# Examples
Example C++ driver file for running Caesar Cipher & Mono-Alphabetic Substitution
Keyword cipher:
``` cpp
#include <iostream>
#include <string>
#include <openMTPK/cipher.hpp>

int main() {
    // declare CIPHER class obj
    Cipher cc;
    
    /* CAESAR CIPHER */
    std::string text0 = "Plaintext";
    int shift_key_0 = 5;
    std::string hashtext_0 = cc.C_cipher(text0, shift_key_0);
    std::cout << "Hashtext0 = " << hashtext_0 << std::endl;
    
    /* TESTING MONOALPHABETIC SUBSTITUION KEYWORD CIPHER */
    std::string shift_key_2 = "Computer";
    std::string text2 = "Password";
    // encode the plaintext
    std::string encoded_text = cc.KC_encode(shift_key_2);
    // call the cipher function
    std::string hashtext_2 = cc.KC_cipher(text2 , encoded_text);
    
    std::cout << "Hashtext2 = " << hashtext_2 << std::endl;

    return 0;
}
```
A Python example showing the same functionalities.
```python
#!/usr/bin/python3.10
from openMTPK import Cipher

c = Cipher()
cipertext_0 = c.C_cipher('Plaintext', 5)
print(ciphertext_0)

ciphertext_1 = c.C_cipher('ATTACKATONCE', 4)
print(ciphertext_1)

text = "Password"
shift = "Computer"
encoded_text = c.KC_encode(shift);
hashtext = c.KC_cipher(text, encoded_text);
print(hashtext)
```
