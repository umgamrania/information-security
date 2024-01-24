import sys

def cipher(plain_text: str, key: int):
    '''
        Masking ascii value to get index
        31 = 00011111
        a  = 01100001 & 31 => 01
        A  = 01000001 & 31 => 01
        b  = 01100010 & 31 => 02

        The MSB shows whether the character is capital or small
    '''

    cipher_text = ""
    for char in plain_text:
        # Getting the MSB as boolean value
        small = (ord(char) & 32) == 32
        index = ord(char) & 31

        index = (index + key) % 26

        # 96 = 01100000, 96 + 1 => 01100001 => 'a'
        # 64 = 01000000, 64 + 1 => 01000001 => 'A'
        cipher_text += f"{chr(index + (96 if small else 64))}"

    return cipher_text

if len(sys.argv) < 3:
    print("USAGE: <plain-text> <key>")
    exit()

print(f"Cipher text: {cipher(sys.argv[1], int(sys.argv[2]))}")