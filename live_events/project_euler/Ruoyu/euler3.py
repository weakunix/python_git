import numpy as np

N = 600851475143
p = None
while N > 1:
    sn = int(np.sqrt(N))
    isprime = True
    for i in range(2 if p is None else p, sn+1):
        if N % i == 0:
            isprime = False
            break
    if isprime:
        if p is None:
            print(N)
        elif N > p:
            print(N)
        else:
            print(p)
        break
    else:
        # i must be the smallest prime factor of N
        p = i
        N = N/i
