import random

n = 2
m = 1 << n

mn = 0
mx = 10

print(n)

for i in range(m):
    print(random.randint(0, 1), end = ' ')
print()

for i in range(m):
    print(random.randint(mn, mx), end = ' ')
print()

for i in range(m - 1):
    for j in range(m - i - 1):
        print(random.randint(mn, mx), end = ' ')
    print()
