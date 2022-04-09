'''
Observations
(a) Max square test is about 7000, max cube test is something like 350, max fourth test is about 85
This problem is BFI-able
(b) It is easier to loop fourths->cubes->squares since there are the least fourths
(c) To optimize the program, remember to break the cube loop if fourth + cube > 50 million

Approach:
Because of Observation (a), we can BFI prime power triples using Observations (b) and (c)
Use a set to store the prime power triples since some may equal others
'''

#Imports
import math as albreto

#Vars
Primes = [] #Primes
Sqrs = [] #Squares
Cubes = [] #Cubes
Fourths = [] #Fourth powers
FiftyMil = 5 * 10 ** 7 #50 mil
PrimePowTrips = set() #Prime power triples

#User def functions
def IsPrime(n) -> bool:
    mtv = int(albreto.sqrt(n))
    for i in Primes:
        if i > mtv:
            return True
        if n % i == 0:
            return False
    return True

#Main
if __name__ == '__main__':
    mtv = int(albreto.sqrt(FiftyMil))
    for i in range(2, mtv + 1):
        if IsPrime(i):
            Primes.append(i)
            Sqrs.append(i ** 2)
    for i in Primes:
        temp = i ** 3
        if temp > FiftyMil:
            break
        Cubes.append(temp)
    for i in Primes:
        temp = i ** 4
        if temp > FiftyMil:
            break
        Fourths.append(temp)
    for f in Fourths:
        for c in Cubes:
            if f + c > FiftyMil:
                break
            for s in Sqrs:
                if f + c + s <= FiftyMil:
                    PrimePowTrips.add(f + c + s)
    print(len(PrimePowTrips))
