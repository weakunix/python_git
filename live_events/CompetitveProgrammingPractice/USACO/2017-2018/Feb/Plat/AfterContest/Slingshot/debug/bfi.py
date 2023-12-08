n, m = map(int, input().split())
sling = []

for i in range(n):
    a, b, c = map(int, input().split())
    sling.append([a, b, c])

for i in range(m):
    a, b = map(int, input().split())
    ans = abs(a - b)
    for j in sling:
        ans = min(abs(j[0] - a) + abs(j[1] - b) + j[2], ans)
    print(ans)
