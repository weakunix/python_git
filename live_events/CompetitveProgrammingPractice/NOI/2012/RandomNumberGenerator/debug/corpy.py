m, a, c, x, n, g = map(int, input().split())

for i in range(n):
    x = (a * x + c) % m
print(x % g)
