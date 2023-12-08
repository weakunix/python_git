import random

n = 5
m = 5

print(n, m);

for i in range(n):
    print(chr(random.randint(ord('A'), ord('Z'))), end = '')
print()

for i in range(m):
    l = random.randint(1, n)
    r = random.randint(l, n)
    print(l, r)
