import random

n = 5
mn = 1
mx = 20

seen = set()

print(n)

for i in range(n):
    while True:
        b = random.randint(1, mx)
        a = random.randint(1, b)
        if a/b in seen:
            continue
        seen.add(a/b)
        print(a, b)
        break;
