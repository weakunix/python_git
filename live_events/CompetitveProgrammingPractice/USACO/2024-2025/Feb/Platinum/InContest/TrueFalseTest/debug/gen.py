import random

mn = 1
mx = 10

n = 4

print(n, n + 1)
for i in range(n):
    print(random.randint(mn, mx), random.randint(mn, mx))
for i in range(n + 1):
    print(i)
