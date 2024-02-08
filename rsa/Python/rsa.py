from random import choice, randint

def random_num(digits):
    '''
        Get a random number with given no. of digits
    '''
    range_start = 10 ** (digits-1)
    range_end = 10 ** (digits) - 1 // 2

    return randint(range_start, range_end)

def is_prime(num):
    for i in range(2, num//2+1):
        if num % i == 0:
            return False
    return True

def random_prime(digits):
    num = random_num(digits)

    while not is_prime(num):
        num += 1

    return num

def compute_phi(p, q):
    return (p-1) * (q-1)

def gcd(a, b):
    if b == 0: return a
    return gcd(b, a % b)

def compute_e(p, q):
    '''
        conditions: 1 < e < phi(n) && e and phi(n) should be co prime
    '''
    phi = compute_phi(p, q)
    values = [] # storing all possible values of e

    for i in range(2, phi):
        if gcd(i, phi) == 1: values.append(i)

    return values

def compute_d(e, p, q):
    '''
        d = (1 + k*phi(n)) / e
        where d should be whole number (i.e. (1 + k*phi(n)) mod e should be 0)
    '''

    k = 2
    phi = compute_phi(p, q)
    while True:
        # avoiding unnecessary division and conversion to int
        # by checking remainder

        temp = (1 + k * phi)
        if temp % e == 0:
            return int(temp / e)
        k += 1
        
def test_pair(e, d, n):
    pt = randint(1, 1000)

    ct = pow(pt, e) % n
    dt = pow(ct, d) % n

    return dt == pt

def encrypt(plain_text):
    p = random_prime(2)
    q = random_prime(2)
    
    n = p*q
    e = choice(compute_e(p, q))
    d = compute_d(e, p, q)

    encrypted = []
    for char in plain_text:
        encrypted.append(chr((ord(char) ** e) % n))
    
    return "".join(encrypted)

print(encrypt("Hello"))