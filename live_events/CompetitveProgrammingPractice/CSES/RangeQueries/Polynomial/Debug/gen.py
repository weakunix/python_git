import random as rand

n = 1000
q = 1000
mx = 1e6

print(n, q);

for i in range(n):
    print(0, end = ' ')
print()

for i in range(q):
    t = rand.randint(1, 2)
    a = rand.randint(1, n)
    b = rand.randint(1, n)
    if (a > b):
        a, b = b, a
    print(t, a, b)
