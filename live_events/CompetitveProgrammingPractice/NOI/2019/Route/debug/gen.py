import random

n = 3
m = 5
a = 0
b = 0
c = random.randint(1, 10)

print(n, m, a, b, c)

mn = 1
mx = 10

print(1, n, 0, 1000)

for i in range(m - 1):
    a = random.randint(1, n - 1)
    b = a
    while b == a:
        b = random.randint(1, n)

    p = random.randint(mn, mx - 1)
    q = random.randint(p + 1, mx)

    print(a, b, p, q)
