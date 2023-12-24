cache = {}

def count(spring, pattern):
    if spring == '': return 0 if pattern else 1
    if pattern == (): return 0 if '#' in spring else 1
    
    key = (spring, pattern)
    if key in cache: 
        return cache[key]
    
    result = 0
    if spring[0] in '.?': result += count(spring[1:], pattern)
    if spring[0] in '#?':
        if len(spring) >= pattern[0] and '.' not in spring[:pattern[0]] and (len(spring) == pattern[0] or spring[pattern[0]] != '#'):
            result += count(spring[pattern[0]+1:], pattern[1:])

    cache[key] = result
    return result

answer = 0
with open("C:/Users/invik/Downloads/input.txt") as f:
    for line in f:
        sp, co = line.rstrip().split()
        sp = '?'.join([sp]*5)
        co = ','.join([co]*5)
        co = tuple(map(int, co.split(',')))
        answer += count(sp, co)

print(answer)
