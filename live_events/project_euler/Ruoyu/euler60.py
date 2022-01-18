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
Primes = [] #All primes
Mod1Primes = [] #Primes that are 1 mod 3 + 3 itself
Mod2Primes = [] #Primes that are 2 mode 3 + 3 itself
PrimeDict = {}

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
                PrimeDict.get(a).append(b)
            except:
                PrimeDict[a] = [b]

def PossibleSet(l, Remaining):
    pass

#Get primes
with open('million_primes.txt', 'r') as PrimeFile:
    for i in PrimeFile:
        i = int(i)
        Primes.append(i)
        if i > 1000:
            pass
        elif i == 3:
            Mod1Primes.append(i)
            Mod2Primes.append(i)
        elif i % 3 == 1:
            Mod1Primes.append(i)
        else:
            Mod2Primes.append(i)

#Main
if __name__ == '__main__':
    Combinations = ListCombinations(Mod1Primes, 2) #First param is the prime list to test
    ConvertToDict(Combinations)
    for i in PrimeDict:
        s = PossibleSet([i], 3) #Change to 4
