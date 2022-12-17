#!/usr/bin/python3.10
from openMTPK import Primality

print("Using the Number Theory module in Python")
print("Methods of Primality class\n\
    - is_prime(n)\n\
    - miller_rabin(self, inters, min_val, max_val)\n\
        - primes within a range\n\
    - solovoy_strassen(p, iters)\n\
    - mod_pow(base, exponent, mod)\n\
    - carmichael_num(n)\n\
    - sieve_of_eratosthenes(n)\n\
        : prime up to a limit\n\
    - pollard_rho(n)\n\
    - ETF(n)\n\
        : Eulers Totient Function\n")

p = Primality()

prime_0 = p.is_prime(2999)
prime_1 = p.carmichael_num(561)
print(prime_0)
print(prime_1)

mod_0 = p.mod_pow(3, 2, 2)
mod_1 = p.mod_pow(5, 2, 7)
print(mod_0)
print(mod_1)

p.miller_rabin(4, 4, 200)

ss_0 = p.solovoy_strassen(15, 50)
ss_1 = p.solovoy_strassen(1049, 50)
print(ss_0)
print(ss_1)

