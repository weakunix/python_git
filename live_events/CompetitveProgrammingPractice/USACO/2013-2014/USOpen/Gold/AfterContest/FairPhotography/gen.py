import random

n = 10
k = 2
mx = 100

locs = random.sample(range(mx), n)

print(n, k);

for i in locs:
    print(i, random.randint(1, 8))
