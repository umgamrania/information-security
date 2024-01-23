from math import floor

def decipher(cipher_text: str, depth: int):
    ct_len = len(cipher_text)
    tick_size = (2 * depth) - 2
    p = floor( ct_len / tick_size )
    r = ct_len % tick_size

    print(f"tick size = {tick_size}")
    print(f"p = {p}")
    print(f"r = {r}")

    matrix = [[] for _ in range(depth)] # preparing empty matrix
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
    else:
        i = 0
        while i < r:
            element_count[i] += 1
            i += 1

    print(element_count)

decipher("rjiauadajgrnaktaiot", 5)