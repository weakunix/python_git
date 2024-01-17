import random

n = 10
allzero = True

print(n)

for i in range(n):
    cur = random.randint(0, 1)
    if (cur):
        allzero = False
    if (i == n - 1 and allzero):
        cur = 1
    print(cur, end = '')
print()

for i in range(2, n + 1):
    cur = random.randint(1, i - 1)
    print(i, cur)

print(10)
for i in range(1, 11):
    print(i)
