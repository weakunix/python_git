import random

n = 5
k = random.randint(1, n);
mx = 10
l = [random.randint(1, mx) for i in range(n)]

print(n, k)
for i in l:
    print(i, end = ' ')
print()

with open('test.in', 'w') as fi:
    fi.write(f'{n} {k}\n')
    for i in l:
        fi.write(f'{i} ')
    fi.write('\n')
