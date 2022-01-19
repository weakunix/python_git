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
Pairs = [] #Pairs of primes
Trips = [] #Triples of primes
Quads = [] #Quadruples of primes

#User def functions
def IsValidPair(a, b) -> bool:
    return int(a + b) in Primes and int(b + a) in Primes

#Get primes
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
print('Primes obtained')

#Main
if __name__ == '__main__':
    for i in Mod1Primes:
       for Prime in PrimeDict:
           if IsValidPair(str(i), str(Prime)):
                PrimeDict.get(Prime).add(i)
       pass
