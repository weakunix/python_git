'''
Observations:
(a) phi(prime) = prime - 1
Primes will not fit this condition because phi(prime) cannot be a permutation of prime

(b) phi(x * y) = phi(x) * phi(y) when x and y are mutually prime

(c) The only time n can not be written as x * y where x and y are mutually prime is when n is p ^ q where p is a prime number

(d) phi(p ^ q) = p ^ q * (1 - 1 / p)

Approach:
We go through every n
If n is prime, store n and phi(n) and ignore it (Observation (a))
If n is p ^ q, we can get phi(n) using Observation (d)
If n is x * y where x and y are mutually prime, we can get phi(n) using Observation (b)

Store previous phi(n) so that we do not have to fully factorize n every time
'''

#Imports
import math as albreto

#Vars
PerfectPowers = set() #Set of n where n is p ^ q (which thus cannot be written as m * n where m and n are mutually prime
Primes = [] #List of primes
PhiDict = {} #Dictionary of phi(n)
Permutations = [] #Set of (n, phi(n)) where phi(n) is a permutation of n
NForMin = (None, None) #Value of n for which phi(n) is a permutation of n and the value of n / phi(n) is minimized in the form of (n / phi(n), n)

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

def Phi(n, SmallestFactor, IsPerfectPower) -> int:
    if IsPerfectPower:
        temp = n - n / SmallestFactor
        PhiDict[n] = temp
        return temp
    temp = SmallestFactor
    OriginalN = n
    n //= SmallestFactor
    while n % SmallestFactor == 0:
        temp *= SmallestFactor
        n //= SmallestFactor
    temp = PhiDict[n] * PhiDict[temp]
    PhiDict[OriginalN] = temp
    return temp

def MakeDictionary(n) -> dict:
    n = int(n)
    DigitDict = {i: 0 for i in range(10)}
    for i in str(n):
        i = int(i)
        DigitDict[i] += 1
    return DigitDict

def IsPermutation(a, b) -> bool:
    return MakeDictionary(a) == MakeDictionary(b)

#Set variables
count = 2
while 2 ** count < 10 ** 7:
    count2 = 2
    while count2 ** count < 10 ** 7:
        PerfectPowers.add(count2 ** count)
        count2 += 1
    count += 1

#Main
if __name__ == '__main__':
    for n in range(2, 10 ** 7):
        if n % 1000 == 0:
            print(n)
        temp = GetSmallestFactor(n)
        if temp > 1:
            temp = Phi(n, temp, n in PerfectPowers)
            if IsPermutation(n, temp):
                Permutations.append((n, temp))
    print(Permutations)
    for i in Permutations:
        temp = i[0] / i[1]
        try:
            if temp < NForMin[0]:
                NForMin = (temp, i[0])
        except:
            NForMin = (temp, i[0])
    print(NForMin)
