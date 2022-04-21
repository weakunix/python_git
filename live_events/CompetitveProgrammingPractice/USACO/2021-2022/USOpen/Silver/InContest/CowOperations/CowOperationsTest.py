'''
Test outputs

1:
YNNNYN
'''

s = [i for i in input()]
Q = int(input())
SubStrings = [[int(i) for i in input().split(' ')] for _ in range(Q)]
CowLetters = {'C', 'O', 'W'}

for i in SubStrings:
    temp = s[i[0] - 1:i[1]]
    while len(temp) > 1:
        a = temp.pop()
        b = temp.pop()
        if a != b:
            temp.append(list(CowLetters - {a, b})[0])
    if len(temp) == 1:
        if temp[0] == 'C':
            print('Y', end = '')
        else:
            print('N', end = '')
    else:
        print('N', end = '')

print()
