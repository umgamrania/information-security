from math import floor

def decipher(cipher_text: str, depth: int):
    ct_len = len(cipher_text)
    tick_size = 2 * depth - 2
    p = floor( ct_len / tick_size )
    r = ct_len % tick_size

    print(f"tick size = {tick_size}")
    print(f"p = {p}")
    print(f"r = {r}")

    matrix = [[] for _ in range(depth)] # preparing empty matrix
    element_count = [0 for _ in range(depth)] # stores no of elements in each row
    
    print(element_count)

    element_count[0] = p + 1 if r > depth else 0
    element_count[-1] = p + 1 if r > depth else 0

    i = depth - 2
    while i > r - depth:
        element_count[i] += 1
        i -= 1

    print(element_count)

decipher("rojtaktuaajgr", 3)