import random

n = 5
c = 5

mn = 1
mx = 5

print(n)

for i in range(n):
    print(random.randint(mn, mx), end = ' ')
print()

for i in range(n):
    print(random.randint(1, c), end = ' ')
print()

for i in range(2, n + 1):
    print(random.randint(1, i - 1), i)
