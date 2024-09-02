n, m, a, b, c, d = map(int, input().split())

cur = 1
modval = 10 ** 9 + 7

for i in range(1, n + 1):
    for j in range(1, m + 1):
        if i == 1 and j == 1:
            cur = 1
        elif j == 1:
            cur = (c * cur + d) % modval
        else:
            cur = (a * cur + b) % modval
        print(cur)
print(cur)
