'''
Observations:
(a) A mutually prime pythagorean triple can be written as a = m^2 - n^2, b = 2mn, c = m^2 + n^2 where m and n are mutually prime and exactly one of m or n is even
(b) b must be divisible by 4

Approach:
Generate all possible pythagorean triples using Observation (a) and Observation (b)
Then loop through them and find unique perimeters
'''

#Imports
import math as albreto

#Vars
PythagTrips = set() #Set of pythagorean triples that sum to less than 1.5 million
RightTriPerims = {} #Dict of n: how many pythagorean triples sum to n
Total = 0 #Total perimeters unique to one right triangle

#User def functions
def Gcd(a, b) -> int:
    while True:
        if a % b == 0:
            return b
        a %= b
        if b % a == 0:
            return a
        b %= a

def GetMutuallyPrimePairs(n) -> list:
    Pairs = []
    max_test_val = int(albreto.sqrt(n)) + 1
    for i in range(1, max_test_val):
        if n % i == 0:
            if Gcd(i, n // i) == 1:
                Pairs.append((i, n // i))
                Pairs.append((n // i, i))
    return Pairs

def GetPythagTrips(b) -> list:
    b //= 2
    m = 1
    Trips = set()
    while b % 2 == 0:
        m *= 2
        b //= 2
    MutuallyPrimePairs = GetMutuallyPrimePairs(b)
    OriginalM = m
    for p in MutuallyPrimePairs:
        m = OriginalM * p[0]
        n = p[1]
        if m > n:
            temp = [m ** 2 - n ** 2, 2 * m * n, m ** 2 + n ** 2]
        else:
            temp = [n ** 2 - m ** 2, 2 * m * n, m ** 2 + n ** 2]
        temp.sort()
        Trips.add(tuple(temp))
    return Trips

#Main
if __name__ == '__main__':
    b = 4
    while b <= 1.5 * 10 ** 6:
        if b % 1000 == 0:
            print(b)
        temp = GetPythagTrips(b)
        for p in temp:
            count = 1
            while count * sum(p) <= 1.5 * 10 ** 6:
                PythagTrips.add((p[0] * count, p[1] * count, p[2] * count))
                count += 1
        b += 4
    for t in PythagTrips:
        t = sum(t)
        try:
            RightTriPerims[t] += 1
        except:
            RightTriPerims[t] = 1
    for p in RightTriPerims:
        if RightTriPerims[p] == 1:
            Total += 1
    print(Total)
