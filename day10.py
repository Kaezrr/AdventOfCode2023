maze = []
valid = set()
directions = {'|': [(-1, 0), (1, 0)],
            '-': [(0, -1), (0, 1)],
            'L': [(-1, 0), (0, 1)],
            'J': [(-1, 0), (0, -1)],
            '7': [(1, 0), (0, -1)],
            'F': [(1, 0), (0, 1)],}
with open("C:/Users/invik/Downloads/input.txt") as f:
    y = 0
    for line in f.readlines():
        line = line.rstrip('\n')
        if not line: continue
        tempMaze = []
        x = 0
        for i in line:
            if i == 'S': start = (y, x)
            if i != '.': valid.add((y, x))
            tempMaze.append(i)
            x += 1
        maze.append(tempMaze)
        y += 1

def longestLoop(y, x):
    count = 0
    coords = [start]
    visited = {start}
    while(True):
        if (y, x) in visited or (y, x) not in valid or maze[y][x] == 'S': break
        count += 1
        visited.add((y, x))
        dire = directions[maze[y][x]]
        if maze[y][x] in {'7', 'J', 'F', 'L'}:
            coords.append((y, x))

        if (y + dire[0][0], x + dire[0][1]) in visited:
            y += dire[1][0]
            x += dire[1][1]
        else:
            y += dire[0][0]
            x += dire[0][1]    
    return (count, coords)
        
path = 0
coords = []
for i in [(0, 1), (1, 0), (-1, 0)]:
    temp = longestLoop(start[0]+i[0], start[1]+i[1])
    path = max((temp[0] + 1) // 2, path)
    coords = temp[1] if len(temp[1])> len(coords) else coords
coords.append(start)

area = 0
for i in range(len(coords)-1):
    area += coords[i][0]*coords[i+1][1] - coords[i][1]*coords[i+1][0]
points = (abs(area // 2) + 1) - path


print(f'Part 1: {path}')
print(f'Part 2: {points}')




    
        
