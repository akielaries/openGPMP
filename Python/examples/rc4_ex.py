#!/usr/bin/python3.10
from openMTPK import RC4


def main():
    print("Using the Number Theory module in Python")
    print("Methods of the RC4 class:\n\
        - byte_swap(a, b)\n\
        - trad_swap(a, b)\n\
        - XOR_swap(a, b)\n\
            : swap functions ^\n\
        \n\
        - KSA(key, S, swap_type)\n\
            : Key Swap Algorithm\n\
        - PRGA(S, plaintext, ciphertext, swap_type)\n\
            : Pseudo-Random Generation Algorithm\n\
        \n\
        - store_hash(plaintext, hashtext, swap_type)\n\
            : stores hash to a value\n\
        - compute(key, plaintext, hashtext, swap_type)\n\
            : driver for RC4 algorithm\n")

    r = RC4()


if __name__ == '__main__':
    main()
