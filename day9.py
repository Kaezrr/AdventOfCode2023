lines = []

with open("C:/Users/invik/Downloads/input.txt") as f:
    for line in f.readlines():
        line = line.rstrip('\n')
        if not line: continue

        lines.append(list(map(int, line.split())))

res1 = 0
res2 = 0
for row in lines:
    temp = []
    temp.append(row)
    while(temp[-1].count(temp[-1][0]) != len(temp[-1])):
        temp.append([temp[-1][i+1] - temp[-1][i] for i in range(len(temp[-1])-1)])

    t1 = temp[-1][-1]
    for i in range(len(temp)-2, -1, -1):
        t1 += temp[i][-1]
    
    t2 = temp[-1][0]
    for i in range(len(temp)-2, -1, -1):
        t2 = temp[i][0] - t2

    res1 += t1
    res2 += t2

print(f'Part 1: {res1}')
print(f'Part 2: {res2}')

