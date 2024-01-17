import random

n = 100
t = 10**12
mn = 0
mx = 10**12

with open ('test.in', 'w') as fi:
    print(n, t)
    fi.write(f'{n} {t}\n')
    for i in range(n):
        a = random.randint(0, 1)
        b = random.randint(mn, mx)
        if not a:
            a = 'A'
        else:
            a = 'B'
        print(a, b)
        fi.write(f'{a} {b}\n')
