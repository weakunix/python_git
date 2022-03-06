'''
Observations:
(a) Let f(n) return a dictionary of the number of sums using k and prime numbers >= k for 2 <= k <= n
For example, f(10) would be {2: 3, 3: 1, 5: 1, 7: 0}
Using prime numbers >= 2, there are 3 combinations: (2, 2, 2, 2, 2), (2, 2, 3, 3), (2, 3, 5) 
Using prime numbers >= 3, there is 1 combination: (3, 7) since we cannot use 2
Using prime numbers >= 5, there is 1 combination: (5, 5) since we cannot use 2 or 3
Using prime numbers >= 7, there are 0 combinations since we cannot use 2,  or 5
(b) We define f(n) in such a way because it allows us to find f(n) using f(n - k)
(c) f(0) returns 1 no matter what since this is only the case when we try to write n as the sum of 1 prime number and we will only consider f(0) when n is prime
(d) f(1) = {}, f(2) = {2: 1}
(e) To get f(n), we will loop through primes k where 2 <= k <= n and take the sum of f(n - k)'s elements with keys >= k to avoid multiple counting
(f) Observation (e) guarentees that the order of numbers will be increasing, thus each sum is only counted once

Approach:
Store all previous f(n) (defined in Observation (a)) and loop through all n until an n that has a total of more than 5000 prime sums is found 
Use Observation (e) to get each succeeding f(n)
'''

#Imports
import math as albreto

#Vars
SumDict = {1: {}, 2: {2: 1}} #Dict of previous f(n)
Primes = [2] #List of primes
Total = 0 #Total prime sums of n
n = 2 #n

#User def functions
def IsPrime(n) -> bool:
    mtv = int(albreto.sqrt(n))
    for p in Primes:
        if p > mtv:
            Primes.append(n)
            return True
        if n % p == 0:
            return False

#Main
if __name__ == '__main__':
    while Total <= 5000:
        n += 1
        New = {}
        ip = IsPrime(n)
        for i in Primes:
            count = 0
            try:
                temp = SumDict[n - i]
                for k in temp:
                    if i <= k:
                        count += temp[k]
            except:
                count = 1
            New[i] = count
        SumDict[n] = New
        Total = 0
        for i in New:
            Total += New[i]
        if ip:
            Total -= 1
    print(n, Total)
