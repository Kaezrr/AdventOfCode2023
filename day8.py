import re
import math

pattern = re.compile(r'[A-Z0-9]{3}')
paths = {}
currents = []

with open("C:/Users/invik/Downloads/input.txt") as f:
    left_right = [0 if i == 'L' else 1 for i in f.readline().rstrip('\n')]
    for line in f.readlines():
        line = line.rstrip('\n')
        if not line: continue

        temp = pattern.findall(line)
        if temp[0][-1] == 'A':
            currents.append(temp[0])

        paths[temp[0]] = temp[1:]

ways = []
for p in currents:
    path = 0    
    while(p[-1] != 'Z'):
        for i in left_right:
            if(p[-1] == 'Z'): break
            p = paths[p][i]
            path += 1

    ways.append(path)

print(f'Answer: {math.lcm(*ways)}')
        
