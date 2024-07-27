import random

n = 3
m = 5

mn = 1
mx = 10

print(n, m)

for i in range(2 ** n - 2):
    print(random.randint(mn, mx), end = ' ')
print()

for i in range(m):
    node = random.randint(2, n)
    k = random.randint(1, node - 1)

    node = random.randint(2 ** (node - 1), 2 ** node - 1)
    top = node
    for i in range(k):
        top //= 2
    print(top, node, random.randint(mn, mx))
