matrix = []
with open("C:/Users/invik/Downloads/input.txt", 'r') as file:
    for line in file.readlines():
       line = [i for i in line if i != '\n']
       matrix.append(line)

gear_adjacents = set()
star_adjacents = {}
for i in range(len(matrix)):
    for j in range(len(matrix[0])):
        if matrix[i][j].isalnum() or matrix[i][j] == '.':
            continue
        
        star_coords = []

        for a, b in [(1, 0), (-1, 0), (0, 1), (0, -1), (-1, -1), (1, 1), (-1, 1), (1, -1)]:
            a += i
            b += j

            if a < 0 or b < 0 or a > len(matrix)-1 or b > len(matrix[0])-1:
                continue

            gear_adjacents.add((a, b))
            if matrix[i][j] == '*':
                star_coords.append((a, b))

        if matrix[i][j] == '*':
            star_adjacents[tuple(star_coords)] = []       

accum = 0
for i in range(len(matrix)):
    num_pos = set()
    number = ''
    for j in range(len(matrix[0])):
        if matrix[i][j].isdigit():
            number += matrix[i][j]
            num_pos.add((i, j))
        elif number:
            for k, v in star_adjacents.items():
                if not num_pos & set(k):
                    continue
                star_adjacents[k].append(int(number))

            if num_pos & gear_adjacents:
                accum += int(number)
            number = ''
            num_pos.clear()

    for k, v in star_adjacents.items():
        if not num_pos & set(k):
            continue
        star_adjacents[k].append(int(number))

    if num_pos & gear_adjacents:
        accum += int(number)

accum2 = 0
for k, v in star_adjacents.items():
    if len(v) != 2:
        continue
    accum2 +=  v[0] * v[1]

print(f'Part 1: {accum}')
print(f'Part 2: {accum2}')
