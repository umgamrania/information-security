import numpy as np

def cipher(plain_text, key, n):
    # padding plain text
    rem = len(plain_text) % n
    if rem > 0:
        plain_text += "x" * (n - rem)

    # plain text needs to be processed in ranges
    range_start = 0

    cipher_text = []

    for i in range(int(len(plain_text) / n)):
        chunk = plain_text[range_start : range_start+n]

        for row in key:
            total = 0
            for i, element in enumerate(row):
                char_index = (ord(chunk[i]) & 31) - 1
                total += element * char_index
            cipher_text.append(chr((total % 26) + 65))

        range_start += n

    return "".join(cipher_text)

n = int(input("Enter n: "))
key = [int(n) for n in input("Enter values for n x n matrix (space seperated): ").split(' ')]

key_np = np.array(key)
key_split = np.array_split(key_np, n)
key = [list(row) for row in key_split]

plain_text = input("Enter plain text: ")

print(f"cipher text: {cipher(plain_text, key, n)}")