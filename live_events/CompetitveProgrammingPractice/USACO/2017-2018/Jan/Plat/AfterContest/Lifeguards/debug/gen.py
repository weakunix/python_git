import random

n = 5
k = random.randint(1, n - 1)


mx = 50
l = [i for i in range(1, mx + 1)]

with open("scuff.txt", "w") as file:
    print(n, k);
    file.write(f'{n} {k}\n')
    for i in range(n):
        a = random.choice(l)
        l.remove(a)
        b = random.choice(l)
        l.remove(b)
        print(min(a, b), max(a, b))
        file.write(f'{min(a, b)} {max(a, b)}\n')
