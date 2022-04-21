'''
Test outputs

1:
YNNNYN
'''

s = [RemapDict[i] for i in input()]
Q = int(input())
SubStrings = [[int(i) for i in input().split(' ')] for _ in range(Q)]

for i in SubStrings:
    temp = sum(s[i[0] - 1:i[1]])
    if temp % 4 == 0 and temp % 8 != 0:
        print('Y', end = '')
    else:
        print('N', end = '')
print()
