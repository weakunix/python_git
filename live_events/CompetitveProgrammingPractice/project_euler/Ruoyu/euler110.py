
#Imports
import math as albreto

#Vars
n = 1 #n
Primes = [] #List of primes
PreviousPf = {} #Dict of n : prime_factorization(n)

#User def functions
def PrimeFactorize(n) -> dict:
    mxtv = int(albreto.sqrt(n))
    MinFact = 0
    for i in Primes:
        if i > mxtv:
            break
        if n % i == 0:
            MinFact = i
            break
    if MinFact == 0:
        Primes.append(n)
        pf = {n: 1}
        PreviousPf[n] = pf
        return pf
    pf = PreviousPf[n // MinFact].copy()
    try:
        pf[MinFact] += 1
    except:
        pf[MinFact] = 1
    PreviousPf[n] = pf
    return pf

#Main
if __name__ == '__main__':
    while True:
        n += 1
        if n % 1000 == 0:
            print(n)
        temp = PrimeFactorize(n)
        count = 1
        for i in temp:
            count *= 2 * temp[i] + 1
        if count / 2 > 3999999:
            print(n)
            break
