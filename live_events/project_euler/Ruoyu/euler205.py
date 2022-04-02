'''
Observations:
(a) To calculate probability, we can just calculate the number of ways each sum P can be achieved, the number of ways each sum C can be achieved, and see how many ways P > C
Divide that by the total P * the total C

Approach:
Use Observation (a) to BFI calculate the probability
REMEMBER TO MANUALLY ROUND TO 7 PLACES
'''

#Vars
PTotal = 0 #Total ways for P sums
PWays = {} #Dict of P sums and how many ways for each one
CTotal = 0 #Total ways for C sums
CWays  = {} #Dict of C sums and how many ways for each one
PWinWays = 0 #Ways for P to win

#User def functions
def GetProb(Total, Remaining, Faces) -> int:
    count = 0
    if Remaining == 0:
        if Faces == 4:
            try:
                PWays[Total] += 1
            except:
                PWays[Total] = 1
        else:
            try:
                CWays[Total] += 1
            except:
                CWays[Total] = 1
        return 1
    for i in range(1, Faces + 1):
        count += GetProb(Total + i, Remaining - 1, Faces)
    return count

#Main
if __name__ == '__main__':
    PTotal = GetProb(0, 9, 4)
    CTotal = GetProb(0, 6, 6)
    for p in PWays:
        count = 0
        for c in CWays:
            if c >= p:
                break
            count += CWays[c]
        PWinWays += count * PWays[p]
    print(PWinWays / (PTotal * CTotal), '\nREMEMBER TO MANUALLY ROUND TO 7 PLACES')
