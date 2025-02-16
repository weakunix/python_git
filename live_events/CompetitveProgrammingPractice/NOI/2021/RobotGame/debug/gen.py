import random

n = 4
m = 1
l = ['0', '1', '*']

print(n, m)

for i in range(m):
    cur = ''

    for j in range(random.randint(1, n - 1)):
        cur += random.choice(l) + 'R'
    print(cur[:-1])
