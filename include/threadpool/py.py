import random

def mod_pow(base, exp, mod):
    result = 1
    base %= mod
    while exp > 0:
        if exp % 2 == 1:
            result = (result * base) % mod
        exp //= 2
        base = (base * base) % mod
    return result

def miller_rabin(n, iters):
    if n < 2:
        return False
    if n == 2 or n == 3:
        return True
    if n % 2 == 0:
        return False
    
    d = n - 1
    while d % 2 == 0:
        d //= 2
    
    for i in range(iters):
        a = random.randint(2, n - 2)
        x = mod_pow(a, d, n)
        if x == 1 or x == n - 1:
            continue
        for j in range(len(str(n)) - 1):
            x = mod_pow(x, 2, n)
            if x == n - 1:
                break
        else:
            return False
    return True

n = 9223372036854775783
iters = 100

if miller_rabin(n, iters):
    print(n, "is probably prime")
else:
    print(n, "is composite")

