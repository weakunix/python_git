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

#Main
if __name__ == '__main__':
    for i in range(2, 10 ** 4 + 1):
        if i not in PerfectSquares:
            Count = 1
            temp = np.sqrt(i)
            a0 = int(temp)
            
