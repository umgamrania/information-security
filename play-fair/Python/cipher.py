from sys import argv

def create_matrix(key: str):
    # Creating a string to store the characters for the matrix
    buf = key.upper() + "ABCDEFGHIKLMNOPQRSTUVWXYZ"
    matrix_str = ""
    for char in buf : 
        if not char in matrix_str:
            matrix_str += char
    matrix_str = matrix_str.replace('j', '')

    # Splitting string into 5x5 matrix
    global matrix
    matrix = []
    range_start = 0
    for _ in range(5):
        matrix.append(matrix_str[range_start : range_start+5])
        range_start += 5
    
    return matrix

def create_pairs(plain_text: str):
    pairs = []

    i = 0
    while i < len(plain_text):
        a = plain_text[i]
        
        if i == len(plain_text) - 1:
            # Last character, string has odd chars
            pairs.append((a, 'x'))
            break

        else:
            b = plain_text[i+1]

            if a == b:
                pairs.append((a, 'x'))
                i += 1
            else:
                pairs.append((a, b))
                i += 2
    
    return pairs

def cipher(plain_text: str, key: str) -> str:
    matrix = create_matrix(key)
    pairs = create_pairs(plain_text)
    cipher_text = []

    for pair in pairs:
        a, b = pair
        row_a, row_b, col_a, col_b = 0, 0, 0, 0

        for i, row in enumerate(matrix):
            if a in row: 
                row_a = i
                col_a = row.index(a)
            if b in row: 
                row_b = i
                col_b = row.index(b)
            
        if row_a == row_b:
            cipher_text.append(matrix[row_a][(col_a + 1) % 5])
            cipher_text.append(matrix[row_b][(col_b + 1) % 5])
        elif col_a == col_b:
            cipher_text.append(matrix[(row_a + 1) % 5][col_a])
            cipher_text.append(matrix[(row_b + 1) % 5][col_b])
        else:
            cipher_text.append(matrix[row_a][col_b])
            cipher_text.append(matrix[row_b][col_a])

    return "".join(cipher_text)

if __name__ == "__main__":
    if len(argv) < 3:
        print("USAGE: <plain-text> <key>")
        exit()
    
    cipher_text = cipher(plain_text=argv[1].upper(), key=argv[2].upper())

    print(cipher_text)

    if 'i' in cipher_text:
        print(cipher_text.replace('i', 'j'))