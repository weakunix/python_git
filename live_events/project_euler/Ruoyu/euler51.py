#Imports
import numpy as np

#Vars
Primes = []
ValueCount = {}
CurrentPow = 0

#User def functions
def IsPrime(n) -> bool:
    if n <= 1:
        return False
    MaxTest = int(np.sqrt(n))
    for k in Primes:
        if k > MaxTest:
            return True
        if n % k == 0:
            return False
    return True

def ListCombinations(l, ChooseNum) -> list:
    if ChooseNum == 0:
        return [[]]
    if ChooseNum == len(l):
        return [l]
    x = ListCombinations(l[1:], ChooseNum - 1)
    for i in range(len(x)):
        x[i] = [l[0]] + x[i]
    y = ListCombinations(l[1:], ChooseNum)
    return x + y

def IsPossibleNum(n) -> None:
    global ValueCount
    strn = str(n)
    listn = [i for i in strn]
    DigitCount = [[] for _ in range(10)]
    for i, k in enumerate(strn):
        k = int(k)
        DigitCount[k].append(i)
    for i, k in enumerate(DigitCount):
        if len(k) >= 3:
            Combinations = ListCombinations(k, 3)
            for c in Combinations:
                temp = listn.copy()
                tempstr = ''
                for d in c:
                    temp[d] = 'x'
                for d in temp:
                    tempstr += d
                if ValueCount.get(tempstr) == None:
                    ValueCount[tempstr] = 1
                else:
                    ValueCount[tempstr] += 1

#Test
if __name__ == '__main__':
    while True:
        CurrentPow += 1
        ValueCount = {}
        for i in range(10 ** (CurrentPow - 1), 10 ** CurrentPow + 1):
            if IsPrime(i):
                Primes.append(i)
                IsPossibleNum(i)
                if i % 1000 == 0:
                    print(i)
        for i in ValueCount:
            if ValueCount[i] >= 8:
                print(i, ValueCount[i])
                raise SystemExit()
