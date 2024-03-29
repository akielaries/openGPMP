#!/usr/bin/python3
from pygpmp import arithmetic as ar


def main():
    b = ar.Basics()

    r1 = b.op_gcd(1703210, 20320)
    r2 = b.op_gcd(2198466, 96096)
    r3 = b.greatest_power(232, 96)
    r4 = b.greatest_power(10, 3)

    print(r1)
    print(r2)
    print(r3)
    print(r4)


if __name__ == "__main__":
    main()
