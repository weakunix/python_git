import random

n = 5

mn = 1
mx = 10

op = ['I', 'A', 'S', 'F']

print(n, random.randint(mn, mx))

for i in range(n):
    print(random.choice(op), random.randint(mn, mx))
