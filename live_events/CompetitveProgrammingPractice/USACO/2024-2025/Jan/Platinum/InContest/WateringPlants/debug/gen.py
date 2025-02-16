import random

n = 4
mn = 1
mx = 10

print(n)
for i in range(n):
    print(random.randint(mn, mx), end = ' ')
print()
for i in range(n - 1):
    print(random.randint(mn, mx), end = ' ')
print()
