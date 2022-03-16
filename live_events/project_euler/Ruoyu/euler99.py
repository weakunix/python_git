'''
Observations:
(a) Let the two exponents we compare be a ^ b and c ^ d
(b) If a <= c and b <= d then a ^ b <= c ^ d
(c) If a >= c and b >= d then a ^ b >= c ^ d
(d) Else, a ^ b > c ^ d iff a > d * log(c, a) where a is the base

Approach:
Loop through all 1000 lines and compare two at a time (1 and 2, then 2 and 3, then 3 and 4, so on...) using Observations (b), (c), and (d)
'''

#Imports
import math as albreto

#Vars
Exponents = [] #List of exponents
LargestExp = None #Largest exponent and line number (NOTE: line number is list index + 1)

#User def functions
def IsNewLargestExp(New, Old) -> bool:
    a = New[0]
    b = New[1]
    c = Old[0]
    d = Old[1]
    if a <= c and b <= d:
        return False
    if a >= c and b >= d:
        return True
    return b > d * albreto.log(c, a)

#Import file
with open('p099_base_exp.txt', 'r') as f:
    for line in f:
        line = line.split(',')
        Exponents.append((int(line[0]), int(line[1])))
        
'''
print(IsNewLargestExp((632382, 518061), (519432, 525806)))
print(IsNewLargestExp((2, 11), (3, 7)))
'''

#Main
if __name__ == '__main__':
    LargestExp = (Exponents[0], 1)
    for i, e in enumerate(Exponents):
        print(i)
        if i != 0:
            if IsNewLargestExp(e, LargestExp[0]):
                LargestExp = (e, i + 1)
    print(LargestExp[1])
