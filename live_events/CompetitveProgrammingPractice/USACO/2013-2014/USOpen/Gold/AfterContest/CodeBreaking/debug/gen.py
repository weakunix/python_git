import random

n = 10
m = 50000

p = [-1, 0, 1, 2, 3]
h = [0, 1, 2, 3, 4]
psbl = [4]

for i in range(5, n):
    p.append(random.randint(0, i - 1))
    h.append(h[p[i]] + 1)
    if h[i] >= 4:
        psbl.append(i)

locs = [random.choice(psbl) for i in range(m)]
vals = [random.randint(10000, 99999) for i in range(m)]

print(n, m)
for i in p[1:]:
    print(i)
for i in range(m):
    print(locs[i], vals[i])

with open('test.in', 'w') as fi:
    fi.write(f'{n} {m}\n')
    for i in p[1:]:
        fi.write(f'{i}\n')
    for i in range(m):
        fi.write(f'{locs[i]} {vals[i]}\n')
