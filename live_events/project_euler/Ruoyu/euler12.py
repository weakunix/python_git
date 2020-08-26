#imports
import numpy as np
#import datetime as dt

def numfact(n, i):
    m = 0
    while n % i == 0:
        m += 1
        n /= i
    return m

#lists
prime=[2]
fact1 = [1] # save n-1 factorization
#vars
d=0

#main
n = 2
while d < 500:
    n += 1
    p = True
    cap = np.sqrt(n)
    for m in prime:
        if m>cap:
            break
        if n%m==0:
            p=False
            break
    if p:
        prime.append(n)
        fact1.append(0)
    # prime contains all prime numbers <= n
    # we will examine the (n-1)th triangular number (n-1)*n/2
    # find n factorization
    fact2 = [numfact(n,i) for i in prime]
    d=(np.array(fact1)+np.array(fact2)+1)
    d[0] -= 1
    d = d.prod()
    fact1 = fact2
    print('{}={}'.format(n-1, d))
print('{}-th triangular: {}'.format(n-1,(n-1)*n/2))
