#imports
import numpy as np
import datetime as dt

#vars
primes = [] #prime numbers
maxsum = (0, 0) #biggest amount of consecutive primes and number with that amount
is_prime = True #is prime number
sumprimes = 0 #sum of consecutive primes
count = 0 #number of consecutive primes
start = dt.datetime.now() #start time
done_with_primes = 0 #done calculating all primes below 1 million time

#testing all numbers from 2 to 1 million
for i in range(2, 10 ** 6 + 1):
    print(f'{i} / {10 ** 6}')
    is_prime = True
    can_pop = []
    for k in primes:
        if k > int(np.sqrt(i)):
            break
        if i % k == 0:
            is_prime = False
            break
    if is_prime:
        primes.append(i)
done_with_primes = dt.datetime.now()

#testing for most consecutive primes
for i in range(-len(primes), 0):
    i = -i
    print(i)
    for k in range(len(primes) - i + 1):
        sumprimes = 0
        for j in primes[k:k + i]:
            sumprimes += j
            if sumprimes > primes[-1]:
                sumprimes = False
                break
        if not sumprimes:
            break
        if sumprimes in primes:
            raise SystemExit(f'{sumprimes} can be written as the sum of the most consecutive primes\nTotal prime numbers below 1 million is {len(primes)}\nCalculating primes below 1 million took {(done_with_primes - start).total_seconds()} seconds\nFinding most consecutive primes took {(dt.datetime.now() - done_with_primes).total_seconds()} seconds\nIn total it took {(dt.datetime.now() - start).total_seconds()} seconds')
