'''
Observations:
Do the math:

a0 = floor(√x)

an n >= 1:

p√x - q
--------
    d

a1:
p = x - a0^2
q = a0 ^ 3 - x * a0
d = x - a0^2

p = d


an:

f = floor(an-1)

New p = dp
New q = d * (df - q)
New d = p^2 * x - (q - df)^2

Possibilities:
Keep fraction since fractions are more accurate than rounded floats
'''

#Imports
import numpy as np

#Vars
TotalOddPeriods = 0 #TotalOddPeriods
Count = 0 #Count
PerfectSquares = {i ** 2 for i in range(1, 100)} #Perfect squares
FirstCase = 0 #First period case

#User def functions
def NextPeriod(Current, i) -> tuple:
    p = Current[0]
    q = Current[1]
    d = Current[2]
    f = int((p * np.sqrt(i) + q) / d)
    return (d * p, d * (d * f - q), p ** 2 * i - (q - d * f) ** 2)

#Main
if __name__ == '__main__':
    #for i in range(2, 14): #10 ** 4 + 1):
    for i in range(23, 24):
        import pdb;pdb.set_trace()
        if i not in PerfectSquares:
            Count = 1
            temp = np.sqrt(i)
            a0 = int(temp)
            temp = (i - a0 ** 2, a0 ** 3 - i * a0, i - a0 ** 2)
            FirstCase = temp
            while True:
                temp = NextPeriod(temp, i)
                Count += 1
                if temp == FirstCase:
                    break
            if Count % 2 == 0: #Count has the first element of period twice thus all odd periods have even "Count"
                TotalOddPeriods += 1
    print(TotalOddPeriods)
