'''
Observations:
Sum must be odd (naturally occurs)
All set members must be same mod 3 unless 3 is in the set

Approach:
BFI: try primes up to certain amount (first up to 1000)
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
Pairs = [] #Pairs of primes
Trips = [] #Triples of primes
Quads = [] #Quadruples of primes
IsValidAddition = False #Is new prime valid addition to set

#User def functions
def ListCombinations(l, ChooseNum) -> list:
    if ChooseNum == 0:
        return [[]]
    if ChooseNum == len(l):
        return [l]
    x = ListCombinations(l[1:], ChooseNum - 1)
    for i in range(len(x)):
        x[i] = [l[0]] + x[i]
    y = ListCombinations(l[1:], ChooseNum)
    return x + y

def IsValidPair(a, b) -> bool:
    return int(a + b) in Primes and int(b + a) in Primes

def ConvertToDict(l) -> None:
    for Pair in l:
        a = Pair[0]
        b = Pair[1]
        if IsValidPair(str(a), str(b)):
            try:
                PrimeDict.get(a).add(b)
            except:
                PrimeDict[a] = {b}

def AddMembers(l, IsFinalMember = False):
    NewSets = []
    MinSum = None
    for p in l:
        try:
            for Prime in PrimeDict[p[-1]]:
                IsValidAddition = True
                for i in p[:-1]:
                    if Prime not in PrimeDict[i]:
                        IsValidAddition = False
                        break
                if IsValidAddition:
                    if IsFinalMember:
                        try:
                            if sum(p) + Prime < MinSum:
                                MinSum = sum(p) + Prime
                        except:
                            MinSum = sum(p) + Prime
                    else:
                        NewSets.append(p + [Prime])
        except:
            pass
    if IsFinalMember:
        return MinSum
    return NewSets

#Get primes
with open('million_primes.txt', 'r') as PrimeFile:
    for i in PrimeFile:
        i = int(i)
        Primes.add(i)
        if i > 10 ** 4:
            pass
        elif i == 3:
            Mod1Primes.append(i)
            Mod2Primes.append(i)
        elif i % 3 == 1:
            Mod1Primes.append(i)
        else:
            Mod2Primes.append(i)
print('Primes obtained')

#Main
if __name__ == '__main__':
    Pairs = ListCombinations(Mod1Primes, 2) #First param is the prime list to test
    ConvertToDict(Pairs)
    print(f'Pairs done with {len(Pairs)} elements')
    Trips = AddMembers(Pairs)
    print(f'Trips done with {len(Trips)} elements')
    Quads = AddMembers(Trips, True)
    print(Quads)
    #print(f'Quads done with {len(Quads)} elements')
    #Quints = AddMembers(Quads, True)
    #print(Quints)
