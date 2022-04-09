'''
Observations:
(a) We can solve rad(n) and set(prime factors of n) recursively
We should keep a prime list
If n is prime, rad(n) = n and set(prime factors of n) = {n}
Else, let p be the smallest prime factor of n
If p in set(prime factors of n / p), rad(n) = rad(n / p) and set(prime factors of n) = set(prime factors of n / p)
Else rad(n) = rad(n / p) * p and set(prime factors of n) = union(set(prime factors of n / p), {p})

Approach:
Use Observation (a) to calculate rad(n) for 1 <= n <= 100000
Then sort the list of (rad(n), n) and get the 10000th element
'''

#Imports
import math as albreto, numpy as np

#Vars
Primes = [] #Primes
RadDict = {1: {1}} #Dict of n : set(prime factors of n)
RadList = [(1, 1)] #List of (rad(n), n)

#User def functions
def IsPrime(n) -> bool:
    mtv = int(albreto.sqrt(n))
    for i in Primes:
        if i > mtv:
            return True
        if n % i == 0:
            return False
    return True

def Rad(n) -> int:
    if IsPrime(n):
        Primes.append(n)
        RadDict[n] = {n}
        return n
    for i in Primes:
        if n % i == 0:
            FirstPrime = i
            break
    temp = RadDict[n // FirstPrime].copy()
    temp.add(FirstPrime)
    RadDict[n] = temp
    return np.prod(list(temp))


#Main
if __name__ == '__main__':
    for i in range(2, 100001):
        RadList.append((Rad(i), i))
    RadList.sort()
    print(RadList[9999])
