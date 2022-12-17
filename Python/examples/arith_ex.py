#!/usr/bin/python3.10
from openMTPK import Basics

b = Basics()

r1 = b.rm_gcd(1703210, 20320)
r2 = b.rm_gcd(2198466, 96096)
r3 = b.greatest_power(232, 96)
r4 = b.greatest_power(10, 3)

print(r1)
print(r2)
print(r3)
print(r4)

