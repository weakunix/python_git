'''
Observations:
(a) sqrt(n) can be written as k + 0.d + 0.0abc...
100 * sqrt(n) can be written as 10k + d + 0.abc... = kd.abc...
This adds a digit
We can keep repeating this to get 100 digits
100 ^ 2 * sqrt(n) gives 2 digits
100 ^ 3 * sqrt(n) gives 3 digits
etc.
(b) To get each succeeding d (above in Observation (a)), we can loop from 9 to 0 and test if (10k + d) ^ 2 < 100 ^ x where x is the power of 100 above in Observation (a)
The first d that satisfies this condition will be the next digit

Approach:
For each non-perfect square n where 1 <= n <= 100, we can generate 100 decimal digits using Observation (a) and (b)
Then just sum them up
'''

#Imports
import math as albreto

#Vars
PerfectSquares = {i ** 2 for i in range(1, 11)} #Perfect squares
Total = 0 #Total of square root digit sums

#User def functions
def GetSqrtDigitSum(n) -> int:
    MaxVal = n
    n = int(albreto.sqrt(n))
    Digits = [n]
    while len(Digits) < 100:
        MaxVal *= 100
        for i in range(-9, 1):
            i *= -1
            if (n * 10 + i) ** 2 < MaxVal:
                n = n * 10 + i
                Digits.append(i)
    return sum(Digits)

#Main
if __name__ == '__main__':
    for n in range(1, 101):
        if n not in PerfectSquares:
            Total += GetSqrtDigitSum(n)

print(Total)
