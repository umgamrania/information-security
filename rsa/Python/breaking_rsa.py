import math

def is_square(n):
    sq = math.sqrt(n)
    return int(sq) == sq

def decode(n):
    a = math.ceil(math.sqrt(n))
    b = None

    while True:
        b2 = (a ** 2) - n
        if is_square(b2):
            b = math.sqrt(b2)
            break
        a += 1
    
    p = a + b
    q = a - b

    return p, q

print(decode(
    int(input("Enter n: "))
))