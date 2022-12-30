#!/usr/bin/python3.10
from openMTPK import Cipher


    def main():
    print("Using the Number Theory module in Python")
    print("Methods of the Cipher class:\n\
        - C_cipher(plaintext, key)\n\
            : takes in plain text and key for shifting text\n\
        \n\
        - KC_encode(key)\n\
            : pass in key to encode for corresponding algorithm\n\
        - KC_cipher(plaintext, encoded_text)\n\
            : recieves encoded key text, plaintext, returning cipher\n")

    c = Cipher()
    ciph = c.C_cipher('Plaintext', 5)
    print(ciph)

    ciph_1 = c.C_cipher('ATTACKATONCE', 4)
    print(ciph_1)

    text = "Password"
    shift = "Computer"
    encoded_text = c.KC_encode(shift);
    hashtext = c.KC_cipher(text, encoded_text);
    print(hashtext)


if __name__ == '__main__':
    main()

