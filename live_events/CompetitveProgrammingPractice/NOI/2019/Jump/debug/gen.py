import random

n = 4
m = 5

mn = 1
mx = 10

print(n, m, n, n)

loc = []
for i in range(n):
    cur = [random.randint(1, n), random.randint(1, n)]
    while cur in loc:
        cur = [random.randint(1, n), random.randint(1, n)]
    loc.append(cur)
    print(cur[0], cur[1])

for i in range(m):
    p = random.randint(1, n)
    t = random.randint(mn, mx)
    l = random.randint(1, n - 1)
    r = random.randint(l + 1, n)
    d = random.randint(1, n - 1)
    u = random.randint(d + 1, n)
    print(p, t, l, r, d, u)
