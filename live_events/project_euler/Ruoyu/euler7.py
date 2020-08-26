import numpy as np
trynum = 2
primecount = 0

def isprime(x):
    prime = 1
    global primecount
    for i in range(2, int(np.sqrt(x)) + 1): #sqrt of num
        if x % i == 0:
            prime = 0
            break
    if prime == 1:
        primecount += 1
        return True
    else:
        return False

if __name__ == '__main__':
    while primecount < 10001:
        if isprime(trynum):
            print("{}th prime is {}".format(primecount,trynum))
        trynum += 1
    print(trynum-1)
