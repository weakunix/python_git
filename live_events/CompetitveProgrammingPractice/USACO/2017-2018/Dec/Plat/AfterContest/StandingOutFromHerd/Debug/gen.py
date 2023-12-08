import random

n = 2
mnc = 'a'
mxc = 'z'
mxsz = 5
sz = [random.randint(1, mxsz) for i in range(n)]

print(n)
for i in range(n):
    for j in range(sz[i]):
        print(chr(random.randint(ord(mnc), ord(mxc))), end = '')
    print()
