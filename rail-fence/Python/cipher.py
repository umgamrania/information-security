def cipher(text: str, depth: int):
    matrix = [[] for _ in range(depth)]

    index = 0
    direction = 1

    for char in text:
        matrix[index].append(char)

        if index == 0: direction = 1
        elif index == depth - 1: direction = -1

        index += direction

    return "".join( # joining array of strings into one string
        ["".join(row_str) for row_str in matrix] # joining rows into string
    )

print(cipher("rajkotgujaratindiaa", 5))