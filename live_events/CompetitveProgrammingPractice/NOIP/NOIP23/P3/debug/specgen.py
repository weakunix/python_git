import random

c = 9 #lol
n = 5
m = 5
q = 0

mn = 0
mx = 30

lim = []
for i in range(4):
    while True:
        cur = random.randint(mn, mx)
        if cur not in lim:
            lim.append(cur)
            break
lim.sort()

a = [lim[1]] + [random.randint(lim[0] + 1, mx) for i in range(n - 2)] + [lim[0]]
b = [lim[2]] + [random.randint(mn, lim[3] - 1) for i in range(m - 2)] + [lim[3]]

with open('test.in', 'w') as fi:
    print(c, n, m, q)
    fi.write(f'{c} {n} {m} {q}\n');
    for i in a:
        print(i, end = ' ')
        fi.write(f'{i} ')
    print()
    fi.write('\n')
    for i in b:
        print(i, end = ' ')
        fi.write(f'{i} ')
    print()
    fi.write('\n')
