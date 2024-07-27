import random

n = 20

mx = 10 ** 6

print(n, 0, 0, 0)

cur = 0
for i in range(n):
    t = random.randint(1, 2)
    if t == 1:
        a = random.randint(-10 ** 9, 10 ** 9)
        b = random.randint(0, mx)
        while cur + a * (1 << b) < 0:
            a = random.randint(-mx, mx)
            b = random.randint(0, mx)
        print(1, a, b)
    else:
        k = random.randint(0, 10**7)
        print(2, k)
