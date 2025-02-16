import random

n = 3
k = random.randint(2, 8);
print(n, k);

mn = 1
mx = 10

l = [(i, j) for i in range(1, n + 1) for j in range(1, n + 1)]
random.shuffle(l)

for i in range(n):
    for j in range(n):
        print(random.randint(mn, mx), end = ' ')
    print()

for i in l:
    print(i[0], i[1])
