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
x = 1 #x
XStorage = [] #Factored x = p * q^2 form storage up until x - 2
DVals = set(i for i in range(1, 1001) if not albreto.sqrt(i).is_integer())

#User def functions
def GetXForm(x) -> list:
    count = 1
    while True:
        count += 1
        temp = albreto.sqrt(x / count)
        if temp.is_integer():
            return [count, int(temp)]

#Main
if __name__ == '__main__':
    while True:
        x += 1
