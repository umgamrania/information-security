from random import choice

def gcd(a: int, b: int) -> int:
    if b == 0: return a
    return gcd(b, a % b)

def coprime(a: int, b: int) -> int:
    return (gcd(a, b) == 1)

def calc_phi(p: int, q: int) -> int:
    return (p-1) * (q-1)

def generate_e(p: int, q: int) -> int:
    n = p * q
    p = calc_phi(p, q)

    values = []
    for i in range(2, p):
        if coprime(i, p) and coprime(i, n): values.append(i)
    return choice(values)

def generate_d(e: int, p: int, q: int) -> int:
    k = 2
    phi = calc_phi(p, q)
    while True:
        d = (k * phi + 1) / e
        if d == int(d): return int(d)
        k += 1

p = 11
q = 7
n = p * q
e = generate_e(p, q)
d = generate_d(e, p, q)

pt = 16
et = pow(pt, e) % n
dt = pow(et, d) % n

print("e = ", e, " d = ", d)
print(pt, dt)