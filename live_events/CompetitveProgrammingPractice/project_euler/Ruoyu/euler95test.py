
#Imports
import math as albreto

#Vars
ProperDivSums = {} #Dict of n : f(n) for non-perfect powers n
Primes = [] #List of primes
PerfectPows = {} #Dict of perfect powers n : f(n)
LongestChain = (0, 0) #Longest chain in the form (length, smallest num)
StartinvVal = 0 #Starting value of chain

#User def functions
def IsPrime(n) -> bool:
    mtv = int(albreto.sqrt(n))
    for i in Primes:
        if i > mtv:
            return True
        if n % i == 0:
            return False
    return True

def PrimeFactorize(n) -> list:
    Pf = []
    for i in Primes:
        count = 0
        while n % i == 0:
            n //= i
            count += 1
        if count > 0:
            Pf.append(i ** count)
        if n == 1:
            return Pf

def GetDivSum(n) -> int:
    try:
        return PerfectPows[n] - n
    except:
        Pf = PrimeFactorize(n)
        temp = 1
        for i in Pf:
            temp *= PerfectPows[i]
        return temp - n

#Gen primes
for i in range(2, 10 ** 6 + 1):
    if IsPrime(i):
        Primes.append(i)

#Perfect powers n and f(n)
for i in Primes:
    PerfectPows[i] = i + 1
for i in range(2, 1001):
    count = 2
    while i ** count <= 10 ** 6:
        if i ** count not in PerfectPows:
            PerfectPows[i ** count] = 0
            for k in range(count + 1):
                PerfectPows[i ** count] += i ** k
        count += 1

#Main
if __name__ == '__main__':
    #Non-perfect powers n and f(n)
    for i in range(2, 10 ** 6 + 1):
        if i % 1000 == 0:
            print(i)
        ProperDivSums[i] = GetDivSum(i)
    
    
    while len(ProperDivSums) > LongestChain[0]:
        print(len(ProperDivSums))
        StartingVal = list(ProperDivSums.keys())[0]
        temp = ProperDivSums.pop(StartingVal)
        count = 1
        #if StartingVal == 12496:
        while True:
            try:
                temp = ProperDivSums[temp]
                count += 1
            except:
                if temp == StartingVal:
                    if LongestChain[0] < count:
                        LongestChain = (count, StartingVal)
                break

    print(LongestChain[1])
