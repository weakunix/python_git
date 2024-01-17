import random

n = 8
m = random.randint(1, n)

nums = [i for i in range(1, n + 1)]
l = []

for i in range(m):
    l.append(random.choice(nums))
    nums.remove(l[-1])

print(n, m)
for i in l:
    print(i, end = ' ')
print()
