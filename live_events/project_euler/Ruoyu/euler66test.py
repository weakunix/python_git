'''
Observations:
x^2 - Dy^2 = (x - √D * y)(x + √D * y) = 1
Also, x^2 - 1 = Dy^2

Possibilities:
Try BFI through all D <= 1000 and find minimal solutions

Or

Instead of looping through D, we loop through x until there is only one D left between 1 to 100
For every x >= 2, we check every y^2 in the following range and find every (x^2 - 1) / y^2
If that is an integer, we remove that D from the list
Optimization: instead of checking every y^2, run some sort of prime factorization algorithm to figure out which y^2 will work
'''

#Imports
import numpy as np

#Vars
x = 0 #x - 1 actually since we are doing x * (x + 2) rather than x ^2 - 1
PerfectSquares = set(i ** 2 for i in range(1, 33)) #Set of perfect squares
DVals = {i for i in range(1, 1001) if i not in PerfectSquares} #Set of D values that will be removed one by one when a solution is found

#User def functions
def PrimeFactorize(n) -> dict:
    pf = {}
    for i in range(2, n + 1):
        Count = 0
        while n % i == 0:
            Count += 1
            n /= i
        if Count > 0:
            pf[i] = Count
    return pf

def PfAdd(a, b) -> dict:
    for p in a:
        try:
            b[p] += a[p]
        except:
            b[p] = a[p]
    return b

def PossibleSquares(pf) -> dict:
    SquareDict = {}
    for p in pf:
        if pf[p] >= 2:
            SquareDict[p] = []
            for i in range(0, pf[p] + 1, 2):
                SquareDict[p].append(i)
    return SquareDict

def PowerCombinations(PowerList, Selected) -> list:
    if len(PowerList) == 0:
        return [Selected]
    PossiblePowers = []
    for i in PowerList[0]:
        PossiblePowers += PowerCombinations(PowerList[1:], Selected + [i])
    return PossiblePowers

def PfSubtract(a, b) -> dict: #a - b
    for p in b:
        a[p] -= b[p]
    return a

#Main
if __name__ == '__main__':
    while len(DVals) > 1:
        print(len(DVals))
        x += 1
        PossibleSquareDict = PossibleSquares(PfAdd(PrimeFactorize(x), PrimeFactorize(x + 2)))
        PossibleYSquare = PowerCombinations([PossibleSquareDict[p] for p in PossibleSquareDict], [])
        for y in PossibleYSquare:
            temp = None
            for i, p in enumerate(PossibleSquareDict):
                try:
                    temp *= p ** y[i]
                except:
                    temp = p ** y[i]
            try:
                DVals.remove(x * (x + 2)// temp)
                #print(f'D = {x * (x + 2) // temp}, x^2 = {x * (x + 2)}, y^2 =  {temp}')
            except:
                pass

    print(f'D = {list(DVals)[0]}')
