import random as rand

n = 1000
q = 1000

print(n, q)

for i in range(n):
    print(rand.randint(1, 10), end = ' ')
print()

for i in range(q):
    t = rand.randint(1, 3)
    print(t, end = ' ')
    print(rand.randint(1, n), end = ' ')
    print(rand.randint(1, n), end = ' ')
    if (t != 3):
        print(rand.randint(1, 10), end = ' ')
    print()
