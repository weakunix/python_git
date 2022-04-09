'''
Sample Cases:
In:
3
6
1 2 3 1 1 1
3
2 2 3
5
0 0 0 0 0

Out:
3
2
0

CORRECT but slow PROGRAM!
10/11
'''

#Main
t = int(input())
for _ in range(t):
    N = int(input())
    SleepLog = input()
    SleepLog = SleepLog.split(' ')
    for i in range(len(SleepLog)):
        SleepLog[i] = int(SleepLog[i])
    Total = sum(SleepLog)
    PossibleTestVal = []
    for i in range(-N, 0):
        i = -i
        if Total % i == 0:
            PossibleTestVal.append(Total // i)
    for i in PossibleTestVal:
        Worked = True
        Log = SleepLog.copy()
        Moves = 0
        while len(Log) > 0:
            if Log[0] == i:
                Log.pop(0)
            else:
                temp = Log.pop(0)
                Log[0] += temp
                Moves += 1
                if Log[0] > i:
                    Worked = False
                    break
        if Worked:
            break
    print(Moves)
