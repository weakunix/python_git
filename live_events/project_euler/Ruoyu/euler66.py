'''
Observations:
We can factorize x^2 - Dy^2 = (x - √D * y)(x + √D * y) = 1

Possibilities:
Try BFI through all D <= 1000 and find minimal solutions
'''

#Imports
import numpy as np

#Vars
LargestX = 0 #Largest x
DVal = 0 #Corresponding D value for largest x
PerfectSquares = set(i ** 2 for i in range(1, 33)) #Set of perfect squares
NotSquares = set() #Set of non perfect squares

#User def functions
def IsPerfectSquare(n) -> bool:
    if n in PerfectSquares:
        return True
    if n in NotSquares:
        return False
    if int(np.sqrt(n)) == np.sqrt(n):
        PerfectSquares.add(n)
        return True
    NotSquares.add(n)
    return False

def GetMinX(D) -> int:
    x = 1
    while True:
        x += 1
        temp = x ** 2 - 1
        if temp % D == 0:
            temp //= D
            if IsPerfectSquare(temp):
                return x

#Main
if __name__ == '__main__':
    for D in range(2, 1001):
        print(D)
        if D not in PerfectSquares:
            NotSquares.add(D)
            temp = GetMinX(D)
            if temp > LargestX:
                LargestX = temp
                DVal = D
    print(LargestX, DVal)
