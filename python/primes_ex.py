#!/usr/bin/python3.10
from RM_pkg import Primality

print("Using the Number Theory module in Python\n")

p = Primality()

prime_0 = p.is_prime(2999)
prime_1 = p.carmichael_num(561)
print(prime_0)
print(prime_1)

mod_0 = p.mod_pow(3, 2, 2)
mod_1 = p.mod_pow(5, 2, 7)
print(mod_0)
print(mod_1)

