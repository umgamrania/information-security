import sys

def cipher(plain_text: str, key: int):
    ct = []

    for char in plain_text:
        ct.append(chr(ord(char) + key))

    return "".join(ct)

if len(sys.argv) < 3:
    print("USAGE: <plain-text> <key>")
    exit()

print(f"Cipher text: {cipher(sys.argv[1], int(sys.argv[2]))}")