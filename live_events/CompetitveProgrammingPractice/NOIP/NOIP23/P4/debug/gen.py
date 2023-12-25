import random

mx = 20

n = 10
m = 3
k = random.randint(1, n)
d = random.randint(1, mx)
l = []

for i in range(m):
    a = random.randint(1, n);
    b = random.randint(1, n);
    l.append([max(a, b), max(a, b) - min(a, b) + 1, random.randint(1, mx)])

with open('test.in', 'w') as fi:
    print(1, 1)
    fi.write(f'1 1\n')

    print(n, m, k, d)
    fi.write(f'{n} {m} {k} {d}\n')

    for i in l:
        for j in i:
            print(j, end = ' ')
            fi.write(f'{j} ')
        print()
        fi.write('\n')
