import random

n = 3
m = 1
t = 2
q = 1

print(n, m, t)

for i in range(m):
    print(random.randint(0, n))

print(q)

for i in range(q):
    print(random.randint(1, n))
