import re

pattern = re.compile(r'Game\s\d+:\s(.+)')

def possibleGame(line):
    matches = pattern.search(line)
    game = matches[1].split(';')
    pos = {}

    for i in game:
        i = list(map(lambda x: x.strip() ,i.split(',')))

        for j in i:
            j = j.split()
            pos[j[1]] = max(int(j[0]), pos.get(j[1], 0))

    prod = 1
    for v in pos.values():
        prod *= v
    
    return prod

answer = 0
with open("C:/Users/invik/Downloads/input.txt", 'r') as file:
    for line in file.readlines():
       answer += possibleGame(line)

print(answer)
