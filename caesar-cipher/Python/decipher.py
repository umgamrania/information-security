import sys

def decipher(cipher_text: str, key: int):
    plain_text = ""
    for char in cipher_text:
        # Getting the MSB as boolean value
        small = (ord(char) & 32) == 32
        index = ord(char) & 31

        original = index - key

        if original < 0: original = 26 - original

        # 96 = 01100000, 96 + 1 => 01100001 => 'a'
        # 64 = 01000000, 64 + 1 => 01000001 => 'A'
        plain_text += f"{chr(original + (96 if small else 64))}"

    return plain_text

if len(sys.argv) < 3:
    print("USAGE: <cipher-text> <key>")
    exit()

print(f"Cipher text: {decipher(sys.argv[1], int(sys.argv[2]))}")