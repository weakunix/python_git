
#Imports
import math as albreto

#Vars
Total = 0 #Sum of perimeters of all equilateral triangles with integral side lengths and area
OneBil = 10 ** 9 #1 billion (const)
m = 1 #m
StillConsiderSecondCase = True #Is second case perimeter still in range (4m^2 <= 1 billion)

#Main
if __name__ == '__main__':
    while True:
        m += 1
        if StillConsiderSecondCase:
            p = 4 * m ** 2
            if p > OneBil:
                StillConsiderSecondCase = False
            elif m % 3 != 0:
                temp = (m ** 2 - 1) // 3
                if albreto.sqrt(temp) % 1 == 0:
                    Total += p

