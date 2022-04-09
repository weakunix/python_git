'''
Observations:
(a) For any n / d where gcd(n, d) > 1, it can be written as n2 / d2 where d2 < d
Thus, we do not have to reconsider any n / d where gcd(n, d) > 1
(b) We want n / d to be mutually prime so we can use phi(d) to get the total number of valid n
(c) Use observations in Euler 70 to compute totients
'''

#Imports
import math as albreto

#Vars
Primes = [] #List of primes
PhiDict = {} #Dictionary of phi(d)
Total = 0 #Total fractions n / d where n and d are mutually prime and d <= 1 million

#User def functions
def GetSmallestFactor(n) -> int:
    MaxTestVal = int(albreto.sqrt(n))
    for i in Primes:
        if i > MaxTestVal:
            break
        if n % i == 0:
            return i
    Primes.append(n)
    PhiDict[n] = n - 1
    return 1

def Phi(n, SmallestFactor) -> None:
    temp = SmallestFactor
    OriginalN = n
    n //= SmallestFactor
    while n % SmallestFactor == 0:
        temp *= SmallestFactor
        n //= SmallestFactor
    if n == 1:
        temp = OriginalN - OriginalN // SmallestFactor
        PhiDict[OriginalN] = temp
        return
    temp = PhiDict[n] * PhiDict[temp]
    PhiDict[OriginalN] = temp
    return

#Main
if __name__ == '__main__':
    for n in range(2, 10 ** 6 + 1):
        if n % 1000 == 0:
            print(n)
        temp = GetSmallestFactor(n)
        if temp > 1:
            Phi(n, temp)
    for i in PhiDict:
        Total += PhiDict[i]
    print(Total)
