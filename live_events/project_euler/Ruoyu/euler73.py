'''
Observations:
(a) For every d for which 4 <= d <= 12000, int(d / 3) + 1 <= n <= ceiling(d / 2) - 1

Approach:
BFI using Observation (a)
'''

#Imports
import numpy as np

#Vars
Total = set()

#Main
if __name__ == '__main__':
    for d in range(4, 12001):
        print(d)
        for n in range(int(d / 3) + 1, int(np.ceil(d / 2))):
            Total.add(n / d)
    print(len(Total))
