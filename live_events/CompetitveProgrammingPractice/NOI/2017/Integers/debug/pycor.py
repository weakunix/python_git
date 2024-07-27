n = int(input().split()[0])
ans = 0
for i in range(n):
    q = input().split()
    if q[0] == '1':
        a = int(q[1])
        b = int(q[2])
        ans += a * (1 << b)
    else:
        k = int(q[1])
        if ans & (1 << k):
            print(1)
        else:
            print(0)
    if ans < 0:
        print('\nASDFJASLKDFJAKLSDJFLAJSDF\n')
