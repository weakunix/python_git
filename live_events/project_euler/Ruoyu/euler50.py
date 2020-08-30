#vars
primes = [] #prime numbers
possible = []
maxsum = (0, 0) #biggest amount of consecutive primes and number with that amount
is_prime = True #is prime number
sumprimes = 0 #sum of consecutive primes
count = 0 #how many consecutive primes

#testing all numbers from 2 to 1 million
for i in range(2, 10 ** 2 + 1):
    print(f'{i}')
    #check if prime
    is_prime = True
    for k in primes:
        if i % k == 0:
            is_prime = False
            break
    if is_prime:
        primes.append(i)
        for k in range(len(possible)):
            if possible[k][1] in primes:
                if possible[k][0] > maxsum[0]:
                    maxsum = possible[k]
                    break
            elif possible[k][1] > i:
                break
        sumprimes = []
        for k in possible:
            sumprimes.append((k[0] + 1, k[1] + i))
        for k in sumprimes:
            possible.append(k)
        if possible == []:
            possible.append((1, i))
                
print(f'{maxsum[1]} can be written as the sum of {maxsum[0]} consecutive primes')             
