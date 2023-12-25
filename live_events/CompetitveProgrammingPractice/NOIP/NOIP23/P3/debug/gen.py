import random

c = 69 #lol
n = 10
m = 9
q = 0

mn = 0
mx = 100

a = [random.randint(mn, mx) for i in range(n)]
b = [random.randint(mn, mx) for i in range(m)]

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
