from math import floor
import sys

def decipher(cipher_text: str, depth: int):
    ct_len = len(cipher_text)
    tick_size = (2 * depth) - 2
    p = floor( ct_len / tick_size )
    r = ct_len % tick_size
    
    element_count = [0 for _ in range(depth)] # stores no of elements in each row
    
    element_count[0] = p
    element_count[-1] = p

    if r > depth:
        element_count[0] += 1
        element_count[-1] += 1

    # processing middle rows
    i = 1
    while i < len(element_count) - 1:
        element_count[i] = p * 2
        i += 1

    if r > depth:
        i = depth - 2
        while i > r - depth:
            element_count[i] += 1
            i -= 1
    i = 0
    while i < min(r, depth):
        element_count[i] += 1
        i += 1

    indices = [0]
    total = 0
    for i in element_count[:-1]:
        indices.append(total + i)
        total += i

    i = 0
    pt = []
    direction = 1

    while len(pt) < len(cipher_text):
        index = indices[i]
        pt.append(cipher_text[index])
        indices[i] += 1

        if i == 0: direction = 1
        elif i == len(indices) - 1: direction = -1

        i += direction
    
    return "".join(pt)

if __name__ == "__main__":
    print(decipher(sys.argv[1], int(sys.argv[2])))