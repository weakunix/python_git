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
        if strn.count(str(i)) > 0 and strn.count(str(i)) % 3 == 0:
            for pv, digit in enumerate(strn):
                if digit == str(i):
                    pvlist.append(pv)
            #import pdb;pdb.set_trace()
            for a in range(len(pvlist) - 2): 
                for b in range(a + 1, len(pvlist) - 1): 
                    for c in range(b + 1, len(pvlist)): 
                        Tempa = pvlist[a]
                        Tempb = pvlist[b]
                        Tempc = pvlist[c]
                        PossibleNums.append(strn[:Tempa] + strn[Tempa + 1:Tempb] + strn[Tempb + 1:Tempc] + strn[Tempc + 1:] + ',' + str(Tempa) + str(Tempb) + str(Tempc))


#Test
if __name__ == '__main__':
    while True:
        CurrentPow += 1
        PossibleNums = []
        for i in range(10 ** (CurrentPow - 1), 10 ** CurrentPow + 1):
            if IsPrime(i):
                Primes.append(i)
                IsPossibleNum(i)
                print(i)
        #import pdb;pdb.set_trace()
        for i in set(PossibleNums):
            if PossibleNums.count(i) >= 8:
                print(i)
                raise SystemExit()
