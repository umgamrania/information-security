def decipher(cipher_text: str, depth: int):
    delta = (2 * (depth-1)) - 1
    i = 0

    while delta + i < len(cipher_text):
        