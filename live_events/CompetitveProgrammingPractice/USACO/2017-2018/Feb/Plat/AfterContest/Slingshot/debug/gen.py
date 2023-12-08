import random

n = 5
m = 3
mx = 20

print(n, m)

for i in range(n):
    for j in range(3):
        print(random.randint(1, mx), end = ' ')
    print()

for i in range(m):
    for j in range(2):
        print(random.randint(1, mx), end = ' ')
    print()
