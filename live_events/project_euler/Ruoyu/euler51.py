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
        if strn.count(str(i)) > 0: #and strn.count(str(i)) % 3 == 0:
            for pv, digit in enumerate(strn):
                if digit == str(i):
                    pvlist.append(pv)
            #import pdb;pdb.set_trace()
            for a in range(len(pvlist) - 1): #CHANGE TO 2
                for b in range(a + 1, len(pvlist)): #CHANGE TO 1 AND ADD EXTRA LOOP
                    Tempa = pvlist[a]
                    Tempb = pvlist[b]
                    PossibleNums.append(strn[:Tempa] + strn[Tempa + 1:Tempb] + strn[Tempb + 1:] + ',' + str(Tempa) + str(Tempb))


#Test
if __name__ == '__main__':
    while True:
        CurrentPow += 1
        PossibleNums = []
        for i in range(10 ** (CurrentPow - 1), 10 ** CurrentPow + 1):
            if IsPrime(i):
                Primes.append(i)
                print(i)
        for i in PossibleNums:
            if PossibleNums.count(i) >= 7:
                print(i)
                break
