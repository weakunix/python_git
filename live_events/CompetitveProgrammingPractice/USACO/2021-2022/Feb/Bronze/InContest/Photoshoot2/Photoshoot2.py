'''
Sample Cases:
In:
5
1 2 3 4 5
1 2 3 4 5

Out:
0

In:
5
5 1 3 2 4
4 5 2 1 3

Out:
2

CORRECT but slow PROGRAM!
10/14
'''

#Main
N = int(input())
CurrentOrder = input().split(' ')
DesiredOrder = input().split(' ')
ReorderDict = {DesiredOrder[i]: i for i in range(N)}
PlaceDifs = {}
Moves = 0
for i in range(N):
    temp = ReorderDict[CurrentOrder[i]]
    PlaceDifs[temp] = temp - i
for i in range(N):
    temp = PlaceDifs[i]
    if temp == 0:
        PlaceDifs.pop(i)
    else:
        Moves += 1
        for k in PlaceDifs:
            if i == k:
                break
            PlaceDifs[k] -= 1
        PlaceDifs.pop(i)
print(Moves)
