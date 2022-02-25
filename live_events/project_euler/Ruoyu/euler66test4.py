'''
Observations:
x^2 - 1 = Dy^2
(x + 1)(x - 1) = Dy^2

Shift x by -1
(x - 2)x = Dy^2
Result is the same

Possibilities:
Try BFI through all D <= 1000 and find minimal solutions

Or

Instead of looping through D, we loop through x until there is only one D left between 1 to 100
For every x >= 2, we check every y^2 in the following range and find every (x^2 - 1) / y^2
If that is an integer, we remove that D from the list
Optimization: instead of checking every y^2, run some sort of prime factorization algorithm to figure out which y^2 will work

Or

Use the observation above that states (x - 2)x = Dy^2
Loop through x and store values up until x - 2 (on each iteration we can pop x - 3 value)

x = p * q^2 where p is not square
x - 2 = r * s^2 (which has already been stored)

(x - 2)x = p * r * (q * s)^2
'''

#Imports
import math as albreto

#Vars
DForMaxX = (None, None) #D for largest x in the form of (x, D)

#User def functions
def Gcd(a, b) -> int:
    while True:
        if b % a == 0:
            return a
        a %= b
        if a % b == 0:
            return b
        b %= a

def GetMutuallyPrimePairs(D) -> set:
    Pairs = set()
    for i in range(1, int(albreto.sqrt(D)) + 1):
        if D % i == 0:
            if Gcd(i, D / i) <= 2:
                Pairs.add((i, D // i))
    return Pairs

#Main
if __name__ == '__main__':
    for D in range(1, 8):
        if not albreto.sqrt(D).is_integer():
            print(D)
            MinX = None
            MutuallyPrimePairs = GetMutuallyPrimePairs(D)
            for Pair in MutuallyPrimePairs:
                a = Pair[0]
                b = Pair[1]
                count = 0
            try:
                if MinX > DForMaxX[0]:
                    DForMaxX = (MinX, D)
            except:
                DForMaxX = (MinX, D)

    print(DForMaxX[1])
