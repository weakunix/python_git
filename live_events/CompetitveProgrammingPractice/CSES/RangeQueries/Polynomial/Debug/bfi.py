n, q = map(int, input().split())
arr = list(map(int, input().split()))
for i in range(q):
    t, a, b = map(int, input().split())
    a -= 1
    b -= 1
    if t == 1:
        for i in range(a, b + 1):
            arr[i] += i - a + 1
    else:
        ans = 0
        for i in range(a, b + 1):
            ans += arr[i]
        print(ans)
