import random

n = 2
w = 2
t = random.randint(1, 10)
v = random.randint(1, 50)

print(n, w, t, v)

for i in range(n):
    l = random.randint(0, w - 2)
    r = random.randint(l + 1, w - 1)
    print(l, r - l, random.randint(-2, 2))
