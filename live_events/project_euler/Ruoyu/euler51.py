#Imports
import numpy as np

#Vars
Primes = []
PossibleNums = []
CurrentPow = 0

#User def functions
def IsPrime(n):
    if n <= 1:
        return False
    MaxTest = int(np.sqrt(n))
    for k in Primes:
        if k > MaxTest:
            return True
        if n % k == 0:
            return False
    return True

def IsPossibleNum(n):
    strn = str(n)
    for i in range(10):
        pvlist = [] #place value list
        if strn.count(str(i)) % 2 == 0: #CHANGE TO 3
            for pv, digit in enumerate(strn):
                if digit == str(i):
                    pvlist.append(pv)
            pass

#Test
while True:
    CurrentPow += 1
    PossibleNums = []
    for i in range(10 ** (CurrentPow - 1), 10 ** CurrentPow + 1):
        if IsPrime(i):
            Primes.append(i)
            print(i)
