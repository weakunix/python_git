'''
Observations:
Sum must be odd (naturally occurs)
All set members must be same mod 3 unless 3 is in the set

Approach:
Get primes from prime file
Sort primes by mod 3 result
Make list into dictionary
Test sets
'''

#Imports
import numpy as np

#Vars
Count = 1 #Count
EarlyPrimes = set() #Primes added early
EarlyNotPrimes = set() #Confirmed not primes
PrimeList = [] #All primes list
Mod1PrimesDict = {} #Dictionary of mod 3 = 1 prime pairs
Mod2PrimesDict = {} #Dictionary of mod 3 = 2 prime pairs
Mod1Trips = [] #Triples of mod 3 = 1 primes
Mod2Trips = [] #Triplets of mod 3 = 2 primes
Mod1Quads = [] #Quadruples of 3 = 1 primes
Mod2Quads = [] #Quadruples of 3 = 2 primes
IsValidAddition = False #Is new prime a valid addition to set

#User def functions
def IsPrime(n, IsEarly = False) -> bool:
    if n in EarlyPrimes:
        if not IsEarly:
            PrimeList.append(n)
            EarlyPrimes.remove(n)
        return True
    if n in EarlyNotPrimes:
        if not IsEarly:
            EarlyNotPrimes.remove(n)
        return False
    MaxTestVal = int(np.sqrt(n))
    IsPrimeVar = True
    FinishTesting = False
    for p in PrimeList:
        if p > MaxTestVal:
            FinishTesting = True
            break
        if n % p == 0:
            IsPrimeVar = False
            break
    if not FinishTesting and n > 2:
        for i in range(PrimeList[-1] + 1, MaxTestVal + 1):
            if IsPrime(i, True):
                if n % i == 0:
                    IsPrimeVar = False
    if IsPrimeVar:
        if IsEarly:
            EarlyPrimes.add(n)
        else:
            PrimeList.append(n)
        return True
    if IsEarly:
        EarlyNotPrimes.add(n)
    return False

def SortPrime(p) -> int:
    FailValues = [2, 5]
    if p in [2, 5]:
        return 0
    if p == 3:
        Mod1PrimesDict[3] = []
        Mod2PrimesDict[3] = []
        return 0
    if p % 3 == 1:
        return 1
    return 2



def IsValidPair(a, b) -> bool:
    a = str(a)
    b = str(b)
    return IsPrime(int(a + b), True) and IsPrime(int(b + a), True)


#Main
if __name__ == '__main__':
    while True:
        Count += 1
        if Count % 100 == 0:
            print(Count)
        if IsPrime(Count):
            temp = SortPrime(Count)
            if temp:
                if temp == 1:
                    temp = Mod1PrimesDict
                    trips_temp = Mod1Trips
                    quads_temp = Mod1Quads
                else:
                    temp = Mod2PrimesDict
                    trips_temp = Mod2Trips
                    quads_temp = Mod2Quads
                for i in temp:
                    if IsValidPair(Count, i):
                        temp.get(i).append(Count)
                for q in quads_temp:
                    IsValidAddition = True
                    for p in q:
                        if Count not in temp[p]:
                            IsValidAddition = False
                            break
                    if IsValidAddition:
                        print(q + [Count], sum(q) + Count)
                        raise SystemExit()
                for t in trips_temp:
                    IsValidAddition = True
                    for p in t:
                        if Count not in temp[p]:
                            IsValidAddition = False
                            break
                    if IsValidAddition:
                        quads_temp.append(t + [Count])
                for p in temp: #Could store these in a list previously to make it faster
                    if Count in temp[p]:
                        for Element in temp[p]:
                            try:
                                if Count in temp[Element]:
                                    trips_temp.append([p, Element, Count])
                            except:
                                pass
                temp[Count] = []
