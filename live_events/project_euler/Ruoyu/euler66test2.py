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
x = 1 #x
PerfectSquares = set(i ** 2 for i in range(1, 33)) #Set of perfect squares
DVals = {i for i in range(1, 1001) if i not in PerfectSquares} #Set of D values that will be removed one by one when a solution is found

#User def functions

#Main
if __name__ == '__main__':
    while len(DVals) > 1:
        print(len(DVals))
        x += 1
        temp = x ** 2 - 1
        to_remove = []
        for D in DVals:
            if temp % D == 0:
                if np.sqrt(temp // D).is_integer():
                    to_remove.append(D)
        for D in to_remove:
            DVals.remove(D)
    print(list(DVals)[0])
