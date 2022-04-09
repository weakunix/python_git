'''
Observations:
(a) 1/x + 1/y = 1/n -> (x + y)/xy = 1/n -> nx + ny = xy -> xy - nx - ny = 0 -> xy - nx - ny + n^2 = n ^ 2 -> (x - n)(y - n) = n^2
This question has been reformatted to "Find the first n such that the number of divisors of n^2 >= 1000"
(b) We can find the prime factorization of n in the following way
If n is prime, it is very simply n
However, if it isn't, a smaller prime must divide n
We get the prime factorization of n / p where p is the smallest prime that divides n and multiply p to that prime factorization
This requires storing a dictionary of previous pf(n)
(c) To get the num_of_div(n^2) we can get pf(n) and for every prime's power, x, multiply 2x + 1 to the final number of divisors

Approach:
Answer Observation (a)'s reformatted question which can be done by incrementing n until num_of_div(n^2) is found, using Observations (b) and (c) to find num_of_div(n^2)
'''

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
        if count / 2 > 999:
            print(n)
            break
