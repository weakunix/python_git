#imports
import numpy as np

#vars
primes = [2, 3, 5, 7] #primes
digits = 1 #number of digits
test_primes = [] #primes we are testing
nums = [x for x in range(10)] #all 1 digit numbers
is_prime = True
family = False #which family is it in
orders = [] #possible family orders
counted = [] #families that have been recorded
import datetime as dt
start = dt.datetime.now()

##check if number is in family
def in_family(x, y):
    x = str(x)
    y = str(y)
    d = ''
    order = ''
    for i in range(len(x)):
        if x[i] != y[i]:
            if d == '':
                d = x[i]
            elif x[i] != d:
                return False
    d = ''
    for i in range(len(x)):
        if x[i] == y[i]:
            order += '0'
        elif d == '':
            d = y[i]
            order += '1'
        elif y[i] == d:
            order += '1'
        else:
            return False
    return int(('0b' + order), 2)

#testing every prime number to see if there are 8 in one family
while True:
    digits += 1
    test_primes = []
    #adding primes
    for i in range(10 ** (digits - 1), 10 ** digits):
        print(f'\033[0;36;1m{i}')
        is_prime = True
        for k in primes:
            if k > int(np.sqrt(i)):
                break
            if i % k == 0:
                is_prime = False
                break
        if is_prime:
            primes.append(i)
            test_primes.append(i)
    for i in test_primes:
        print(f'\033[0;33;1m{i}')
        orders = [1 for _ in range(2 ** digits)]
        for j in test_primes:
            if i != j: 
                family = in_family(i, j) 
                if family:
                    orders[family] += 1
            if 8 in orders:
                raise SystemExit(f'{i} is the smallest prime that is part of an 8 prime value family by replacing part of the number\n{(dt.datetime.now() - start).total_seconds()}')
