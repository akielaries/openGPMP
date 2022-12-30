# Examples
Example C++ driver file for running Caesar Cipher & Mono-Alphabetic Substitution
Keyword cipher:
```cpp
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

