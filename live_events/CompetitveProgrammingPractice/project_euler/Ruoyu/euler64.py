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
PerfectSquares = {i ** 2 for i in range(1, 101)} #Perfect squares
FirstCase = 0 #First period case

#User def functions
def Gcd(a, b) -> int:
    while a != 0 and b != 0:
        a %= b
        if a == 0:
            return b
        b %= a
        if b == 0:
            return a

def SimplifyFrac(t) -> tuple:
    g = Gcd(Gcd(t[0], t[1]), t[2])
    return (t[0] // g, t[1] // g, t[2] // g)

def NextPeriod(Current, i) -> tuple:
    p = Current[0]
    q = Current[1]
    d = Current[2]
    f = int((p * np.sqrt(i) + q) / d)
    t = (d * p, d * (d * f - q), p ** 2 * i - (q - d * f) ** 2)
    return SimplifyFrac(t)

#Main
if __name__ == '__main__':
    for i in range(2, 10 ** 4 + 1):
        if i not in PerfectSquares:
            Count = 1
            temp = np.sqrt(i)
            a0 = int(temp)
            temp = (1, a0, i - a0 ** 2)
            FirstCase = temp
            while True:
                temp = NextPeriod(temp, i)
                Count += 1
                if temp == FirstCase:
                    break
            if Count % 2 == 0: #Count has the first element of period twice thus all odd periods have even "Count"
                print(i)
                TotalOddPeriods += 1
    print(TotalOddPeriods)
