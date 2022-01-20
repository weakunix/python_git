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

#Vars
FailValues = [2, 5] #Primes that won't work
Primes = set() #All primes
Mod1Primes = [] #Primes that are 1 mod 3 + 3 itself
Mod2Primes = [] #Primes that are 2 mode 3 + 3 itself
PrimeDict = {} #Dictionary of prime pairs
Trips = [] #Triples of primes
Quads = [] #Quadruples of primes
IsValidAddition = False #Is new prime a valid addition to set

#User def functions
def IsValidPair(a, b) -> bool:
    return int(a + b) in Primes and int(b + a) in Primes

#Get primes
'''
READ FILE (BAD)
with open('million_primes.txt', 'r') as PrimeFile:
    for i in PrimeFile:
        i = int(i)
        Primes.add(i)
        if i > 10 ** 4:
            pass
        elif i in FailValues:
            pass
        elif i == 3:
            Mod1Primes.append(i)
            Mod2Primes.append(i)
        elif i % 3 == 1:
            Mod1Primes.append(i)
        else:
            Mod2Primes.append(i)
'''

print('Primes obtained')

#Main
if __name__ == '__main__':
    for i in Mod1Primes:
        for Prime in PrimeDict:
            if IsValidPair(str(i), str(Prime)):
                PrimeDict.get(Prime).append(i)
        for t in Trips:
            IsValidAddition = True
            for p in t:
                if i not in PrimeDict[p]:
                    IsValidAddition = False
                    break
            if IsValidAddition:
                print(t + [i], sum(t) + i)
                raise SystemExit()
        for p in PrimeDict: #Could store these in a list previously to make it faster
            if i in PrimeDict[p]:
                for Element in PrimeDict[p]:
                    try:
                        if i in PrimeDict[Element]:
                            Trips.append([p, Element, i])
                    except:
                        pass
        PrimeDict[i] = []
