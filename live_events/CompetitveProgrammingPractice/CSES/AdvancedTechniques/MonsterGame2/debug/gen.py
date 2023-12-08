import random

n = 10
x = 10**6

s = [random.randint(1, x) for i in range(n)]
f = [random.randint(1, x) for i in range(n)]

print(n, x)
for i in s:
    print(i, end = ' ')
print()
for i in f:
    print(i, end = ' ')
print()

with open('test.in', 'w') as fi:
    fi.write(f'{n} {x}\n')
    for i in s:
        fi.write(f'{i} ')
    fi.write('\n')
    for i in f:
        fi.write(f'{i} ')
    fi.write('\n')
