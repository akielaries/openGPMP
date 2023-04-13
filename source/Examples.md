# Examples
See the [openMTPK/samples](https://github.com/akielaries/openMTPK/tree/main/samples) folder
for many more examples on how to use openMTPK.

Example C++ driver file for running Caesar Cipher & Mono-Alphabetic Substitution
Keyword cipher:
```cpp
/**
 * Showing the Cipher Class functionalities
 */
#include <iostream>
#include <string>
// include the openMTPK Number Theory header
#include <openMTPK/nt.hpp>


int main() {
    // declare CIPHER class obj (this lies within the mtpk namespace)
    mtpk::Cipher cc;
    
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
#!/usr/bin/python3
from openmtpk import nt


def main():
    c = nt.Cipher()
    ciph = c.caesar("Plaintext", 5)
    print(ciph)

    ciph_1 = c.caesar("ATTACKATONCE", 4)
    print(ciph_1)

    text = "Password"
    shift = "Computer"
    encoded_text = c.keyword_encode(shift)
    hashtext = c.keyword(text, encoded_text)
    print(hashtext)


if __name__ == "__main__":
    main()
```

