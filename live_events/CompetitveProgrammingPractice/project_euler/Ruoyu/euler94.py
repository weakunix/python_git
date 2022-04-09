
#Imports
import math as albreto

#Vars
Total = 0 #Sum of perimeters of all equilateral triangles with integral side lengths and area
OneBil = 10 ** 9 #1 billion (const)

#Main
if __name__ == '__main__':
    for i in range(2, 333333334):
        if i % 10000 == 0:
            print(i)
        if albreto.sqrt((3 * i + 1) * (i - 1)) % 1 == 0:
            print('FOUND ONE GET TROLLED BRRRRRRRR')
            Total += 3 * i + 1
        if albreto.sqrt((3 * i - 1) * (i + 1)) % 1 == 0:
            print('FOUND ONE GET TROLLED BRRRRRRRR')
            Total += 3 * i - 1
    print(Total)
