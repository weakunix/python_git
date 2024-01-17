import random

n = 5
m = 7
l = []
seen = [1]

for i in range(2, n + 1):
    l.append([i, random.choice(seen)])
    seen.append(i)

for i in range(m - n + 1):
    a = 0
    b = 0
    while (a == b):
        a = random.randint(1, n)
        b = random.randint(1, n)
        if [a, b] in l or [b, a] in l:
            a = b
    l.append([a, b])

random.shuffle(l)

with open('test.in', 'w') as fi:
    print(n, m)
    fi.write(f'{n} {m}\n')
    for i in l:
        print(i[0], i[1])
        fi.write(f'{i[0]} {i[1]}\n')
