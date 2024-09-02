import random

n = 5

mn = 1
mx = 5

print(n, n - 1)

for i in range(2, n + 1):
    print(i, random.randint(1, i - 1), random.randint(mn, mx))
